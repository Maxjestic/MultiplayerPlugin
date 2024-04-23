// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Adds widget to viewport, sets properties */
	UFUNCTION( BlueprintCallable )
	void MenuSetup();
};
