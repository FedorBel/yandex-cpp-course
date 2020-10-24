#include <algorithm>

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
	SimpleVector()
	{
		data = new T[0];		
		this->capacity = 0;
		this->size = 0;
	}

  explicit SimpleVector(size_t size)
  {
	  data = new T[size];
	  this->capacity = size;
	  this->size = size;
  }
  ~SimpleVector()
  {
	  delete[] data;
  }

  /*

  // Not good
  void operator=(const SimpleVector& other)
  {
	  delete[] data;
	  data = new T[other.capacity];
	  end_ = data + size;
	  capacity = other.capacity;
	  size = other.size;
	  std::copy(other.begin(), other.end(), begin());
  }
  */

  SimpleVector(const SimpleVector& other)
	  : data(new T[other.capacity]),
	  size(other.size),
	  capacity(other.capacity)
  {
	  std::copy(other.begin(), other.end(), begin());
  }

  // Better
  void operator=(const SimpleVector& rhs) {
	  if (rhs.size <= capacity) {
		  // У нас достаточно памяти - просто копируем элементы
		  std::copy(rhs.begin(), rhs.end(), begin());
		  size = rhs.size;
	  }
	  else {
		  // Это так называемая идиома copy-and-swap.
		  // Мы создаём временный вектор с помощью
		  // конструктора копирования, а затем обмениваем его поля со своими.
		  // Так мы достигаем двух целей:
		  //  - избегаем дублирования кода в конструкторе копирования
		  //    и операторе присваивания
		  //  - обеспечиваем согласованное поведение конструктора копирования
		  //    и оператора присваивания
		  SimpleVector<T> tmp(rhs);
		  std::swap(tmp.data, data);
		  std::swap(tmp.size, size);
		  std::swap(tmp.capacity, capacity);
	  }
  }

  T& operator[](size_t index)
  {
	  return data[index];
  }

  T* begin() { return data; }
  T* end() { return data + size; }

  const T* begin() const { return data; }
  const T* end() const { return data + size; }

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

		  capacity = 1;
		  size = 1;

		  data[0] = value;
		  
	  }
	  else if (size < capacity)
	  {
		  data[size] = value;
		  size++;
	  }
	  else
	  {
		  T* new_vector = new T[capacity * 2];
		  capacity *= 2;
		  std::copy(begin(), end(), new_vector);
		  delete[] data;
		  data = new_vector;
		  
		  data[size] = value;
		  size++;
	  }
	  
  }

private:
	T* data;
	size_t capacity;
	size_t size;
};
