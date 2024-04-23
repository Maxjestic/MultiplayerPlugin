// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSessionsSubsystem.generated.h"

/**
 * Handles sessions, working besides GameInstance
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/**
	 * Default constructor
	 * Binds internal callbacks to delegates
	 */
	UMultiplayerSessionsSubsystem();


	///
	/// To handle session functionality. The menu class will call these.
	///

	/**
	 * Accesses subsystem and calls its create session function
	 * 
	 * @param NumPublicConnections Number of players that can join the session
	 * @param MatchType Match type that will be handled by session
	 */
	void CreateSession( int32 NumPublicConnections, FString MatchType );

	/**
	 * Accesses subsystem and calls its find sessions function
	 * 
	 * @param MaxSearchResults Search limit
	 */
	void FindSessions( int32 MaxSearchResults );

	/**
	 * Accesses subsystem adn calls its join session function
	 * 
	 * @param SessionSearchResult Found session to join
	 */
	void JoinSession( const FOnlineSessionSearchResult& SessionSearchResult );

	/** Accesses subsystem adn calls its start function */
	void StartSession();

	/** Accesses subsystem adn calls its destroy function */
	void DestroySession();

protected:
	///
	/// Internal callbacks for the delegates we'll add to the Online Session Interface list.
	/// These don't need to be called outside this class.
	///
	void OnCreateSessionComplete( FName SessionName, bool bWasSuccessful );
	void OnFindSessionsComplete( bool bWasSuccessful );
	void OnJoinSessionComplete( FName SessionName, EOnJoinSessionCompleteResult::Type Result );
	void OnStartSessionComplete( FName SessionName, bool bWasSuccessful );
	void OnDestroySessionComplete( FName SessionName, bool bWasSuccessful );

private:
	/** Used to handle sessions */
	IOnlineSessionPtr SessionInterface;

	///
	/// To add to Online Session Interface delegate list.
	/// We'll bind our MultiplayerSessionSubsystem internal callbacks to these.
	///
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;

	///
	/// Delegate handles for delegates above
	///
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	FDelegateHandle StartSessionCompleteDelegateHandle;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
};
