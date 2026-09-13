Simple plugin for Network Manager to just use ifup/ifdown to connect to VPNs

Coded by Grok.

For NM support: copy /etc and /usr into /, restart dbus and NetworkManager.

To add connection:
```sh
nmcli connection add type vpn con-name wg0 \
  vpn.service-type org.freedesktop.NetworkManager.ifupdown \
  connection.interface-name wg0 \
  vpn.data "iface=wg0,gateway=x.x.x.x" \
  ipv4.method disabled ipv6.method ignore \
  connection.autoconnect no
```

Connect: `nmcli connection up wg9`

Disconnect: `nmcli connection down wg9`

For Plasma widget support: see plasma-build.md
