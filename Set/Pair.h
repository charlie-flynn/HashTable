#pragma once

template<typename T1, typename T2>
struct Pair
{
public:
	T1 key;
	T2 value;

	Pair<T1, T2>();
	Pair<T1, T2>(T1 key, T2 value);
	~Pair<T1, T2>() = default;
};

template<typename T1, typename T2>
inline Pair<T1, T2>::Pair() : key(T1()), value(T2())
{
}

template<typename T1, typename T2>
inline Pair<T1, T2>::Pair(T1 key, T2 value) : key(key), value(value)
{
}
