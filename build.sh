rm bin -r -f
cmake -DCMAKE_C_COMPILER=emcc -DCMAKE_CXX_COMPILER=em++ -DWEB_ASM=ON -S ./ -B ./bin
cmake --build ./bin -j$(nproc)
