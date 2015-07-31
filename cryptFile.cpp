#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include "..\cryptopp562\osrng.h"
#include "..\cryptopp562\cryptlib.h"
#include "..\cryptopp562\filters.h"
#include "..\cryptopp562\des.h"
#include "..\cryptopp562\modes.h"
#include "..\cryptopp562\secblock.h"
#include "..\cryptopp562\aes.h"
using namespace std;
using namespace CryptoPP;

bool encryptFile(string filename, SecByteBlock key, byte* iv){
	ifstream file;
	file.open(filename);
	if(file.is_open()){
		string line;
		ofstream encFile;
		encFile.open("encText.txt", ios::app);
		CBC_Mode<AES>::Encryption enc;
		enc.SetKeyWithIV(key, key.size(), iv);
		while(getline(file, line)){
			string cipher;
			//cout << line << endl;
			StringSource ss(line, true, new StreamTransformationFilter(enc, new StringSink(cipher)));
			
			if(encFile.is_open()){
				encFile.write(cipher.c_str(), cipher.size());
				encFile << '\r\n';
			}
			else
				cout << "couldn't write" << endl;
			//cout << cipher << endl;
		}
		cout << "finished encrypting" << endl;
		encFile.close();
		file.close();
		return true;
	}
	else{
		cout << "Unable to open file." << endl;
		return false;
	}
}

bool decryptFile(string filename, SecByteBlock key, byte* iv){
	ifstream file;
	file.open(filename);
	if(file.is_open()){
		string line;
		CBC_Mode<AES>::Decryption dec;
		dec.SetKeyWithIV(key, key.size(), iv);
		while(getline(file, line)){
			string plain;
			//cout << line << endl;
			StringSource ss(line, true, new StreamTransformationFilter(dec, new StringSink(plain)));
			//cout << plain << endl;
		}

		file.close();
		return true;
	}
	else{
		cout << "Unable to open file." << endl;
		return false;
	}
}

int main(){
	AutoSeededRandomPool rand;
	SecByteBlock key(AES::DEFAULT_KEYLENGTH);
	rand.GenerateBlock(key, key.size());

	byte iv[AES::BLOCKSIZE];
	rand.GenerateBlock(iv, sizeof(iv));

	encryptFile("test.txt", key, iv);
	decryptFile("encText.txt", key, iv);
}
