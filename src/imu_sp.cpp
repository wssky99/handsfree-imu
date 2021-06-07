#include <iostream>
#include "imu_sp.h"

using namespace std;
namespace ly
{
void read_data()
{
  //设置串口名，配置串口类
  std::string portName;
  portName = "/dev/ttyUSB0";
  //extern class serialPort;
  serialPort imu_port(portName);
  //初始化各数据
   short int linear_acceleration_x = 0;
   short int linear_acceleration_y = 0;
   short int linear_acceleration_z = 0;
   short int angular_velocity_x = 0;
   short int angular_velocity_y = 0;
   short int angular_velocity_z = 0;
   short int angle_x = 0;
   short int angle_y = 0;
   short int angle_z = 0;
   short int magnetic_field_x = 0;
   short int magnetic_field_y = 0;
   short int magnetic_field_z = 0;
   unsigned char *msg ;
   unsigned char *temp1 ;
   unsigned char *temp2 ;
   unsigned char flag1[1];
   unsigned char flag2[1];
   unsigned char data[9];
   msg = data;
   temp1 = flag1;
   temp2 = flag2;    
        
   //连续读取
   while(1)
   {    
        //sleep(0.5);//延时
        int answer1 = imu_port.SP_Read(temp1,1);//读取串口数据,判断是否为0x55
        if(flag1[0] == 0x55)
        {
          //printf("\r\n""%d", temp1[0]);
          int answer2 = imu_port.SP_Read(temp2,1);//读取串口数据,判断是否为0x51-0x54
          if(flag2[0] == 0x51)//加速度数据
          {
            //printf("\t""%d", temp2[0]);
            int answer3 = imu_port.SP_Read(msg,9);//读取串口数据
            int temp3 = (data[0]+data[1]+data[2]+data[3]+data[4]+data[5]+data[6]+data[7]+0x55+0x51)& 0xff;

            if (temp3 == data[8])
            {
                //printf("\t""校验成功！");
                linear_acceleration_x = (((short)data[1] <<8) | data[0]) ;
                linear_acceleration_y = (((short)data[3] <<8) | data[2]) ;
                linear_acceleration_z = (((short)data[5] <<8) | data[4]) ;
                printf("加速度:""\r\n");
                printf("\t" "x轴加速度：" "\t" "%0.2f" "m/s2" "\r\n", (float)linear_acceleration_x/ 32768.0 * 16 * -9.8);
                printf("\t" "y轴加速度：" "\t" "%0.2f" "m/s2" "\r\n", (float)linear_acceleration_y/ 32768.0 * 16 * -9.8);
                printf("\t" "z轴加速度：" "\t" "%0.2f" "m/s2" "\r\n" "\r\n", (float)linear_acceleration_z/ 32768.0 * 16 * -9.8);
           }
           else
           {
                printf("校验错误！");
           }

        }

          else if(flag2[0] == 0x52)//角速度数据
          {
                 //printf("\t""%d", temp2[0]);
                 int answer3 = imu_port.SP_Read(msg,9);//读取串口数据
                 int temp3 = (data[0]+data[1]+data[2]+data[3]+data[4]+data[5]+data[6]+data[7]+0x55+0x52)& 0xff;
                 if (temp3 == data[8])
                 {
                    //printf("\t""校验成功！");
                    angular_velocity_x =( ((short)data[1] <<8) | data[0]) ;
                    angular_velocity_y =( ((short)data[3] <<8) | data[2]) ;
                    angular_velocity_z =( ((short)data[5] <<8) | data[4]) ;
                    printf("角速度:""\r\n");
                    printf("\t" "x轴角速度：" "\t" "%0.2f" "°/s" "\r\n", (float)angular_velocity_x / 32768.0 * 2000 * M_PI / 180);
                    printf("\t" "y轴角速度：" "\t" "%0.2f" "°/s" "\r\n", (float)angular_velocity_y / 32768.0 * 2000 * M_PI / 180);
                    printf("\t" "z轴角速度：" "\t" "%0.2f" "°/s" "\r\n" "\r\n", (float)angular_velocity_z / 32768.0 * 2000 * M_PI / 180);
                 }
                 else
                 {
                      printf("校验错误！");
                 }
          }
          else if(flag2[0] == 0x53)//角度数据
          {
                 //printf("\t""%d", temp2[0]);
                 int answer3 = imu_port.SP_Read(msg,9);//读取串口数据
                 int temp3 = (data[0]+data[1]+data[2]+data[3]+data[4]+data[5]+data[6]+data[7]+0x55+0x53)& 0xff;
                 if (temp3 == data[8])
                 {
                    //printf("\t""校验成功！");
                    angle_x = ( ((short)data[1] <<8) | data[0]) ;
                    angle_y = ( ((short)data[3] <<8) | data[2]) ;
                    angle_z = ( ((short)data[5] <<8) | data[4]) ;
                    printf("角度:""\r\n");
                    printf("\t" "x轴角度：" "\t" "%0.2f" "°" "\r\n", (float)angle_x / 32768.0 * 180);
                    printf("\t" "y轴角度：" "\t" "%0.2f" "°" "\r\n", (float)angle_y / 32768.0 * 180);
                    printf("\t" "z轴角度：" "\t" "%0.2f" "°" "\r\n" "\r\n", (float)angle_z / 32768.0 * 180);
                 }
                 else
                 {
                      printf("校验错误！");
                 }
          }
          else if(flag2[0] == 0x54)//磁场数据
          {
                 int answer3 = imu_port.SP_Read(msg,9);//读取串口数据
                 int temp3 = (data[0]+data[1]+data[2]+data[3]+data[4]+data[5]+data[6]+data[7]+0x55+0x54)& 0xff;
                 if (temp3 == data[8])
                 {
                    //printf("\t""校验成功！");
                    magnetic_field_x =( ((short)data[1] <<8) | data[0]) ;
                    magnetic_field_y =( ((short)data[3] <<8) | data[2]) ;
                    magnetic_field_z =( ((short)data[5] <<8) | data[4]) ;
                    printf("磁场:""\r\n");
                    printf("\t" "x轴磁场：" "\t" "%0.2f" "mG" "\r\n", (float)magnetic_field_x);
                    printf("\t" "y轴磁场：" "\t" "%0.2f" "mG" "\r\n", (float)magnetic_field_y);
                    printf("\t" "z轴磁场：" "\t" "%0.2f" "mG" "\r\n" "\r\n", (float)magnetic_field_z);
                 }
                 else
                 {
                      printf("校验错误！");
                 }    
          }

        }

    }
}
}

