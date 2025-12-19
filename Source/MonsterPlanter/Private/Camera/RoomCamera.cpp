// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/RoomCamera.h"
#include "Camera/CameraDef.h"

ARoomCamera::ARoomCamera()
{
	// カメラチャンネル設定
	CameraChannel = ECameraChannel::Room1;
}
