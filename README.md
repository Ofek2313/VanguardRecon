# VanguardRecon

A local network port scanner built in C++ for Linux.

## About

VanguardRecon is a command-line tool for scanning open ports and discovering active hosts on your local network. It uses raw Linux sockets to perform TCP port scanning and host discovery without any external dependencies.

> **Disclaimer:** This tool is intended for personal and educational use only. Only scan networks and devices you own or have explicit permission to test.

## Features

- TCP port scanning across a configurable port range
- Local network host discovery
- Banner grabbing from open ports
- No external libraries required — built on standard Linux socket APIs

## Requirements

- Linux
- g++ with C++17 support

## Building

```bash
g++ -std=c++17 vanguard.cpp scanner.cpp HostDiscovery.cpp -o vanguard
```

## Usage

```bash
./vanguard <target-ip>
```

Example:

```bash
./vanguard 192.168.1.1
```

By default, the scanner checks ports 1 through 1000 on the target host and performs a local network scan.

## Project Structure

```
VanguardRecon/
├── vanguard.cpp          # Entry point
├── scanner.h / .cpp      # Port scanning logic
├── HostDiscovery.h / .cpp # Local network host discovery
└── Network/              # Additional networking utilities
```

## License

This project is unlicensed. For personal and educational use only.
