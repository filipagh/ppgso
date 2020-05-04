// SynLab.h interface to SynLab.dll
// Copyright (c) 2016 Synertial
// Written by Edwin P. Berlin, Jr.

#ifndef __SYNLAB_H__
#define __SYNLAB_H__

#include "Matrix.h"
#include "SynPackets.h"

#define SYNLAB_VERSION	"3.0"

#ifndef DLLEXPORT
#define DLLEXPORT		__declspec(dllexport)
#endif

//Export all IGS 190 functions as C functions
#ifdef __cplusplus
extern "C" {
#endif

//Used to set the desired transformation based on two poses
typedef struct {
	uint32_t Flags;					//See below
	Quaternion Ref1;
	Quaternion Ref2[SYN_MAX_SENSORS];
} TSetStruct;

//Values for TSetStruct Flags:
#define TF_REF_IMU		0x0000003F		//Mask for reference IMU address
#define TF_REF1			0x00000040		//Ref1 is valid
#define TF_REF2			0x00000080		//Ref2 is valid
#define TF_REF1RAW		0x00000100		//Raw orientation is stored in Ref1

//Can represent a position and an orientation
typedef struct {
	Vector Position;				//In meters
	Quaternion Orientation;
} Syn6DOF;

typedef struct {
	uint32_t Flags;					//See below
	Syn6DOF BaseB;					//Calibration of Base Station B
	Syn6DOF BaseC;					//Calibration of Base Station C
	Syn6DOF Wand1;					//Current position and orientation of controller 1
	Syn6DOF Wand2;					//Current position and orientation of controller 2
} SynLightHouse;

//Values for SynLightHouse Flags:
#define SLHF_LIGHTHOUSE_ENABLED		0x00000001	//We are using the LightHouse tracking system, usually HTC Vive
#define SLHF_BASE_B_OK				0x00000002	//Base station B is functioning and BaseB member is valid
#define SLHF_BASE_C_OK				0x00000004	//Base station C is functioning and BaseC member is valid
#define SLHF_WAND_1_OK				0x00000008	//Wand 1 is functioning and Wand1 member is valid
#define SLHF_WAND_2_OK				0x00000010	//Wand 2 is functioning and Wand2 member is valid

typedef struct {
	uint32_t Flags;					//See below
	Syn6DOF BaseB;					//Calibration of Base Station B
	Syn6DOF BaseC;					//Calibration of Base Station C
} SynLightHouseCalibration;

//Values for SynLightHouseCalibration Flags:
#define SLHCF_CALIBRATED		0x00000001		//The base stations are calibrated

//Transformed sensor data
typedef struct {
	Quaternion Rotation;
	Vector Position;				//In meters
	Vector Normal;					//Unit vector
	Vector Aux;						//Acceleration or magnetometer in uT
	uint32_t Flags;					//See below
} TransformedSensorData;

//Values for TransformedSensorData Flags:
#define TSF_ROTATION			0x01		//Rotation is valid
#define TSF_POSITION			0x02		//Position is actual position
#define TSF_LINE				0x04		//Line: X = Position + Normal * t
#define TSF_PLANE				0x08		//Plane: Normal * (X - Position) = 0
#define TSF_AUX					0x30		//Indicates what is in Aux
//Meaning of TSF_AUX
	#define TSF_AUX_NONE		0x00		//Aux is not valid
	#define TSF_AUX_MAG			0x10		//Aux is magnetometer reading in uT
	#define TSF_AUX_ACCEL		0x20		//Aux is acceleration not including gravity in m/s^2
	#define TSF_AUX_ACCEL_GRAV	0x30		//Aux is acceleration including gravity in m/s^2

//Fixed array size for transformed sensors
//Sensors are indexed by their address
typedef struct {
	uint16_t Flags;					//See below
	uint16_t FrameCount;			//Incremented each frame at nominal FPS
	TSetStruct TSet;				//Sets the transformation
	SynLightHouseCalibration Calib;	//Calibration when there are Trackers
	TransformedSensorData Sensor[SYN_MAX_SENSORS];
} TransformedSensors;

//Values for TransformedSensors Flags:
#define TSSF_REF1SET	0x0001		//Pose 1 was just set in last call to SynApplyTransformation()
#define TSSF_REF2SET	0x0002		//Pose 2 was just set in last call to SynApplyTransformation()

//Nodes in a skeleton
typedef struct {
	char *Name;						//Each Node can have a name
	Vector Position;				//In meters
	uint8_t Tracker;				//The index of a tracker associated with this node
	uint8_t Flags;					//See below
	uint8_t PreviousFlags;			//value of Flags previous frame
	uint8_t pad;
	float ContactRadius;			//Radius of sphere in meters around this point if it is a contact point
	float TrackerScale;				//Weights the influence of the tracker if more than one way to set position
	//Computed after traversing hierarchy
	Vector CurrentPosition;
	Vector ContactPoint;
	Vector LastContactPoint;
	Vector ContactPointVector;
	Vector LastContactPointVector;
	float ContactPointMu;
	uint32_t ParentBone;			//This node is the child of bone ParentBone
} Node;

//If the node has no ParentBone
#define BONE_NONE			0xFFFFFFFFU

//Values for Node Flags:
#define NF_INVISIBLE	0x01		//This node is invisible
#define NF_CONTACT		0x02		//This node is a contact point
#define NF_TRACKER		0x04		//Use Tracker to set position of this node
#define NF_ON_FLOOR		0x08		//This is a contact point and it is touching the floor
#define NF_COMPUTED		0x10		//Current position and transform have been computed

typedef struct {
	char *Name;						//Each Bone can have a name
	uint32_t Parent;				//Index of the parent Node
	uint32_t Child;					//Index of the child Node
	uint16_t Flags;					//See below
	uint8_t NumIMUs;				//Number of IMUs that contribute to this bone transform (0 or 1)
	uint8_t pad;
	uint8_t IMU[2];					//Address of each IMU (NOTE: order matters)
	float IMUScale;					//Scale for interpolation/extrapolation when NumIMUs is 2
	float Thickness;				//Circumference of this bone divided by its length (unitless)
	//These members are used when BF_USE_AXES is set:
	Vector UpAxis;
	Vector ForwardAxis;
	Vector RightAxis;
	float AxisScaleUp;				//Scale for rotation around Up vector
	float AxisScaleForward;			//Scale for rotation around Forward vector
	float AxisScaleRight;			//Scale for rotation around Right vector
	//NOTE: These limits are not currently used
	float LimitUpMin;				//Lower limit for rotation around Up vector
	float LimitUpMax;				//Upper limit for rotation around Up vector
	float LimitForwardMin;			//Lower limit for rotation around Forward vector
	float LimitForwardMax;			//Upper limit for rotation around Forward vector
	float LimitRightMin;			//Lower limit for rotation around Right vector
	float LimitRightMax;			//Upper limit for rotation around Right vector
	//Computed after traversing hierarchy
	Quaternion CurrentTransform;	//From associated IMUs
	Vector ReferenceAxis;			//Previous frame rotation axis to aid interpolation
	float ReferenceAngle;			//Previous frame rotation angle to aid interpolation
} Bone;

//Values for Bone Flags:
#define BF_INVISIBLE		0x0001		//This bone is invisible
#define BF_ELASTIC			0x0002		//If both endpoints are fixed, bone is stretched to fit
#define BF_USE_AXES			0x0004		//Use the local axes to constrain motion
#define BF_LIMIT_UP			0x0008		//Use the limits on rotation about the Up vector
#define BF_LIMIT_FORWARD	0x0010		//Use the limits on rotation about the Forward vector
#define BF_LIMIT_RIGHT		0x0020		//Use the limits on rotation about the Right vector
//For internal calculations:
#define BF_REFERENCE		0x0100		//The Reference member has been set

//These parameters control the operation of the Synertial device
typedef struct {
	uint32_t Flags;					//See below
	float FPS;						//Nominal frames per second
	float WalkingStaticFriction;	//Static coefficient of friction at feet, unitless
	float WalkingKineticFriction;	//Kinetic coefficient of friction at feet, unitless
	float WalkingJumpHoldoff;		//Prevent jumping after landing from a jump for this time in seconds
	float WalkingJumpThreshold;		//Distance above (or below if negative) floor to detect a jump, meters
	float FloorEpsilon;				//A tolerance use in friction model, meters
	float QScale;					//Scale parameter modeling measurement noise, meters
	float Gravity;					//Acceleration due to gravity, in g's, nominally 1
	float ViewScale;				//Default scale for viewing
} SynParameters;

//Values for SynParameters Flags:
#define SPF_ENABLE_JUMPING		0x00000001	//Turn off to stick to floor
#define SPF_IGNORE_FLOOR		0x00000002	//Turn off to disable gravity and floor
#define SPF_FIX_ROOT			0x00000004	//Keep the root of the skeleton at the origin
#define SPF_USE_ACTUAL_FPS		0x00000008	//Use the actual FPS, not the value in the Skeleton file
#define SPF_USE_TRACKERS		0x00000010	//Use the trackers if available

typedef struct {
	char *Name;						//The entire skeleton can have a name
	uint32_t Units;					//Units used in file, one of SynUnitEnum values
	uint32_t ReferenceIMU;			//The reference IMU for initialization
	float ReferenceAngle;			//The reference axis is the +X axis rotated this many degrees around Z
	uint32_t NumNodes;				//Number of Nodes
	Node *nodes;					//Array of Nodes, nodes[0] is root position
	uint32_t NumBones;				//Number of Bones
	Bone *bones;					//Array of Bones
	//Used by walking/jumping code
	SynParameters Params;
	Vector CenterOfMass;			//Set after traversing hierarchy
	uint32_t StateSize;				//Size of the StateData memory block
	void *StateData;				//Points to a block of memory used by internal state, StateSize bytes
} Skeleton;

typedef struct {
	Skeleton skeleton;				//The figure to animate
	float FrameRate;				//Frames per second
	TSetStruct TSet;				//Transformation set from two poses
	uint32_t NumFrames;				//Number of Frames
	SynFrame *frames;				//Array of Frames
} Sequence;

///////
//Enums

//Values for errors that could be returned by some functions
//Use SynGetErrorString() to get a readable string for these
typedef enum {
	SynErrorNone 					= 0,		//Success
	SynErrorFail					= 1,		//General operation failed
	SynErrorFileRead				= 2,		//File read error
	SynErrorFileWrite				= 3,		//File write error
	SynErrorInvalidIMUAddress		= 4,		//Invalid IMU address
	SynErrorWSAStartup 				= 5,		//WSAStartup failed
	SynErrorSocketVersion			= 6,		//Couldn't find a usable version of windows sockets
	SynErrorSocketError				= 7,		//Socket error
	SynErrorSocketBindError			= 8,		//Socket bind error
	SynErrorioctlsocketError		= 9,		//ioctlsocket error
	SynErrorConnectionClosed		= 10,		//Connection closed
	SynErrorBadPacketSize			= 11,		//Bad packet size
	SynErrorNoData					= 12,		//No data
	SynErrorBadSensorCount			= 13,		//Bad sensor count
	SynErrorBadPacketType			= 14,		//Bad packet type
	SynErrorNotATree				= 15,		//Skeleton bones are not in tree order
	SynErrorBadSensorAddress		= 16,		//Bad sensor address
	SynErrorBadFragmentationHeader	= 17,		//Bad fragmentation header
	SynErrorMemory					= 18,		//Memory allocator failed
	SynErrorInvalidHandle			= 19,		//Invalid handle
	SynErrorCallbackSpecified		= 20,		//SynRead was called but a callback was specified
	SynErrorSocketSendError			= 21,		//Socket send error
	SynErrorTimeout					= 22,		//Operation timed out
	SynErrorThread					= 23,		//Could not create thread
} SynErrorEnum;

//Values for Units
//Use SynGetUnitsString() to get a readable string for these
typedef enum {
	SynUnitsMillimeters 		= 0,
	SynUnitsCentimeters			= 1,
	SynUnitsMeters 				= 2,
	SynUnitsKilometers 			= 3,
	SynUnitsInches 				= 4,
	SynUnitsFeet 				= 5,
	SynUnitsYards 				= 6,
	SynUnitsMiles 				= 7,
	//Always the last entry
	SynNumUnits 				= 8,			//Number of possible values for Units
} SynUnitsEnum;

//A handle to a Synertial device
typedef void* SynHandle;

typedef struct {
	SynUID			UID;
	SynHubConfig	HubConfig;
	bool			openedLocally;		//if true, hub is already opened on the local host
} SynHubInfo;

//An invalid SynHandle
#define INVALID_SYN_HANDLE		((SynHandle)NULL)

typedef void (*pSynCallback)(SynFrame *frame);

///////////
//Functions

////////////////////////////////////////////////////////////
//Returns the version of this interface as a readable string
//This should match SYNLAB_VERSION
DLLEXPORT const char *SynGetVersion();

//////////////////////////////////////////////////////
//Get the UID of the Synertial device opened on Handle
//Returns 0 if success
DLLEXPORT int SynGetUID(SynHandle Handle, SynUID *uid);

/////////////////////////////////////////////////////////
//Call this to begin using the Synertial device interface
//When you are done, you should call SynFinish()
//It is OK to call SynInit() several times
//without calling SynFinish() as long as you call
//SynFinish() before exiting your program.
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynInit();

//////////////////////////////////////////////////////////
//Call this to finish using the Synertial device interface
//It is OK to call SynFinish() several times or
//without calling SynInit()
//This will close any open Synertial devices
DLLEXPORT void SynFinish();

///////////////////////////////////////////////////////////////////////////////
//This function enumerates all the Synertial devices found on the local network
//HubInfoArray points to a user-allocated array of SynHubInfo structs
//Num is initially the number of entries in the array
//Changes Num to the number of entries filled in, one per Synertial device
//detected (not to exceed the original value of Num)
//ListenTime is the time in ms to wait for responses before returning
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynEnumerate(SynHubInfo *HubInfoArray, uint32_t *Num, uint32_t ListenTime);

///////////////////////////////////////////////////
//This function opens a Synertial device for access
//HubUID is a SynUID struct as embedded in 
//one of the SynHubInfo entries returned by SynEnumerate
//If HubUID is NULL, the next available Synertial device is opened
//If the open is successful, this function returns a handle
//to the opened device for use with subsequent functions.
//When you are done using a device, you should call SynClose()
//or SynFinish(), which will close all open devices.
//The callback parameter points to a function which is called
//every time frame data is received from the device.  This parameter
//may be NULL, in which case you can read the most recent device
//data received using SynRead().
//Returns one of SynErrorEnum
//Returns 0 if success and sets Handle to a valid handle
DLLEXPORT int SynOpen(SynHandle *Handle, SynUID *HubUID, pSynCallback callback);

////////////////////////////////////
//Close the device if currently open
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynClose(SynHandle Handle);

//////////////////////////////////
//Read from a single opened device
//You may use this for polling the device, but the preferred
//method is to pass a callback function to SynOpen() which
//is called whenever a new frame of data is received from the device.
//Do not call this function if you have specified a callback function in SynOpen().
//In that case, SynErrorCallbackSpecified will be returned
//Returns one of SynErrorEnum
//Returns SynErrorConnectionClosed if connection closed
//Returns SynErrorNoData if no data is currently available to read
//Returns 0 if success
DLLEXPORT int SynRead(SynHandle Handle, SynFrame *frame);

//////////////////////////////////////////////////////////////////////////
//Fills in HubConfig with the configuration of the device opened on Handle
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynGetHubConfig(SynHandle Handle, SynHubConfig *HubConfig);

//////////////////////////////////////////////////////////////////////
//Sets the device opened on Handle with the configuration in HubConfig
//Modifies HubConfig by filling actual values set
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynSetHubConfig(SynHandle Handle, SynHubConfig *HubConfig);

/////////////////////////////////
//Resets the hub and erases NVRAM
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynResetHub(SynHandle Handle);

////////////////////////////////////////////////////////
//SensorConfig points to a single SynSensorConfig struct
//Fills in SensorConfig with configuration from the sensor at address Address
//on the device opened on Handle
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynGetSensorConfig(SynHandle Handle, uint8_t Address, SynSensorConfig *SensorConfig);

////////////////////////////////////////////////////////////
//SensorConfig points to an array of SynSensorConfig structs
//On input, NumSensors is set to the number of entries in SensorConfig
//Normally, SensorConfig should be large enough for SYN_MAX_SENSORS
//Fills in SensorConfig with configuration from each IMU sensor on the
//device opened on Handle
//Sets NumSensors to the number of IMU sensors responding
//This ignores any sensors that are not IMUs
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynGetAllIMUSensorConfigs(SynHandle Handle, uint8_t *NumSensors, SynSensorConfig *SensorConfig);

//////////////////////////////////////////////////////////////
//Sets configuration of the sensor at the address specified in
//SensorConfig->Address on the device opened on Handle
//If SensorConfig->Address is SENSOR_ADDRESS_ALL, all sensors
//of the type indicated by the DF_DEVICE field will be set.
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynSetSensorConfig(SynHandle Handle, SynSensorConfig *SensorConfig);

///////////////////////////////////////////////////////////
//Returns battery voltages in volts and hub current in amps
//Returns 0 if success
DLLEXPORT int SynGetBatteryInfo(SynHandle Handle, float *BatteryVoltageA, float *BatteryVoltageB, float *SystemCurrent);

////////////////////////////////////////////////////////////////////////////////////////
//Sets calibration and tracking information associated with a LightHouse tracking system
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynSetLightHouse(SynHandle Handle, SynLightHouse *LH);

//////////////////////////////////
//Write calibration data .lhc file
DLLEXPORT int SynWriteCal(SynLightHouseCalibration *cal, char *filename);

/////////////////////////////////
//Read calibration data .lhc file
DLLEXPORT int SynReadCal(SynLightHouseCalibration *cal, char *filename);

//////////////////////////////////////////////////////
//Call this to start accumulating data for calibration
//The calibration jig should not move during this time
//To calibrate a device, call
//SynStartCalibration(), then call
//SynContinueCalibration() repeatedly until it returns true, then call
//SynFinishCalibration()
//You must always call SynFinishCalibration() after SynStartCalibration()
//Calibrate a single device at a time
//CalJig is an array of NumJig positions (in meters) of sensors on a calibration jig
//JigAddress is an array of NumJig addresses of the jig sensors
//NumJig must be at least 4
//Returns 0 if success
DLLEXPORT int SynStartCalibration(uint8_t *JigAddress, Vector *CalJig, int NumJig);

////////////////////////////////////////////////////////////
//Pass tracker data from the calibration jig to this routine
//Call it repeatedly until it returns true
DLLEXPORT bool SynContinueCalibration(SynFrame *sf);

//////////////////////////////////////
//Calibrate using Tracker[] AvgTheta's
//Producing Positions and Orientations of base stations in cal
//Returns 0 if success
DLLEXPORT int SynFinishCalibration(SynLightHouseCalibration *cal);

///////////////////////////////////////////////////////////////
//Fills in Params with default (recommended) parameter settings
DLLEXPORT void SynGetDefaultParams(SynParameters *Params);

/////////////////////////////////////////////////////////
//Returns number of frames we didn't have time to process
//in DroppedCount
//This number is cleared when SynClearDropped() is called
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynGetDropped(SynHandle Handle, uint32_t *DroppedCount);

////////////////////////////////////////////////////////////
//Clears the dropped frame count returned by SynGetDropped()
//Returns one of SynErrorEnum
//Returns 0 if success
DLLEXPORT int SynClearDropped(SynHandle Handle);

////////////////////////////////////////////////
//Returns a readable string given an error code,
//one of the SynErrorEnum values
DLLEXPORT const char *SynGetErrorString(int err);

///////////////////////////////////////////////
//Returns a readable string given a Units code,
//one of the SynUnitsEnum values
DLLEXPORT const char *SynGetUnitsString(int Units);

//////////////////////////////////////////
//Convert a value from one unit to another
//If unitFrom or unitTo are invalid, returns value
DLLEXPORT float SynConvertUnits(int unitFrom, int unitTo, float value);

///////////////////////////////////////////////////////
//Returns a readable string given a sensor status code,
//from the SD_STATUS field or the SD_AUX_STATUS field of
//the SensorData Flags member.  Must shift the field right
//to right justify the bits before passing to this function
DLLEXPORT const char *SynGetStatusString(int status);

///////////////////////////////////////////////////////////
//If we are using a SyncModule, this gives the actual video
//frame rate given VidStandard
//Returns 0.f if VidStandard is invalid
DLLEXPORT float SynGetVideoFrameRate(uint8_t VidStandard);

///////////////////////////////////////
//This is a readable description of the
//JamState member of a SyncData struct
DLLEXPORT const char *SynGetJamStateName(uint8_t JamState);

///////////////////////////////////////////////////////////
//Read from a template skeleton file, default extension .sk
//Uses malloc to allocate memory for pointer members of s
//Call SynFreeSkeleton() to free memory allocated by this
//Returns 0 if success
DLLEXPORT int SynReadSkeleton(Skeleton *s, const char *filename);

//////////////////////////////////////////////////////////
//Write to a template skeleton file, default extension .sk
//s->Units specifies which units to use
//Returns 0 if success
DLLEXPORT int SynWriteSkeleton(Skeleton *s, const char *filename);

////////////////////////////////////////////
//Free memory allocated by SynReadSkeleton()
//Returns 0 if success
DLLEXPORT int SynFreeSkeleton(Skeleton *s);

///////////////////////////////////////////////////////////
//Applies the transformation in Pose->TSet to the IMUs in p
//Result in Pose->Sensor[]
//This turns sensors from reporting orientation in their own
//coordinate system to one common coordinate system.
//ReferenceIMU should be one of the following values
#define SYN_SET_NONE	-1	//Use Pose->TSet as-is for this transformation
#define SYN_SET_POSE2	-2	//Set entries in Pose->TSet to use this pose as the initiailization pose (pose 2)
//If ReferenceIMU >= 0, it should be the address of the IMU used as a reference for pose 1
//Returns 0 if success
//
//The initialization procedure involves recording two SynFrames
//Pose2 is the desired starting pose, normally facing the +Y direction.
//Pose1 is similar to the starting pose but a specified sensor is
//rotated approximately +90 degrees around the desired X axis from Pose2.
//For example, if the chosen sensor is the forearm sensor, this pose
//would have the forearm raised parallel to the floor, while the second
//pose has it down by one's side.  The other sensors of this pose are ignored.
//ReferenceIMU is the address of the forearm sensor of the Pose1 SynFrame.
//Pose->TSet is filled in with the data needed to perform the correct transformations
//each frame.
DLLEXPORT int SynApplyTransformation(TransformedSensors *Pose, SynFrame *f, int ReferenceIMU);

///////////////////////////////////////////
//Apply the sensor data in Pose to skeleton
//Use transformation set in Pose->TSet
//Must first call ApplyTransformation() to fill in Pose
//Returns 0 if success
DLLEXPORT int SynApplyPose(Skeleton *s, TransformedSensors *Pose);

#ifdef __cplusplus
}
#endif

#endif
