cmake_minimum_required(VERSION 3.10)

# Proje adını belirleyin
project(LaserControl)

# C++ standardını ayarlayın
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Seri kütüphanesi için include dizinini belirtin
include_directories(/usr/local/include)

# Seri kütüphanesi için library dizinini belirtin
link_directories(/usr/local/lib)

# Ana kaynak dosyasını ekleyin
add_executable(LaserControl main.cpp)

# Seri kütüphanesi ile bağlantı kurun
target_link_libraries(LaserControl serial)
