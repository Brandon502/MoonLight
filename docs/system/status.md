# System Status

<img width="518" alt="image" src="https://github.com/user-attachments/assets/49e4a72a-ee1e-47a4-afe6-d0dd49573a86" />

## Functional

* 🌙 **Performance**: loops per second: nr of times main loop is executed
* 🌙 **Safe Mode** 🆕: After a crash, the device will start in Safe Mode disabling possible causes of crashes. See also [MoonLight](https://moonmodules.org/MoonLight/moonlight/general/). In case of safe mode, the statusbar will show a shield: 🛡️. Try to find the reason of the crash and correct and restart the device. If no crash, it will go out of safe mode.

* **Sleep**: Device is set in low power mode.
* **Restart**: The device will restart
* **Factory reset**: all settings will be removed.

## Technical

* 🌙 Reordered info from dynamic to static

### Server

[SystemStatus.h](https://github.com/MoonModules/MoonLight/blob/main/lib/framework/SystemStatus.h) and [SystemStatus.cpp](https://github.com/MoonModules/MoonLight/blob/main/lib/framework/SystemStatus.cpp)

### UI

[SystemStatus.svelte](https://github.com/MoonModules/MoonLight/blob/main/interface/src/routes/system/status/SystemStatus.svelte)
