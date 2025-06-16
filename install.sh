#!/bin/bash

set -e
APP_NAME="loggr"
INSTALL_DIR="/usr/local/bin" DATA_DIR="$HOME/.local/share/$APP_NAME"

REPO_URL="https://github.com/user-forty-seven/loggr.git"
REPO_DIR="$(mktemp -d loggr_XXXX)"

# colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # no color

if [ -z "$BASH_VERSION" ]; then
  echo "${YELLOW}Please run this script with bash${NC}"
  exit 1
fi


check_nlohmann_installed() {
    echo -e "${BLUE}Checking for nlohmann/json...${NC}"
    echo '#include <nlohmann/json.hpp>
    int main() { return 0; }' | g++ -std=c++11 -x c++ -o /dev/null - >/dev/null 2>&1
}

install_nlohmann() {
    if command -v apt &>/dev/null; then
        sudo apt install -y nlohmann-json3-dev
    elif command -v dnf &>/dev/null; then
        sudo dnf install -y nlohmann-json-devel
    elif command -v pacman &>/dev/null; then
        sudo pacman -S --noconfirm nlohmann-json
    elif command -v zypper &>/dev/null; then
        sudo zypper install -y nlohmann_json-devel
    elif command -v brew &>/dev/null; then
        brew install nlohmann-json
    else
        echo -e "${RED}Unsupported package manager. Please install nlohmann/json manually.${NC}"
        exit 1
    fi
}

check_tools() {
  for cmd in g++ cmake make git; do
      if ! command -v $cmd &>/dev/null; then
          echo -e "${RED}Error: $cmd is not installed.${NC}"
          exit 1
      fi
  done
}

clone_and_build_repo() {

    check_tools 

    echo -e "${BLUE}Cloning repository...${NC}"
    if ! git clone "$REPO_URL" "$REPO_DIR"; then
        echo -e "${RED}Failed to clone repository. Exiting.${NC}"
        exit 1
    fi

    cd "$REPO_DIR" || {
        echo -e "${RED}Failed to enter repository directory.${NC}"
        exit 1
    }

    echo -e "${BLUE}Building project with CMake...${NC}"
    mkdir -p build && cd build

    if ! cmake ..; then
        echo -e "${RED}CMake configuration failed. Exiting.${NC}"
        exit 1
    fi

    if ! make -j"$(nproc)"; then
        echo -e "${RED}Build failed during 'make'. Exiting.${NC}"
        exit 1
    fi

    echo -e "${GREEN}Build completed successfully!${NC}"
}

main() {
    check_nlohmann_installed || install_nlohmann
    clone_and_build_repo
    # install the binary
    echo -e "${BLUE}Installing to $INSTALL_DIR. Please allow sudo permissions${NC}"
    sudo true
    sudo make install
    sudo chmod +x "$INSTALL_DIR/$APP_NAME"
    
    # make room for data
    mkdir -p "$DATA_DIR"

    echo -e "${GREEN}Installation complete!${NC}"
    rm -rf "$REPO_DIR"
    echo -e "${YELLOW}ps, you can cleanly delete it anytime by running the uninstall script *wink*${NC}"
}

main
