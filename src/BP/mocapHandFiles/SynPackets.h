//SynPackets.h
//Definition of packet protocol for Synertial motion capture devices

#ifndef SYN_PACKETS_H_
#define SYN_PACKETS_H_


#include <stdint.h>

//The packet version number for this file
#define SYN_PACKET_VERSION		123

#define SYN_LOG_PORT			11400	//Default port for log/debug packets sent from hub to host
#define SYN_HUB_PORT			11401	//Known port for broadcast packets sent to any hub from any host
#define SYN_HOST_PORT			11402	//Known port for broadcast packets sent to any host from any hub (other than frame packets)
#define SYN_FRAME_PORT			11405	//Known port assigned for frame packets sent to any host

//Maximum number of sensors, any combination of Inertial Measurement Units (IMUs) or Trackers or Sync Module
//with the restriction that a single Sync Module has address SYN_SYNC_MODULE_ADDRESS
//and tracker addresses start at SYN_TRACKER_BASE_ADDRESS
#define SYN_MAX_SENSORS				64

#define SYN_SYNC_MODULE_ADDRESS		56
#define SYN_TRACKER_BASE_ADDRESS	56

//Maximum length of UDP data to avoid IP fragmentation
#define SYN_MAX_UDP_PACKETSIZE	1460	//This is the largest packet size for a UDP datagram sent without IP fragmentation
										//Size is reduced because wireless stack has 1460 max...

// All packet types are sent UDP broadcast EXCEPT for Frame (i.e., Frame_A and Frame_B)
typedef enum {
	PType_Reset 				= 1,			//Host command, no payload: resets hub to factory settings
	PType_Resetting				= 2,			//Hub confirmation of Reset command from host, no payload
	PType_Reboot				= 3,			//Host command, no payload: reboots hub with saved settings
	PType_Rebooting				= 4,			//Hub confirmation of Reset command from host, no payload
	PType_Stream 				= 5,			//Host command, no payload: tells hub to start streaming
	PType_Streaming				= 6,			//Hub confirmation of Stream command from host, no payload
	PType_Unstream				= 7,			//Host command, no payload: tells hub to stop streaming
	PType_Unstreamed			= 8,			//Hub confirmation of Unstream command from host, no payload
	PType_SendHubConfig 		= 9,			//Host command, no payload: tells hub to send a PType_ActiveHubConfig packet
	PType_NewHubConfig			= 10,			//Host command containing new hub settings to be applied by hub
	PType_ActiveHubConfig	 	= 11,			//Hub response to PType_SendHubConfig or PType_NewHubConfig, contains active settings
	PType_SendSensorConfigs		= 12,			//Host command, no payload: tells hub to send ALL PType_ActiveSensorConfig packets
	PType_NewSensorConfig	 	= 13,			//Host command containing new hub sensor settings for a single sensor to be applied by hub
	PType_ActiveSensorConfig	= 14,			//Hub response to new hub sensor settings, contains a single new sensor settings state
	PType_Frame_A 				= 15,			//Frame packet part A, sent from hub to host. Handles up to SYN_MAX_FRAMEPART_SENSORS sensors.
	PType_Frame_B				= 16,			//Frame packet part B, sent from hub to host. Only sent if more than SYN_MAX_FRAMEPART_SENSORS sensors are attached to hub.
	PType_Log					= 17,			//Everyone loves a log.
} HubPacketTypeEnum;


/*
 * IMPORTANT Note on Endianness:
 * All scalar types for the protocol described in this header are sent little-endian.
 * Let me repeat: these are NOT sent in "network order" as all known targets
 * for these comms are little-endian machines. You have been warned!!
 */

#pragma pack(1)							//Don't pad these structs

/* ---------------------------------------------------------------------------------------------------
 *                   Hub Config Section
 * ---------------------------------------------------------------------------------------------------*/

typedef struct {						//Holds settings for any IP-based interface
	uint8_t		IPaddr[4];				//IP address of interface in little-endian format,
										//	for example, 192.168.0.22 is encoded as { 22, 0, 168, 192 }
										//  This has no effect in a command if DHCP flag is set
	uint8_t		SubnetMask[4];			//This has no effect in a command if DHCP flag is set
	uint8_t		Gateway[4];				//This has no effect in a command if DHCP flag is set
	uint8_t		DnsServer[4];			//This has no effect in a command if DHCP flag is set
	uint8_t		UDPTTL;					//UDP Time To Live setting
	uint8_t		pad;
	uint16_t	Flags;					//Only flag is for DHCP
} HubIPConfig;							//Size is 20 bytes

