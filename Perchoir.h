/*	Handle perch figures
 *
 *	17/12/2017	First version
 */

#ifndef PERCHOIR_H
#define PERCHOIR_H

#include <SimpleDHT.h>
#include <string>

#include "Context.h"

class Perchoir {
	float temperature;
	float humidite;
	int err;
	unsigned long dernier;	// Last sample time

	Context &context;

protected :
	bool sample( void ){
		SimpleDHT22 DHT;

		err = DHT.read2(pinDHT, &this->temperature, &this->humidite, NULL);

		return( err == SimpleDHTErrSuccess );
	}

	const char *strerror( void ){
		switch( this->err ){
		case SimpleDHTErrSuccess: return "No error";
		case SimpleDHTErrStartLow: return "Error to wait for start low signal";
		case SimpleDHTErrStartHigh: return "Error to wait for start high signal";
		case SimpleDHTErrDataLow: return "Error to wait for data start low signal";
		case SimpleDHTErrDataRead: return "Error to wait for data read signal";
		case SimpleDHTErrDataEOF: return "Error to wait for data EOF signal";
		case SimpleDHTErrDataChecksum: return "Error to validate the checksum";
		case SimpleDHTErrZeroSamples: return "Both temperature and humidity are zero";
		default: return "Who know ...";
		}
	}

public :
	Perchoir( Context &ctx ) : temperature(0), humidite(0), err(SimpleDHTErrSuccess), dernier(0), context( ctx ) {
	}

	bool publishFigures( void ){
		if( millis() > this->dernier && // prevent overflow
		  this->dernier &&	// enforce 1st run
		  millis() > this->dernier + DELAY * 1e3 ){
			if( !this->sample() ){
				context.publish( MQTT_Error, this->strerror() );
#				ifdef SERIAL_ENABLED
					Serial.print("DHT.sample() :");
					Serial.println( this->strerror() );
#				endif
				return false;
			}

			String troot = MQTT_Topic + "Perchoir/";

			context.publish( (troot+"Temperature").c_str(), context.toString( this->temperature ).c_str() );
			context.publish( (troot+"Humidite").c_str(), context.toString( this->humidite ).c_str() );

			this->dernier = millis();
Serial.println( this->dernier );
		}

		return true;
	}
};
#endif