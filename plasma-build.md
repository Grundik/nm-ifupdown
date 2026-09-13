```sh
git clone https://invent.kde.org/plasma/plasma-nm.git
tar xzf plasma-nm-ifupdown.tar.gz
cp -a plasma-nm-ifupdown/ifupdown plasma-nm/vpn/ifupdown

# add to plasma-nm/vpn/CMakeLists.txt:
#   add_subdirectory(ifupdown)

cmake -B build -S plasma-nm -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build --target plasmanetworkmanagement_ifupdownui
# install .so into:
#   $(qtpaths --plugin-dir)/plasma/network/vpn/
```
