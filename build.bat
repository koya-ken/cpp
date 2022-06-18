@echo off
cmake -B build . -A x64 -DCMAKE_INSTALL_PREFIX=install
cmake --build build --target install --config Release