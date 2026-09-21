# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Serpiente_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Serpiente_autogen.dir/ParseCache.txt"
  "Serpiente_autogen"
  )
endif()
