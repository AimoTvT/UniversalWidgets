// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonUIs/Selects/Wheels/CommonSelectWheel.h"
#include "Widgets/CommonUIs/Selects/Wheels/CommonSelectWheelSector.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "FunctionLibrary/UniversalBaseFunctionLibrary.h"
#include "FunctionLibrary/UniversalWidgetFunctionLibrary.h"
#include "CommonInputSubsystem.h"
#include <Kismet/GameplayStatics.h>

UCommonSelectWheel::UCommonSelectWheel()
{
	bAutomaticallyRegisterInputOnConstruction = 1;
}

void UCommonSelectWheel::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (SizeBoxWidget && WidgetSlotSizeBoxWidget)
	{
		WidgetSlotSizeBoxWidget->SetWidthOverride(SizeBoxWidget->GetWidthOverride() * CenterDistanceMultiple);
		WidgetSlotSizeBoxWidget->SetHeightOverride(SizeBoxWidget->GetHeightOverride() * CenterDistanceMultiple);
	}
}

void UCommonSelectWheel::NativeConstruct()
{
	Super::NativeConstruct();
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
	{
		CommonInputSubsystem->OnInputMethodChangedNative.AddUObject(this, &UCommonSelectWheel::CommonInputType_Event);
	}
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(UpdateTimerHandle, this, &UCommonSelectWheel::UpdatePosition_Event, 0.05f, true);
	}
}

void UCommonSelectWheel::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	switch (InVisibility)
	{
	case ESlateVisibility::Visible:
		if (GetWorld() && !GetWorld()->GetTimerManager().IsTimerActive(UpdateTimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(UpdateTimerHandle, this, &UCommonSelectWheel::UpdatePosition_Event, 0.05f, true);
		}
		break;
	default:
		if (GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(UpdateTimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(UpdateTimerHandle);
		}
		break;
	}
}

void UCommonSelectWheel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime); 
}

FReply UCommonSelectWheel::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	return Super::NativeOnTouchEnded(InGeometry, InGestureEvent);
}

FReply UCommonSelectWheel::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UCommonSelectWheel::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FVector2D Position = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	TriggerSelectIndex(SetSelectPosition(Position));
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

FReply UCommonSelectWheel::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	if (GetOwningPlayer())
	{
		float X = 0.0f;
		float Y = 0.0f;
		bool bIsCurrently;
		GetOwningPlayer()->GetInputTouchState(ETouchIndex::Type(InGestureEvent.GetTouchpadIndex()), X, Y, bIsCurrently);
		if (bIsCurrently)
		{
			SetSelectPosition(FVector2D(X, Y));
		}
	}
	return Super::NativeOnTouchStarted(InGeometry, InGestureEvent);
}


void UCommonSelectWheel::UpdatePosition_Event()
{
	switch (CommonInputType)
	{
	case ECommonInputType::MouseAndKeyboard:
		FVector2D Position = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
		SetSelectPosition(Position);
		break;
	case ECommonInputType::Gamepad:
		if (APlayerController* PlayerController = GetOwningPlayer())
		{
			FVector2D Axis = FVector2D(PlayerController->GetInputAxisKeyValue(InputKeyX), PlayerController->GetInputAxisKeyValue(InputKeyY));
			UUniversalBaseFunctionLibrary::PrintString(this, InputKeyX.ToString() + FString::SanitizeFloat(Axis.X), 2.0f, TEXT("X"));
			UUniversalBaseFunctionLibrary::PrintString(this, InputKeyY.ToString() + FString::SanitizeFloat(Axis.Y), 2.0f, TEXT("Y"));
			//SetSelectAxis(Axis);
		}
		break;
	case ECommonInputType::Touch:
		break;
	case ECommonInputType::Count:
		break;
	default:
		break;
	}
}

void UCommonSelectWheel::CommonInputType_Event(ECommonInputType InCommonInputType)
{
	CommonInputType = InCommonInputType;
}

