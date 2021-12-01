#include "Comms.h"
#include "../Window/Window.h"


Result Comms::interfaceInfoSending(const InterfaceInfo info) {
    // Đây là hàm để chuyển info từ bên tui sang bên ông.
    // Tui đã pack lại thành biến info ở trên r á.
    // Ông làm gì đó ở đây để chuyển info về bên ông i.
    // Cần thiết thì return success hay failure để tui xử lí.
    // K thì ông sửa hàm thành void luôn cho tiện :v
    return Result::success;
}


// Mỗi khi có thay đổi gì trong GameInfo thì ông cứ gọi hàm này, tui sẽ tự cập nhật lại.
Result Comms::gameInfoSending(const GameInfo info) {
    auto window = Window::getInstance();
    (*window)->updateGameInfo(info);
}
