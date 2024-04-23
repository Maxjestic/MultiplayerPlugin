// Copyright Maxjestic


#include "Menu.h"

void UMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility( ESlateVisibility::Visible );
	SetIsFocusable( true );

	if (const UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus( TakeWidget() );
			InputModeData.SetLockMouseToViewportBehavior( EMouseLockMode::DoNotLock );
			PlayerController->SetInputMode( InputModeData );
			PlayerController->SetShowMouseCursor( true );
		}
	}
}
