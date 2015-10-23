#include <assert.h>
#include <atomic>
#include <iostream>
#include <stdlib.h>
#include <thread>

using namespace std;

//std::atomic<bool> x, y;
//std::atomic<int> z;
//
//void write_x_then_y()
//{
//	x.store(true, std::memory_order_relaxed);
//	y.store(true, std::memory_order_relaxed);
//}
//
//void read_y_then_x()
//{
//	while (!y.load(std::memory_order_relaxed));
//	if (x.load(std::memory_order_relaxed))
//		++z;
//}



bool x, y;
int z;

void write_x_then_y()
{
	x = true;
	y = true;
}

void read_y_then_x()
{
	while (!y);
	if (x)
		++z;
}



int main(int argc, char* argv[]) {

	/*
	// atomic<bool> atomic_bool;
	// atomic<char> atomic_char;
	// atomic<signed char> atomic_signed_char;
	// atomic<int> atomic_int;
	// atomic<unsigned> atomic_unsigned;
	// atomic<short> atomic_short;
	// atomic<unsigned short> atomic_unsigned_short;
	// atomic<long> atomic_long;
	// atomic<unsigned long> atomic_unsigned_long;
	// atomic<long long> atomic_long_long;
	// atomic<unsigned long long> atomic_unsigned_long_long;
	// atomic<char16_t> atomic_char16_t;
	// atomic<char32_t> atomic_char32_t;
	// atomic<wchar_t> atomic_wchar_t;
	// 

	atomic_bool abool;
	atomic_char achar;
	atomic_schar aschar;
	atomic_int aint;
	atomic_uint auint;
	atomic_short ashort;
	atomic_ushort aushort;
	atomic_long along;
	atomic_ulong aulong;
	atomic_llong allong;
	atomic_ullong aullong;
	atomic_char16_t achar16_t;
	atomic_char32_t achar32_t;
	atomic_wchar_t awchar_t;
	
	
	// atomic_int_least8_t int_least8_t
	// atomic_uint_least8_t uint_least8_t
	// atomic_int_least16_t int_least16_t
	// atomic_uint_least16_t uint_least16_t
	// atomic_int_least32_t int_least32_t
	// atomic_uint_least32_t uint_least32_t
	// atomic_int_least64_t int_least64_t
	// atomic_uint_least64_t uint_least64_t
	// atomic_int_fast8_t int_fast8_t
	// atomic_uint_fast8_t uint_fast8_t
	// atomic_int_fast16_t int_fast16_t
	// atomic_uint_fast16_t uint_fast16_t
	// atomic_int_fast32_t int_fast32_t
	// atomic_uint_fast32_t uint_fast32_t
	// atomic_int_fast64_t int_fast64_t
	// atomic_uint_fast64_t uint_fast64_t
	// atomic_intptr_t intptr_t
	// atomic_uintptr_t uintptr_t
	// atomic_size_t size_t
	// atomic_ptrdiff_t ptrdiff_t
	// atomic_intmax_t intmax_t
	// atomic_uintmax_t uintmax_t

	int_least8_t intl8t;
	uint_least8_t uintl8t;
	int_least16_t intl16t;
	uint_least16_t uintl16t;
	int_least32_t intl32t;
	uint_least32_t uintl32t;
	int_least64_t intl64t;
	uint_least64_t uintl64t;
	int_fast8_t intf8t;
	uint_fast8_t uintf8t;
	int_fast16_t intf16t;
	uint_fast16_t uintf16t;
	int_fast32_t intf32t;
	uint_fast32_t uintf32t;
	int_fast64_t intf64t;
	uint_fast64_t uintf64t;
	intptr_t intptrt;
	uintptr_t uintptrt;
	size_t sizet;
	ptrdiff_t ptrdifft;
	intmax_t intmaxt;
	uintmax_t unitmaxt;
	

	cout << "atomic bool is " << (abool.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic signed char is " << (aschar.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic int is " << (aint.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic unsigned int is " << (auint.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic short is " << (ashort.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic unsigned short is " << (aushort.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic long is " << (along.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic unsigned long is " << (aulong.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic long long is " << (allong.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic unsigned long long is " << (aullong.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic char16_t is " << (achar16_t.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic char32_t is " << (achar32_t.is_lock_free() ? "lock free" : "not lock free") << endl;
	cout << "atomic wchar_t is " << (awchar_t.is_lock_free() ? "lock free" : "not lock free") << endl;
	//*/
	
	x = false;
	y = false;
	z = 0;
	std::thread a(write_x_then_y);
	std::thread b(read_y_then_x);
	a.join();
	b.join();
	assert(z.load() != 0);


	return EXIT_SUCCESS;
}