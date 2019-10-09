#include <cstdint>
#include "L1_Peripheral/lpc40xx/gpio.hpp"
#include "utility/log.hpp"
#include "utility/time.hpp"

class Bus {
    public:
        enum class ControlType {
            kMemory = 0,
            kIO
        };
        
        void Initialize() {
            //Setting each pin as Open Drain
            ad[0].GetPin().SetAsOpenDrain();
            ad[1].GetPin().SetAsOpenDrain();
            ad[2].GetPin().SetAsOpenDrain();
            ad[3].GetPin().SetAsOpenDrain();
            ad[4].GetPin().SetAsOpenDrain();
            ad[5].GetPin().SetAsOpenDrain();
            ad[6].GetPin().SetAsOpenDrain();
            ad[7].GetPin().SetAsOpenDrain();
            //Do the rest yourself...
            
            //To disable Open drain do the following:
            //  ad[0].GetPin().SetAsOpenDrain(false);
            //  ad[1].GetPin().SetAsOpenDrain(false);
            //  ad[2].GetPin().SetAsOpenDrain(false);
            //  ad[3].GetPin().SetAsOpenDrain(false);
            //  ad[4].GetPin().SetAsOpenDrain(false);
            //  ad[5].GetPin().SetAsOpenDrain(false);
            //  ad[6].GetPin().SetAsOpenDrain(false);
            //  ad[7].GetPin().SetAsOpenDrain(false);

            //Do the rest of the set up here...
            //
            write_enable.SetAsOutput();
            ale.SetAsOutput();
            m_io.SetAsOutput();
            interrupt.SetAsInput();
        }
        
        void Write(ControlType control, uint8_t address, uint8_t data) {
			ale.SetHigh();
			m_io.SetLow();
			write_enable.SetHigh();
			
			//Write address onto pins
			for (int i = 0; i < 8; i++) {
				ad[i].SetAsOutput();
				
				uint8_t bit = address & 1;
				
				if (bit) {
					ad[i].SetHigh();
				} else {
					ad[i].SetLow();
				}
				address >>= 1;
			}
			
			ale.SetLow();
			m_io.SetHigh();
			
			
			//Write data onto pints
			for (int i = 0; i < 8; i++) {
				uint8_t bit = data & 1;
				
				if (bit) {
					ad[i].SetHigh();
				} else {
					ad[i].SetLow();
				}
				data >>= 1;
			}
			
			m_io.SetLow();
        }
        
        uint8_t Read(ControlType control, uint8_t address) {
            ale.SetHigh();
			m_io.SetLow();
			write_enable.SetHigh();
			
			//Write address onto pins
			for (int i = 0; i < 8; i++) {
				ad[i].SetAsOutput();
				uint8_t bit = address & 1;
				
				if (bit) {
					ad[i].SetHigh();
				} else {
					ad[i].SetLow();
				}
				
				address >>= 1;
			}
			
			ale.SetLow();	
			write_enable.SetLow();			
			m_io.SetHigh();
			
			//Put data on a/d pins onto unint8_t data variable
			uint8_t data = 0;
			
			for (int i = 7; i >= 0 ; i--) {
				data <<= 1;
				ad[i].SetAsInput();
				if (ad[i].Read()) {
					data += 1;
				}
				
			}
			
			//Set M/IO to High to read data
			m_io.SetLow();
			
			return data;
        }
        
    private:
        sjsu::lpc40xx::Gpio ad[8]= {
            sjsu::lpc40xx::Gpio(2, 2),
            sjsu::lpc40xx::Gpio(2, 5),
            sjsu::lpc40xx::Gpio(2, 7),
            sjsu::lpc40xx::Gpio(2, 9),
            sjsu::lpc40xx::Gpio(0, 15),
            sjsu::lpc40xx::Gpio(0, 18),
            sjsu::lpc40xx::Gpio(0, 1),
            sjsu::lpc40xx::Gpio(0, 10),
        };
            
        //The gpio below will be used in Lab 4
        sjsu::lpc40xx::Gpio write_enable = sjsu::lpc40xx::Gpio(0, 17);
        sjsu::lpc40xx::Gpio ale = sjsu::lpc40xx::Gpio(0, 22);
        sjsu::lpc40xx::Gpio m_io = sjsu::lpc40xx::Gpio(0, 0);
        sjsu::lpc40xx::Gpio interrupt = sjsu::lpc40xx::Gpio(0, 11);
};
