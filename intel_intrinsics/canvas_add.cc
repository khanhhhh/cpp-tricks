/* This code use Intel Intrinsics to vectorize operation which is usually done by compiler
 * */


#include<cstdint>
inline void canvas_add(uint8_t *canvas, uint8_t *addon, int count)
{
	__m128i * cp = (__m128i *)canvas;
	const __m128i * ap = (__m128i *)addon;

	for (int i = 0; i < count; i += 16)
	{
		__m128i vc = _mm_loadu_si128(cp);
		__m128i va = _mm_loadu_si128(ap);
		vc = _mm_add_epi8(vc, va);
		_mm_storeu_si128(cp, vc);

		cp++;
		ap++;
	}
}
inline void canvas_add(uint16_t *canvas, uint16_t *addon, int count)
{
	__m128i * cp = (__m128i *)canvas;
	const __m128i * ap = (__m128i *)addon;

	for (int i = 0; i < count; i += 8)
	{
		__m128i vc = _mm_loadu_si128(cp);
		__m128i va = _mm_loadu_si128(ap);
		vc = _mm_add_epi16(vc, va);
		_mm_storeu_si128(cp, vc);

		cp++;
		ap++;
	}
}
inline void canvas_add(uint32_t *canvas, uint32_t *addon, int count)
{
	__m128i * cp = (__m128i *)canvas;
	const __m128i * ap = (__m128i *)addon;

	for (int i = 0; i < count; i += 4)
	{
		__m128i vc = _mm_loadu_si128(cp);
		__m128i va = _mm_loadu_si128(ap);
		vc = _mm_add_epi32(vc, va);
		_mm_storeu_si128(cp, vc);

		cp++;
		ap++;
	}
}
inline void canvas_add(uint64_t *canvas, uint64_t *addon, int count)
{
	__m128i * cp = (__m128i *)canvas;
	const __m128i * ap = (__m128i *)addon;

	for (int i = 0; i < count; i += 2)
	{
		__m128i vc = _mm_loadu_si128(cp);
		__m128i va = _mm_loadu_si128(ap);
		vc = _mm_add_epi64(vc, va);
		_mm_storeu_si128(cp, vc);

		cp++;
		ap++;
	}
}

#include<cstdio>
void print(uint16_t *arr, uint16_t count)
{
	for (int i=0; i<count; i++)
		std::printf("%d ",arr[i]);
	std::printf("\n");
}
uint16_t *ones(int count)
{
	auto arr = new uint16_t[count];
	for (int i=0; i<count; i++)
		arr[i] = 1;
	return arr;
}
int main()
{
	auto a = ones(1000);
	auto b = ones(1000);
	print(a, 1000);
		canvas_add(a, b, 1000);
	print(a, 1000);
	return 0;
}
