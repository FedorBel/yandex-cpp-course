#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Email
{
	string from;
	string to;
	string body;
};

class Worker
{
public:
	virtual ~Worker() = default;
	virtual void Process(unique_ptr<Email> email) = 0;
	virtual void Run()
	{
		// только первому worker-у в пайплайне нужно это имплементировать
		throw logic_error("Unimplemented");
	}

protected:
	// реализации должны вызывать PassOn, чтобы передать объект дальше
	// по цепочке обработчиков
	void PassOn(unique_ptr<Email> email) const
	{
		if (next_worker)
			next_worker->Process(move(email));
	}

	// указатель на следующий обработчик
	unique_ptr<Worker> next_worker;

public:
	void SetNext(unique_ptr<Worker> next)
	{
		next_worker = move(next);
	}
};

class Reader : public Worker
{
public:
	explicit Reader(istream &in) : input_(in) {}

	void Process(unique_ptr<Email> email) override
	{
	}

	void Run() override
	{
		vector<unique_ptr<Email>> emails;
		unique_ptr<Email> email_ptr;
		while (input_.peek() != EOF)
		{
			email_ptr = make_unique<Email>();
			if (getline(input_, email_ptr->from) &&
				getline(input_, email_ptr->to) &&
				getline(input_, email_ptr->body))
			{
				PassOn(move(email_ptr));
			}
		}
	}

private:
	istream &input_;
};

class Filter : public Worker
{
public:
	using Function = function<bool(const Email &)>;

public:
	explicit Filter(Function comp) : comp_(move(comp)) {}

	void Process(unique_ptr<Email> email) override
	{
		if (comp_(*email))
		{
			PassOn(move(email));
		}
	}

private:
	Function comp_;
};

class Copier : public Worker
{
public:
	explicit Copier(string copy_to) : copy_to_(move(copy_to)) {}

	void Process(unique_ptr<Email> email) override
	{
		if (copy_to_ != email->to)
		{
			unique_ptr<Email> copy = make_unique<Email>();
			CopyEmail(*email, *copy);
			PassOn(move(email));
			PassOn(move(copy));
		}
		else
		{
			PassOn(move(email));
		}
	}

private:
	string copy_to_;

	void CopyEmail(const Email &source, Email &target)
	{
		target.to = copy_to_;
		target.from = source.from;
		target.body = source.body;
	}
};

class Sender : public Worker
{
public:
	Sender(ostream &out) : output_(out) {}

	void Process(unique_ptr<Email> email) override
	{
		WriteEmail(*email);
		PassOn(move(email));
	}

private:
	ostream &output_;

	void WriteEmail(const Email &email)
	{
		output_ << email.from << "\n";
		output_ << email.to << "\n";
		output_ << email.body << "\n";
	}
};

// реализуйте класс
class PipelineBuilder
{
public:
	// добавляет в качестве первого обработчика Reader
	explicit PipelineBuilder(istream &in)
	{
		handler_ = make_unique<Reader>(in);
		last_handler_ = handler_.get();
	}

	// добавляет новый обработчик Filter
	PipelineBuilder &FilterBy(Filter::Function filter)
	{
		UpdatePipeline(make_unique<Filter>(filter));
		return *this;
	}

	// добавляет новый обработчик Copier
	PipelineBuilder &CopyTo(string recipient)
	{
		UpdatePipeline(make_unique<Copier>(recipient));
		return *this;
	}

	// добавляет новый обработчик Sender
	PipelineBuilder &Send(ostream &out)
	{
		UpdatePipeline(make_unique<Sender>(out));
		return *this;
	}

	// возвращает готовую цепочку обработчиков
	unique_ptr<Worker> Build()
	{
		return move(handler_);
	}

private:
	unique_ptr<Worker> handler_;
	Worker *last_handler_;

	void UpdatePipeline(unique_ptr<Worker> next_handler)
	{
		Worker *next_handler_ptr = next_handler.get();
		last_handler_->SetNext(move(next_handler));
		last_handler_ = next_handler_ptr;
	}
};

void TestSanity()
{
	string input = ("erich@example.com\n"
					"richard@example.com\n"
					"Hello there\n"

					"erich@example.com\n"
					"ralph@example.com\n"
					"Are you sure you pressed the right button?\n"

					"ralph@example.com\n"
					"erich@example.com\n"
					"I do not make mistakes of that kind\n");
	istringstream inStream(input);
	ostringstream outStream;

	PipelineBuilder builder(inStream);
	builder.FilterBy([](const Email &email) {
		return email.from == "erich@example.com";
	});
	builder.CopyTo("richard@example.com");
	builder.Send(outStream);
	auto pipeline = builder.Build();

	pipeline->Run();

	string expectedOutput = ("erich@example.com\n"
							 "richard@example.com\n"
							 "Hello there\n"

							 "erich@example.com\n"
							 "ralph@example.com\n"
							 "Are you sure you pressed the right button?\n"

							 "erich@example.com\n"
							 "richard@example.com\n"
							 "Are you sure you pressed the right button?\n");
	ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestSanity);
	return 0;
}
