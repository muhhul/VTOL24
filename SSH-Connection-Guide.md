# SSH Connection Guide

## Introduction
This guide explains how to connect from an Ubuntu Intel NUC (server) to an Ubuntu laptop (client) using SSH. It includes installation steps, connection commands, and troubleshooting tips.

## Prerequisites
- Both machines are connected to the same WiFi network.
- SSH is installed on both machines.
- You have basic command-line knowledge.

## Steps

### 1. Install SSH
Ensure SSH is installed on both machines.

**On the Ubuntu Intel NUC (Server):**
```
sudo apt update
sudo apt install openssh-server
```

**On the Ubuntu Laptop (Client):**

```
sudo apt update
sudo apt install openssh-client
```

**Verify SSH installation:**

```
ssh -V
```

### 2. Find IP Address of Intel NUC
On the Intel NUC, open a terminal and run:

```
hostname -I
```
Note the IP address (e.g., 192.168.252.2).

### 3. Configure SSH on the Intel NUC
Ensure the SSH service is running:

```
sudo systemctl start ssh
sudo systemctl enable ssh
sudo systemctl status ssh
```

### 4. Connect via SSH
On the Ubuntu Laptop, open a terminal and run:

```
ssh username@192.168.252.2
```
Replace username with the actual username of the Intel NUC (vtol2022) and 192.168.252.2 with the Intel NUC's IP address.

### 5. Authentication
If prompted, confirm the authenticity of the host by typing yes.

Enter the password for the specified user on the Ubuntu laptop.

### 6. Using SSH
Once connected, you can navigate the filesystem, manage files, run programs, and perform system administration tasks on the Ubuntu laptop.

Common Commands
List directory contents: ```ls```

Change directory: ```cd <directory>```

Print working directory: ```pwd```

Copy files: ```cp <source> <destination>```

Move/rename files: ```mv <source> <destination>```

Remove files: ```rm <file>```

Create directory: ```mkdir <directory>```

Edit files: ```nano <file> or vim <file>```

Update packages: ```sudo apt update```

Upgrade packages: ```sudo apt upgrade```

Manage services: ```sudo systemctl <command>```

### 7. Exiting SSH
To close the SSH session, type:

```
exit
```
