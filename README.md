# loggr

## ...is a personal command line organiser which helps you log tasks and manage them accordingly

- Add, edit, and delete tasks
- List taks 
- Mark and unmark tasks
- Clear tasks

```bash
loggr <command> [subcommand] [args...]

# Task Management Commands

loggr add task "<description>"               
# Add a new task with the given description

loggr edit task <task_id> "<new description>" 
# Edit the task with the given ID

loggr remove task <task_id>                  
# Remove the task with the specified ID

loggr clear tasks all                        
# Delete ALL tasks (asks for confirmation)

loggr clear tasks completed                  
# Delete only tasks that are marked as completed


# Task Listing Commands

loggr list tasks                             
# List all tasks (completed + uncompleted)

loggr list tasks marked                      
# List only completed (marked) tasks

loggr list tasks unmarked                    
# List only uncompleted (unmarked) tasks


# Task Status Commands

loggr mark task <task_id>                    
# Mark a task as completed

loggr unmark task <task_id>                  
# Unmark a completed task (set it as pending)


# Utility Commands

loggr help                                   
# Show help message with all available commands

loggr info                                   
# Display general info about loggr
 
```

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
