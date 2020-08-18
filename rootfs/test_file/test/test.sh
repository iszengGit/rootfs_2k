#!/bin/sh
#-------------------------------------#

if [ -f test.log ]; then
	rm test.log
fi
#测试前请根据自己要测试的项修改此脚本
#测试/dev/spidev1.0，打印读写数据，写结果到test.log
./spi_test /dev/spidev1.0 | tee -a test.log				
#测试/dev/i2c-2，打印读写数据，写结果到test.log		
./i2c_test /dev/i2c-2  | tee -a test.log						
#自测,打印发送接收数据一样 写结果到test.log	
./can_test can0 can1 | tee -a test.log		
#gpio_test pin0 pin1 pin2...控制gpio电平让led循环打印亮灭，按回车键退出,		
./gpio_test 28 29 | tee -a test.log					
#pwm_test pwm0 pwm1 pwm2... 蜂鸣器自动改变占空比,改变频率，按回车键退出	
./pwm_test 1 2	| tee -a test.log						
#打印按键按下，按键弹起，按回车键退出
./key_test | tee -a test.log
#最暗到最亮，最亮到最暗循环，按回车键退出
./backlight_test | tee -a test.log						
./beep_test | tee -a test.log	
#测试串口/dev/ttySAC2
./uart_test /dev/ttySAC2 | tee -a test.log
./uart_test /dev/ttySAC2 /dev/ttySAC3 | tee -a test.log	
#led_test循环闪烁，按回车键退出
./led_test | tee -a test.log	
#执行看门狗后会重启						
./watchdog_test | tee -a test.log						

