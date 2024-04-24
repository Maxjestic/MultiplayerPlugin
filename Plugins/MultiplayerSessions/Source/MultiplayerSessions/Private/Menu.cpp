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

	if (const UGameInstance* GameInstance = GetGameInstance())
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic( this, &ThisClass::OnCreateSession );
		MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddUObject( this, &ThisClass::OnFindSessions );
		MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject( this, &ThisClass::OnJoinSession );
		MultiplayerSessionsSubsystem->MultiplayerOnStartSessionComplete.AddDynamic( this, &ThisClass::OnStartSession );
		MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic( this, &ThisClass::OnDestroySession );
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

void UMenu::OnCreateSession( bool bWasSuccessful )
{
	if(bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage( -1, 15.f, FColor::Yellow, FString( TEXT( "Session created successfully!" ) ) );
		}
		
		if (UWorld* World = GetWorld())
		{
			World->ServerTravel( "/Game/ThirdPerson/Maps/Lobby?listen" );
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage( -1, 15.f, FColor::Red, FString( TEXT( "Failed to create session!" ) ) );
		}
	}
}

void UMenu::OnFindSessions( const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful )
{
}

void UMenu::OnJoinSession( EOnJoinSessionCompleteResult::Type Result )
{
}

void UMenu::OnStartSession( bool bWasSuccessful )
{
}

void UMenu::OnDestroySession( bool bWasSuccessful )
{
}

void UMenu::HostButtonClicked()
{
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession( NumPublicConnections, MatchType );
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
