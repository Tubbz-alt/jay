/* 
	PAVx -- Pod-Based Autonomous Vehicles 
	Library Created By: Sargis S Yonan
	March 2017
*/ 

// pid.h

// Some PID concepts borrowed the bitcraze/crazieflie-firmware repository
// https://www.bitcraze.io

#ifndef _PID_H_
#define _PID_H_

#define PID_ROLL_RATE_KP  70.0
#define PID_ROLL_RATE_KI  0.0
#define PID_ROLL_RATE_KD  0.0
#define PID_ROLL_RATE_INTEGRATION_LIMIT    33.3

#define PID_PITCH_RATE_KP  70.0
#define PID_PITCH_RATE_KI  0.0
#define PID_PITCH_RATE_KD  0.0
#define PID_PITCH_RATE_INTEGRATION_LIMIT   33.3

#define PID_YAW_RATE_KP  70.0
#define PID_YAW_RATE_KI  16.7
#define PID_YAW_RATE_KD  0.0
#define PID_YAW_RATE_INTEGRATION_LIMIT     166.7

#define PID_ROLL_KP  3.5
#define PID_ROLL_KI  2.0
#define PID_ROLL_KD  0.0
#define PID_ROLL_INTEGRATION_LIMIT    20.0

#define PID_PITCH_KP  3.5
#define PID_PITCH_KI  2.0
#define PID_PITCH_KD  0.0
#define PID_PITCH_INTEGRATION_LIMIT   20.0

#define PID_YAW_KP  10.0
#define PID_YAW_KI  1.0
#define PID_YAW_KD  0.35
#define PID_YAW_INTEGRATION_LIMIT     360.0

#define PID_INACTIVE_LOWER_THRESHOLD (0.0001)
#define DEFAULT_PID_INTEGRATION_LIMIT  5000.0

enum Active {
	PID_ACTIVE,
	PID_INACTIVE
};
typedef enum Active Active_t;

enum UpdateFlag {
	UPDATE_ERROR,
	NO_UPDATE
};
typedef enum UpdateFlag UpdateFlag_t;

struct PID {
	double desired;
	double error;
	double lastError;
	double integral;
	double derivative;
	double kp;
	double ki;
	double kd;
	double pOutput;
	double iOutput;
	double dOutput;
	double iCeiling;
	double iFloor;
	double dt;
};
typedef struct PID PID_t;

PID_t *PIDCreateInstance(const double desired, const double kp,
             const double ki, const double kd, const double dt);

void PIDSetIntegralLimit(PID_t* pid, const double limit);

// Reset the PID error values
void PIDReset(PID_t* pid);

// Update the PID parameters.
double PIDUpdate(PID_t* pid, const double measured, const UpdateFlag_t updateError);

// Set a new set point for the PID to track.
void PIDSetDesired(PID_t* pid, const double desired);

// Set a new set point for the PID to track.
double PIDGetDesired(PID_t* pid);

// Find out if PID is active
Active_t PIDIsActive(PID_t* pid);

// Set a new error. Use if a special error calculation is needed.
void PIDSetError(PID_t* pid, const double error);

// Set a new proportional gain for the PID.
void PIDSetKp(PID_t* pid, const double kp);

// Set a new integral gain for the PID.
void PIDSetKi(PID_t* pid, const double ki);

// Set a new derivative gain for the PID.
void PIDSetKd(PID_t* pid, const double kd);


// Set a new dt gain for the PID. Defaults to IMU_UPDATE_DT upon construction
void PIDSetDt(PID_t* pid, const double dt);

#endif