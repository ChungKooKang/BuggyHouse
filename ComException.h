#pragma once
#include <Windows.h>
#include <exception>
#include <string>
#include <sstream>


	class com_exception : public std::exception
	{
	private:
		HRESULT mResult;
		std::string mDescription;

	public:
		com_exception(HRESULT hr) : mResult{ hr }
		{
		}
		com_exception(HRESULT hr, std::string msg) : mResult{ hr }, mDescription{ msg }
		{

		}

		virtual const char* what() const override
		{
			std::stringstream ss;
			ss << "Failure with Code : " << mResult << std::endl << mDescription << std::endl;

			return ss.str().c_str();
		}
	};

	inline void ThrowIfFailed(HRESULT hr, std::string msg = "") // inline�� �Լ�ȣ�⽺���� �ٿ��� ������ ������Ű�� ���̴�. 
										  // �Լ��� �ڵ带 �ش��ٿ� �ٿ��� ȣ�⽺���� ������� �ʰ� �ϴ� ���̴�.
										  // �̰��� compiler�� �Ǵ��ؼ� �ϴµ� �̰��� �츮�� ���ص� �ź��� ���� �ִ�.
	{
		if (FAILED(hr))
		{
			throw com_exception(hr, msg);
		}
	}

