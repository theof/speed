`sudo apt install libsdl2-dev libsdl2-doc libsdl2-2.0-0`

```bash
mkdir build
```
```bash
cd build &&
cmake -DCMAKE_BUILD_TYPE=Debug ..   OR  cmake -DCMAKE_BUILD_TYPE=Release .. &&
make &&
./speed
```