#define SYN_IPCONFIG_USE_DHCP	0x0001U	//flag indicates DHCP is--or should be--active
//#define SYN_IPCONFIG_CONN_FAIL	0x0002U	//read-only flag indicates interface connection failed for any reason

typedef struct {
	uint8_t		SSID[33];				//zero-terminated
	uint8_t		SecType;
	uint8_t		PassPhrase[65];			//zero-terminated
	uint8_t		pad;
} HubWlanConfig;						//Size is 100 bytes

//Values for SecType:
typedef enum {							//deciding by fiat for now that we only support 3 common security types
	HubSWST_Open 		= 0,
	HubSWST_WEP 		= 1,
	HubSWST_WPA_WPA2 	= 2,
} HubWlanSecurityTypeEnum;


typedef struct {
	uint8_t 			ConfigFlags;			//See below
	uint16_t 			DestPort;				//UDP port number for destination for Framedata only
	uint8_t 			DestIP[4];				//IP address of destination for Framedata only in little-endian format,
												//	for example, 192.168.0.22 is encoded as { 22, 0, 168, 192 }
												//  For broadcast mode, set to 255.255.255.255
												//  All other comms are sent broadcast so don't strictly-speaking require a valid "from" IP address
	HubIPConfig 		EthIPSettingsActive;	//IP settings for ethernet that are currently active
	HubIPConfig 		WlanIPSettingsActive;	//IP settings for wireless that are currently active
	HubWlanConfig	 	WlanNetworkSettings;
	uint32_t 			FramePeriod;			//Period of frames (1 / frame rate) in microseconds
	uint32_t 			ErrorCode;				//Possible code indicating an error
	uint8_t 			Name[128];				//Name of this hub, zero terminated
	uint32_t 			NumSensors;				//Number of sensors in hub
} SynHubConfig;

//Values for ConfigFlags
#define SYN_CONFIG_SYNC_MOD_PRESENT		0x01	//Set by hub only - indicates sync module is connected
#define SYN_CONFIG_TRACKERS_PRESENT		0x02	//Set by hub only - indicates tracker sensors are connected
#define SYN_CONFIG_USE_SYNC_MOD			0x04	//Tells hub to use the sync module if it is present
#define SYN_CONFIG_USE_IMU_STROBE		0x08	//Tells hub to use the internal hardware strobe for IMU timing, (not implemented)
#define SYN_CONFIG_USE_TRACKERS			0x10	//Tells hub to use the trackers if present
#define SYN_CONFIG_USE_WLAN				0x20	//Tells hub to use WLAN if present, if not set hub will use ethernet
												// note that we have decided never to use both interfaces concurrently

//Values for ErrorCode:
typedef enum {
	HubErrorNone 			= 0,
	HubErrorPacketVersion	= 1,		//Sent if packetversion on hub doesn't match received packet
										//probably more to follow
} HubErrorEnum;


/* ---------------------------------------------------------------------------------------------------
 *                   Sensor Config Section
 * ---------------------------------------------------------------------------------------------------*/

//Info we can read or set in each IMU
typedef struct {
	uint8_t Vmaj;				//Sensor firmware version
	uint8_t Vmin;
	uint16_t Vpatch;
	uint8_t Vcode;				//MCU firmware version
	uint8_t pad[3];
	uint32_t ReportInterval;	//Internal IMU update period in uSec
	uint32_t ARVRScaling;		//2^30 * fraction of the angular velocity can be used to correct angular position errors
	uint32_t ARVRMaxRot;		//2^29 * maximum amount of angular correction that can be used to correct angular position errors in radians
	uint32_t ARVRMaxErr;		//2^29 * maximum angular error allowed to accumulate before the angular position output is updated in a single step in radians
	uint32_t ARVRStability;		//2^29 * amount of change in angular position that must occur before the angular position output is updated with a new value
} IMUConfig;

