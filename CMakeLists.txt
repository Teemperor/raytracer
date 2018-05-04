cmake_minimum_required(VERSION 3.10)
project(raytracer)

set(CMAKE_CXX_STANDARD 11)

find_package( Threads )

find_package(SFML COMPONENTS graphics window system)

if(NOT SFML_FOUND)
  include_directories($ENV{SFML_INC})
  link_directories($ENV{SFML_LIB})
  set(SFML_LIBRARIES sfml-audio sfml-graphics sfml-window sfml-system)
else()
  include_directories(${SFML_INCLUDE_DIR})
endif()

add_executable(raytracer main.cpp lib/Object.cpp lib/Object.h lib/Ray.cpp lib/Ray.h lib/Sphere.cpp lib/Sphere.h lib/Level.cpp lib/Level.h lib/Vec3.cpp lib/Vec3.h lib/Plane.cpp lib/Plane.h lib/Circle.cpp lib/Circle.h lib/Color.cpp lib/Color.h lib/Hit.cpp lib/Hit.h lib/Raytracer.cpp lib/Raytracer.h lib/Light.cpp lib/Light.h lib/PointLight.cpp lib/PointLight.h lib/TextureRect.cpp lib/TextureRect.h)
target_link_libraries(raytracer ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})