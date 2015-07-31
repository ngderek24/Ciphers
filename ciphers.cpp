#include <iostream>
#include <cctype>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

//encrypts input plaintext with specified number of shifts
string caesarEncrypt(string plaintext, int shift){
	string ciphertext;
	for(int i = 0; i < plaintext.size(); i++){
		if(isspace(plaintext[i])){
			ciphertext += ' ';
			continue;
		}
		if(!isalpha(plaintext[i]))
			return "Error: input must contain only alphabetic letters and whitespaces.";
		if(isupper(plaintext[i])){
			if(plaintext[i] + shift > 90)
				ciphertext += ((plaintext[i] + shift) % 91) + 'A';
			else
				ciphertext += plaintext[i] + shift;
		}
		else{
			if(plaintext[i] + shift > 122)
				ciphertext += ((plaintext[i] + shift) % 123) + 'a';
			else
				ciphertext += plaintext[i] + shift;
		}
	}
	return ciphertext;
}

//decrypts input ciphertext with specified number of shifts
string caesarDecrypt(string ciphertext, int shift){
	int revShift = 26 - shift;
	return caesarEncrypt(ciphertext, revShift);
}

//encrypts input plaintext with specified keyword using Vigenere Cipher
string vigenereEncrypt(string plaintext, string keyword){
	string ciphertext;
	for(int a = 0; a < keyword.size(); a++)
		tolower(keyword[a]);
	int repeatedNum = (int)(plaintext.size()/keyword.size() + 1);

	string temp;
	for(int n = 0; n < repeatedNum; n++)
		temp += keyword;
	string encKeyword = temp.substr(0, plaintext.size());

	for(int i = 0; i < plaintext.size(); i++){
		temp = plaintext[i];
		ciphertext += caesarEncrypt(temp, encKeyword[i] - 97);
	}
	return ciphertext;
}

//decrypts Vigenere ciphertext with specified keyword
string vigenereDecrypt(string ciphertext, string keyword){
	string plaintext;
	for(int a = 0; a < keyword.size(); a++)
		tolower(keyword[a]);
	int repeatedNum = (int)(ciphertext.size()/keyword.size() + 1);

	string temp;
	for(int n = 0; n < repeatedNum; n++)
		temp += keyword;
	string encKeyword = temp.substr(0, ciphertext.size());

	for(int i = 0; i < ciphertext.size(); i++){
		temp = ciphertext[i];
		plaintext += caesarDecrypt(temp, encKeyword[i] - 97);
	}
	return plaintext;
}

//encrypts plaintext using ADFGVX with given character map and keyword
string ADFGVXencrypt(map<char, string> &characters, string plaintext, string keyword){
	string temp;
	for(int i = 0; i < plaintext.size(); i++){
		temp += characters[plaintext[i]];
	}

	string sortedKey = keyword;
	sort(sortedKey.begin(), sortedKey.end());

	string ciphertext;
	for(int j = 0; j < sortedKey.size(); j++){
		size_t pos = keyword.find(sortedKey[j]);
		for(int k = pos; k < temp.size(); k += keyword.size()){
			ciphertext += temp[k];
		}
	}
	return ciphertext;
}
