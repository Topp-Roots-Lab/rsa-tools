# RSA-Tools

This repo contains scripts used along side the [RSA-GiA](https://github.com/Topp-Roots-Lab/rsa-gui) suite of tools to analyze root system architectures. Currently, there are two Python scripts that complete a task, and each has a corresponding C++ script used to set a uid for each respectively.

Due to user and group restrictions, it's necessary to elevate the priveleges and set a uid for these scripts. However, since Linux now ignores the setuid on all interpreted executables for security reasons, we have to use a binary file to perform the setuid. Addtional information can be found here: https://unix.stackexchange.com/a/2910

## FileHandlers

This script renames a directory in the original_images folder.

## Analysis

Contains the binaries and scripts for each component run by [RSA-GiA](https://github.com/Topp-Roots-Lab/rsa-gui).

These include,
* GiaRoots (a.k.a., Gia2D)
* Reconstruction & Skeleton (RootworkPers)
* File management scripts
* Quality control scripts

## Importer

This script creates the directory subtree in the original_images folder, which corresponds the names of the files located in some directory. It's primary function is to move image sets into a designated folder for the next steps in processing.

### Installation

When installing a new instance of RSA-GiA, you will need to include these as well.
`rsa-mv2orig-launcher.cpp` sets the uid when executing `rsa-mv2orig.py`.
`rsa-renameorig-launcer.cpp` sets the uid when executing `rsa-renameorig.py`.

Both C++ scripts include hardcoded locations for the Python scripts that they execute. **Remember to recompile the respective script if you change these locations.**

Ideally, compile the C++ script(s) on the system that will be executing them. Below is an example of how to compile the rsa-mv2orig-launcher on Ubuntu or CentOS in terminal.

```bash
g++ rsa-mv2orig-launcher.cpp -o rsa-mv2orig-launcher
```