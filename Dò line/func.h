#define ENA A0
#define ENB A5
#define IN_1 A1
#define IN_2 A2
#define IN_3 A3
#define IN_4 A4
#define l1 8
#define l2 9
#define l3 10
#define l4 11
#define l5 12
#define vr A5
bool check2Back = true;
short aheadTimes = 1;
byte speedDiv = 3;
void goAhead(int sp)
{
    check2Back = true;
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    analogWrite(ENA, sp);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    analogWrite(ENB, sp);
}
void stopCar()
{
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, 0);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, 0);
}
void goBack(int sp)
{
    if(check2Back){
        aheadTimes = 1;
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);
        analogWrite(ENA, 130);
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
        analogWrite(ENB, 130);
        delay(150);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_3, LOW);
        check2Back = false;
    }
    else if (aheadTimes >= 0)
    {
        aheadTimes-=1;
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, HIGH);
        analogWrite(ENA, 130);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, HIGH);
        analogWrite(ENB, 130);
        delay(150);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_4, LOW);
    }else if(aheadTimes < 0){
        stopCar();
    }
}
void turnLeft(int sp, int subsp)
{
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, sp);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    analogWrite(ENB, 255);
}
void turnRight(int sp, int subsp)
{
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    analogWrite(ENA, 255);
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, sp);
}


boolean IFsensor(byte pinSS)
{
    return !digitalRead(pinSS);
}
byte IFsensor_return()
{ 
    boolean ifs1 = IFsensor(l1);
    boolean ifs2 = IFsensor(l2);
    boolean ifs3 = IFsensor(l3);
    boolean ifs4 = IFsensor(l4);
    boolean ifs5 = IFsensor(l5);
    
    if (ifs1 == 0 && ifs2 == 0 && ifs3 == 0 && ifs4 == 0 && ifs5 == 0)
        return 10;
    else if (ifs1 == 1 && ifs2 == 0 && ifs3 == 0 && ifs4 == 0 && ifs5 == 0)
        return 1;
    else if (ifs1 == 1 && ifs2 == 1 && ifs3 == 0 && ifs4 == 0 && ifs5 == 0)
        return 2;
    else if (ifs1 == 0 && ifs2 == 1 && ifs3 == 0 && ifs4 == 0 && ifs5 == 0)
        return 3;
    else if (ifs1 == 0 && ifs2 == 1 && ifs3 == 1 && ifs4 == 0 && ifs5 == 0)
        return 4;
    else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 1 && ifs4 == 0 && ifs5 == 0)
        return 5;
    else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 1 && ifs4 == 1 && ifs5 == 0)
        return 6;
    else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 0 && ifs4 == 1 && ifs5 == 0)
        return 7;
    else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 0 && ifs4 == 1 && ifs5 == 1)
        return 8;
    else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 0 && ifs4 == 0 && ifs5 == 1)
        return 9;
    else if (ifs1 == 1 && ifs2 == 1 && ifs3 == 1 && ifs4 == 1 && ifs5 == 1)
        return 0;
    else if (ifs1 == 1 && ifs2 == 1 && ifs3 == 1 && ifs4 == 0 && ifs5 == 0)
        return 11;
    else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 1 && ifs4 == 1 && ifs5 == 1)
        return 12;
    else if (ifs1 == 0 && ifs2 == 1 && ifs3 == 1 && ifs4 == 1 && ifs5 == 0)
        return 13;
    else if(ifs1 == 1 && ifs2 == 1 && ifs3 == 0 && ifs4 == 0 && ifs5 == 1){
        return 5;
    }
    else if (ifs1 == 1 && ifs2 == 1 && ifs3 == 1 && ifs4 == 1 && ifs5 == 0)
    {
        return 7;
    }
    else if (ifs1 == 1 && ifs2 == 1 && ifs3 == 1 && ifs4 == 1 && ifs5 == 0)
    {
        return 3;
    }
    else if (ifs1 == 1 && ifs2 == 1 && ifs3 == 0 && ifs4 == 0 && ifs5 == 0)
    {
        return 9;
    }
    else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 0 && ifs4 == 1 && ifs5 == 1)
    {
        return 1;
    }
}
