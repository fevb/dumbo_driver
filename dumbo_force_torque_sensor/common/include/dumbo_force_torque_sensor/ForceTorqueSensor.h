/*
 *  ForceTorqueSensor.h
 *
 *  Created on: Aug 3, 2012
 *  Authors:   Francisco Viña 
 *            fevb <at> kth.se
 */

/* Copyright (c) 2012, Francisco Vina, CVAP, KTH
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of the KTH nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL KTH BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef FORCETORQUESENSOR_H_
#define FORCETORQUESENSOR_H_

#include <string>
#include <kvaser_canlib/canlib.h>
#include <geometry_msgs/Wrench.h>
#include <geometry_msgs/WrenchStamped.h>
#include <pthread.h>
#include <dumbo_force_torque_sensor/ft_sensor_function.h>
#include <eigen3/Eigen/Core>


class ForceTorqueSensor {

public:
	// ArmSelect can be either 'left' or 'right'
	ForceTorqueSensor(std::string Serial_Number,
			std::string ArmSelect);

	virtual ~ForceTorqueSensor();

	// initialize and connect to the sensor
	bool Init();

	// disconnect from the CAN bus
	void Disconnect();

	bool isInitialized()
	{
		return (m_Initialized);
	}

	// get the raw F/T measurement
	bool Get_ft(geometry_msgs::Wrench &ft_raw);

protected:
	pthread_mutex_t m_CAN_mutex;
	canHandle m_DeviceHandle;
	int m_CAN_Channel;
	bool m_Initialized;
	bool m_CANDeviceOpened;


	std::string m_SerialNumber;
	std::string m_ArmSelect;
	std::string m_sensor_frame_id;


	float m_Calibration_Matrix[6][6];
};

#endif /* FORCETORQUESENSOR_H_ */
