// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "SMyCompoundWidget.h"

#include "Widgets/SWeakWidget.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{
		InGameWidget = SNew(SMyCompoundWidget);

		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(InGameWidgetContainer, SWeakWidget).PossiblyNullContent(InGameWidget.ToSharedRef())
		);
	}
}
