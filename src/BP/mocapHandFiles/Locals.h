//locals.h
//Types and functions not exported
//opyright (c) 2016
//Written by Edwin P. Berlin, Jr., Secret Software

#define INVALID_INDEX		~0
//Returns current index into AllHandles[] of Handle
//Returns INVALID_INDEX if it isn't there
//Note this index can be changed by an open or close, etc.
uint32_t GetHandleIndex(SynHandle Handle);

/////////////////////////////////////////////////
//Variables for Kalman filter PVg model predictor
//Remember P and Q are symmetrical
typedef struct {
	float PVg_P00, PVg_P01, PVg_P02, PVg_P11, PVg_P12, PVg_P22;
	float PVg_Q00, PVg_Q01, PVg_Q02, PVg_Q11, PVg_Q12, PVg_Q22;
	//Larger makes it slower
	float PVg_R;
	//Kalman state
	Vector ModelPVg_P, ModelPVg_V, ModelPVg_A;
	//Time information
	uint16_t FrameCount;
	bool FrameCountValid;
} KalmanPVg;

//State values for a suit
typedef struct {
	uint16_t Flags;
	uint16_t LastFrameCount;
	int32_t JumpHoldoff;				//How many frames to prevent jumping
	int32_t MinContactPoint;			//Index into nodes (or -1 if not valid)
	KalmanPVg Kalman;
	//For tracking:
	Vector TrackerOffset;
	Vector PredictedCM;
	Vector CMFromMarker;
	bool CMFromMarkerValid;
} SynState;

//Values for SynState Flags:
#define SSF_JUMPING					0x00000001	//We are jumping on this frame
#define SSF_HAVE_TRACKER_OFFSET		0x00000002	//We have set TrackerOffset

//Information about the hub we're connected to
typedef struct {
	SynPacketHeader	Header;
	SynHubConfig HubConfig;
	SynSensorConfig SensorConfig[SYN_MAX_SENSORS];
} SynHub;

//SynHandle is typedef'd as void * but really points to one of these
typedef struct {
	pSynCallback callback;
	SynLightHouse LH;
	uint16_t Flags;
	uint16_t LastFrameCount;
	uint32_t DroppedCount;
	SynHub Hub;
	SynPacketHeader LastHeader;
	SynFrame Frame;
} SynLocals;

//Values for SynLocals Flags:
#define SLF_PREVIOUS			0x00000001	//The current frame is not the first of a sequence
#define SLF_FRAME_VALID			0x00000002	//The Frame member has valid data which has not yet been read
#define SLF_CONNECTION_CLOSED	0x00000004	//The connection was closed

//Qscale scales the Q matrix, in meters
//Gravity scales gravity in g's
void PredictorInit(KalmanPVg *Kalman, float Qscale, float Gravity);
//Set position and velocity explicitly
void PredictorSetPV(KalmanPVg *Kalman, Vector P, Vector V, uint16_t FrameCount);
//Timestep a PVg predictor
void PredictorTimeStep(KalmanPVg *Kalman, float FPS, uint16_t FrameCount);
//Update when we have a measurement
//Time is time in seconds, can be frame count / FPS
void PredictorMeasurementStep(KalmanPVg *Kalman, Vector &Position, uint16_t FrameCount);

//Compute the position of the root
//Use walking and jumping and determine if we jumped
//Also use trackers if we're tracking
//Updates s->nodes[0].CurrentPosition
//and other state in L needed for tracking
//FrameCount is incremented each frame at nominal FPS
//First true is first frame of a sequence
//TrackerUpdate is true if NewCM is set by the trackers
void ComputePosition(SynState *State, Skeleton *s, uint16_t FrameCount, bool First, bool TrackerUpdate, Vector NewCM);
