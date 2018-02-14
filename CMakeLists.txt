cmake_minimum_required (VERSION 2.6)
project (iso-tp)
add_library(iso-tp SHARED iso-tp.cpp)
set_target_properties(iso-tp PROPERTIES PUBLIC_HEADER "iso-tp.h")

install (TARGETS iso-tp
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         PUBLIC_HEADER DESTINATION include
         RUNTIME DESTINATION bin)
