#include <iomanip>
#include <cmath>
#include "query.cpp"

using namespace std;

typedef struct string_fins {
  string principal; 
	string int_rate;
	string ncompound;
} StringFinancials;

typedef struct num_fins {
  double principal;	
	double int_rate;
	double ncompound;
} IntegralFinancials;

IntegralFinancials transform_string_fins(StringFinancials fin);
StringFinancials fetch_financials(void);
void print_financials(IntegralFinancials fin, double total);
double interest_calc(IntegralFinancials);

const auto default_precision{ cout.precision() };

int main(void) {
  StringFinancials str_fin = fetch_financials();
	IntegralFinancials int_fin = transform_string_fins(str_fin);
	double total = interest_calc(int_fin);
	print_financials(int_fin, total);
}

StringFinancials fetch_financials(void) {
	StringFinancials fin = {
    .principal = query("@ Fill in this investment info for me @\nPrincipal: "),	
	  .int_rate = query("Interest Rate: "),
    .ncompound = query("Number Of Yearly Compoundings: "),
	};

	return fin;
}

double interest_calc(IntegralFinancials fin)
{
	double rate = fin.int_rate * 0.01;
	return fin.principal * (pow((1.0 + rate/fin.ncompound), fin.ncompound));   
}

IntegralFinancials transform_string_fins(StringFinancials str_fin) {
	IntegralFinancials fin = {
    .principal = stod(str_fin.principal),
		.int_rate = stod(str_fin.int_rate),
		.ncompound = stod(str_fin.ncompound),
	};

	return fin;
}

// longest line is 29 chars long
void print_financials(IntegralFinancials fin, double total) {
  double interest = total - fin.principal;

	const string int_rate_msg{ "Interest Rate:      % " };
	const string compd_msg{    "Times Compounded:     " };
	const string princip_msg{  "Principal:          $ " };
	const string int_msg{      "Interest:           $ " };
	const string amt_sav_msg{  "Amount In Savings:  $ " };

	cout << '\n' << '\n' << left << fixed << setprecision(2)
		<< int_rate_msg << fin.int_rate << '\n'
    << compd_msg << right  << fin.ncompound << '\n'
		<< princip_msg << right << fin.principal << '\n'
		<< int_msg << right << interest << '\n'
		<< amt_sav_msg << right << total ;
}
