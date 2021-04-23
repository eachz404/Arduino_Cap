#include <UNO_Obloq.h>
#include <DFRobot_URM10.h>
#include <SoftwareSerial.h>
#include <DFRobot_Libraries.h>

// 动态变量
String         data, redata;
volatile float keyval, dis;
// 静态常量
const String topics[5] = {"HStRA_XGg","","","",""};
// 创建对象
UNO_Obloq      olq;
SoftwareSerial softSerial(2, 6);
DFRobot_URM10  urm10;
DFRobot_Tone   DFTone;


// 主程序开始
void setup() {
	softSerial.begin(9600);
  olq.startConnect(&softSerial, "lz-9_2.4G", "sdlz2018", "kpvRAlXGg", "kpDgAluMgz", topics, "iot.dfrobot.com.cn", 1883);
	Serial.begin(9600);
	Serial.println(olq.IPAddress);
	olq.publish(olq.topic_0, "Online");
}
void loop() {
	keyval = digitalRead(5);
	dis = (urm10.getDistanceCM(3, 4));
	if (((dis<40) && (dis>0))) {
		DFTone.play(9, 131, 500);
		delay(500);
		DFTone.play(9, 349, 500);
		delay(100);
	}
	if ((keyval==1)) {
		olq.publish(olq.topic_0, "Help");
		if ((Serial.available())) {
			data = Serial.read();
			olq.publish(olq.topic_0, "Location:");
			olq.publish(olq.topic_0, data);
			keyval = 0;
		}
	}
	if ((Serial.available())) {
		data = Serial.read();
		olq.publish(olq.topic_0, "Location:");
		olq.publish(olq.topic_0, data);
	}
	if ((olq.available(olq.topic_0))) {
		redata = olq.getMessage(olq.topic_0);
		Serial.println(redata);
	}
	if ((redata==String("GPS"))) {
		if ((Serial.available())) {
			data = Serial.read();
			olq.publish(olq.topic_0, "Location:");
			olq.publish(olq.topic_0, data);
		}
	}
	if (((dis<15) && (dis>0))) {
		delay(3000);
		if (((dis<15) && (dis>0))) {
			olq.publish(olq.topic_0, "Help");
			data = Serial.read();
			olq.publish(olq.topic_0, "Location:");
			olq.publish(olq.topic_0, data);
		}
	}
}
