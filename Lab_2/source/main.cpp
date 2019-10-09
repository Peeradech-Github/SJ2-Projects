#include "Bus.hpp"
#include <cstdint>
#include "utility/log.hpp"
#include "utility/time.hpp"
#include "L1_Peripheral/lpc40xx/gpio.hpp"

int main() {
    Bus::ControlType control = Bus::ControlType::kMemory;
    uint8_t address, data, result;
    address = 0b10100010;
    data = 0b10000110;
    Bus bus;
	
    bus.Initialize();
   
    LOG_INFO("writing data to SRAM, [data %08b at address %08b]", data, address);
    bus.Write(control, address, data);
    LOG_INFO("Data Wrote to SRAM at address %08b", address);
	
    LOG_INFO("reading data from SRAM, [address %08b]", address);
    result = bus.Read(control, address);
    LOG_INFO("Data Read to SRAM is:%08b", result);
   
    return 0;
}





   
