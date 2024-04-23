// Copyright Maxjestic


#include "Menu.h"

#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"

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

	if(UGameInstance* GameInstance = GetGameInstance())
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
}

bool UMenu::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	if(Button_Host)
	{
		Button_Host->OnClicked.AddDynamic( this, &ThisClass::HostButtonClicked );
	}
	
	if(Button_Join)
	{
		Button_Join->OnClicked.AddDynamic( this, &ThisClass::JoinButtonClicked );
	}
	
	return true;
}

void UMenu::HostButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage( -1, 15.f, FColor::Yellow, FString( TEXT( "Host button clicked" ) ) );
	}

	if(MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession( 4, FString("FreeForAll") );
	}
}

void UMenu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage( -1, 15.f, FColor::Yellow, FString( TEXT( "Join button clicked" ) ) );
	}
}
