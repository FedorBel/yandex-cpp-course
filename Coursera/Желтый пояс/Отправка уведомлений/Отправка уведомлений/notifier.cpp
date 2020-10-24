class INotifier
{
public:
	virtual void Notify(const string& message) = 0;
};

class SmsNotifier : public INotifier
{
public:
	SmsNotifier(const string& number)
	{
		this->number = number;
	}

	void Notify(const string& message) override
	{
		SendSms(number, message);
	}

private:
	string number;
};

class EmailNotifier : public INotifier
{
public:
	EmailNotifier(const string& email)
	{
		this->email = email;
	}

	void Notify(const string& message) override
	{
		SendEmail(email, message);
	}

private:
	string email;
};