
#include "Log.hpp"
#include "System.hpp"
#include "Bluetooth.hpp"

int main() {

    Log << "a" << "b";
    bl::Bluetooth::test();

    while(true) {
        cu::System::sleep(1.0 / 60.0);
    }

    return 0;
}
