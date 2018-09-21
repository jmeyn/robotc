#pragma config(Sensor, in1,    stopButton,     sensorAnalog)
#pragma config(Sensor, in2,    resetButton,    sensorAnalog)
#pragma config(Sensor, in3,    potentiometer,  sensorPotentiometer)
#pragma config(Motor,  port1,           hour,          tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           minute,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           second,        tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
		int servoPos;
		int count = 0;
		int pValue = 0;

		int secondSpeed;
		int minuteSpeed;
		int hourSpeed;

		long bStopButton;
		long bResetButton;
		long bPotentiometer;

		bool running = true;

		while( true )
		{
				//check sensors
				bStopButton = SensorValue[stopButton];
				bResetButton = SensorValue[resetButton];
				bPotentiometer = SensorValue[potentiometer];

				//logic/decisions
				pValue = (((int)((bPotentiometer / 4095.0) * 100.0)) - 50); //range is [-50, 50]
				minuteSpeed = 80 + pValue;
				hourSpeed = (int)(minuteSpeed / 2.0);
				secondSpeed = 100 - (int)(pValue * 1.5);

				count++;
				  //Second speed (count = 0.01 of a second)
				if(count >= secondSpeed)
			  {
						count = 0;

						if(servoPos == 40)
						{
								servoPos = -70;
						}
						else
						{
								servoPos = 40;
						}
				}

				if(bStopButton == false)
				{
						running = false;
				}

				if(bResetButton == false)
				{
						running = true;
				}

				//Set Motors
				if(running)
				{
						motor[second] = servoPos;
						motor[minute] = minuteSpeed;
						motor[hour] = hourSpeed;
				}
				else
				{
						motor[second] = 0;
						motor[minute] = 0;
						motor[hour] = 0;
				}

				//delay !!!NEVER CHANGE!!!
				wait1Msec(10);
		}
}
