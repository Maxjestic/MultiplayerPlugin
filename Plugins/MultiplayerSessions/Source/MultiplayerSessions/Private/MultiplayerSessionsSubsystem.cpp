// Copyright Maxjestic


#include "MultiplayerSessionsSubsystem.h"

#include "OnlineSubsystem.h"

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
}

void UMultiplayerSessionsSubsystem::FindSessions( int32 MaxSearchResults )
{
}

void UMultiplayerSessionsSubsystem::JoinSession( const FOnlineSessionSearchResult& SessionSearchResult )
{
}

void UMultiplayerSessionsSubsystem::StartSession()
{
}

void UMultiplayerSessionsSubsystem::DestroySession()
{
}

void UMultiplayerSessionsSubsystem::OnCreateSessionComplete( FName SessionName, bool bWasSuccessful )
{
}

void UMultiplayerSessionsSubsystem::OnFindSessionsComplete( bool bWasSuccessful )
{
}

void UMultiplayerSessionsSubsystem::OnJoinSessionComplete( FName SessionName, EOnJoinSessionCompleteResult::Type Result )
{
}

void UMultiplayerSessionsSubsystem::OnStartSessionComplete( FName SessionName, bool bWasSuccessful )
{
}

void UMultiplayerSessionsSubsystem::OnDestroySessionComplete( FName SessionName, bool bWasSuccessful )
{
}
