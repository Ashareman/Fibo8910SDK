/* Copyright (C) 2018 RDA Technologies Limited and/or its affiliates("RDA").
 * All rights reserved.
 *
 * This software is supplied "AS IS" without any warranties.
 * RDA assumes no responsibility or liability for the use of the software,
 * conveys no license or title under any patent, copyright, or mask work
 * right to the product. RDA reserves the right to make changes in the
 * software without notification.  RDA also make no representation or
 * warranty that such application will be suitable for the specified use
 * without further testing or modification.
 */

#ifndef _IMAGE_SENSOR_H_
#define _IMAGE_SENSOR_H_

#include "osi_compiler.h"
#include "fibocom.h"
#include "drv_config.h"

OSI_EXTERN_C_BEGIN

#include "drv_camera.h"

#ifdef CONFIG_FIBOCOM_BASE
//err code
#define  DRV_CAMERA_SUCCESS             (0)
#define  DRV_CAMERA_FAILED             (-1)
#define  DRV_CAMERA_HAS_INITED         (-2)
#define  DRV_CAMERA_NOT_INIT           (-3)
#define  DRV_CAMERA_INIT_FAILED        (-4)
#define  DRV_CAMERA_POWERON_FAILED     (-5)
#define  DRV_CAMERA_INVALID_PARAMETER  (-6)
#endif

typedef struct
{
    bool (*cameraOpen)(void);
    void (*cameraClose)(void);
    void (*cameraGetID)(uint8_t *data, uint8_t len);
    void (*cameraSetBrightness)(uint8_t level);
    void (*cameraSetContrast)(uint8_t level);
    void (*cameraSetImageEffect)(uint8_t effect_type);
    void (*cameraSetEv)(uint8_t level);
    void (*cameraSetAWB)(uint8_t mode);
    void (*cameraCaptureImage)(uint32_t size);
    void (*cameraStartPrev)(uint32_t size);
    void (*cameraStopPrev)(void);
    void (*cameraPrevNotify)(void);
    void (*cameraGetSensorInfo)(sensorInfo_t **pSensorInfo);
#ifdef CONFIG_FIBOCOM_LIANDI
    void (*cameraSetScanMode)(uint16_t scanMode);
#endif
    void (*cameraFlashSet)(uint8_t level);
} SensorOps_t;

//general sensor drv need ping-pang buffer for continus data mode
#ifdef CONFIG_CAMERA_SINGLE_BUFFER
#define SENSOR_FRAMEBUFFER_NUM (1)
#else
#define SENSOR_FRAMEBUFFER_NUM (2)
#endif

typedef struct image_dev_tag
{
    bool poweron_flag;
    uint32_t nPixcels;
    uint8_t framebuffer_count;
    sensorInfo_t *pSensorInfo;
    SensorOps_t *pSensorOpsApi;
    uint16_t *pFramebuffer[SENSOR_FRAMEBUFFER_NUM];
} IMAGE_DEV_T, *IMAGE_DEV_T_PTR;

#ifdef CONFIG_FIBOCOM_LIANDI
typedef enum
{
    CHECK_CAM_LOAD_0,
    CHECK_CAM_LOAD_1,
    CHECK_CAM_LOAD_2,
}check_cam_load_t;
#endif

typedef struct cam_dev_tag
{
    char *pNamestr;
    uint32_t img_width;
    uint32_t img_height;
    uint32_t nPixcels;
} CAM_DEV_T, *CAM_DEV_T_PTR;

bool drvCamInit(void);
#ifdef CONFIG_FIBOCOM_BASE
bool drvCamGetSensorInfo(CAM_DEV_T * pCamDevice);
#ifdef CONFIG_FIBOCOM_LIANDI
void drvCamSetScanMode(uint16_t scanMode);
#endif
#else
void drvCamGetSensorInfo(CAM_DEV_T *pCamDevice);
#endif
bool drvCamPowerOn(void);
bool drvCamStartPreview(void);
uint16_t *drvCamPreviewDQBUF(void);
void drvCamPreviewQBUF(uint16_t *pFrameBuf);
bool drvCamStopPreview(void);
bool drvCamCaptureImage(uint16_t **pFrameBuf);
bool drvCamGePrevStatus(void);
void drvCamClose(void);

OSI_EXTERN_C_END

#endif
