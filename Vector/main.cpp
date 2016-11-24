using u32 = unsigned long;

template <u32 dimension, typename ValueType>
class Vector
{
private:
	ValueType* value;

	template <typename>
	using toValueType = ValueType;

	static constexpr unsigned long SizeByIndex(unsigned long index)
	{
		// te lui om te maken
		return 3;
	}
public:
	template <typename>
	using toU32 = unsigned int;

	template<typename... Args>
	Vector(Args... sizes)
	{
		//value = new ValueType[... * sizes];
	}

	~Vector()
	{
		delete[] value;
	}

	template<typename... Args>
	void At(toU32<Args>... sizes)// -> std::enable_if_t<(sizeof...(sizes) == dimension)>
	{
		// te lui maar kan gewoon
	}
};

int main()
{
	u32 i = 10;
	Vector<3, u32> myvec(i, i, i);

	myvec.At(1, 2, 3);

	return 0;
}