const net = require('net');

// Connect to QEMU's serial port over TCP
const client = net.createConnection({ port: 1234 }, () => {
    console.log('Connected to ESP32 emulator');
});

// Handle incoming data
client.on('data', (data) => {
    console.log(data);
});

client.on('error', (err) => {
    console.error('Connection error:', err);
});

client.on('close', () => {
    console.log('Connection closed');
});