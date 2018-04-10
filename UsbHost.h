
#ifndef _USBHOST_H_
#define _USBHOST_H_

// ���ӳ��򷵻�״̬��
#define ERR_SUCCESS         0x00    // �����ɹ�
#define ERR_USB_CONNECT     0x15    /* ��⵽USB�豸�����¼�,�Ѿ����� */
#define ERR_USB_DISCON      0x16    /* ��⵽USB�豸�Ͽ��¼�,�Ѿ��Ͽ� */
#define ERR_USB_BUF_OVER    0x17    /* USB��������������������̫�໺������� */
#define ERR_USB_DISK_ERR    0x1F    /* USB�洢������ʧ��,�ڳ�ʼ��ʱ������USB�洢����֧��,�ڶ�д�����п����Ǵ����𻵻����Ѿ��Ͽ� */
#define ERR_USB_TRANSFER    0x20    /* NAK/STALL�ȸ����������0x20~0x2F */
#define ERR_USB_UNSUPPORT   0xFB    /*��֧�ֵ�USB�豸*/
#define ERR_USB_UNKNOWN     0xFE    /*�豸��������*/


/* ����״̬��������USB������ʽ */
/*   λ4ָʾ��ǰ���յ����ݰ��Ƿ�ͬ��, 0=��ͬ��, 1-ͬ�� */
/*   λ3-λ0ָʾUSB�豸��Ӧ��: 0010=ACK, 1010=NAK, 1110=STALL, 0011=DATA0, 1011=DATA1, XX00=Ӧ�������߳�ʱ��Ӧ�� */
#ifndef	USB_INT_RET_ACK
#define	USB_INT_RET_ACK		     USB_PID_ACK		/* ����:����OUT/SETUP���񷵻�ACK */
#define	USB_INT_RET_NAK		     USB_PID_NAK		/* ����:����NAK */
#define	USB_INT_RET_STALL	     USB_PID_STALL	/* ����:����STALL */
#define	USB_INT_RET_DATA0	     USB_PID_DATA0	/* ����:����IN���񷵻�DATA0 */
#define	USB_INT_RET_DATA1	     USB_PID_DATA1	/* ����:����IN���񷵻�DATA1 */
#define	USB_INT_RET_TOUT	     0x00			/* ����:Ӧ�������߳�ʱ��Ӧ�� */
#define	USB_INT_RET_TOUT1	     0x04			/* ����:Ӧ�������߳�ʱ��Ӧ�� */
#define	USB_INT_RET_TOUT2	     0x08			/* ����:Ӧ�������߳�ʱ��Ӧ�� */
#define	USB_INT_RET_TOUT3	     0x0C			/* ����:Ӧ�������߳�ʱ��Ӧ�� */
#endif

//number of root hub ports
#define ROOT_HUB_PORT_NUM      2

//maximum number of external hub ports
#define MAX_EXHUB_PORT_NUM     4

//none external hub port
#define EXHUB_PORT_NONE        0xff

//maximum number of interfaces per devicve
#define MAX_INTERFACE_NUM      4
//maximum number of endpoints per interface
#define MAX_ENDPOINT_NUM       3
//maximum level of external hub
#define MAX_EXHUB_LEVEL        1

//in 
#define ENDPOINT_OUT           0
//out
#define ENDPOINT_IN            1

//endpoint struct
typedef struct _ENDPOINT
{
	UINT8 EndpointAddr;
	UINT16 MaxPacketSize;
	
	UINT8 EndpointDir : 1;
	UINT8 TOG : 1;
} ENDPOINT, *PENDPOINT;

//hid report define
#define TAG_USAGE         0x00

#define TAG_USAGE_PAGE    0x00
#define TAG_REPORT_SIZE   0x07
#define TAG_REPORT_COUNT  0x09
#define TAG_REPORT_ID     0x08

#define TAG_INPUT         0x08

#define TYPE_MAIN         0
#define TYPE_GLOBAL       1
#define TYPE_LOCAL        2

//usage page
#define USAGE_PAGE_NONE    0x00
#define USAGE_PAGE_BUTTON  0x09
//usage
#define USAGE_NONE         0x00
#define USAGE_X            0x30
#define USAGE_Y            0x31
#define USAGE_WHEEL        0x38

typedef struct _USAGE
{
	UINT8  usage[4];

	UINT8  usageLen;
} USAGE;

//hid item
typedef struct _HID_ITEM_INFO
{
   	union
    {
       struct 
       {
           UINT8             ItemSize :2;
           UINT8             ItemType :2; 
           UINT8             ItemTag  :4; 
       } ItemVal;
       
       UINT8                 val;
    } ItemDetails;

} HID_ITEM_INFO; 

//mouse struct
typedef struct _MOUSEDATA_STRUCT
{
	UINT8  buttonStart; //bit offset of button data
	UINT8  buttonSize;  //bit size of button data
	
	UINT8  xStart;		//bit offset of x data
	UINT8  xSize;       //bit size of x data
	
	UINT8  yStart;		//bit offset of y data
	UINT8  ySize;       //bit size of y data
	
	UINT8  wheelStart;	//bit offset of wheel data
	UINT8  wheelSize;   //bit size of wheel data
} MOUSEDATA_STRUCT;

//interface struct
typedef struct _INTERFACE
{
	UINT8     InterfaceClass;
	UINT8     InterfaceProtocol;
	
	UINT8     EndpointNum;   //number of endpoints in this interface
	ENDPOINT  Endpoint[MAX_ENDPOINT_NUM]; //endpoints
	
	MOUSEDATA_STRUCT  MouseDataStruct;	
} INTERFACE, *PINTERFACE;

//device struct
typedef struct _USB_DEVICE
{
	UINT8       DeviceClass;
	UINT8       MaxPacketSize0;
	
	UINT16      VendorID;
	UINT16      ProductID;
	UINT16      bcdDevice;

	UINT8       DeviceAddress;
	UINT8       DeviceSpeed;
	UINT8       InterfaceNum;
	INTERFACE   Interface[MAX_INTERFACE_NUM];
	
	UINT8       HubPortNum;
} USB_DEVICE, *PUSB_DEVICE;

//hub struct
#define  PORT_DEVICE_NONE         0
#define  PORT_DEVICE_INSERT       1
#define  PORT_DEVICE_ENUM_FAILED  2
#define  PORT_DEVICE_ENUM_SUCCESS 3

typedef struct _USB_HUB_PORT
{
	UINT8  HubPortStatus;
	USB_DEVICE UsbDevice;
	
} USB_HUB_PORT, *USB_PHUB_PORT;

#define  LOW_SPEED      0
#define  FULL_SPEED     1


extern void InitUsbHost(void);
extern void InitUsbData(void);
extern void DealUsbPort(void);
extern void InterruptProcessRootHubPort(UINT8 port_index);
extern void UpdateUsbKeyboardLed(UINT8 led);

#endif

