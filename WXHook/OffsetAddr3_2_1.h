#pragma once
// 微信版本 3.2.1.154

/***************** 登录 ******************/
#define ISLOGIN		0x1AD4588			// 0-->扫码  1-->正在登录 2-->已登录状态
#define ISLOGINWXID 0x18A6290 + 0x4		// 登录成功存储 wxid_

#define GOTOQRCODE1		0x264830			// 跳转到二维码界面 264830 3ADE40
#define GOTOQRCODE2		0x3ADE40
// #define QRCODEWEB		0x178F9C0			// 二维码短链地址
#define QRCODEPICTURE   0x266A3D				// hook的二维码图片地址
#define QRCODEHOOKADDR  0x58BC80

/************** 一键备份 ****************/
#define BACKUPSTR	0x14F17C8				// 按钮的名称字符
#define GOTOBACKUP1	0x3BE220				// 调用函数
#define GOTOBACKUP2	0x3BF510

/************ 手机聊天备份至电脑 ************/

#define BACKUPTOCOMPUTER1	0xDD7C97		//手机聊天记录备份到电脑
#define BACKUPTOCOMPUTER2	0x658D00		
#define BACKUPTOCOMPUTER3	0x28C0D0

#define BACKUPWD1			0x4CB996		//	备份时返回的密钥基址
#define BACKUPWD2			0x962530

// 重连时调用的call地址与直接点击时重复的一段，测试可用
#define CONNECTBACKUP1		0x255C90
#define CONNECTBACKUP2		0x6E14B0
#define CONNECTBACKUP3		0x412ED0
#define CONNECTBACKUP4		0x4142A0

// 保存备份的密钥
#define BACKUPKEY1			0xAA3AE0		// A1A7C0
#define DBHOOKADDR			0x52D8E8		// 5152F8
