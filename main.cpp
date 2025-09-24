#include <stdio.h>

static const double YEAR_RISE = 1.5;
static const double YEARS_5 = 5.0;
static const double YEARS_7 = 7.0;
static const double YEARS_10 = 10.0;

double olev_by_year(unsigned int num_years);

int main() {
  double year_5_rise = olev_by_year(YEARS_5);
  double year_7_rise = olev_by_year(YEARS_7);
  double year_10_rise = olev_by_year(YEARS_10);

  printf("Ocean Levels in X years\n\n\n");

  printf(
    "In Five Years, the ocean will rise %f millimeters\n\n",
    year_5_rise);

  printf(
    "In Seven Years, the ocean will rise %f millimeters\n\n",
    year_7_rise);

  printf(
    "In Ten Years, the ocean will rise %f millimeters\n\n",
    year_10_rise);

  return 0;
}

double olev_by_year(unsigned int num_years) {
  return (num_years * YEAR_RISE);
} 