int UCommonSelectWheel::SetSelectPosition(FVector2D InPosition)
{
	FVector2D LocalSize = GetPaintSpaceGeometry().GetLocalSize() / 2;
	InPosition = InPosition - UUniversalWidgetFunctionLibrary::GetLocalPosition(this) - LocalSize; 
	InPosition = InPosition / LocalSize;
	return SetSelectIndex(GetSelectAxisIndex(InPosition));
}

int UCommonSelectWheel::SetSelectAxis(FVector2D InAxis)
{
	return SetSelectIndex(GetSelectAxisIndex(InAxis));
}

int UCommonSelectWheel::GetSelectAxisIndex(FVector2D InAxis)
{
	float Distance = FVector2D::Distance(FVector2D(0.0f), InAxis);
	if (UUniversalBaseFunctionLibrary::IsClampLimitScopes(Distance, CenterDistanceMultiple, 1.0f))
	{
		float SectorAngle = 360 / MaxSectorNum;
		float Angle = UUniversalBaseFunctionLibrary::GetAngle2D(FVector2D(0.0f, 0.0f), InAxis, -90.0f - SectorAngle / 2.0f);
		//UUniversalBaseFunctionLibrary::PrintString(this, FString::SanitizeFloat(Angle), 2.0f, TEXT("Angle"));
		int Index = Angle / SectorAngle;
		return Index;
	}
	return Distance > 1.0f ? -2 : -1;
}

int UCommonSelectWheel::SetSelectIndex(int InSelectIndex)
{
	if (SelectIndex != InSelectIndex)
	{
		UCommonSelectWheelSector* OldCommonSelectWheelSector = nullptr;
		if (CommonSelectWheelSectorWidgets.IsValidIndex(SelectIndex) && CommonSelectWheelSectorWidgets[SelectIndex])
		{
			OldCommonSelectWheelSector = CommonSelectWheelSectorWidgets[SelectIndex];
			OldCommonSelectWheelSector->SetSelect(false);
		}
		int OldSelectIndex = SelectIndex;
		SelectIndex = InSelectIndex;
		if (CommonSelectWheelSectorWidgets.IsValidIndex(SelectIndex) && CommonSelectWheelSectorWidgets[SelectIndex])
		{
			CommonSelectWheelSectorWidgets[SelectIndex]->SetSelect(true);
		}
		if (InSelectIndex == -1)
		{
			UGameplayStatics::PlaySound2D(this, Cast<USoundBase>(CanceltHoveredSlateSoundOverride.GetResourceObject()), 1.0f, 1.0f, 0.0f, nullptr, GetOwningPlayer());
		}
		BPSetSelectIndex(OldSelectIndex, OldCommonSelectWheelSector, SelectIndex, CommonSelectWheelSectorWidgets.IsValidIndex(SelectIndex) ? CommonSelectWheelSectorWidgets[SelectIndex] : nullptr);
	}
	return SelectIndex;
}

void UCommonSelectWheel::BPSetSelectIndex_Implementation(int OldSelectIndex, UCommonSelectWheelSector* OldCommonSelectWheelSector, int NewSelectIndex, UCommonSelectWheelSector* NewCommonSelectWheelSector)
{
}

