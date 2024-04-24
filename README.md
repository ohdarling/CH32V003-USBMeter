# CH32V003-USBMeter

A USBMeter powered by CH32V003 and INA219.

<img src="images/diy-usb-meter.jpg?raw=true" alt="diy-usb-meter" style="zoom:50%;" />



## Folder Structure

* hardware: All files required for PCB production and soldering
  * Gerber
  * Schematic
  * BOM
  * Interactive Solder Helper
* firmware: Sources of USBMeter firmware
  * Project managed by PlatformIO
  * Based on platform-ch32v
* 3D_model: 3D models required for assembly
  * STL file of the device enclosure
  * JLC production file for the front panel



## Compile Firmware

USBMeter's firmware project is managed by PlatformIO, please ensure it was installed on your system.

**Install on macOS**

```bash
brew install platformio
```

**Compile and Upload Firmware**

```bash
cd firmware
pio run --target upload
```

You must connect WCH-LinkE to USBMeter first.



## DIY Tutorial

For a complete DIY tutorial, please refer to the following series of articles.

**Note: These articles are written in Chinese.**

- [DIY USB 电流表（1）：元件选型和原理图绘制](https://xujiwei.com/blog/2024/02/diy-usb-meter-schematic/)
- [DIY USB 电流表（2）：PCB 布局布线](https://xujiwei.com/blog/2024/02/diy-usb-meter-pcb-design/)
- [DIY USB 电流表（3）：PCB 免费打样详解](https://xujiwei.com/blog/2024/03/diy-usermeter-order-pcb/)
- [DIY USB 电流表（4）：PCB 焊接与调试](https://xujiwei.com/blog/2024/03/diy-usb-meter-pcb-soldering/)
- [DIY USB 电流表（5）：使用 VSCode + PlatformIO 搭建固件开发环境](https://xujiwei.com/blog/2024/04/diy-usb-meter-setup-fw-dev/)
- [DIY USB 电流表（6）：点个屏，使用 I2C 驱动 0.96 寸 OLED](https://xujiwei.com/blog/2024/04/diy-usb-meter-oled-display/)
- [DIY USB 电流表（7）：读取和显示 INA219 电流电压数据](https://xujiwei.com/blog/2024/04/diy-usb-meter-read-ina219/)
- [DIY USB 电流表（8）：检测按键和绘制功率曲线](https://xujiwei.com/blog/2024/04/diy-usb-meter-power-history/)



## Special Thanks

* CH32V003-GameConsole
  * https://github.com/wagiminator/CH32V003-GameConsole
* INA219_WE
  * https://github.com/wollewald/INA219_WE



## License

MIT License
