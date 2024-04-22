// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MenuSystemCharacter.generated.h"

class FOnlineSessionSearch;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class IOnlineSession;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN( LogTemplateCharacter, Log, All );

UCLASS( config=Game )
class AMenuSystemCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true") )
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true") )
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* LookAction;

public:
	AMenuSystemCharacter();

protected:
	/** Called for movement input */
	void Move( const FInputActionValue& Value );

	/** Called for looking input */
	void Look( const FInputActionValue& Value );

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent ) override;

	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/*
	 * Online Subsystem related functions
	 */
public:
	/** Pointer to the online session Interface */
	IOnlineSessionPtr OnlineSessionInterface;

protected:
	/** Creates game session */
	UFUNCTION( BlueprintCallable )
	void CreateGameSession();

	/** Joins game session */
	UFUNCTION( BlueprintCallable )
	void JoinGameSession();

	/** Callback to CreateSessionCompleteDelegate */
	void OnCreateSessionComplete( FName SessionName, bool bWasSuccessful );

	/** Callback to FindSessionsCompleteDelegate */
	void OnFindSessionsComplete( bool bWasSuccessful );

	/** Callback to JoinSessionCompleteDelegate */
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result );

private:
	/** Delegate to on when session creation is completed */
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

	/** Delegate to on when session is found */
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;

	/** Delegate to on when joining session completed */
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	/** Is populated with result of find sessions */
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
