# ~~~
# Summary:      Local, non-generic plugin setup
# Copyright (c) 2020-2021 Mike Rossiter
# License:      GPLv3+
# ~~~

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.


# -------- Options ----------

set(OCPN_TEST_REPO
    "opencpn/obababel-alpha"
    CACHE STRING "Default repository for untagged builds"
)
set(OCPN_BETA_REPO
    "opencpn/obababel-beta"
    CACHE STRING
    "Default repository for tagged builds matching 'beta'"
)
set(OCPN_RELEASE_REPO
    "opencpn/obababel-prod"
    CACHE STRING
    "Default repository for tagged builds not matching 'beta'"
)

option(OBABEL_USE_SVG "Use SVG graphics" ON)

#
#
# -------  Plugin setup --------
#
set(PKG_NAME obabel_pi)
set(PKG_VERSION  2.0.0)
set(PKG_PRERELEASE "")  # Empty, or a tag like 'beta'

set(DISPLAY_NAME obababel)    # Dialogs, installer artifacts, ...
set(PLUGIN_API_NAME obababel) # As of GetCommonName() in plugin API
set(PKG_SUMMARY "Assist transfer of routes to Chartplotters")
set(PKG_DESCRIPTION [=[
Using GPSBabel, installed locally, the plugin assists in transferring routes and waypoints to Chartplotters.
]=])

set(PKG_AUTHOR "Mike Rossiter")
set(PKG_IS_OPEN_SOURCE "yes")
set(PKG_HOMEPAGE https://github.com/Rasbats/obababel_pi)
set(PKG_INFO_URL https://opencpn.org/OpenCPN/plugins/obababel.html)

set(SRC
            src/obabel_pi.h
            src/obabel_pi.cpp           
            src/obabelUIDialogBase.cpp
            src/obabelUIDialogBase.h
            src/obabelUIDialog.cpp
            src/obabelUIDialog.h
            src/icons.h
            src/icons.cpp
)

set(PKG_API_LIB api-16)  #  A directory in libs/ e. g., api-17 or api-16

macro(late_init)
  # Perform initialization after the PACKAGE_NAME library, compilers
  # and ocpn::api is available.
  if (OBABEL_USE_SVG)
    target_compile_definitions(${PACKAGE_NAME} PUBLIC OBABEL_USE_SVG)
  endif ()
endmacro ()

macro(add_plugin_libraries)
  # Add libraries required by this plugin
  add_subdirectory("libs/tinyxml")
  target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)

  add_subdirectory("libs/wxJSON")
  target_link_libraries(${PACKAGE_NAME} ocpn::wxjson)

  add_subdirectory("libs/plugingl")
  target_link_libraries(${PACKAGE_NAME} ocpn::plugingl)

  add_subdirectory("libs/jsoncpp")
  target_link_libraries(${PACKAGE_NAME} ocpn::jsoncpp)
endmacro ()
