// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyHUD.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Notifications/SProgressBar.h"

/**
 * 
 */
class MARIO3D_API SMyCompoundWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyCompoundWidget)
	{}

// Ukázka jak předat další parametry...
	SLATE_ARGUMENT(TWeakObjectPtr<FText>, DummyArgument1)
	SLATE_ARGUMENT(TWeakObjectPtr<float>, DummyArgument2)
	SLATE_ARGUMENT(TWeakObjectPtr<float>, Number)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<AMyHUD> OwningHUD;
	
	TSharedPtr<STextBlock> TextBlock;

	void SetHealthBar(float Progress);

	TSharedPtr<SProgressBar> ProgressBar;

	
};
