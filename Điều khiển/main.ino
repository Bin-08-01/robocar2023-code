// Khai báo các thư viện cần thiết
#include <stdio.h>
#include <stdint.h>
#include <ServoTimer2.h>
#include <SoftwareSerial.h>

// Chọn cổng cho module bluetooth HC05, ở đây là 0, 1
SoftwareSerial HC05 (9, 8);// RX = 0, TX = 1

// Khai báo các Servo, ở đây là 3 servo
ServoTimer2 SERVO_1, SERVO_2, SERVO_3;

// Khai báo các cổng cho các servo
#define Servo_PIN_1 3
#define Servo_PIN_2 6
#define Servo_PIN_3 11

// Khai báo các cổng cho mạch điều khiển động cơ L298N
#define ENA A0 
#define IN_1 A1
#define IN_2 A2
#define IN_3 A3
#define IN_4 A4 
#define ENB A5 

// Khai báo góc quay của servo
uint16_t count_Servo_1 = 900;
uint16_t count_Servo_2 = 1200;
uint16_t count_Servo_3 = 1500;

int speedCar = 255; // Tốc độ xe mặc định
int speedDiv = 2; // Tỉ lệ tốc độ giảm của xe khi cua

// Khai báo các hàm
void Control_Servo();
void Control_Motor();
void goAhead(int sp);
void goBack(int sp);
void turnLeft(int sp);
void turnRight(int sp);
void goAheadLeft(int sp);
void goAheadRight(int sp);
void goBackLeft(int sp);
void goBackRight(int sp);
void stopCar();

void setup()
{
    // kết nối servo với các cổng đã được khai báo ở trên
    SERVO_1.attach(Servo_PIN_1); 
    SERVO_2.attach(Servo_PIN_2);
    SERVO_3.attach(Servo_PIN_3);
    Delay_MS(1);
    SERVO_1.write(count_Servo_1);
    SERVO_2.write(count_Servo_2);
    SERVO_3.write(count_Servo_3);

    // 2 câu lệnh dưới dùng để khởi tạo tốc độ baud rate của module HC05 và Serial, 9600 b/s là tốc độ truyền nhận dữ liệu với thiết bị ngoại vi 
    Serial.begin(9600);
    HC05.begin(9600);

    // Cấu hình các chân của mạch điều khiển động cơ L298N
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    // Điều chỉnh tốc độ quay của các động cơ lúc khởi tạo
    analogWrite(ENA, speedCar);
    analogWrite(ENB, speedCar);
}

// Function này mục đích là để tạo khoảng thời gian nghỉ lúc động cơ, servo đang trong quá trình thực thi lệnh
void Delay_MS(unsigned long ms)
{
    unsigned long start_time = millis();
    while (millis() - start_time < ms)
    {
    }
}

// Function này là hàm mà chương trình sẽ được nạp vào và thực thi ngay bởi mạch arduino.
/*Cụ thể:
- Khi nạp chương trình vào, hàm ControlMotor() sẽ được gọi và bây giờ có thể điều khiển các động cơ để xe di chuyển
- Trong hàm ControlMotor() các các biểu thức điều kiện switch case để xác định mệnh lệnh nhận vào. Khi mệnh lệnh nhận vào có giá trị là 'W' thì bảng điều khiển sẽ được chuyển sang cho điều khiển động cơ servo tay cẩu.
*/
void loop()
{
    ControlMotor();
}

void ControlMotor(){
    while (true) // Khởi tạo vòng lặp
    {
        if (HC05.available()) // Kiểm tra nếu kết nối của module HC05 được thiết lập thành công thì chương trình sẽ chạy
        {
            char data = HC05.read(); // Đọc dữ liệu được gửi đến module HC05
            Serial.println(data); // In ra giá trị của dữ liệu
            switch (data) // Biểu thưc điều kiện
            {
            case 'W':
                goto Out; 
                break;
            // Từ 0-q thay đổi tốc độ của xe
            case '0':
                speedCar = 400; 
                break;
            case '1':
                speedCar = 450;
                break;
            case '2':
                speedCar = 540;
                break;
            case '3':
                speedCar = 610;
                break;
            case '4':
                speedCar = 680;
                break;
            case '5':
                speedCar = 820;
                break;
            case '6':
                speedCar = 880;
                break;
            case '7':
                speedCar = 900;
                break;
            case '8':
                speedCar = 980;
                break;
            case '9':
                speedCar = 500;
                break;
            case 'q':
                speedCar = 1023;
                break;
            // Điều hướng xe
            case 'F':
                goAhead(speedCar);
                break;
            case 'B':
                goBack(speedCar);
                break;
            case 'R':
                turnRight(speedCar);
                break;
            case 'L':
                turnLeft(speedCar);
                break;
            case 'G':
                goAheadLeft(speedCar);
                break;
            case 'I':
                goAheadRight(speedCar);
                break;
            case 'H':
                goBackLeft(speedCar);
                break;
            case 'J':
                goBackRight(speedCar);
                break;
            case 'S':
                stopCar();
                break;
            }
        }
        else{
          Serial.println("Fail");
        }
    }
    Out:
      ControlServo();
}

