// WinCryptoTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <wincrypt.h>
#include <bcrypt.h> // for CNG(Crypto API:Next Generation)
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa376210(v=vs.85).aspx

#include <iostream>


// https://msdn.microsoft.com/en-us/library/windows/desktop/aa379886(v=vs.85).aspx

void Test_CryptAcquireContext()
{
	HCRYPTPROV hCryptProv = NULL;

	LPCWSTR UserName = _T("MyKeyContainer");

	if (CryptAcquireContext(&hCryptProv, UserName, NULL, PROV_RSA_FULL, 0)) {

		// on second time call, display below message because the key container has been already created using CRYPT_NEWKEYSET
		std::wcout << L"A Cryptographic context with the " << UserName << " key container has beed acquired." << std::endl;
	}
	else {

		if (GetLastError() == NTE_BAD_KEYSET) {

			if (CryptAcquireContext(&hCryptProv, UserName, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
				
				// on first time call, display below message.
				std::wcout << L"A new key container has been created." << std::endl;
			}
			else {

				std::wcout << L"Could not create a new key container." << std::endl;

				exit(1);
			}
		}
		else {

			std::wcout << L"A Cryptographic service handle could not be acquired." << std::endl;

			exit(1);
		}
	}

	if (CryptReleaseContext(hCryptProv, 0)) {

		std::wcout << L"The handle has beed released." << std::endl;
	}
	else {

		std::wcout << L"The handle could not be released." << std::endl;
	}
}


int main()
{
	Test_CryptAcquireContext();

	return 0;
}

