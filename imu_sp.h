#ifndef __IMU_SP_H
#define __IMU_SP_H

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <serialPort.h>
#include <unistd.h>
namespace ly {
int sb_sum_chech(const char byte_temp[]);
int find_first_package(const char buffer[]);
void read_data(void);
//extern class serialPort;
}


#endif // __IMU_SP_H