//Info we can read or set in the sync module
typedef struct {
	uint8_t MSMult;				//Multiplier, between 1 and 8 only
	uint8_t VidStandard;		//See below, read only
	uint16_t MSFreq;			//Integer estimate of multiplied frame rate in Hz, read only, in units of 10 uSec
} SyncConfig;

//Values for VidStandard:
/******************************************************************
		ONE BYTE VIDEO STANDARD DEFINES
		0 - PROGRESS
		1 - SLOW (1000/1001)
		2-4 FPS 24,25,30,50,60  (WITH THE "SLOW" BIT, CAN MAKE EVERYTHING)
		5-7 PAL,NTSC, 1280x720,1920x1080,720x576 or 480 (ED)
*******************************************************************/
#define		SYNC_FPS_SLOW		0x01	//1=slow=(1000/1001)eg 29.97, 0=fast, whole frame number eg 30.00
//
#define		SYNC_FPS_MASK		0x0F	// 0000 XXXX set FPS, includes "SLOW" bit
#define		SYNC_FPS_MASK_NS	0x0E	// 0000 XXXX set FPS, Excludes "SLOW" bit
#define		SYNC_FPS_24			0x00	// 0000 0000 =	24 FPS
#define		SYNC_FPS_23_97		0x01	// 0000 0001 =	24 FPS + slow bit = 23.976
#define		SYNC_FPS_25			0x02	// 0000 0010 =	25 FPS
#define		SYNC_FPS_30			0x04	// 0000 0100 =	30 FPS
#define		SYNC_FPS_29_97		0x05	// 0000 0101 =	30 FPS + slow bit = 29.97
#define		SYNC_FPS_50			0x06	// 0000 0110 =	50 FPS
#define		SYNC_FPS_60			0x08	// 0000 1000 =	60 FPS
#define		SYNC_FPS_59_94		0x09	// 0001 1001 =	60 FPS + slow bit =59.94
//
#define		SYNC_FMT_MASK		0x70	// XXX0 0000 3 bits set Format
#define		SYNC_FMT_PAL		0x00	// PAL black burst
#define		SYNC_FMT_NTSC		0x10	// NTSC blackburst
#define		SYNC_FMT_720		0x20	// 1280x720
#define		SYNC_FMT_1080		0x30	// 1980x1080
#define		SYNC_FMT_ED			0x40	// Extended Definition 720x576 or 720x480
//
#define		SYNC_PROGRESSIVE	0x80	//mask, 1=progressive, 0=interlaced
#define		SYNC_INTERLACED		0x00	//mask, 1=progressive, 0=interlaced

//Info we can read or set in each Tracker
typedef struct {
	uint32_t Flags;						//There are no configuration parameters for trackers
} TrackerConfig;

//Values for Flags:
#define TRACKER_CONFIG_FLAGS_RESERVED	0xFFFFFFFF

//Info we can read or set in each sensor
typedef struct {
	uint8_t Address;			//Sensor address, 0 to SYN_MAX_SENSORS-1
	uint8_t DeviceFlags;		//See below
	uint16_t pad;
	union {
		//This struct is valid when DF_TRACKER = 0 and DF_SYNC = 0
		IMUConfig IMU;
		//This struct is valid when DF_TRACKER = 1
		TrackerConfig Tracker;
		//This struct is valid when DF_SYNC = 1
		SyncConfig Sync;
	};
} SynSensorConfig;

//!!!Added epb
//If Address is this value in a PType_NewSensorConfig packet,
//then all sensors of the type indicated by the DF_DEVICE field
//should be set.
#define SENSOR_ADDRESS_ALL				0xFF

//Values for DeviceFlags
#define DF_DEVICE						0x03		//What type of sensor this is (read only)
//Meaning of DF_DEVICE field:
	#define DF_DEVICE_IMU				0x00		//Sensor is an IMU
	#define DF_DEVICE_TRACKER			0x01		//Sensor is a tracker
	#define DF_DEVICE_SYNC				0x02		//Sensor is a sync module
	#define DF_DEVICE_RESERVED			0x03		//Reserved
