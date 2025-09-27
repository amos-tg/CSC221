#include <stdio.h>

#define SURVEY_SIZE (16500.0f)
#define PER_WEEK_PERCENT (0.15f)
#define PREFER_CITRUS_PERCENT (0.58f)

const double CUSTOMERS = SURVEY_SIZE * PER_WEEK_PERCENT;
const double CUST_PREF_CITRUS = CUSTOMERS * PREFER_CITRUS_PERCENT;

const char *INIT_MSG = 
  "### Energy Drink Consumption Statistics ###";
const char *CUST_MSG = 
  "This many people consume energy drinks once or more per week: ";
const char *PREF_CITRUS_MSG = 
  "This many customers prefer citrus flavored energy drinks: ";

int main() {
	printf("\n%s\n\n\n", INIT_MSG);
  printf("%s%g\n", CUST_MSG, CUSTOMERS);
  printf("%s%g\n", PREF_CITRUS_MSG, CUST_PREF_CITRUS);

	return 0;
}
