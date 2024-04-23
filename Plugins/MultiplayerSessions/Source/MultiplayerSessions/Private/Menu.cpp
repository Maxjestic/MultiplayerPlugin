// Copyright Maxjestic


#include "Menu.h"

#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup( const int32 InNumOfPublicConnections, const FString InMatchType )
{
	NumPublicConnections = InNumOfPublicConnections;
	MatchType = InMatchType;
	
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

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (Button_Host)
	{
		Button_Host->OnClicked.AddDynamic( this, &ThisClass::HostButtonClicked );
	}

	if (Button_Join)
	{
		Button_Join->OnClicked.AddDynamic( this, &ThisClass::JoinButtonClicked );
	}

	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();

	Super::NativeDestruct();
}

void UMenu::HostButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage( -1, 15.f, FColor::Yellow, FString( TEXT( "Host button clicked" ) ) );
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession( NumPublicConnections, MatchType );
		if (UWorld* World = GetWorld())
		{
			World->ServerTravel( "/Game/ThirdPerson/Maps/Lobby?listen" );
		}
	}
}

void UMenu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage( -1, 15.f, FColor::Yellow, FString( TEXT( "Join button clicked" ) ) );
	}
}

void UMenu::MenuTearDown()
{
	RemoveFromParent();

	if (const UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			const FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode( InputModeData );
			PlayerController->SetShowMouseCursor( false );
		}
	}
}