void ControlServo(){
    while (true)
    {
        if (HC05.available() > 0)
        {
            char data = HC05.read();
            Serial.println(data);
            switch (data)
            {
            case 'W':
                Serial.println("Goto Motor channel.");
                count_Servo_1 = 900;
                count_Servo_2 = 1200;
                count_Servo_3 = 1500;
                Control_Servo_1(count_Servo_1);
                Control_Servo_2(count_Servo_2);
                Control_Servo_3(count_Servo_3);
                goto Out;
                break;
            case 'U':
                count_Servo_1 = 1500;
                Control_Servo_1(count_Servo_1);
                break;
            case 'u':
                count_Servo_1 = 900;
                Control_Servo_1(count_Servo_1);
                break;
            case 'L':
                if (count_Servo_2 >= 2100)
                {
                    count_Servo_2 = 2100;
                    Control_Servo_2(count_Servo_2);
                }
                else
                {
                    count_Servo_2 += 50;
                    Control_Servo_2(count_Servo_2);
                }
                break;
            case 'R':
                if (count_Servo_2 <= 1200)
                {
                    count_Servo_2 = 1200;
                    Control_Servo_2(count_Servo_2);
                }
                else
                {
                    count_Servo_2 -= 50;
                    Control_Servo_2(count_Servo_2);
                }
                break;
            case 'F':
                Serial.println("S3-F");
                if (count_Servo_3 >= 2240)
                {
                    count_Servo_3 = 2240;
                    Control_Servo_3(count_Servo_3);
                }
                else
                {
                    count_Servo_3 += 50;
                    Control_Servo_3(count_Servo_3);
                }
                break;
            case 'B':
                if (count_Servo_3 <= 1200)
                {
                    count_Servo_3 = 1200;
                    Control_Servo_3(count_Servo_3);
                }
                else
                {
                    count_Servo_3 -= 50;
                    Control_Servo_3(count_Servo_3);
                }
                break;
            case 'S':
                break;
            }
        }
    }
    Out:
        ControlMotor();
}

void Control_Servo_1(uint16_t rotation)
{
    uint16_t temp = 900;

    if (temp < rotation)
    {
        for (uint16_t i = temp; i <= rotation; i += 50)
        {
            Delay_MS(10);
            SERVO_1.write(i);
            Delay_MS(10);
        }
    }
    else
    {
        SERVO_1.write(temp);
        // Delay_MS(100);
        Serial.print("s1 = ");
        Serial.println(temp);
    }
    Serial.print("R-s1 = ");
    Serial.println(rotation);
}
void Control_Servo_2(uint16_t rotation)
{
    Delay_MS(100);
    SERVO_2.write(rotation);
    Serial.print("S2F1 = ");
    Serial.println(rotation);
}
void Control_Servo_3(uint16_t rotation)
{
    Delay_MS(100);
    SERVO_3.write(rotation);
    Serial.print("S3F1 = ");
    Serial.println(rotation);
}


/**
 * Function motor
 */

// digitalWrite() gồm 2 tham số, tham số 1 là chân cần truyền vào giá trị, tham số 2 là LOW(0) hoặc HIGH(1) là giá trị cần để cho mạch điều khiển biết tín hiệu bật/tắt đầu ra trên chân được chọn.
void goAhead(int sp) 
{
    
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, sp);
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, sp);
    Serial.println(sp);
}
void goBack(int sp)
{
    digitalWrite(IN_1, LOW); 
    digitalWrite(IN_2, HIGH);
    analogWrite(ENA, sp);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    analogWrite(ENB, sp);
    Serial.println(sp);
}
void turnRight(int sp)
{
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, sp);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    analogWrite(ENB, sp);
    Serial.println(sp);
}
void turnLeft(int sp)
{
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    analogWrite(ENA, sp);
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, sp);
    Serial.println(sp);
}
void goAheadLeft(int sp)
{
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    analogWrite(ENA, sp / speedDiv);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    analogWrite(ENB, sp);
    Serial.println(sp);
}
void goAheadRight(int sp)
{
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    analogWrite(ENB, sp / speedDiv);

    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    analogWrite(ENA, sp);
    Serial.println(sp);
}
void goBackLeft(int sp)
{
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, sp / speedDiv);
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, sp);
    Serial.println(sp);
}
void goBackRight(int sp)
{
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, sp / speedDiv);

    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, sp);
    Serial.println(sp);
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
