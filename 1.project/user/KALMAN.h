/*
SimpleKalmanFilter - a Kalman Filter implementation for single variable models.
Created by Denys Sene, January, 1, 2017.
Released under MIT License - see LICENSE file for details.
*/
#ifndef KALMAN_H_
#define KALMAN_H_
// class SimpleKalmanFilter
void SimpleKalmanFilter(int index, float mea_e, float est_e, float q);
float updateEstimate(int index, float mea);
void setMeasurementError(int index, float mea_e);
void setEstimateError(int index, float est_e);
void setProcessNoise(int index, float q);
float getKalmanGain(int index);
float getEstimateError(int index);
#endif
