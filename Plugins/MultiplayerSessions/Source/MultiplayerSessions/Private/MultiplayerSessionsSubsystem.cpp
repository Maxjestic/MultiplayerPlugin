// Copyright Maxjestic


#include "MultiplayerSessionsSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Online/OnlineSessionNames.h"

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
	: CreateSessionCompleteDelegate( FOnCreateSessionCompleteDelegate::CreateUObject( this, &ThisClass::OnCreateSessionComplete ) ),
	  FindSessionsCompleteDelegate( FOnFindSessionsCompleteDelegate::CreateUObject( this, &ThisClass::OnFindSessionsComplete ) ),
	  JoinSessionCompleteDelegate( FOnJoinSessionCompleteDelegate::CreateUObject( this, &ThisClass::OnJoinSessionComplete ) ),
	  StartSessionCompleteDelegate( FOnStartSessionCompleteDelegate::CreateUObject( this, &ThisClass::OnStartSessionComplete ) ),
	  DestroySessionCompleteDelegate( FOnStartSessionCompleteDelegate::CreateUObject( this, &ThisClass::OnDestroySessionComplete ) )
{
	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
}

void UMultiplayerSessionsSubsystem::CreateSession( int32 NumPublicConnections, FString MatchType )
{
	if (!SessionInterface.IsValid())
	{
		return;
	}

	if (FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession( NAME_GameSession ))
	{
		SessionInterface->DestroySession( NAME_GameSession );
	}

	CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle( CreateSessionCompleteDelegate );

	LastSessionSettings = MakeShareable( new FOnlineSessionSettings() );
	LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	LastSessionSettings->NumPublicConnections = NumPublicConnections;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->bUseLobbiesIfAvailable = true;
	LastSessionSettings->Set( FName( "MatchType" ), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing );

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->CreateSession( *LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings ))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle( CreateSessionCompleteDelegateHandle );
		MultiplayerOnCreateSessionComplete.Broadcast( false );
	}
}

void UMultiplayerSessionsSubsystem::FindSessions( int32 MaxSearchResults )
{
	if (!SessionInterface.IsValid())
	{
		return;
	}

	FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle( FindSessionsCompleteDelegate );

	LastSessionSearch = MakeShareable( new FOnlineSessionSearch() );
	LastSessionSearch->MaxSearchResults = MaxSearchResults;
	LastSessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	LastSessionSearch->QuerySettings.Set( SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals );
	
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if(!SessionInterface->FindSessions( *LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef() ))
	{
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle( FindSessionsCompleteDelegateHandle );
		MultiplayerOnFindSessionsComplete.Broadcast( TArray<FOnlineSessionSearchResult>(), false );
	}
}

void UMultiplayerSessionsSubsystem::JoinSession( const FOnlineSessionSearchResult& SessionSearchResult )
{
	if (!SessionInterface.IsValid())
	{
		MultiplayerOnJoinSessionComplete.Broadcast( EOnJoinSessionCompleteResult::UnknownError );
		return;
	}

	JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle( JoinSessionCompleteDelegate );

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if(!SessionInterface->JoinSession( *LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionSearchResult))
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle( JoinSessionCompleteDelegateHandle );
		MultiplayerOnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
	}
}

void UMultiplayerSessionsSubsystem::StartSession()
{
}

void UMultiplayerSessionsSubsystem::DestroySession()
{
}

void UMultiplayerSessionsSubsystem::OnCreateSessionComplete( FName SessionName, bool bWasSuccessful )
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle( CreateSessionCompleteDelegateHandle );
	}

	MultiplayerOnCreateSessionComplete.Broadcast( bWasSuccessful );
}

void UMultiplayerSessionsSubsystem::OnFindSessionsComplete( bool bWasSuccessful )
{
	if(SessionInterface)
	{
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle( FindSessionsCompleteDelegateHandle );
	}

	if(LastSessionSearch->SearchResults.Num() <= 0)
	{
		MultiplayerOnFindSessionsComplete.Broadcast( TArray<FOnlineSessionSearchResult>(), false );
		return;
	}
	
	MultiplayerOnFindSessionsComplete.Broadcast( LastSessionSearch->SearchResults, bWasSuccessful );
}

void UMultiplayerSessionsSubsystem::OnJoinSessionComplete( FName SessionName, EOnJoinSessionCompleteResult::Type Result )
{
	if(SessionInterface)
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle( JoinSessionCompleteDelegateHandle );
	}

	MultiplayerOnJoinSessionComplete.Broadcast( Result );
}

void UMultiplayerSessionsSubsystem::OnStartSessionComplete( FName SessionName, bool bWasSuccessful )
{
}

void UMultiplayerSessionsSubsystem::OnDestroySessionComplete( FName SessionName, bool bWasSuccessful )
{
}
