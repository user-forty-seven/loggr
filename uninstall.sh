#!/bin/bash

set -e # exit on error

APP_NAME="loggr"
INSTALL_DIR="/usr/local/bin"
DATA_DIR="$HOME/.local/share/$APP_NAME"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # no Color

echo -ne "${YELLOW}Are you sure that you want to delete loggr? (y/n): ${NC}"
read confirm
confirm=${confirm,,}  # convert to lowercase
confirm=$(echo "$confirm" | xargs | tr '[:upper:]' '[:lower:]')

if [[ "$confirm" != "y" ]]; then
    echo -e "${RED}Uninstallation cancelled.${NC}"
    exit 0
fi

echo -e "${BLUE}Starting uninstallation... Please allow sudo permissions.${NC}"

sudo true


if [ -f "$INSTALL_DIR/$APP_NAME" ]; then
    sudo rm -f "$INSTALL_DIR/$APP_NAME"
    echo -e "${GREEN}Binary removed.${NC}"
else
    echo -e "${YELLOW}Binary not found at $INSTALL_DIR/$APP_NAME.${NC}"
    exit 1;
fi

if [ -d "$DATA_DIR" ]; then
    rm -rf "$DATA_DIR"
    echo -e "${GREEN}Data directory removed.${NC}"
else
    echo -e "${YELLOW}Data directory not found at $DATA_DIR.${NC}"
fi


echo -ne "${YELLOW}Would you like us to attempt to uninstall the nlohmann/json from your system? (y/n): ${NC}"
read response
response=${response,,}  # convert to lowercase
response=$(echo "$response" | xargs | tr '[:upper:]' '[:lower:]')

if [[ "$response" == "y" ]]; then
    echo -e "${BLUE}Detecting package manager...${NC}"

    if command -v apt &>/dev/null; then
        sudo apt remove -y nlohmann-json3-dev
    elif command -v dnf &>/dev/null; then
        sudo dnf remove -y json-devel
    elif command -v pacman &>/dev/null; then
        sudo pacman -R --noconfirm nlohmann-json
    elif command -v zypper &>/dev/null; then
        sudo zypper remove -y nlohmann_json-devel
    elif command -v brew &>/dev/null; then
        brew uninstall nlohmann-json
    else
        echo -e "${RED}Could not detect a supported package manager. Please uninstall manually if needed.${NC}"
    fi
else
    echo -e "${YELLOW}Keeping system package nlohmann/json as is.${NC}"
fi

echo -e "${GREEN}Uninstallation complete! Have a great day!${NC}"
