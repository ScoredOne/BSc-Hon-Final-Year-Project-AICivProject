// Fill out your copyright notice in the Description page of Project Settings.

#include "AICivProjectV1.h"
#include "SpectatorCamera.h"


//////////////////////////////////////////////////////////////////


ASpectatorCamera::ASpectatorCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// enable Tick function
	PrimaryActorTick.bCanEverTick = true;

	// disable standard WASD movement
	bAddDefaultMovementBindings = false;

	// not needed Pitch Yaw Roll
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// set defaults
	CameraRadius = 900.0f;
	CameraRadiusMin = 100.0f;                // min height
	CameraRadiusMax = 1000.0f;                // max height

	CameraZAnlge = 0.0;                        // yaw

	CameraHeightAngle = 30.0f;                // pitch
	CameraHeightAngleMin = 15.0f;
	CameraHeightAngleMax = 60.0f;

	CameraZoomSpeed = 200.0f;                // wheel
	CameraRotationSpeed = 10.0f;            // wheel + ctrl
	CameraMovementSpeed = 3000.0f;            // in all directions

	CameraScrollBoundary = 25.0f;            // screen edge width

	bCanMoveCamera = true;

	// intialize the camera
	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("RTS Camera"));
	CameraComponent->AttachParent = GetRootComponent();
	CameraComponent->bUsePawnControlRotation = false;
	RepositionCamera();
}


//////////////////////////////////////////////////////////////////


void ASpectatorCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	Super::SetupPlayerInputComponent(InputComponent);

	// mouse zoom
	InputComponent->BindAction("ZoomOutByWheel", IE_Pressed, this, &ASpectatorCamera::ZoomOutByWheel);
	InputComponent->BindAction("ZoomInByWheel", IE_Pressed, this, &ASpectatorCamera::ZoomInByWheel);

	// mouse rotate (+Ctrl or +Alt)
	InputComponent->BindAction("RotateLeftByWheel", IE_Pressed, this, &ASpectatorCamera::RotateLeftByWheel);
	InputComponent->BindAction("RotateRightByWheel", IE_Pressed, this, &ASpectatorCamera::RotateRightByWheel);
	InputComponent->BindAction("RotateUpByWheel", IE_Pressed, this, &ASpectatorCamera::RotateUpByWheel);
	InputComponent->BindAction("RotateDownByWheel", IE_Pressed, this, &ASpectatorCamera::RotateDownByWheel);

	// keyboard move (WASD, Home/End)
	InputComponent->BindAxis("MoveForward", this, &ASpectatorCamera::MoveCameraForwardInput);
	InputComponent->BindAxis("MoveRight", this, &ASpectatorCamera::MoveCameraRightInput);
	InputComponent->BindAxis("MoveUp", this, &ASpectatorCamera::MoveCameraUpInput);
	InputComponent->BindAxis("ZoomIn", this, &ASpectatorCamera::ZoomCameraInInput);

	// double speed (WASD +Shift)
	InputComponent->BindAxis("FastMove", this, &ASpectatorCamera::FastMoveInput);
	// yaw and pitch (WASD +Ctrl)
	InputComponent->BindAxis("Rotate", this, &ASpectatorCamera::RotateInput);
}


//////////////////////////////////////////////////////////////////


void ASpectatorCamera::ZoomInByWheel()
{
	if (!bCanMoveCamera)    return;

	CameraRadius -= CameraZoomSpeed * FastMoveValue;
	CameraRadius = FMath::Clamp(CameraRadius, CameraRadiusMin, CameraRadiusMax);

	RepositionCamera();
}


void ASpectatorCamera::ZoomOutByWheel()
{
	if (!bCanMoveCamera)    return;

	CameraRadius += CameraZoomSpeed * FastMoveValue;
	CameraRadius = FMath::Clamp(CameraRadius, CameraRadiusMin, CameraRadiusMax);

	RepositionCamera();
}


