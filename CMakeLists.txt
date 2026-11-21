cmake_minimum_required(VERSION 3.16)
project(ssocks VERSION 0.0.17 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT MSVC)
  add_compile_options(-Wall -Wextra)
endif()

include_directories(. src)

set(SSOCKS_LIBSOURCES
  src/libsocks/bor-util.c
  src/libsocks/client.c
  src/libsocks/log-util.c
  src/libsocks/net-util.c
  src/libsocks/output-util.c
  src/libsocks/socks-common.c
  src/libsocks/socks4.c
  src/libsocks/socks5-client.c
  src/libsocks/socks5-server.c
  src/libsocks/ssl-util.c
  src/configd-util.c
  src/auth-util.c
)

if(WIN32)
  list(APPEND SSOCKS_LIBSOURCES src/win_getopt.c)
  link_libraries(ws2_32)
endif()

foreach(tool ssocks ssocksd nsocks rcsocks rssocks)
  add_executable(${tool} src/${tool}.c ${SSOCKS_LIBSOURCES})
  install(TARGETS ${tool} RUNTIME DESTINATION bin)
endforeach()
