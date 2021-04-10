#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

class Shape : public IShape
{
public:
	void SetPosition(Point pos) override
	{
		this->position_ = pos;
	}

	Point GetPosition() const override
	{
		return position_;
	}

	void SetSize(Size size) override
	{
		this->size_ = size;
	}

	Size GetSize() const override
	{
		return size_;
	}

	void SetTexture(shared_ptr<ITexture> texture_ptr) override
	{
		this->texture_ptr_ = move(texture_ptr);
	}

	ITexture* GetTexture() const override
	{
		return texture_ptr_.get();
	}

	// Рисует фигуру на указанном изображении
	void Draw(Image& image) const override
	{
		int global_x = this->position_.x;
		int global_y = this->position_.y;

		auto image_width = static_cast<int>(image.empty() ? 0 : image[0].size());
		auto image_height = static_cast<int>(image.size());

		if (global_x < 0 || global_x > image_width ||
			global_y < 0 || global_y > image_height)
		{
			return;
		}

		int texture_width = 0;
		int texture_height = 0;
		if (texture_ptr_)
		{
			const auto& texture = texture_ptr_->GetImage();
			auto [texture_width_tmp, texture_height_tmp] = texture_ptr_->GetSize();
			texture_width = texture_width_tmp;
			texture_height = texture_height_tmp;
			for (int y = 0; y < texture_height && y < this->size_.height && (y + global_y) < image_height; y++)
			{
				for (int x = 0; x < texture_width && x < this->size_.width && (x + global_x) < image_width; x++)
				{
					if (IsPointInShape({ x, y }))
					{
						image[y + global_y][x + global_x] = texture[y][x];
					}
				}
			}
		}

		const char default_texture = '.';
		for (int y = 0; y < this->size_.height && (y + global_y) < image_height; y++)
		{
			for (int x = 0; x < this->size_.width && (x + global_x) < image_width; x++)
			{
				if (y < texture_height && x < texture_width)
				{
					continue;
				}
				if (IsPointInShape({ x, y }))
				{
					image[y + global_y][x + global_x] = default_texture;
				}
			}
		}
	}

private:
	Point position_;
	Size size_;
	shared_ptr<ITexture> texture_ptr_;

	virtual bool IsPointInShape(Point p) const = 0;
};

class Ellipse : public Shape
{
public:
	// Возвращает точную копию фигуры.
	// Если фигура содержит текстуру, то созданная копия содержит ту же самую
	// текстуру. Фигура и её копия совместно владеют этой текстурой.
	unique_ptr<IShape> Clone() const override
	{
		return make_unique<Ellipse>(*this);
	}

private:
	bool IsPointInShape(Point p) const override
	{
		return IsPointInEllipse(p, this->GetSize());
	}
};

class Rectangle : public Shape
{
public:
	// Возвращает точную копию фигуры.
	// Если фигура содержит текстуру, то созданная копия содержит ту же самую
	// текстуру. Фигура и её копия совместно владеют этой текстурой.
	unique_ptr<IShape> Clone() const override
	{
		return make_unique<Rectangle>(*this);
	}

private:
	bool IsPointInShape(Point p) const override
	{
		return true;
	}
};

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
	switch (shape_type)
	{
	case ShapeType::Rectangle:
		return make_unique<Rectangle>();
		break;
	case ShapeType::Ellipse:
		return make_unique<Ellipse>();
		break;
	default:
		return nullptr;
		break;
	}
}