# OV7670驱动

- 使用HAL库
- 以STM32F407VET为例子

## 使用

OV7670的源代码在`Core/Src/ov7670`中,头文件在`Core/Inc/ov7670`中，依赖扩展的微秒延时,也可以选择自己写延时函数。在需要使用的地方引入`ov7670/index.h`即可使用

## 关于修改配置

- 使用不同的端口的话可以直接在`Core/Inc/ov7670/index.h`和`Core/Inc/ov7670/sccb.h`中修改宏来设置端口别名
- 若使用的HAL库版本不同或不使用HAL库，则在`Core/Inc/ov7670/index.h`和`Core/Inc/ov7670/sccb.h`中修改相关的宏
  - `Core/Inc/ov7670/index.h`中需要修改的宏有
    - OV7670_CLK_Init()
    - OV7670_CLK_Off()
    - OV7670_GPIO_Init()
  - `Core/Inc/ov7670/sccb.h`中需要修改的宏有
    - SCCB_SID_High
    - SCCB_SID_Low
    - SCCB_SIC_High
    - SCCB_SIC_Low
    - SCCB_SID_DATA