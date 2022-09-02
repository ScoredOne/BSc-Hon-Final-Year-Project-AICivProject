// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "SpectatorCamera.generated.h"

UCLASS()
class AICIVPROJECTV1_API ASpectatorCamera : public ASpectatorPawn
{
	GENERATED_UCLASS_BODY()

public:

	//------------------------------------

	/** Camera Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* CameraComponent;

	//------------------------------------

	/** Camera Rotation around Axis Z */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraZAnlge;

	/** Camera Height Angle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraHeightAngle;

	/** Camera Pitch Angle Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraHeightAngleMax;

	/** Camera Pitch Angle Min */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraHeightAngleMin;

	/** Camera Radius From Pawn Position */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraRadius;

	/** Camera Radius Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraRadiusMax;

	/** Camera Radius Min */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraRadiusMin;

	/** Camera Zoom Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraZoomSpeed;

	/** Camera Rotation Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraRotationSpeed;

	/** Camera Movement Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraMovementSpeed;

	/** Camera Scroll Boundary */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraScrollBoundary;

	/** Should the camera move? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		bool bCanMoveCamera;

	//------------------------------------

private:

	/** Sets up player inputs
	*    @param InputComponent - Input Component
	*/
	void SetupPlayerInputComponent(class UInputComponent* InputComponent);

	//------------------------------------

public:

	/** Zooms In The Camera */
	void ZoomInByWheel();

	/** Zooms Out The Camera */
	void ZoomOutByWheel();

	/** Rotate The Camera Left */
	void RotateLeftByWheel();

	/** Rotate The Camera Right */
	void RotateRightByWheel();

	/** Rotate The Camera Up */
	void RotateUpByWheel();

	/** Rotate The Camera Down */
	void RotateDownByWheel();

	//---

	/** Calculates the new Location and Rotation of The Camera */
	void RepositionCamera();

	//------------------------------------

private:

	// set them to +/-1 to get player input from keyboard
	float FastMoveValue;                                            // movement speed multiplier : 1 if shift unpressed, 2 is pressed
	float RotateValue;                                                // turn instead of move camera

	float MoveForwardValue;
	float MoveRightValue;
	float MoveUpValue;
	float ZoomInValue;

	//---

public:

	/** Left or Right Shift is pressed
	* @param direcation - (1.0 for Right, -1.0 for Left)
	*/
	void FastMoveInput(float Direction);

	/** Left or Right Ctrl is pressed
	* @param direcation - (1.0 for Right, -1.0 for Left)
	*/
	void RotateInput(float Direction);

	/** Input recieved to move the camera forward
	* @param direcation - (1.0 for forward, -1.0 for backward)
	*/
	void MoveCameraForwardInput(float Direction);

	/** Input recieved to move the camera right
	* @param direcation - (1.0 for right, -1.0 for left)
	*/
	void MoveCameraRightInput(float Direction);

	/** Input recieved to move the camera right
	* @param direcation - (1.0 for right, -1.0 for left)
	*/
	void MoveCameraUpInput(float Direction);

	/** Input recieved to move the camera right
	* @param direcation - (1.0 for right, -1.0 for left)
	*/
	void ZoomCameraInInput(float Direction);

	//---

private:

	/** Moves the camera forward
	* @param direcation - (+ forward, - backward)
	*/
	void MoveCameraForward(float Direction);

	/** Moves the camera right
	* @param direcation - (+ right, - left)
	*/
	void MoveCameraRight(float Direction);

	/** Gets the rotation of the camera with only the yaw value
	* @return - returns a rotator that is (0, yaw, 0) of the Camera
	*/
	FRotator GetIsolatedCameraYaw();

	//---

	/** Moves the camera up/down
	* @param direcation - (+ up, - down)
	*/
	void MoveCameraUp(float Direction);

	//---

	/** Zooms the camera in/out
	* @param direcation - (+ in, - out)
	*/
	void ZoomCameraIn(float Direction);

	/** Turns the camera up/down
	* @param direcation - (+ up, - down)
	*/
	void TurnCameraUp(float Direction);

	/** Turns the camera right/left
	* @param direcation - (+ right, - left)
	*/
	void TurnCameraRight(float Direction);

	//------------------------------------

public:

	/** Tick Function, handles keyboard inputs */
	virtual void Tick(float DeltaSeconds) override;

	//------------------------------------
};
