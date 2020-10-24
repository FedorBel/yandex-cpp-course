#include <algorithm>

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
	SimpleVector()
	{
		data = new T[0];
		end_ = data;
		this->capacity = 0;
		this->size = 0;
	}

  explicit SimpleVector(size_t size)
  {
	  data = new T[size];
	  end_ = data + size;
	  this->capacity = size;
	  this->size = size;
  }
  ~SimpleVector()
  {
	  delete[] data;
  }

  T& operator[](size_t index)
  {
	  return data[index];
  }

  T* begin() { return data; }
  T* end() { return end_; }

  const T* begin() const { return data; }
  const T* end() const { return end_; }

  size_t Size() const
  {
	  return size;
  }
  size_t Capacity() const
  {
	  return capacity;
  }
  void PushBack(const T& value)
  {
	  if (capacity == 0)
	  {
		  T* new_vector = new T[1];
		  delete[] data;

		  data = new_vector;
		  end_ = data + 1;

		  capacity = 1;
		  size = 1;

		  data[0] = value;
		  
	  }
	  else if (size < capacity)
	  {
		  data[size] = value;
		  size++;
		  end_++;
	  }
	  else
	  {
		  T* new_vector = new T[capacity * 2];
		  capacity *= 2;
		  std::copy(data, end_, new_vector);
		  delete[] data;
		  data = new_vector;
		  
		  data[size] = value;
		  size++;
		  end_ = data + size;
	  }
	  
  }

private:
	T* data;
	T* end_;
	size_t capacity;
	size_t size;
};
