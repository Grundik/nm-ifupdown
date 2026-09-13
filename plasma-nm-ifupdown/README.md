# plasma-nm UI plugin for ifupdown VPN

Plasma refuses to activate VPN profiles whose `vpn.service-type` has no
matching plugin under `plasma/network/vpn` with metadata key
`X-NetworkManager-Services`.

This plugin registers:

```
X-NetworkManager-Services = org.freedesktop.NetworkManager.ifupdown
```

and provides a tiny settings UI (`iface` + `gateway`).

## Why this is needed

`handler.cpp` in plasma-nm does:

```cpp
KPluginMetaData::findPlugins("plasma/network/vpn",
    md => md.value("X-NetworkManager-Services") == serviceType);
```

If the list is empty → notification
"Plasma is missing support for 'ifupdown' VPN connections."

NetworkManager itself is fine; only the Plasma applet blocks.

## Build options

### A. Drop into plasma-nm source (simplest)

```bash
git clone https://invent.kde.org/plasma/plasma-nm.git
cp -a plasma-nm-ifupdown/ifupdown plasma-nm/vpn/ifupdown
# in plasma-nm/vpn/CMakeLists.txt add:
#   add_subdirectory(ifupdown)
cmake -B build -S plasma-nm -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build --target plasmanetworkmanagement_ifupdownui
sudo cmake --install build --component ...  # or install the .so by hand
```

Install path must be:

```
…/qt6/plugins/plasma/network/vpn/plasmanetworkmanagement_ifupdownui.so
```

### B. Standalone (needs plasma-nm private headers/libs)

`VpnUiPlugin` / `SettingWidget` live in plasma-nm internal libraries
(`plasmanm_editor`), which distros rarely ship as a -dev package.
Prefer option A unless you already build plasma-nm yourself.

## After install

```bash
# optional: restart plasmashell so it rescans plugins
kquitapp6 plasmashell; plasmashell &

nmcli connection up wg0   # still works
# tray Connect should work too
```

## Profile data keys (same as the Python service)

| vpn.data key | meaning                          |
|--------------|----------------------------------|
| iface        | ifupdown interface name (wg0)    |
| gateway      | external peer IP (v4 or v6)      |
