// /*
//   Overall steps: application ->render window content ->DWM(display window manager ) ->GPU ->display framebuffer -> display monitor
// */
// // #include <iostream>
// // int main(void) {
// //   std::cout << "Hello, World!" << std::endl;
// //   return 0;
// // }
// #ifndef UNICODE
// #define UNICODE
// #endif
// #include <windows.h>
// // hwnd = handle to the window
// // uMsg = message
// // wParam = additional msg info
// // lParam = additional msg info
// LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
//   // how a future window will behave
//   const wchar_t CLASS_NAME[] = L"Window Instance";
//   WNDCLASS wc{};
//   wc.lpfnWndProc = WindowProc;
//   wc.hInstance = hInstance;
//   wc.lpszClassName = CLASS_NAME;
//   // End of how a future window will behave

//   RegisterClass(&wc);
//   // Create the window itself:
//   /*
//   calls CreateWindowEx to create a window with the specified class name, title, style, size, position, and other parameters. If the window creation fails, it returns 0. Otherwise, it shows the window and enters a message loop to process messages sent to the window.

//   in the func itself:
//   func ->user32.dll ->windows Gui/window mngmnt subsystem -> kernel32.dll -> windows kernel subsystem
//   */
//   HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Learn to program windows", WS_OVERLAPPEDWINDOW,
//                              // size and position:
//                              CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//                              nullptr  // parentwindow
//                              ,
//                              nullptr,    // menu
//                              hInstance,  // instance handle
//                              nullptr);   // additional application data
//   if (!hwnd)
//     return 0;
//   // handle is returned, not the window itself, the handle is for future window ref
//   ShowWindow(hwnd, nCmdShow);
//   // Run the message loop:
//   MSG msg{};
//   while (GetMessage(&msg, nullptr, 0, 0) > 0) {
//     TranslateMessage(&msg);
//     DispatchMessage(&msg);
//   }
//   return 0;
// }
// LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//   switch (uMsg) {
//     case WM_DESTROY:
//       PostQuitMessage(0);
//       return 0;
//     case WM_PAINT: {
//       PAINTSTRUCT ps;
//       HDC hdc =
//           BeginPaint(hwnd, &ps);
//       FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
//       EndPaint(hwnd, &ps);
//     }
//       return 0;
//   }
//   return DefWindowProc(hwnd, uMsg, wParam, lParam);
// }

// // the code above accesses the DWM on its surface, gets a handle and through that handle modifies the basic window preoperties;
// // what does it mean:
// // the window gets created + the data about the window itself is sent to the lower level of the OS, the os then talks to the gpu to render that window, the gpu renders, produces a framebuffer, the framebuffer gets loaded again by the os -> window appears on the screen.
// // game engine -> vulkan -> gpu driver -> gpu -> generate the image + save it in a framebuffer -> gets read via a handle by DWM -> gets the image displayed