bool UCommonSelectWheel::TriggerSelectIndex(int InSelectIndex)
{
	if (CommonSelectWheelSectorWidgets.IsValidIndex(InSelectIndex))
	{
		UCommonSelectWheelSector* CommonSelectWheelSector = CommonSelectWheelSectorWidgets[InSelectIndex];
		if (CommonSelectWheelSector->IsAllowTrigger())
		{
			CommonSelectWheelSector->OnTrigger();
			if (PageDownSelectWheelDataStruct.ID == CommonSelectWheelSector->SelectWheelDataStructs.ID)
			{
				SetPageIndex(PageIndex + 1, MaxSectorNum);
				return true;
			}
			if (PageUpSelectWheelDataStruct.ID == CommonSelectWheelSector->SelectWheelDataStructs.ID)
			{
				SetPageIndex(PageIndex - 1, MaxSectorNum);
				return true;
			}
			if (LastSelectWheelDataStruct.ID == CommonSelectWheelSector->SelectWheelDataStructs.ID)
			{
				if (PageIndex)
				{
					SetPageIndex(PageIndex - 1, MaxSectorNum);
				}
				else
				{
					if (BoxSelectWheelDataStructs.Num())
					{
						TArray<FSelectWheelDataStruct*> Keys;
						BoxSelectWheelDataStructs.GetKeys(Keys);
						int BoxPageIndex = BoxSelectWheelDataStructs.FindRef(Keys.Last());
						BoxSelectWheelDataStructs.Remove(Keys.Last());
						BoxSelectWheelDataStructs.GetKeys(Keys);
						if (BoxSelectWheelDataStructs.Num())
						{
							FSelectWheelDataStruct* SelectWheelDataStruct = Keys.Last();
							if (SelectWheelDataStruct)
							{
								SetSelectWheelDataStructsData(SelectWheelDataStruct->SelectWheelDataStructs, MaxSectorNum, BoxPageIndex);
							}
						}
						else
						{
							SetSelectWheelDataStructsData(DefaultSelectWheelDataStructs, MaxSectorNum, BoxPageIndex);
						}
					}
				}
				return true;
			}
			if (bAllowSelectNull || !CommonSelectWheelSector->SelectWheelDataStructs.ID.IsNone())
			{
				if (CommonSelectWheelSector->SelectWheelDataStructs.BoxSelectNum)
				{
					BoxSelectWheelDataStructs.Add(&CommonSelectWheelSector->SelectWheelDataStructs, PageIndex);
					SetSelectWheelDataStructsData(CommonSelectWheelSector->SelectWheelDataStructs.SelectWheelDataStructs, MaxSectorNum, 0);
					return true;
				}
				OnSelectData.Broadcast(this, CommonSelectWheelSector->SelectWheelDataStructs);
			}
			return true;
		}			
		return false;
	}
	UGameplayStatics::PlaySound2D(this, Cast<USoundBase>(CanceltPressedSlateSoundOverride.GetResourceObject()), 1.0f, 1.0f, 0.0f, nullptr, GetOwningPlayer());
	OnSelectData.Broadcast(this, CanceltSelectWheelDataStruct);
	return false;
}

void UCommonSelectWheel::SetDefaultSelectWheelDataStructsData(const TArray<FSelectWheelDataStruct>& InSelectWheelDataStructs, int InMaxSectorNum)
{
	DefaultSelectWheelDataStructs = InSelectWheelDataStructs;
	BoxSelectWheelDataStructs.Empty();
	SetSelectWheelDataStructsData(DefaultSelectWheelDataStructs, InMaxSectorNum);
}

void UCommonSelectWheel::SetSelectWheelDataStructsData(const TArray<FSelectWheelDataStruct>& InSelectWheelDataStructs, int InMaxSectorNum, int InPageIndex)
{
	SelectWheelDataStructs = InSelectWheelDataStructs;
	SelectWheelDataStructs.Sort([](const FSelectWheelDataStruct& A, const FSelectWheelDataStruct& B) {return A.PriorityIndex > B.PriorityIndex; });

	SectorNum = SelectWheelDataStructs.Num();
	MaxSectorNum = InMaxSectorNum;

	SetPageIndex(InPageIndex, MaxSectorNum);
	
}

