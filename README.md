# loggr

## ...is a personal command line organiser which helps you log tasks and manage them accordingly


## Installation
You can install `loggr` via this command:

```bash
bash <(curl -s https://raw.githubusercontent.com/user-forty-seven/loggr/refs/heads/main/install.sh)
```

## Uninstallation:
Similar to the installation part, you can uninstall `loggr` via this command:

```bash
bash <(curl -s https://raw.githubusercontent.com/user-forty-seven/loggr/refs/heads/main/uninstall.sh)
```

### Building the project
Requires:
 - a C++17-compatible compiler
 - git
 - make
 - cmake 
 - nlohmann/json library

```
git clone https://github.com/user-forty-seven/loggr.git
cd loggr
mkdir build 
cd build
cmake ..
make 
```

To install globally:

```
sudo make install
```


> **Note.**
> loggr is supported only on Linux and Unix-like systems as of now.

## Third-Party Libraries
This project makes use of the following open-source library:
- [nlohmann/json](https://github.com/nlohmann/json) - JSON for Modern C++
