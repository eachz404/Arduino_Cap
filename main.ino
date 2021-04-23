/*!
 * MindPlus
 * uno
 *
 */
#include <UNO_Obloq.h>
#include <DFRobot_URM10.h>
#include <SoftwareSerial.h>
#include <DFRobot_Libraries.h>

// 动态变量
String         mind_s_data, mind_s_redata;
volatile float mind_n_keyval, mind_n_dis;
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
	olq.publish(olq.topic_0, "ONLINE:");
	olq.publish(olq.topic_0, olq.IPAddress);
}
void loop() {
	mind_n_keyval = digitalRead(10);
	mind_n_dis = (urm10.getDistanceCM(3, 4));
	if (((mind_n_dis<40) && (mind_n_dis>0))) {
		DFTone.play(9, 131, 500);
		delay(100);
		DFTone.play(9, 349, 500);
		delay(500);
	}
	if ((mind_n_keyval==1)) {
		Serial.println(mind_n_keyval);
		olq.publish(olq.topic_0, "Help");
		mind_s_data = "22.83503782118704, 113.2672100536825";
		olq.publish(olq.topic_0, "Location:");
		olq.publish(olq.topic_0, mind_s_data);
	}
	if ((olq.available(olq.topic_0))) {
		mind_s_redata = olq.getMessage(olq.topic_0);
	}
	if ((mind_s_redata==String("GPS"))) {
		mind_s_data = "22.83503782118704, 113.2672100536825";
		olq.publish(olq.topic_0, "Location:");
		olq.publish(olq.topic_0, mind_s_data);
	}
	if (((mind_n_dis<15) && (mind_n_dis>0))) {
		delay(3000);
		if (((mind_n_dis<15) && (mind_n_dis>0))) {
			olq.publish(olq.topic_0, "Help");
			mind_s_data = "22.83503782118704, 113.2672100536825";
			olq.publish(olq.topic_0, "Location:");
			olq.publish(olq.topic_0, mind_s_data);
		}
	}
}