#define DF_INIT_SUCCESS					0x04		//Device successfully initialized (read only)
//These flags are used only if device is IMU:
#define DF_NO_MAG						0x08	//Ignore the magnetometer
#define DF_AUX_VECTOR					0x30	//This field indicates what is in the Aux vector
//Meaning of the DF_AUX_VECTOR field:
	#define DF_AUX_VECTOR_NONE			0x00	//The Auxiliary vector is not valid data
	#define DF_AUX_VECTOR_MAG			0x10	//The Auxiliary vector is magnetometer, uT
	#define DF_AUX_VECTOR_ACCEL			0x20	//The Auxiliary vector is acceleration not including gravity, m/s^2
	#define DF_AUX_VECTOR_ACCEL_GRAV	0x30	//The Auxiliary vector is acceleration including gravity, m/s^2
#define DF_INCLUDE_DELAY				0x40	//Set this flag to include the Delay member in IMU frames
#define DF_SET_ERROR					0x80	//This flag will be set in a PType_ActiveSensorConfig packet if there was an error
//There are no flags specific to trackers or sync modules

//For reference, these are the previous values:
//#define DF_INIT_SUCCESS			0x01
//#define DF_INCLUDE_ACCEL			0x02	//Only if device is IMU
//#define DF_INCLUDE_DELAY			0x04
//#define DF_INCLUDE_ACCURACY		0x08	//Only if device is IMU
//#define DF_INCLUDE_POSITION		0x10	//Only if device is tracker
//#define DF_SYNC					0x40	//This device is a sync module
//#define DF_TRACKER				0x80	//This device is a tracker


/* ---------------------------------------------------------------------------------------------------
 *                   Data Types used below
 * ---------------------------------------------------------------------------------------------------*/

//Quaternion in floats
typedef struct {
	float w;							//Scalar part
	float x, y, z;						//Vector part
} fQuat;

//Vector in floats
typedef struct {
	float x, y, z;
} fVec;

/* ---------------------------------------------------------------------------------------------------
 *                   Frame Data Section
 * ---------------------------------------------------------------------------------------------------*/

typedef struct {
	uint8_t Flags;						//Flags may be added later
	uint8_t VidStandard;				//Same as in SyncInfo
	uint8_t MSMult;						//Multiplier, between 1 and 8 only
	uint8_t JamState;					//See below
	uint16_t MSFreq;					//Integer estimate of multiplied frame rate in Hz
	uint16_t JamTime;					//Time since jam in seconds
	uint8_t TCFrm;						//Timecode Hours:Minutes:Seconds:Frames
	uint8_t TCSec;
	uint8_t TCMin;
	uint8_t TCHrs;
} SyncData;

//Values for Flags:
#define SYNC_FLAGS_RESERVED		0xFF

//Values for JamState:
#define SYNC_JAMSTATE_NOT_SYNCED	0		//Sync module is not synced
#define SYNC_JAMSTATE_SYNCING		1		//Sync module is in the process of syncing
#define SYNC_JAMSTATE_SYNCED		2		//Sync module is synced

//Here is what the LED indicates:
//The LED is red prior to jam
//Blinks red while the incoming frequency is measured
//Blinks green while the output is phase corrected to the measured input
//Is a solid green after jam

typedef struct {
	float ThetaBX;							//X angle from face of base station B in degrees
	float DelayBX;							//Delay from reference time in seconds
	float ThetaBZ;							//Z angle from face of base station B in degrees
	float DelayBZ;							//Delay from reference time in seconds
	float ThetaCX;							//X angle from face of base station C in degrees
	float DelayCX;							//Delay from reference time in seconds
	float ThetaCZ;							//Z angle from face of base station C in degrees
	float DelayCZ;							//Delay from reference time in seconds
} TrackerData; //32 bytes

typedef struct {
	fQuat Rotation;						//Unit quaternion for rotation
	fVec Auxiliary;						//Acceleration or magnetic field vector
	float Delay;						//Delay from reference time in uSec
} IMUData; //32 bytes

//Data from each IMU
typedef struct {
	uint16_t Flags;				//Bits and fields from each IMU
	uint8_t Address;			//Sensor address, 0 to SYN_MAX_SENSORS-1
	uint8_t pad;				//total number of sensors connected to hub
	union {
		//This struct is valid when SD_TRACKER and SD_SYNC are both 0
		IMUData IMU;
		//This struct is valid when SD_TRACKER is 1
		TrackerData Tracker;
		//This struct is valid when SD_SYNC is 1
		SyncData Sync;
	};
} SensorData; //size is 36 bytes

