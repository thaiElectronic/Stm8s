#include "KALMAN.h"
#include "stdint.h"
#include "math.h"

typedef struct EKF{
  float _err_measure;
  float _err_estimate;
  float _q;
  float _current_estimate;
  float _last_estimate;
  float _kalman_gain;
} Ekf;

Ekf ekf[20];

void SimpleKalmanFilter(int index, float mea_e, float est_e, float q){
  ekf[index]._err_measure = mea_e;
  ekf[index]._err_estimate = est_e;
  ekf[index]._q = q;
}

float updateEstimate(int index, float mea)
{
  ekf[index]._kalman_gain = ekf[index]._err_estimate/(ekf[index]._err_estimate + ekf[index]._err_measure);
  ekf[index]._current_estimate = ekf[index]._last_estimate + ekf[index]._kalman_gain * (mea - ekf[index]._last_estimate);
  ekf[index]._err_estimate = ((1.0 - ekf[index]._kalman_gain)*(ekf[index]._err_estimate)) + fabs((ekf[index]._last_estimate - ekf[index]._current_estimate)*(ekf[index]._q));
  ekf[index]._last_estimate = ekf[index]._current_estimate;
  return ekf[index]._current_estimate;
}
void setMeasurementError(int index, float mea_e)
{
  ekf[index]._err_measure = mea_e;
}
void setEstimateError(int index, float est_e)
{
  ekf[index]._err_estimate = est_e;
}
void setProcessNoise(int index, float q)
{
  ekf[index]._q=q;
}
float getKalmanGain(int index) {
  return ekf[index]._kalman_gain;
}
float getEstimateError(int index) {
  return ekf[index]._err_estimate;
}
