#include "Comms.h"
#include "../Interface/Window/Window.h"


Result Comms::interfaceInfoSending(const InterfaceInfo info) {
    // Đây là hàm để chuyển info từ bên tui sang bên ông.
    // Tui đã pack lại thành biến info ở trên r á.
    // Ông làm gì đó ở đây để chuyển info về bên ông i.
    // Cần thiết thì return success hay failure để tui xử lí.
    // K thì ông sửa hàm thành void luôn cho tiện :v
    // NOTE: Khi tui gọi hàm này thì ông nhớ luôn gọi lại hàm gameInfoSending, cho dù k có gì để send nha.

    std::cout << "InterfaceInfo sending...\n";

    return Result::success;
}


// Ông chỉ gọi hàm này khi tui gọi interfaceInfoSending th nha, tại mình k có làm multithread.
Result Comms::gameInfoSending(const GameInfo info) {
    auto window = Window::getInstance();
    (*window)->updateGameInfo(info);

    return Result::success;
}
