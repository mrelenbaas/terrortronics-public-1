/**
   @file USBCharacter.cpp

   @mainpage USB Project

   @section description Description
   USB communication in Unreal.

   @section circuit Circuit
   - empty

   @section libraries Libraries
   - empty

   @section notes Notes
   - empty

   @section author Author
   - Bradley Elenbaas (mr.elenbaas@gmail.com)
   - Version: 2
   - Date: November 29, 2023

   @section ip Intellectual Property
   Copyright (c) 2023 Bradley Elenbaas. All rights
   reserved.

   @section license License
   Unreal license.

   @section description Description
   Empty.

   @section pins Pins
   - empty

   @section reference Resources
   - empty

   @section warnings WARNINGS
   - empty

   @section ut Unit Tests
   - empty
*/

#include "USBCharacter.h"

//LPCWSTR p = L"COM25";
Serial* SP;
// TODO: Remember that the "device" namespace is already used by something else.
// TODO: Remember that this code doesn't disconnect, and that this needs to be implemented.
// https://youtu.be/HNfpKFER2hI?si=m6o__woUO7EK7cdq
// https://www.youtube.com/watch?v=PfVkCSsy8hA
char device2[] = { '\\', '\\', '.', '\\', 'C', 'O', 'M', '\0', '\0', '\0', '\0' };
wchar_t wtext[11];
LPWSTR finalDevice;

char incomingData[256] = "";			// don't forget to pre-allocate memory
//printf("%s\n",incomingData);
int dataLength = 256;
int readResult = 0;

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

Serial::Serial(const char* portName)
{
	//We're not yet connected
	this->connected = false;

    //char device[] = { '\\', '\\', '.', '\\', 'C', 'O', 'M', '\0', '\0', '\0', '\0' };
    //Serial* SP2;
    for (int i = 0; i < 256; ++i)
    {
        if (i < 10)
        {
            device2[7] = 48 + i;
            device2[8] = '\0';
            device2[9] = '\0';
        }
        else if (i < 100)
        {
            device2[7] = 48 + (i / 10);
            device2[8] = 48 + (i % 10);
            device2[9] = '\0';
        }
        else
        {
            device2[7] = 48 + (i / 100);
            device2[8] = 48 + (i % 100 / 10);
            device2[9] = 48 + (i % 100 % 10);
        }

		mbstowcs(wtext, device2, strlen(device2) + 1);
		finalDevice = wtext;

		this->hSerial = CreateFile(finalDevice,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (this->hSerial == INVALID_HANDLE_VALUE)
		{
			if (GetLastError() == ERROR_FILE_NOT_FOUND)
			{
				printf("ERROR: Handle was not attached. Reason: %s not available.\n", portName);
			}
			else
			{
				printf("ERROR!!!");
			}
		}
		else
		{
			DCB dcbSerialParams = { 0 };
			if (!GetCommState(this->hSerial, &dcbSerialParams))
			{
				printf("failed to get current serial parameters!");
			}
			else
			{
				dcbSerialParams.BaudRate = CBR_9600;
				dcbSerialParams.ByteSize = 8;
				dcbSerialParams.StopBits = ONESTOPBIT;
				dcbSerialParams.Parity = NOPARITY;
				dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;
				if (!SetCommState(hSerial, &dcbSerialParams))
				{
					printf("ALERT: Could not set Serial Port parameters");
				}
				else
				{
					this->connected = true;
					PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
					break;
				}
			}
		}
    }
}

Serial::~Serial()
{
	if (this->connected)
	{
		this->connected = false;
		CloseHandle(this->hSerial);
	}
}

int Serial::ReadData(char* buffer, unsigned int nbChar)
{
	DWORD bytesRead;
	unsigned int toRead;
	ClearCommError(this->hSerial, &this->errors, &this->status);

	if (this->status.cbInQue > 0)
	{
		if (this->status.cbInQue > nbChar)
		{
			toRead = nbChar;
		}
		else
		{
			toRead = this->status.cbInQue;
		}
		if (ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL))
		{
			return bytesRead;
		}

	}
	return 0;

}

bool Serial::WriteData(const char* buffer, unsigned int nbChar)
{
	DWORD bytesSend;

	if (!WriteFile(this->hSerial, (void*)buffer, nbChar, &bytesSend, 0))
	{
		ClearCommError(this->hSerial, &this->errors, &this->status);

		return false;
	}
	else
	{
		return true;
	}
}

bool Serial::IsConnected()
{
	return this->connected;
}


//////////////////////////////////////////////////////////////////////////
// AUSBCharacter

AUSBCharacter::AUSBCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void AUSBCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//readResult = SP->ReadData(incomingData, dataLength);

	printf("Welcome to the serial test app!\n\n");
	char device[] = { '\\', '\\', '.', '\\', 'C', 'O', 'M', '\0', '\0', '\0', '\0' };
	SP = new Serial("\\\\.\\COM3");
	if (SP->IsConnected())
	{
		//printf("We're connected");
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "CONNECTED");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "NOT CONNECTED");
	}
	readResult = 0;
}

//////////////////////////////////////////////////////////////////////////
// Input

//public void AUSBCharacter::Something()
//{
//}

// Called every frame
//void AUSBCharacter::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaTime);

	//readResult = SP->ReadData(incomingData, dataLength);
	//incomingData[readResult] = 0;

	//printf("%s", incomingData);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, incomingData);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, incomingData);
//}

void AUSBCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUSBCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUSBCharacter::Look);

	}

}

/**
   The main function.
*/
void AUSBCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

	readResult = SP->ReadData(incomingData, dataLength);
	if (readResult)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "1");
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, incomingData);
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "0");
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, incomingData);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "HERE");
}

void AUSBCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




