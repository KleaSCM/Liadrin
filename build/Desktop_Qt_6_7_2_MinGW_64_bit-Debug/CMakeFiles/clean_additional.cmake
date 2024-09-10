# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Liadrin_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Liadrin_autogen.dir\\ParseCache.txt"
  "Liadrin_autogen"
  )
endif()
