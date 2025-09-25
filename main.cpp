#include <stdio.h>

#define HIGHWAY_MPG 28.9
#define TOWN_MPG 23.5
#define GAS_TANK_SIZE 20

static const float TOWN_MAX_MILES = (GAS_TANK_SIZE * TOWN_MPG);
static const float HIGHWAY_MAX_MILES = (GAS_TANK_SIZE * HIGHWAY_MPG);

static const char *TOWN_MILES_MSG = "Max distance traveled in town per tank of gas = ";
static const char *HIGHWAY_MILES_MSG = "Max distance traveled on the highway per tank of gas = "; 
static const char *INIT_MSG = "## Max Distances traveled per tank of gas in different settings ##";

int main() {
	printf("\n%s\n\n\n", INIT_MSG);
	printf("%s%g\n\n", HIGHWAY_MILES_MSG, HIGHWAY_MAX_MILES);
	printf("%s%g\n\n", TOWN_MILES_MSG,TOWN_MAX_MILES);

	return 0;
}
