// Fill out your copyright notice in the Description page of Project Settings.


#include "CD_PlayerState.h"

ACD_PlayerState::ACD_PlayerState(){
	this->state = PlayerStates::Normal;
}

PlayerStates ACD_PlayerState::GetPlayerState() {
	return this->state;
}

void ACD_PlayerState::SetPlayerState(PlayerStates NewState) {
	this->state = NewState;
}