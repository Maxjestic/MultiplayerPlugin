// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

class UMultiplayerSessionsSubsystem;
class UButton;

/**
 * Simple menu connected to multiplayer session subsystem
 * Allows to
 *	host a game with specified number of players and match type
 *	join a hosted game
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Adds widget to viewport, sets properties */
	UFUNCTION( BlueprintCallable )
	void MenuSetup();
	
protected:
	//~ Begin UUserWidget Interface
	virtual bool Initialize() override;
	//~ End UUserWidget Interface
	
private:
	///
	/// Pointers to buttons in widget used to bind to events
	///
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Host;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Join;

	///
	/// Callbacks to buttons events
	///
	UFUNCTION()
	void HostButtonClicked();
	
	UFUNCTION()
	void JoinButtonClicked();

	/** Handles online session functionality */
	TObjectPtr<UMultiplayerSessionsSubsystem> MultiplayerSessionsSubsystem;
};