void ASpectatorCamera::RotateLeftByWheel()
{
	if (!bCanMoveCamera)    return;

	CameraZAnlge -= CameraRotationSpeed * FastMoveValue;

	RepositionCamera();
}


void ASpectatorCamera::RotateRightByWheel()
{
	if (!bCanMoveCamera)    return;

	CameraZAnlge += CameraRotationSpeed * FastMoveValue;

	RepositionCamera();
}


void ASpectatorCamera::RotateUpByWheel()
{
	if (!bCanMoveCamera)    return;

	CameraHeightAngle += CameraRotationSpeed * FastMoveValue;
	CameraHeightAngle = FMath::Clamp(CameraHeightAngle, CameraHeightAngleMin, CameraHeightAngleMax);

	RepositionCamera();
}


void ASpectatorCamera::RotateDownByWheel()
{
	if (!bCanMoveCamera)    return;

	CameraHeightAngle -= CameraRotationSpeed * FastMoveValue;
	CameraHeightAngle = FMath::Clamp(CameraHeightAngle, CameraHeightAngleMin, CameraHeightAngleMax);

	RepositionCamera();
}

//---------------

void ASpectatorCamera::RepositionCamera()
{
	FVector newLocation(0.0f, 0.0f, 0.0f);
	FRotator newRotation(0.0f, 0.0f, 0.0f);

	float sinCameraZAngle = FMath::Sin(FMath::DegreesToRadians(CameraZAnlge));
	float cosCameraZAngle = FMath::Cos(FMath::DegreesToRadians(CameraZAnlge));

	float sinCameraHeightAngle = FMath::Sin(FMath::DegreesToRadians(CameraHeightAngle));
	float cosCameraHeightAngle = FMath::Cos(FMath::DegreesToRadians(CameraHeightAngle));

	newLocation.X = cosCameraZAngle * cosCameraHeightAngle * CameraRadius;
	newLocation.Y = sinCameraZAngle * cosCameraHeightAngle * CameraRadius;
	newLocation.Z = sinCameraHeightAngle * CameraRadius;

	newRotation = (FVector(0.0f, 0.0f, 0.0f) - newLocation).Rotation();

	// new camera location and rotation
	CameraComponent->SetRelativeLocation(newLocation);
	CameraComponent->SetRelativeRotation(newRotation);
}


//////////////////////////////////////////////////////////////////


void ASpectatorCamera::FastMoveInput(float Direction)
{
	if (!bCanMoveCamera)    return;

	// left or right does not matter, to set double speed in any direction
	FastMoveValue = FMath::Abs(Direction) * 2.0f;

	// used as multiplier so must be 1 if not pressed
	if (FastMoveValue == 0.0f)
	{
		FastMoveValue = 1.0f;
	}
}


void ASpectatorCamera::RotateInput(float Direction)
{
	if (!bCanMoveCamera)    return;

	// left or right does not matter
	RotateValue = FMath::Abs(Direction);
}


void ASpectatorCamera::MoveCameraForwardInput(float Direction)
{
	if (!bCanMoveCamera)    return;

	MoveForwardValue = Direction;
}


void ASpectatorCamera::MoveCameraRightInput(float Direction)
{
	if (!bCanMoveCamera)    return;

	MoveRightValue = Direction;
}


void ASpectatorCamera::MoveCameraUpInput(float Direction)
{
	if (!bCanMoveCamera)    return;

	MoveUpValue = Direction;
}


void ASpectatorCamera::ZoomCameraInInput(float Direction)
{
	if (!bCanMoveCamera)    return;

	ZoomInValue = Direction;
}


//------------------------------------------------------------


void ASpectatorCamera::MoveCameraForward(float Direction)
{
	float MovementValue = Direction * CameraMovementSpeed;
	FVector DeltaMovement = MovementValue * GetIsolatedCameraYaw().Vector();
	FVector NewLocation = GetActorLocation() + DeltaMovement;

	SetActorLocation(NewLocation);
}


