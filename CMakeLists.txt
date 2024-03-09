cmake_minimum_required(VERSION 3.8)
project(Stream)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTLIBS REQUIRED
    gobject-2.0
    glib-2.0
    gstreamer-webrtc-1.0
    gstreamer-sdp-1.0
    gstreamer-pbutils-1.0
    gstreamer-rtsp-server-1.0
    gstreamer-check-1.0
)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

include_directories(
    /usr/lib/x86_64-linux-gnu/glib-2.0/include
    /usr/include/glib-2.0
    /usr/local/include/gstreamer-1.0
    /usr/local/include/libsoup-2.4
    /usr/local/include/json-glib-1.0
    /usr/include/gstreamer-1.0
)

set(CAM_FILES CamStreamer.cpp)
set(SCREEN_FILES ScreenStreamer.cpp)

link_directories(${GSTLIBS_LIBRARY_DIRS})

add_executable(CamStreamer ${CAM_FILES})
add_executable(ScreenStreamer ${SCREEN_FILES})

target_link_libraries(CamStreamer ${GSTLIBS_LIBRARIES})
target_link_libraries(ScreenStreamer ${GSTLIBS_LIBRARIES})