#include <iostream>



using namespace std;

int main(int argc, char const *argv[]) {
  double valores;
  double media = 0;

  for(int i = 0; i < 5 ; i++){
     cin >> valores;
     media += valores;
  }
  cout << media/5;

  return 0;
}