//Values of bits and fields in Flags
#define SD_DEVICE						0x0003		//Field indicates what type of sensor this is
//Meaning of SD_DEVICE field:
	#define SD_DEVICE_IMU				0x0000		//Sensor is an IMU
	#define SD_DEVICE_TRACKER			0x0001		//Sensor is a tracker
	#define SD_DEVICE_SYNC				0x0002		//Sensor is a sync module
	#define SD_DEVICE_RESERVED			0x0003		//Reserved
//These flags are valid if device is an IMU:
#define SD_ROTATION						0x0004		//Rotation member is valid
#define SD_DELAY						0x0008		//Delay member is valid
#define SD_STATUS						0x0030		//Status of the Rotation member
	//Meaning of SD_STATUS field:
	#define SD_STATUS_UNRELIABLE		0x0000		//IMU data is unreliable
	#define SD_STATUS_LOW				0x0010		//IMU data reliability is low
	#define SD_STATUS_MEDIUM			0x0020		//IMU data reliability is medium
	#define SD_STATUS_HIGH				0x0030		//IMU data reliability is high
#define SD_AUX							0x00C0		//Indicates what is in the Auxiliary member
	//Meaning of SD_AUX field:
	#define SD_AUX_NONE					0x0000		//Auxiliary is not valid
	#define SD_AUX_MAG					0x0040		//Auxiliary is magnetic field strength in micro Tesla
	#define SD_AUX_ACCEL				0x0080		//Auxiliary is acceleration not including gravity in meters/second^2
	#define SD_AUX_ACCEL_GRAV			0x00C0		//Auxiliary is acceleration including gravity in meters/second^2
#define SD_AUX_STATUS					0x0300		//Status of the Auxiliary member
	//Meaning of SD_AUX_STATUS field:
	#define SD_AUX_STATUS_UNRELIABLE	0x0000		//Auxiliary data is unreliable
	#define SD_AUX_STATUS_LOW			0x0100		//Auxiliary data reliability is low
	#define SD_AUX_STATUS_MEDIUM		0x0200		//Auxiliary data reliability is medium
	#define SD_AUX_STATUS_HIGH			0x0300		//Auxiliary data reliability is high
//!!!Added epb
//These two flags reiterate the values of the DeviceFlags member of SynSensorConfig
//These are only valid when SD_AUX is not SD_AUX_NONE
#define SD_INIT_SUCCESS					0x0400		//Device successfully initialized (read only)
#define SD_NO_MAG						0x0800		//Ignore the magnetometer
//These flags are valid if device is a tracker:
#define SD_TRACKER_BX					0x1000		//Tracker ...BX members are valid
#define SD_TRACKER_BZ					0x2000		//Tracker ...BZ members are valid
#define SD_TRACKER_CX					0x4000		//Tracker ...CX members are valid
#define SD_TRACKER_CZ					0x8000		//Tracker ...CZ members are valid
//!!!Removed epb
////These bits are reserved for future:
//#define SD_RESERVED					0x0C00		//Currently unused bits reserved for future

//For reference, these are the previous values:
//#define SD_TRACKER				0x0080		//Sensor is a tracker
//#define SD_SYNC					0x0100		//Sensor is a sync module
////These flags are valid if SD_DATA_TRACKER is 0 and SD_SYNC is 0:
//#define SD_STATUS					0x0003		//Status bits - see below
//#define SD_ROTATION				0x0004		//Rotation member is valid
//#define SD_ACCEL					0x0008		//Acceleration member is valid
//#define SD_DELAY					0x0010		//Delay member is valid
//#define SD_ACCURACY				0x0020		//Accuracy member is valid
////These flags are valid if SD_DATA_TRACKER is 1:
//#define SD_TRACKER_BX				0x1000		//Tracker ...BX members are valid
//#define SD_TRACKER_BZ				0x2000		//Tracker ...BZ members are valid
//#define SD_TRACKER_CX				0x4000		//Tracker ...CX members are valid
//#define SD_TRACKER_CZ				0x8000		//Tracker ...CZ members are valid
////These bits are reserved for future:
//#define SD_RESERVED				0x0E40		//Currently unused bits reserved for future
//
////Meaning of SD_DATA_STATUS field
//#define IMU_STATUS_UNRELIABLE		0x0000		//IMU data is unreliable
//#define IMU_STATUS_LOW			0x0001		//IMU data reliability is low
//#define IMU_STATUS_MEDIUM			0x0002		//IMU data reliability is medium
//#define IMU_STATUS_HIGH			0x0003		//IMU data reliability is high

