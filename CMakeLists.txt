cmake_minimum_required (VERSION 2.6)
project (iso-tp)
add_library(iso-tp iso-tp.cpp)

install (TARGETS iso-tp
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)
