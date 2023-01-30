#include <iostream>
#include <string>
#include <vector>
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

#define REPLACE "r"
#define INSERT "i"
#define DELETE "d"

static const vector<vector<string> > POSSIBILITIES = { {"id", "di", "rr"},
    					     {"dr", "rd"},
                   {"dd"} };

int check_model(string str1, string str2, int len1, int len2, string model)
{
	int idx1 = 0;
	int idx2 = 0;
	int pad = 0;
	int cost = 0;

	while (idx1 < len1 || idx2 < len2) {
		if (str1[idx1] != str2[idx2 - pad]) {
			cost++;
			if(2 < cost) {
				return cost;
			}

			string option;
			option = model[cost-1];
			if(option == DELETE){
				idx1++;
			}
			else if(option == INSERT){
				idx2++;
			}
			else if(option == REPLACE){
				idx1++;
				idx2++;
				pad = 0;
			}
		}
		else {
			idx1++;
			idx2++;
			pad = 0;
		}
	}
	return (cost + (len1 - idx1) + (len2 - idx2));
}

//' Perform mbleven comparison on two strings
//'
//' This is an Rcpp implementation of the mbleven algorithm. It takes two
//' strings as input and returns 0, 1, or 2 when the edit distance of the
//' strings are 0, 1, or 2 repsecitvely. If the edit distance if over three
//' edits, the algoirthm will return -1.
//'
//' @param str1 A character(1) vector.
//' @param str2 A character(1) vector.
//' @export
//' @examples
//' mbleven_compare('aaa', 'aaa')
//' mbleven_compare('aaa', 'abb')
//' mbleven_compare('aaa', 'bbb')
// [[Rcpp::export]]
int mbleven_compare(std::string str1, std::string str2)
{
	int len1 = str1.length();
	int len2 = str2.length();

	if(len1 < len2) {
		int temp = len1;
		len1 = len2;
		len2 = temp;

		string temp2 = str1;
		str1 = str2;
		str2 = temp2;
	}

	if (len1 - len2 > 2) {
		return -1;
	}
	vector<string> models = POSSIBILITIES[len1-len2];
	int res = 3;

	for(unsigned int i = 0; i < models.size(); i++){
		int cost = check_model(str1, str2, len1, len2, models[i]);
		if(cost < res){
			res = cost;
		}
	}

	if(res == 3) {
		res = -1;
	}

	return res;
}
