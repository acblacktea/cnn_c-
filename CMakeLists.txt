INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/inc/")
add_executable(test test.cpp
              ${PROJECT_SOURCE_DIR}/src/activation.cpp
              ${PROJECT_SOURCE_DIR}/src/cNN_block.cpp
              ${PROJECT_SOURCE_DIR}/src/connect_block.cpp
              ${PROJECT_SOURCE_DIR}/src/flatten.cpp
              ${PROJECT_SOURCE_DIR}/src/loss.cpp
              ${PROJECT_SOURCE_DIR}/src/Matrix.cpp
              ${PROJECT_SOURCE_DIR}/src/nerual_block.cpp
              ${PROJECT_SOURCE_DIR}/src/network.cpp
              ${PROJECT_SOURCE_DIR}/src/pool.cpp
              ${PROJECT_SOURCE_DIR}/src/save.cpp
              )