void UCommonSelectWheel::SetPageIndex(int InPageIndex, int InMaxSectorNum)
{
	PageIndex = InPageIndex;
	SetSelectIndex(-1);
	for (UCommonSelectWheelSector* CommonSelectWheelSector : CommonSelectWheelSectorWidgets)
	{
		if (CommonSelectWheelSector)
		{
			CommonSelectWheelSector->RemoveFromParent();
		}
	}
	CommonSelectWheelSectorWidgets.Empty();
	if (!CanvasPanelWidget)
	{
		return;
	}

	float SectorAngle = 360.0 / InMaxSectorNum;
	int MaxShowSectorNum = FMath::Clamp(InMaxSectorNum, 4, 10);
	MaxShowSectorNum -= 2;
	int PlayIndex = 1; 
	if (BoxSelectWheelDataStructs.Num())
	{
		PlayIndex = 0;
		SpawnSelectWheelSectorWidget(PageIndex ? PageUpSelectWheelDataStruct : LastSelectWheelDataStruct, SectorAngle * CommonSelectWheelSectorWidgets.Num());
	}
	else if (PageIndex)
	{
		SpawnSelectWheelSectorWidget(PageUpSelectWheelDataStruct, SectorAngle * CommonSelectWheelSectorWidgets.Num());
	}
	else if (SelectWheelDataStructs.Num() >= MaxShowSectorNum)
	{
		PlayIndex = 0;
		MaxShowSectorNum++;
	}

	bool bPageDownSelect = false;
	PlayIndex = PlayIndex + PageIndex * MaxShowSectorNum;
	if (!SelectWheelDataStructs.IsValidIndex(PlayIndex))
	{
		MaxShowSectorNum++;
		PlayIndex = SelectWheelDataStructs.Num() - SelectWheelDataStructs.Num() % InMaxSectorNum;
	}
	else if(SelectWheelDataStructs.IsValidIndex(PlayIndex + MaxShowSectorNum + 1))
	{
		bPageDownSelect = true;
	}
	else
	{
		MaxShowSectorNum++;
	}

	for (size_t i = 0; i < MaxShowSectorNum; i++)
	{
		if (SelectWheelDataStructs.IsValidIndex(i + PlayIndex))
		{
			SpawnSelectWheelSectorWidget(SelectWheelDataStructs[i + PlayIndex], SectorAngle * CommonSelectWheelSectorWidgets.Num());
		}
		else
		{
			SpawnSelectWheelSectorWidget(DefaultSelectWheelDataStruct, SectorAngle * CommonSelectWheelSectorWidgets.Num());
		}
	}
	if (bPageDownSelect)
	{
		SpawnSelectWheelSectorWidget(PageDownSelectWheelDataStruct, SectorAngle * CommonSelectWheelSectorWidgets.Num());
	}
}

UCommonSelectWheelSector* UCommonSelectWheel::SpawnSelectWheelSectorWidget(const FSelectWheelDataStruct& InSelectWheelDataStruct, float InSectorAngle)
{
	TSoftClassPtr<UCommonSelectWheelSector> SoftCommonSelectWheelSectorClass = InSelectWheelDataStruct.SoftCommonSelectWheelSectorClass;
	if (SoftCommonSelectWheelSectorClass.IsNull())
	{
		if (DefaultSelectWheelDataStruct.SoftCommonSelectWheelSectorClass.IsNull())
		{
			return nullptr;
		}
		SoftCommonSelectWheelSectorClass = DefaultSelectWheelDataStruct.SoftCommonSelectWheelSectorClass;
	}
	if (!SoftCommonSelectWheelSectorClass.IsValid())
	{
		SoftCommonSelectWheelSectorClass.LoadSynchronous();
	}
	UCommonSelectWheelSector* CommonSelectWheelSector = CreateWidget<UCommonSelectWheelSector>(GetOwningPlayer(), SoftCommonSelectWheelSectorClass.Get());
	if (CommonSelectWheelSector)
	{
		int InIndex = CommonSelectWheelSectorWidgets.Add(CommonSelectWheelSector);
		CommonSelectWheelSector->SetSlotAngle(InSectorAngle);
		CommonSelectWheelSector->SetSectorAngleProgress(1.0f / MaxSectorNum);
		CommonSelectWheelSector->SetSelectWheelDataStructs(InSelectWheelDataStruct, InIndex);
		UPanelSlot* PanelSlot = CanvasPanelWidget->AddChild(CommonSelectWheelSector);
		if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot))
		{
			CanvasPanelSlot->SetZOrder(InIndex);
			CanvasPanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
			CanvasPanelSlot->SetPosition(FVector2D(0.0f, 0.0f));
			CanvasPanelSlot->SetSize(FVector2D(0.0f, 0.0f));
		}
		return CommonSelectWheelSector;
	}
	return nullptr;
}
