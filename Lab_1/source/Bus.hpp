#include <cstdint>

#include "L1_Peripheral/lpc40xx/gpio.hpp"
#include "utility/log.hpp"
#include "utility/time.hpp"

class
Bus
	{

	public:
	enum

	class ControlType
	{
		kMemory = 0,
		kIO
	};

	void Initialize()
	{
		//Setting each pin as Open Drain

		ad[0].GetPin().SetAsOpenDrain();
		ad[1].GetPin().SetAsOpenDrain();
		ad[2].GetPin().SetAsOpenDrain();
		ad[3].GetPin().SetAsOpenDrain();
		ad[4].GetPin().SetAsOpenDrain();
		ad[5].GetPin().SetAsOpenDrain();
		ad[6].GetPin().SetAsOpenDrain();
		ad[7].GetPin().SetAsOpenDrain();

		//To disable Open drain do the following:
		//ad[1].GetPin().SetAsOpenDrain(false);

		//Do the rest of the setup here...//

		write_enable.SetAsOutput();
		ale.SetAsOutput();
		m_io.SetAsOutput();
		interrupt.SetAsInput();
	}

	void Write(uint8_t address, uint8_t data) //void Write(ControlType control, uint8_t address, uint8_t data)
	{
		LOG_INFO("Address Recieved: 0x%X", address);
		LOG_INFO("Data Recieved: 0x%X", data);
		write_enable.SetHigh();
		//Set pins to output and puts address on the pins
		for (int i = 0; i <= 7; i++)
		{
			ad[i].SetAsOutput();
			if(address & (1 << i))
				ad[i].SetHigh();
			else
				ad[i].SetLow();
		}
		LOG_INFO("A/D pins set to output and address put on.");
	


		LOG_INFO("Enabling Control Pins");
		//Enable buffer and latches
		ale.SetHigh();
		sjsu::Delay(1s); //100ns is overtimed, find the actual time.
		LOG_INFO("Disabling ALE control pin");
		ale.SetLow();
		sjsu::Delay(1s);

		//Put data on the pins.
		for (int i = 0; i <= 7; i++)
		{
			ad[i].SetAsOutput();
			if(data & (1 << i))
				ad[i].SetHigh();
			else
				ad[i].SetLow();
		}
		LOG_INFO("A/D pins set to data");
	}

	uint8_t Read (uint8_t address) //uint8_t Read (ControlType control ,uint8_t address)
	{
		
		uint8_t ret = 0;
		/*
		//Set pins to output and puts address on the pins
		for (int i = 0; i <= 7; i++)
			
		{
			ad[i].SetAsOutput();
			if(address & (1 << i))
				ad[i].SetHigh();
			else
				ad[i].SetLow();
		}
		//Enable buffer and latches
		ale.SetHigh();
		write_enable.SetLow();
		sjsu::Delay(1ms); //100ns is overtimed, find the actual time.
		ale.SetLow();
		write_enable.SetHigh();
		sjsu::Delay(1ms); // To allow buffer to switch directions
		*/
		write_enable.SetHigh();
		//Put data on the pins.
		for (int i = 0; i <= 7; i++)
		{
			ad[i].SetAsInput();
			if(ad[i].Read())
				ret |= (1 << i);
		}
		
		return ret;
	}

	private:
		sjsu::lpc40xx::Gpio ad[8] ={
		sjsu::lpc40xx::Gpio(2,2),
		sjsu::lpc40xx::Gpio(2,5),
		sjsu::lpc40xx::Gpio(2,7),
		sjsu::lpc40xx::Gpio(2,9),
		sjsu::lpc40xx::Gpio(0,15),
		sjsu::lpc40xx::Gpio(0,18),
		sjsu::lpc40xx::Gpio(0,1),
		sjsu::lpc40xx::Gpio(0,10),
};

//The gpio below will be used in Lab 4
sjsu::lpc40xx::Gpio write_enable = sjsu::lpc40xx::Gpio(0,17);
sjsu::lpc40xx::Gpio ale = sjsu::lpc40xx::Gpio(0,22);
sjsu::lpc40xx::Gpio m_io = sjsu::lpc40xx::Gpio(0,0);
sjsu::lpc40xx::Gpio interrupt = sjsu::lpc40xx::Gpio(0,11);
};
