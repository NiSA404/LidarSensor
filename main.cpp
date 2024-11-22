#include <iostream>
#include <serial/serial.h>
#include <vector>
#include <iomanip>

uint8_t calculateChecksum(const std::vector<uint8_t>& packet) {
    uint8_t sum = 0;
    for (size_t i = 2; i < packet.size() - 3; ++i) {
        sum += packet[i];
    }
    return sum;
}

void sendPacket(serial::Serial& laser, const std::vector<uint8_t>& packet) {
    laser.write(packet);
}

std::vector<uint8_t> readPacket(serial::Serial& laser) {
    std::vector<uint8_t> response(256);
    size_t bytes_read = laser.read(response, response.size());
    response.resize(bytes_read);
    return response;
}

int main() {
    try {
        // Seri portu açma
        serial::Serial laser("/dev/tty.usbserial-XXXXX", 9600, serial::Timeout::simpleTimeout(1000));

        if(laser.isOpen()) {
            std::cout << "Port başarıyla açıldı." << std::endl;
        } else {
            std::cerr << "Port açılmadı." << std::endl;
            return 1;
        }

        // Tek Ölçüm Komutu Gönderme
        std::vector<uint8_t> single_measurement_command = {0xAE, 0xA7, 0x04, 0x00, 0x05, 0x09, 0xBC, 0xBE};
        sendPacket(laser, single_measurement_command);

        // Cevap Okuma
        std::vector<uint8_t> response = readPacket(laser);

        // Cevabı Yazdırma
        std::cout << "Cevap: ";
        for (auto byte : response) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;

        laser.close();
    } catch (const serial::IOException& e) {
        std::cerr << "Seri port açma hatası: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
