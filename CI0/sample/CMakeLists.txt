
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_executable(sample
  ${SOURCES}
  )

target_link_libraries(sample PUBLIC sfml-graphics)
