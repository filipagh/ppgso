//Tracking.h

//////////////////////////////////////
//Apply tracking code using cal and sd
//Returns true if Position has been set
bool Track(SynLightHouseCalibration *cal, SensorData *sd, TransformedSensorData *tsd);

/////////////////////////////////////////
//Scan all tracked nodes to find the best
//offset to minimize tracking error
//Returns new position for CM
//True if NewCM was calculated
bool TrackerOffset(Skeleton *s, TransformedSensors *Pose, Vector *NewCM);

///////////////////////////////////////////
//If we have valid tracking for this frame,
//we'll modify State->Kalman.ModelPVg_P and State->Kalman.ModelPVg_V
void FollowTracker(SynState *State, Skeleton *s, uint16_t FrameCount, Vector NewCM);
