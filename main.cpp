/*
 * C++ implementation of the API keys on mining sites.
 * Currently supports: www.btcguild.com, www.mtred.com
 */
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int siteCount = 0;
struct info {
		string siteAddr;
		string apiKey;
	};
info mtred;
info btcguild;

typedef string group[2];

void chompKey(group keysPre); // Determines which line is for which site and then gets the key alone
void keyFileProblem(int code); // Outputs errors in the keyfile

int main() {
	
	mtred.siteAddr = "https://mtred.com/api/user/key/";
	btcguild.siteAddr = "http://www.btcguild.com/api.php?api_key=";
	group keys;
	ifstream keyfile;
	string keystr;
	/* Get the current key from the keyfile and store
	 * sites that are active start with '@'
	 */
	keyfile.open("key.txt");
	for(int i = 0; i<2; i++) {
		getline(keyfile, keys[i]);
		if(keys[i][0] != '@')
			keyFileProblem(i);
		else 
			siteCount++;
		
	}
	chompKey(keys);
	  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    res = curl_easy_perform(curl);
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  cout << res
	return(0);
}

void chompKey(group keysPre) {
	for(int i=0; i<2; i++) {
		if(keysPre[i][1] == 'm') {
			keysPre[i].erase(0,8);
			mtred.siteAddr.append(keysPre[i]);
		}
		else {
			keysPre[i].erase(0,11);
			btcguild.siteAddr.append(keysPre[i]);
		}
	}
	
}


 void keyFileProblem(int code) {
	 switch(code) {
		 case 0:
			cout << "Problem on key file line 1.\n";
			break;
		case 1:
			cout << "Problem on key file line 2.\n";
			break;
	}
}
		
