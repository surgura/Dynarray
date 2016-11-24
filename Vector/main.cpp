/// This Source Code Form is subject to the terms of the Mozilla Public
/// License, v. 2.0. If a copy of the MPL was not distributed with this
/// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

using u32 = unsigned long;

template <u32 dimension, typename ValueType>
class Vector
{
private:
	ValueType* value;

	template <typename To, typename>
	using to = To;

	static constexpr unsigned long SizeByIndex(unsigned long index)
	{
		// te lui om te maken
		return 3;
	}



	template <u32 N, typename... T>
	class u : public u<N-1, u32, T...>
	{
	public:
		using type = T;
	};

	template <typename... T>
	class u<0, T...>
	{
	};
	/*
	template <u32 N, typename... Types>
	class x : x<N-1, u32, Types...>
	{

	};*/
public:
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
	void At(to<u32, Args>... sizes)// -> std::enable_if_t<(sizeof...(sizes) == dimension)>
	{
		// te lui maar kan gewoon
	}
};

int main()
{
	u32 i = 10;
	Vector<3, u32> myvec(i, i, i);

	myvec.At<std::string, std::string, std::string>(1, 2, 3);

	return 0;
}