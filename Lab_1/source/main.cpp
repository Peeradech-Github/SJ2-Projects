#include "Bus.hpp"
#include <cstdint>
#include "utility/log.hpp"
#include "utility/time.hpp"
#include "L1_Peripheral/lpc40xx/gpio.hpp"

int main()
{
    Bus::ControlType control = Bus::ControlType::kMemory;
    uint8_t address, data;
    address = 0b10011001;
    data = 0b10011001;
    Bus bus;


       
    sjsu::Delay(10s);
    bus.Initialize();

   
    LOG_INFO("writing data to SRAM 0, [data %b at address %b]", data, address);
    bus.Write(control, address, data);
    LOG_INFO("Data Wrote to SRAM0 at address %b", address);


    sjsu::Delay(30s);
    address = 0b11101110;
    data = 0b11101110;

    LOG_INFO("writing data to SRAM 1, [data %b at address %b]", data, address);
    bus.Write(control, address, data);
    LOG_INFO("Data Wrote to SRAM1 at address %b", address);

   

    sjsu::Delay(30s);
    address = 0b010011001;
    LOG_INFO("reading data from SRAM 0, [data %b at address %b]", data, address);
    bus.Read(control, address);
    LOG_INFO("Data Wrote to SRAM0 is:%b", data);

    sjsu::Delay(30s);
    address = 0b11101110;
    LOG_INFO("reading data from SRAM 1, [data %b at address %b]", data, address);
    bus.Read(control, address);
    LOG_INFO("Data Wrote to SRAM1 is:%b", data);




   
