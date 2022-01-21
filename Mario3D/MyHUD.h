// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MARIO3D_API AMyHUD : public AHUD
{
	GENERATED_BODY()

	public:
		TSharedPtr<class SMyCompoundWidget> InGameWidget;
		TSharedPtr<class SWidget> InGameWidgetContainer;

		virtual void BeginPlay() override;
};
