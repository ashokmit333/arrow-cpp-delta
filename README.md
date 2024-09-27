# arrow-cpp-delta

Writing delta table from cpp using cython

Steps for Arrow Lib Set-Up:
Step 1:
git clone https://github.com/apache/arrow.git
Setp 2:
Mac: brew update && brew bundle --file=arrow/cpp/Brewfile
Linux: sudo apt-get install build-essential cmake python3-dev
Step 3:
python3 -m venv pyarrow-dev
source ./pyarrow-dev/bin/activate
pip install -r arrow/python/requirements-build.txt

    # This is the folder where we will install the Arrow libraries during
    # development
    mkdir dist
    export ARROW_HOME=$(pwd)/dist
    export LD_LIBRARY_PATH=$(pwd)/dist/lib:$LD_LIBRARY_PATH
    export CMAKE_PREFIX_PATH=$ARROW_HOME:$CMAKE_PREFIX_PATH
    export ARROW_BUILD_TYPE=release

Step 4: Install arrow cpp
cmake -S arrow/cpp -B arrow/cpp/build \
 -DCMAKE_INSTALL_PREFIX=$ARROW_HOME \
            --preset ninja-release-python
    cmake --build arrow/cpp/build --target install
Step 5: Install pyarrow
    pushd arrow/python
    export PYARROW_PARALLEL=4
    python setup.py build_ext --build-type=$ARROW_BUILD_TYPE \
 --bundle-arrow-cpp bdist_wheel
pip install the wheel created in python\dist folder

Step 6:add the venv folder python path
