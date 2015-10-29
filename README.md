oBabel Plugin for OpenCPN
Compiling

    This plugin now builds out of the OpenCPN source tree

git clone https://github.com/Rasbats/oBabel_pi.git

Build:

mkdir oBabel_pi/build
cd oBabel_pi/build
cmake ..
cmake --build .

Windows note: You must place opencpn.lib into your build directory to be able to link the plugin DLL. You can get this file from your local OpenCPN build, or alternatively download from http://sourceforge.net/projects/opencpnplugins/files/opencpn_lib/

Debugging: If you check out the plugin source into the plugins subdirectory of your OpenCPN source tree, you can build it as part of it (exactly as with the versions prior to 1.0)
