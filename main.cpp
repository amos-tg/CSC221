#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

struct RoomInputs {
  double price_paint_per_gallon;
  double square_feet;
};

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

vector<RoomInputs> getRoomSpec(void) {
  const char *input_err = "Error: invalid user input";
  vector<RoomInputs> rooms;
  int num_rooms;

  cout << "How many rooms need to be painted? : ";
  cout.flush();
  cin >> num_rooms;
  if (cin.fail() || num_rooms < 1) {
    cerr << input_err << endl;
    exit(1);
  }

  cout << endl;

  for (int i = 0; i < num_rooms; ++i) {
    struct RoomInputs room;

    cout << "How much does paint cost per gallon for room " 
      << (i + 1) << "? : $";
    cout.flush();
    cin >> room.price_paint_per_gallon;
    if (cin.fail() || room.price_paint_per_gallon < 10.0) {
      cerr << input_err << endl;
      exit(1);
    }

    cout << "What is the total wall space square footage in room " 
      << (i + 1) << "? : ";
    cout.flush();
    cin >> room.square_feet;
    if (cin.fail() || room.square_feet < 0) {
      cerr << input_err << endl;
      exit(1);
    } 

    cout << endl; 

    rooms.push_back(room); 
  }

  cout << '\n' << endl;

  return rooms;
}


RoomOutputs calcRoomCosts(vector<RoomInputs> rooms) {
  double square_ft_total = 0;
  RoomOutputs room_vals{ 0, 0, 0, 0, 0, 0 };
  room_vals.num_rooms = rooms.size();

  /// gallons per square foot
  constexpr double gpsf = { 1.0 / 110.0 };
  /// labor per square foot
  constexpr double lpsf = { 8.0 / 110 };
  /// labor charge per hour
  const double lcph = 25.0;

  for (int i = 0; i < room_vals.num_rooms; ++i) {
    double room_gals_paint;
    square_ft_total += rooms[i].square_feet;      
    room_gals_paint = ceil(rooms[i].square_feet * gpsf);
    room_vals.gals_paint += room_gals_paint;
    room_vals.paint_cost += room_gals_paint * rooms[i].price_paint_per_gallon;
  }

  room_vals.labor_hours = square_ft_total * lpsf;
  room_vals.labor_cost = room_vals.labor_hours * lcph;
  room_vals.total_cost += room_vals.labor_cost + room_vals.paint_cost; 

  return room_vals;
}

void displayRoomSpec(RoomOutputs room) {
  cout 
    << fixed << setprecision(0) 
    << "Estimate for Painting " << room.num_rooms << " Rooms:" << '\n'
    << "Gallons of paint to purchase: " << room.gals_paint << '\n'
    << setprecision(2)
    << "Number of hours required to paint rooms: " << room.labor_hours << '\n'
    << "Cost of paint: $" << room.paint_cost << '\n' 
    << "Cost of labor: $" << room.labor_cost << '\n'
    << "Total cost for job: $" << room.total_cost << endl;
}
