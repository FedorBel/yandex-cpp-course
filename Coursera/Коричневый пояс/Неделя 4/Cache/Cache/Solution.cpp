#include "Common.h"
#include <list>
#include <unordered_map>
#include <atomic>
#include <mutex>

using namespace std;

class LruCache : public ICache
{
public:
	LruCache(
		shared_ptr<IBooksUnpacker> books_unpacker,
		const Settings& settings
	) : books_unpacker_(move(books_unpacker)),
		max_memory_(settings.max_memory)
	{
	}

	using NamePtr = std::shared_ptr<const string>;

	BookPtr GetBook(const string& book_name) override
	{
		lock_guard g(m);
		auto it = books_map_.find(book_name);
		BookPtr book_ptr = nullptr;
		if (it != books_map_.end())
		{
			book_ptr = it->second->second->GetBook();
			books_list_.splice(books_list_.begin(), books_list_,it->second);
		}
		else
		{
			book_ptr = books_unpacker_->UnpackBook(book_name);
			books_list_.push_front(make_pair(book_name, make_unique<BookInfo>(book_ptr, this->memory_used_by_books_)));
			books_map_[book_name] = books_list_.begin();
		}
	
		Shrink();
		return book_ptr;
	}

private:
	shared_ptr<IBooksUnpacker> books_unpacker_;
	const atomic<size_t> max_memory_;

private:
	atomic<size_t> memory_used_by_books_ = 0;

	// class to control memory used by books
	class BookInfo
	{
	public:
		explicit BookInfo(BookPtr book_ptr, atomic<size_t>& memory_used_by_books) :
			book_ptr_(move(book_ptr)),
			memory_used_by_books_(memory_used_by_books)
		{
			memory_used_by_books_ += book_ptr_->GetContent().size();
		}

		~BookInfo()
		{
			memory_used_by_books_ -= book_ptr_->GetContent().size();
		}

		BookPtr GetBook()
		{
			return book_ptr_;
		}
	private:
		atomic<size_t>& memory_used_by_books_;
		BookPtr book_ptr_;
	};

private:
	// containers for LRU
	list<pair<string, unique_ptr<BookInfo>>> books_list_;
	unordered_map<string, decltype(books_list_.begin())> books_map_;

private:
	mutex m;

	void Shrink()
	{
		while (memory_used_by_books_ > max_memory_)
		{
			auto it = prev(books_list_.end());
			books_map_.erase(it->first);
			books_list_.erase(it);
		}
	}
};


unique_ptr<ICache> MakeCache(
	shared_ptr<IBooksUnpacker> books_unpacker,
	const ICache::Settings& settings
)
{
	return make_unique<LruCache>(books_unpacker, settings);
}
