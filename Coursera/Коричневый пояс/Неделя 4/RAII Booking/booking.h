namespace RAII
{
// class FlightProvider;
// class HotelProvider;

template <typename Provider>
class Booking
{
public:
    Booking(Provider* provider, int cnt) : provider_(provider)
    {
    }
    ~Booking()
    {
        if (provider_)
        {
            provider_->CancelOrComplete(*this);
        }
    }

    Booking(const Booking&) = delete;
    Booking(Booking&& other) : provider_(other.provider_)
    {
        other.provider_ = nullptr;
    }

    Booking& operator=(const Booking&) = delete;
    Booking& operator=(Booking&& other)
    {
        this->provider_ = other.provider_;
        other.provider_ = nullptr;
        return *this;
    }

private:
    Provider* provider_ = nullptr;
};
}