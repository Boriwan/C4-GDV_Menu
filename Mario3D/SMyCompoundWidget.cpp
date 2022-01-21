// Fill out your copyright notice in the Description page of Project Settings.


#include "SMyCompoundWidget.h"

#include "Mario.h"
#include "SlateOptMacros.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Notifications/SProgressBar.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMyCompoundWidget::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/

	FSlateFontInfo TextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TextStyle.Size = 70.f;


	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		  .HAlign(HAlign_Left)
		  .VAlign(VAlign_Top)
		[
			SNew(SBox)
		.HeightOverride(100)
		.WidthOverride(400)
			[
				SAssignNew(ProgressBar, SProgressBar)
				.Percent(1)
			]
		]
		+ SOverlay::Slot()[
			SNew(SImage)
			.ColorAndOpacity(FColor::Blue)
		]
		+ SOverlay::Slot()
		  .HAlign(HAlign_Center)
		  .VAlign(VAlign_Top)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Mario"))
			.ColorAndOpacity(FColor::Red)
			.Font(TextStyle)
		]
		+ SOverlay::Slot()
		  .HAlign(HAlign_Center)
		  .VAlign(VAlign_Center)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.Padding(25)
			[
				SNew(SBox)
				.WidthOverride(1000)
				.HeightOverride(100)
				[
					SNew(SButton)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Start"))
						.Justification(ETextJustify::Center)
						.Font(TextStyle)

					]
				]
			]

			+ SVerticalBox::Slot()
			.Padding(25)
			[
				SNew(SBox)
				.WidthOverride(1000)
				.HeightOverride(100)
				[
					SNew(SButton)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Options"))
						.Justification(ETextJustify::Center)
						.Font(TextStyle)
					]
				]
			]
			+ SVerticalBox::Slot()
	//		.Padding(25)
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.Padding(15)
				[
					SNew(SBox)
						.WidthOverride(310)
						.HeightOverride(180)
					[
						SNew(SButton)
						[
							SNew(STextBlock)
								.Text(FText::FromString("Credits"))
								.Justification(ETextJustify::Center)
								.Font(TextStyle)
						]
					]
				]
				+ SHorizontalBox::Slot()
				.Padding(15)
				[
					SNew(SBox)
						.WidthOverride(310)
						.HeightOverride(180)
					[
						SNew(SButton)
						[
							SNew(STextBlock)
								.Text(FText::FromString("Quit"))
								.Justification(ETextJustify::Center)
								.Font(TextStyle)
						]
					]
				]
			]

		]

	];
}


void SMyCompoundWidget::SetHealthBar(float Progress)
{
	ProgressBar->SetPercent(Progress);
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
