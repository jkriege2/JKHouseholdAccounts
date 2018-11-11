# Project: JKHouseholdAccounts (https://github.com/jkriege2/JKHouseholdAccounts)
# Copyright (c) 2018, Jan Krieger <jan@jkrieger.de>
#
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# Configure the installer scripts
configure_file(installer.cmake.nsi ${CMAKE_BINARY_DIR}/installer.nsi @ONLY)

# Compiler Runtime DLLs
if (MSVC)
  # Visual Studio
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP true)
  include(InstallRequiredSystemLibraries)
  install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION .)
else()
  # MinGW
  get_filename_component(MINGW_DLL_DIR ${CMAKE_CXX_COMPILER} PATH)
  install(FILES
    ${MINGW_DLL_DIR}/libatomic-1.dll
    ${MINGW_DLL_DIR}/libgcc_s_dw2-1.dll
    ${MINGW_DLL_DIR}/libstdc++-6.dll
    ${MINGW_DLL_DIR}/libwinpthread-1.dll
    DESTINATION .
  )
endif()

# Qt Libraries
get_target_property(QtCore_LOCATION Qt5::Core LOCATION)
get_filename_component(QT_DLL_DIR ${QtCore_LOCATION} PATH)
install(FILES
#  ${QT_DLL_DIR}/icudt51.dll
#  ${QT_DLL_DIR}/icuin51.dll
#  ${QT_DLL_DIR}/icuuc51.dll
  ${QT_DLL_DIR}/Qt5Core.dll
  ${QT_DLL_DIR}/Qt5Gui.dll
  ${QT_DLL_DIR}/Qt5Widgets.dll
  ${QT_DLL_DIR}/Qt5PrintSupport.dll
  ${CMAKE_SOURCE_DIR}/installer_win/qt.conf
  ${CMAKE_SOURCE_DIR}/LICENSE.txt
  DESTINATION .
)
# Qt Platform Plugin
install(FILES
  ${QT_DLL_DIR}/../plugins/platforms/qwindows.dll
  DESTINATION plugins/platforms
)
# Qt SQL Plugin
install(FILES
  ${QT_DLL_DIR}/../plugins/sqldrivers/qsqlite.dll
  DESTINATION plugins/sqldrivers
)
# Qt PrintSupport Plugin
install(FILES
  ${QT_DLL_DIR}/../plugins/printsupport/windowsprintersupport.dll
  DESTINATION plugins/printsupport
)
# License
install(FILES

  DESTINATION .
)
