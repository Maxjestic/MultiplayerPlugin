// Copyright Maxjestic


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin( APlayerController* NewPlayer )
{
	Super::PostLogin( NewPlayer );

	if (GameState)
	{
		const int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage( 1, 60.f, FColor::Yellow, FString::Printf( TEXT( "Players in game: %d" ), NumOfPlayers ) );
		}
	}

	if (const APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>())
	{
		const FString PlayerName = PlayerState->GetPlayerName();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage( -1,
											  60.f,
											  FColor::Cyan,
											  FString::Printf( TEXT( "%s has joined the game!" ), *PlayerName ) );
		}
	}
}

void ALobbyGameMode::Logout( AController* Exiting )
{
	Super::Logout( Exiting );

	if (GameState)
	{
		const int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage( 1, 60.f, FColor::Yellow, FString::Printf( TEXT( "Players in game: %d" ), NumOfPlayers - 1 ) );
		}
	}

	if (const APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>())
	{
		const FString PlayerName = PlayerState->GetPlayerName();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage( -1, 60.f, FColor::Cyan, FString::Printf( TEXT( "%s has left the game!" ), *PlayerName ) );
		}
	}
}