void ASpectatorCamera::MoveCameraRight(float Direction)
{
	float MovementValue = Direction * CameraMovementSpeed;
	FVector DeltaMovement = MovementValue * (FRotator(0.0f, 90.0f, 0.0f) + GetIsolatedCameraYaw()).Vector();
	FVector NewLocation = GetActorLocation() + DeltaMovement;

	SetActorLocation(NewLocation);
}


FRotator ASpectatorCamera::GetIsolatedCameraYaw()
{
	// FRotator containing Yaw only
	return FRotator(0.0f, CameraComponent->ComponentToWorld.Rotator().Yaw, 0.0f);
}

//---------------

void ASpectatorCamera::MoveCameraUp(float Direction)
{
	float MovementValue = Direction * CameraMovementSpeed;
	FVector DeltaMovement = FVector(0.0f, 0.0f, MovementValue);
	FVector NewLocation = GetActorLocation() + DeltaMovement;
	NewLocation.Z = FMath::Clamp(NewLocation.Z, CameraRadiusMin, CameraRadiusMax);

	SetActorLocation(NewLocation);
}

//---------------

void ASpectatorCamera::ZoomCameraIn(float Direction)
{
	float MovementValue = Direction * CameraMovementSpeed;                // zoom speed is too low here
	CameraRadius += MovementValue;
	CameraRadius = FMath::Clamp(CameraRadius, CameraRadiusMin, CameraRadiusMax);

	RepositionCamera();
}


void ASpectatorCamera::TurnCameraUp(float Direction)
{
	CameraHeightAngle -= Direction * CameraRotationSpeed * 10.0f;        // rotation speed is too low
	CameraHeightAngle = FMath::Clamp(CameraHeightAngle, CameraHeightAngleMin, CameraHeightAngleMax);

	RepositionCamera();
}


void ASpectatorCamera::TurnCameraRight(float Direction)
{
	CameraZAnlge += Direction * CameraRotationSpeed * 10.0f;            // rotation speed is too low here

	RepositionCamera();
}


//////////////////////////////////////////////////////////////////


void ASpectatorCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// mouse position and screen size
	FVector2D MousePosition;
	FVector2D ViewportSize;

	UGameViewportClient* GameViewport = GEngine->GameViewport;

	check(GameViewport);
	GameViewport->GetViewportSize(ViewportSize);

	// if viewport is focused, contains the mouse, and camera movement is allowed
	if (
		GameViewport->IsFocused(GameViewport->Viewport)
		&&
		GameViewport->GetMousePosition(MousePosition)
		&&
		bCanMoveCamera
		)
	{
		// movement direction
		if (MousePosition.X < CameraScrollBoundary)
		{
			MoveRightValue = -1.0f;
		}
		else if (ViewportSize.X - MousePosition.X < CameraScrollBoundary)
		{
			MoveRightValue = 1.0f;
		}

		if (MousePosition.Y < CameraScrollBoundary)
		{
			MoveForwardValue = 1.0f;
		}
		else if (ViewportSize.Y - MousePosition.Y < CameraScrollBoundary)
		{
			MoveForwardValue = -1.0f;
		}

		// rotate
		if (RotateValue != 0.0f)
		{
			TurnCameraUp(MoveForwardValue * FastMoveValue * DeltaSeconds);
			TurnCameraRight(MoveRightValue * FastMoveValue * DeltaSeconds);
		}
		// move horizontal
		else
		{
			MoveCameraForward(MoveForwardValue * FastMoveValue * DeltaSeconds);
			MoveCameraRight(MoveRightValue * FastMoveValue * DeltaSeconds);
		}

		// move vertical
		MoveCameraUp(MoveUpValue * FastMoveValue * DeltaSeconds);

		// zoom
		ZoomCameraIn(ZoomInValue * FastMoveValue * DeltaSeconds);
	}
}