///////////////////////////////////////////////////////////////////////////////////////

//We must have sizeof(SynPacket) <= SYN_MAX_UDP_PACKETSIZE, so
//sizeof(SynPacketHeader) + 4 + SYN_MAX_FRAMEPART_SENSORS * sizeof(SensorData) <= SYN_MAX_UDP_PACKETSIZE
//SYN_MAX_FRAMEPART_SENSORS <= (SYN_MAX_UDP_PACKETSIZE - sizeof(SynPacketHeader) - 4) / sizeof(SensorData)
//SYN_MAX_FRAMEPART_SENSORS <= (1460 - 16 - 4) / 36 = 40
//Can be smaller, but must be at least 32 to allow for 64 sensors with only two parts
#define SYN_MAX_FRAMEPART_SENSORS		36

typedef struct {
	uint8_t NumSensors;									//Total number of sensors connected to hub, NOT the number of elements in Sensor[]
	uint8_t pad[3];
	SensorData Sensor[SYN_MAX_FRAMEPART_SENSORS];		//Room for maximum number, only required are sent
} SynFramePart;

//This structure allows host software to combine up to two SynFramePart structs into one struct
//that contains all the sensor data for a frame
typedef struct {
	uint8_t NumSensors;							//Total number of sensors connected to hub, and the number of elements in Sensor[]
	uint8_t Flags;								//Reserved for now
	uint16_t FrameCount;						//Incremented each frame
	SensorData Sensor[SYN_MAX_SENSORS];
} SynFrame;


/* ---------------------------------------------------------------------------------------------------
 *                   SynPacket Section
 * ---------------------------------------------------------------------------------------------------*/

/*
 * A few notes on SynPacketHeader:
 * - The Count field is used in several different ways, specifically:
 * -- The host increments the count in every new packet it sends
 * -- Any response from a hub to a command keeps the count value for that reponse,
 *    allowing the host to match up responses to commands if it desires.
 * -- Hubs increment the count for every new frame sent. This counter lives in the
 *    hub so no relationship to any values coming in host-sent packets. The host
 *    uses this value to assemble full frames (if necessary) and to detect dropped
 *    or otherwise missing frames.
 *
 * - The UID field uniquely identifies any hub and also provides a pseudo-routing function, specifically:
 * -- For any ethernet-based hub, the UID is its MAC address in the lower bytes (sent little-endian as per usual)
 *    with 0x00 in both upper bytes. If a hub has more than one interface, the MAC is taken from the wired one.
 *    (though I guess in theory that doesn't really matter...)
 * -- For USB hubs (which are typically PCs running SynUSB), the UID is similarly the MAC address in the
 *    lower bytes, the COM port number in the second-highest byte, and 0x00 in the highest byte.
 *    PCs with multiple SynUSB connections therefore look to the host like multiple hubs that happen
 *    to share the same IP address.
 * -- The UID value has a different meaning when coming from a host. It determines which hub the
 *    sent packet is designated for. Since all packets except for frame packets are sent broadcast,
 *    receiving hubs will only process packets containing their UID. A special value of SYN_ALL_HUBS
 *    indicates that a packet should be processed by all hubs. "SendHubConfig" packets are typically sent this way
 *    during enumeration.
 */

 #define SYN_ALL_HUBS	(0xFFFFFFFFFFFFFFFFULL)

typedef union {
	uint64_t	UID64;
	struct {
		uint8_t	MAC[6];						//The MAC address of the hub wired ethernet adapter
		uint8_t COM;						//0 or the COM port number if SynUSB is emulating a hub
		uint8_t Reserved;
	} Parts;
} SynUID;

