// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/NumericalProgress/NumericalProgressWidget.h"

void UNumericalProgressWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (Numerical != InterpNumerical)
	{
		InterpNumerical = FMath::FInterpTo(InterpNumerical, Numerical, InDeltaTime, InterpSpeed);
		BPSetProgress(0, InterpNumerical / NumericalMax);

	}
	if (InterpTime <= 0.0f)
	{
		if (InterpFloatingNumerical != Numerical + FloatingNumerical && Numerical / NumericalMax <= 1.0f)
		{
			InterpFloatingNumerical = FMath::FInterpTo(InterpFloatingNumerical, Numerical + FloatingNumerical, InDeltaTime, InterpSpeed);
			BPSetProgress(1, InterpFloatingNumerical / NumericalMax);
		}
	}
	else
	{
		InterpTime -= InDeltaTime;
	}
}

void UNumericalProgressWidget::SetNumerical(float InNumerical)
{
	if (FloatingNumerical == 0.0f && InNumerical < Numerical)
	{
		InterpTime = DelayInterpTime;
	}
	Numerical = InNumerical;
	BPOnSet(0);
}

void UNumericalProgressWidget::SetMaxNumerical(float InNumerical)
{
	NumericalMax = InNumerical;
	BPOnSet(1);
	InterpFloatingNumerical += 0.2f;
	if (Numerical == InterpNumerical)
	{
		BPSetProgress(0, Numerical / NumericalMax);
	}
	if (InterpFloatingNumerical == Numerical + FloatingNumerical)
	{
		BPSetProgress(0, (Numerical + FloatingNumerical) / NumericalMax);
	}
}

void UNumericalProgressWidget::SetFloatingNumerical(float InNumerical)
{
	FloatingNumerical = InNumerical;
	BPOnSet(2);
}

void UNumericalProgressWidget::SetNumericalProgress(float InProgress)
{
	InterpFloatingNumerical = 0.0f;
	Numerical = NumericalMax * InProgress;
	InterpNumerical = NumericalMax * InProgress;
	BPOnSet(3);
}

void UNumericalProgressWidget::BPSetProgress_Implementation(uint8 InIndex, float InProgress)
{
}


void UNumericalProgressWidget::BPOnSet_Implementation(uint8 InIndex)
{
	NativeOnSet(InIndex);
}

void UNumericalProgressWidget::NativeOnSet(uint8 InIndex)
{
}