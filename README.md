# ESP32 on QEMU

This guide provides step-by-step instructions to set up and run an ESP-IDF project for ESP32 using QEMU (an emulator for ESP32).  You can develop and test ESP32 applications without actual hardware.

## Features
- Complete ESP32 emulation.
- BMP280 emulation.

## Setup Instructions

### Prerequisites
- ESP-IDF installed (`export.sh` sourced)
- QEMU installed (for emulation)

### Steps to Build and Run

#### **1. Create Project (If Not Done)**
```bash
idf.py create-project esp32_counter
cd esp32_counter
```
#### **2. Write Main Code**
Modify `main/esp32_counter.c` and add the counter logic.

#### **3. Create Project**
Build the Project
```bash
idf.py build
```
#### **4. Run on Hardware**
```bash
idf.py flash
idf.py monitor
```
#### **5. Run on QEMU**
Merge binaries:
```bash
esptool.py --chip esp32 merge_bin -o flash_image.bin --flash_mode dio --flash_size 4MB \
    0x1000 build/bootloader/bootloader.bin \
    0x8000 build/partition_table/partition-table.bin \
    0x10000 build/esp32_counter.bin
```

Run in QEMU:
```bash
qemu-system-xtensa -nographic -machine esp32 \
    -drive file=flash_image.bin,if=mtd,format=raw
```

In case your `flash_image.bin` is less than 4.0MB you will have to run:
```bash
truncate -s 4M flash_image.bin
```

verify the size of `flash_image.bin` using:
```bash
ls -lh flash_image.bin
```

Then re-run using QEMU


#### **6. Print data on serial port? `(hack)`**
Modify QEMU command - Update your QEMU command to expose the serial port via TCP:
```bash
qemu-system-xtensa -nographic -machine esp32 \
    -drive file=flash_image.bin,if=mtd,format=raw \
    -serial tcp::1234,server,nowait
```
This makes QEMU listen on TCP port 1234 for serial connections.


#### **7. Read on serial port using JS**
Create a Node.js script to read from the TCP port:
```javascript
const net = require('net');

// Connect to QEMU's serial port over TCP
const client = net.createConnection({ port: 1234 }, () => {
    console.log('Connected to ESP32 emulator');
});

// Handle incoming data
client.on('data', (data) => {
    console.log(data.toString());
});

client.on('error', (err) => {
    console.error('Connection error:', err);
});

client.on('close', () => {
    console.log('Connection closed');
});
```