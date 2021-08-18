#pragma once


#ifndef INTERNET_FUNCTION_HPP
#define INTERNET_FUNCTION_HPP

#include <string>
#include <stringapiset.h>
#define This (*this)

namespace Internet {
	enum function_msg {
		_SUCCESS_ = 0 , 
		_ERROR_ = -1 
	};

	class useful_function {
	private:
		int i, Len1, Len2;
	protected:
		void set_mem(int i = 0, int Len1 = 0, int Len2 = 0);

	public:
		//big5轉unicode是用MultiByteToWideChar
		int Big5ToUniCode(char* Big5, wchar_t* UniCode, int Len);

		//unique轉big5是用WideCharToMultiByte
		int UniCodeToBig5(wchar_t* UniCode, char* Big5, int Len);

		// wchar string process function
		int wstrlen(wchar_t* Src, int Size);
		int wstrcpy(wchar_t* Dst, int Size, wchar_t* Src);
		int wstrcat(wchar_t* Dst, int Size, wchar_t* Src);
	};

	void useful_function::set_mem(int i, int Len1, int Len2) {
		This.i = i;
		This.Len1 = Len1;
		This.Len2 = Len2;
	}

	int useful_function::Big5ToUniCode(char* Big5, wchar_t* UniCode, int Len) {
		int result = MultiByteToWideChar(950, 0, Big5, -1, UniCode, Len);
		return result;
	}

	int useful_function::UniCodeToBig5(wchar_t* UniCode, char* Big5, int Len) {
		int result = WideCharToMultiByte(950, 0, UniCode, -1, Big5, Len, NULL, NULL);
		Big5[Len] = 0;
		return result;
	}

	// wchar string process function
	int useful_function::wstrlen(wchar_t* Src, int Size) {
		This.set_mem();
		for (This.i = 0; This.i < Size; This.i++)
			if (!Src[This.i]) break;

		return (This.i < Size ? This.i : _ERROR_);

	}
	int useful_function::wstrcpy(wchar_t* Dst, int Size, wchar_t* Src) {
		This.set_mem(0, This.wstrlen(Src, Size));

		if (This.Len1 > Size - 1) This.Len1 = Size - 1;

		for (This.i = 0; This.i <= This.Len1; This.i++)
			Dst[This.i] = Src[This.i];

		return This.Len1;
	}
	int useful_function::wstrcat(wchar_t* Dst, int Size, wchar_t* Src) {
		This.set_mem(0,
			This.wstrlen(Dst, Size),
			This.wstrlen(Src, Size));

		if ((This.Len1 + This.Len2) > (Size - 1))
			return _ERROR_;

		for (This.i = 0; This.i <= This.Len2; This.i++)
			Dst[This.Len1 + This.i] = Src[This.i];

		return _SUCCESS_;
	}
}

#endif // !INTERNET_FUNCTION_HPP