typedef struct {
	uint8_t			Version;				//Datamodel Version, must always match SYN_PACKET_VERSION
											//Only PType_SendHubConfig packets with an incorrect Version are parsed, resulting in
											//a returned error from the hub. All other incorrectly versioned packets are discarded
	uint8_t			Type;					//Values from HubPacketTypeEnum above
	uint16_t		Count;
	uint8_t 		BatteryPotential_A;		//Measured potential of battery A. Divide by 16 to convert to volts.
	uint8_t			BatteryPotential_B;		//Measured potential of battery B. Divide by 16 to convert to volts.
	uint8_t			DeviceCurrentDraw;		//Average current draw of device [in last second?]. Divide by 64 to convert to amps.
	uint8_t			Flags;					//Unused for now
	SynUID			UID;
} SynPacketHeader; //size is 16 bytes

#define	SYN_MAX_PAYLOADSIZE	(SYN_MAX_UDP_PACKETSIZE - sizeof(SynPacketHeader))

typedef struct {
	uint8_t	LogText[SYN_MAX_PAYLOADSIZE];	//Null-terminated log string
} SynLog;

typedef struct {
	SynPacketHeader				Header;
	union {
		uint8_t					Payload[SYN_MAX_PAYLOADSIZE];
		SynHubConfig			HubConfig;
		SynSensorConfig			SensorConfig;
		SynLog					Log;
		SynFramePart			Frame;
	};
} SynPacket;

/*
 * So, a SynPacket as sent, depending on what type it is, consists of either:
 * - Just a Header field
 * - Both a Header field and a payload, which may be one of:
 * -- SynHubConfig
 * -- SynSensorConfig
 * -- SynLog
 * -- SynFramePart
 */

#pragma pack()

/*

Protocol
========
The host sends commands and data to the hub by sending SynPacket packets
to SYN_HUB_PORT via UDP in broadcast mode.  Header.Type defines what type
of packet is being sent or received.

The host can put the Synertial device in a known state using one of these optional packet types:
	PType_Reset				//Resets the device to its factory default state.
							//Device responds with PType_Resetting packet type
	PType_Reboot			//Restarts the device to its power on state as previously set in non-volatile memory.
							//Device responds with PType_Rebooting packet type

At startup, the host sends packet type:
	PType_SendHubConfig		//Tells each hub to broadcast a PType_ActiveHubConfig so we can get its IP address, etc.

Each Synertial device that receive this command responds with a PType_ActiveHubConfig
broadcast to SYN_HOST_PORT.  Hosts can use this to enumerate all the available Synertial devices.

There is configuration information associated with a hub, as well as configuration
for individual sensors.  These commands are for configuring a hub:
	PType_NewHubConfig		//Device responds with PType_ActiveHubConfig packet type
							//The response may differ from the configuration sent
							//for members that may not be changed or is the sender
							//requested impossible values.  This may be directed to
							//a single device or broadcast to all.
	PType_SendHubConfig		//Device responds with PType_ActiveHubConfig packet type
							//Not only used to enumerate, but this may request a
							//PType_ActiveHubConfig packet from a specific hub only
The hub should be configured for the specific transport (Ethernet or wireless), and destination port and IP,
which may be a specific IP or broadcast.

These commands are for configuring individual sensors:
	PType_SendSensorConfigs	//Device responds with PType_ActiveSensorConfig packet type
							//Device sends one PType_ActiveSensorConfig packet for each sensor in the device
	PType_NewSensorConfig	//Host command containing new hub sensor settings for a single sensor to be applied by hub
							//Device responds with a single PType_ActiveSensorConfig packet

The host can turn streaming on and off using these packet types:
	PType_Stream			//Device responds with PType_Streaming packet type UNLESS device has 0 sensors,
							//  in that case it responds with PType_Unstreamed packet type
	PType_Unstream			//Device responds with PType_Unstreamed packet type

For internal debugging purposes, a hub may also send this to a host:
	PType_Log				//A way to send strings out of the hub

Once the hub network settings are configured and streaming is turned on, the hub sends these packet types:
	PType_Frame_A 			//Frame packet part A, sent from hub to host. Handles up to SYN_MAX_FRAMEDATA_SENSORS sensors.
	PType_Frame_B			//Frame packet part B, sent from hub to host. Only sent if more than SYN_MAX_FRAMEDATA_SENSORS sensors are attached to hub.

*/

#endif
