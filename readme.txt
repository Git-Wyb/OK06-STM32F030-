2022.10.10
测试，进入HardFault_Handler硬件错误中断

2022.12.16  优化PI，减小电机启动瞬间PWM累加值，防止启动时抖动SOFT_START_20MS_MORE_DUTY； 输入捕获定时器时钟设为0.5MHz.

2022.12.22  添加测试模式
checksum : 0x005097F7 

2023.02.16  低电平给无线开电，高电平关电；OPEN/STOP/CLOSE上拉输入，高电平有效。