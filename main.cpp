#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;


/// Holds one room's worth of user input specifications
struct RoomInputs {
  double price_paint_per_gallon;
  double square_feet;
};

// I think some padding on the int doesn't 
// matter much in this context
//
/// All the outputs which are displayed get grouped 
/// here to avoid wieldy numbers of parameters 
struct RoomOutputs {
  int num_rooms;
  double gals_paint; 
  double labor_hours;
  double labor_cost;
  double paint_cost;
  double total_cost;
};

vector<RoomInputs> getRoomSpec(void);
RoomOutputs calcRoomCosts(vector<RoomInputs> rooms);
void displayRoomSpec(RoomOutputs room);

int main(void) {
  vector<RoomInputs> room_user_input_vals = getRoomSpec();

  RoomOutputs room_display_costs = calcRoomCosts(room_user_input_vals);

  displayRoomSpec(room_display_costs);

  return 0;
}

/// Gets the user input for each room, which is stored in a struct 
/// and returned as a vector.
vector<RoomInputs> getRoomSpec(void) {
  const char *input_err = "Error: invalid user input";

  vector<RoomInputs> rooms;
  int num_rooms;

  // gets the number of rooms
  cout << "How many rooms need to be painted? : ";
  cout.flush();
  cin >> num_rooms;
  if (cin.fail() || num_rooms < 1) {
    cerr << input_err << endl;
    exit(1);
  }

  cout << endl;

  // gets the room specifications for num_rooms number of rooms
  for (int i = 1; i <= num_rooms; ++i) {
    struct RoomInputs room;

    // gets the room price of paint per gallon in room i
    cout << "How much does paint cost per gallon for room " << i << "? : $";
    cout.flush();
    cin >> room.price_paint_per_gallon;
    if (cin.fail() || room.price_paint_per_gallon < 10.0) {
      cerr << input_err << endl;
      exit(1);
    }

    // gets the wall space square footage in room i
    cout << "What's the wall space square footage in room " << i << "? : ";
    cout.flush();
    cin >> room.square_feet;
    if (cin.fail() || room.square_feet < 0) {
      cerr << input_err << endl;
      exit(1);
    } 

    cout << endl; 

    // adds the room specifications to the collection
    rooms.push_back(room); 
  }

  cout << '\n' << endl;

  return rooms;
}


/// Takes a vector<RoomInputs>, which is all the user input on a room by 
/// room basis. The user input data is used to calculate the display 
/// outputs as dictated by the instructions which is returned in a 
/// RoomOutputs struct.
RoomOutputs calcRoomCosts(vector<RoomInputs> rooms) {
  double square_ft_total = 0;
  //braces automatically zero initializes the structs fields.
  RoomOutputs room_vals{};
  room_vals.num_rooms = rooms.size();

  /// gallons per square foot
  constexpr double gpsf = { 1.0 / 110.0 };
  /// labor per square foot
  constexpr double lpsf = { 8.0 / 110 };
  /// labor charge per hour
  const double lcph = 25.0;

  // - sets square feet total in Display vals as the sum of all
  //   rooms square footage,
  // - calculates the rooms gallons of paint needed rounded up to nearest int
  // - adds the gallons of paint needed to the total
  // - calculates the paint cost and adds it to the total
  for (int i = 0; i < room_vals.num_rooms; ++i) {
    double room_gals_paint;
    square_ft_total += rooms[i].square_feet;      
    room_gals_paint = ceil(rooms[i].square_feet * gpsf);
    room_vals.gals_paint += room_gals_paint;
    room_vals.paint_cost += room_gals_paint * rooms[i].price_paint_per_gallon;
  }

  // calculats labor hours, cost of labor, and total cost
  room_vals.labor_hours = square_ft_total * lpsf;
  room_vals.labor_cost = room_vals.labor_hours * lcph;
  room_vals.total_cost += room_vals.labor_cost + room_vals.paint_cost; 

  return room_vals;
}

/// Takes the Display Outputs in the form of a RoomOutputs struct 
/// and displays the structs values to the user.
void displayRoomSpec(RoomOutputs room) {
  cout 
    // setprecision to 0 for the ints because fixed makes them 
    // output as floating point regardless of type
    << fixed << setprecision(0) 
    << "Estimate for Painting " << room.num_rooms << " Rooms:" << '\n'
    << "Gallons of paint to purchase: " << room.gals_paint << '\n'
    // update precision to reflect currency standards
    << setprecision(2)
    << "Number of hours required to paint rooms: " << room.labor_hours << '\n'
    << "Cost of paint: $" << room.paint_cost << '\n' 
    << "Cost of labor: $" << room.labor_cost << '\n'
    << "Total cost for job: $" << room.total_cost << endl;
}
