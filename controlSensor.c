/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <stdio.h>
#include "car_lib.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define LIGHT_BEEP 0     // to test light and beep
#define POSITION_CONTROL 0  // to test postion control
#define SPEED_CONTROL 0    // to test speed control
#define SERVO_CONTROL 0    // to test servo control(steering & camera position)
#define LINE_TRACE 0             // to test line trace sensor
#define DISTANCE_SENSOR 1    // to test distance sensor

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
void main(void)
{
    unsigned char status;
    short speed;
    unsigned char gain;
    int position, posInit, posDes, posRead;
    short angle;
    int channel;
    int data;
    char sensor;
    int i, j;
    int tol;
    char byte = 0x80;
    int test;

    CarControlInit();

while(1)
{
    printf("Which test?(1: Position, 2: Servo, 3: Sensor) : ");
    scanf("%d", &test);


if(test == 1) // POSITION_CONTROL
{
        SpeedControlOnOff_Write(CONTROL);

    //P-gain
    gain = SpeedPIDProportional_Read();        // default value = 10, range : 1~50
    printf("SpeedPIDProportional_Read() = %d \n", gain);
    gain = 20;
    SpeedPIDProportional_Write(gain);

    //I-gain
    gain = SpeedPIDIntegral_Read();        // default value = 10, range : 1~50
    printf("SpeedPIDIntegral_Read() = %d \n", gain);
    gain = 30;
    SpeedPIDIntegral_Write(gain);
    
    //D-gain
    gain = SpeedPIDDifferential_Read();        // default value = 10, range : 1~50
    printf("SpeedPIDDefferential_Read() = %d \n", gain);
    gain = 20;
    SpeedPIDDifferential_Write(gain);

    gain = 30;
    PositionProportionPoint_Write(gain);

    speed = 50; // speed set     --> speed must be set when using position controller
    DesireSpeed_Write(speed);

    while(1)
    {
        printf("put your speed and destination(exit: 0) : ");
        scanf("%d %d", &speed, &position);
        if(speed == 0) break;

        DesireSpeed_Write(speed);
        moveDestination(position);
    }
} 


else if(test == 2) // SERVO_CONTROL
{
    int dir;

    speed = 80; // speed set     --> speed must be set when using position controller
    DesireSpeed_Write(speed);
    while(1)
    {
        printf("go / return / setting(1/2/3) (exit: 0) : ");
        scanf("%d", &dir);
        if(dir == 0) {
            break;
        }
        else if(dir == 1)
        {
            moveDestination(2000);
        }
        else if(dir == 2)
        {
            moveDestination(-2000);
        }
        else if(dir == 3)
        {
            printf("put your steering angle(exit: 0) : ");
            scanf("%d", &angle);

            SteeringServoControl_Write(angle);
        }
        else
        {
            continue;
        }
    }
} 

else if (test == 3) // DISTANCE_SENSOR
{ 
    // 5. distance sensor --------------------------------------------------------
    for(i=0; i<1000; i++)
    {
        printf("Please input ADC channel number(exit: 0) :");
        scanf("%d", &channel);
        if(channel == 0) break;

        for(j=0; j<50; j++)
        {
            data = DistanceSensor(channel);
            printf("channel = %d, distance = 0x%04X(%d) \n", channel, data, data);
            usleep(100000);
        }
    } 
}

}
}


