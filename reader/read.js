const net = require('net');

let buffer = '';

const client = net.createConnection({ port: 1234 }, () => {
    console.log('Connected to ESP32 emulator');
});

client.on('data', (data) => {
    buffer += data.toString();
    
    const lines = buffer.split(/\r?\n/);
    
    buffer = lines.pop() || '';
    
    lines.forEach(line => {
        if (line.trim()) {  
            console.log(line);
        }
    });
});

client.on('error', (err) => {
    console.error('Connection error:', err);
});

client.on('close', () => {
    if (buffer) console.log(buffer); 
    console.log('Connection closed');
});