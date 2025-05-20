#pragma once

#include "Engine/DataTable.h"
#include "UniversalWidgetsStruct.generated.h"

class UCommonSelectWheelSector;

/** * 选择轮盘数据,内有数据组,内作为分组 */
USTRUCT(BlueprintType)
struct FSelectWheelDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	/** * ID //ID  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ID;

	/** * 最大时间  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxTime = 0.0;

	/** * 名字 //Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	/** * 描述 //Description */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	/** * 图像资源 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayThumbnail = true, AllowedClasses = "/Script/Engine.Texture,/Script/Engine.MaterialInterface,/Script/Engine.SlateTextureAtlasInterface", DisallowedClasses = "/Script/MediaAssets.MediaTexture"))
	TSoftObjectPtr<UObject> SoftImageResource;

	/** * 优先索引,越大越靠前  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 PriorityIndex = 2;

	/** * 盒子选择数量  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 BoxSelectNum = 0;

	/** *   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 DataA = 0;

	/** *   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 DataB = 0;

	/** * 图片资源颜色  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor ImageResourceColor = FColor(255, 255, 255, 255);

	/** * 默认图片颜色  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor DefaultImageColor = FColor(255, 255, 255, 128);

	/** * 选择图片颜色  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SelectImageColor = FColor(0, 0, 0, 200);

	/** * 默认文字颜色  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor DefaultTextColor = FColor(255, 255, 255, 255);

	/** * 选择文字颜色  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SelectTextColor = FColor(0, 255, 255, 255);

	/** *  选择轮盘数据组 */
	TArray<FSelectWheelDataStruct> SelectWheelDataStructs;

	/** *  扇形控件类 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UCommonSelectWheelSector> SoftCommonSelectWheelSectorClass = TSoftClassPtr<UCommonSelectWheelSector>(FSoftObjectPath(TEXT("/Script/UMGEditor.WidgetBlueprint'/UniversalWidgets/Widgets/CommonUIs/Selects/Wheels/BP_CommonSelectWheelSector.BP_CommonSelectWheelSector_C'")));;


	FSelectWheelDataStruct() = default;

	FSelectWheelDataStruct(uint8 InPriorityIndex) : PriorityIndex(InPriorityIndex) {};

	FSelectWheelDataStruct(FName InID, uint8 InPriorityIndex) : ID(InID), PriorityIndex(InPriorityIndex) {};

	FSelectWheelDataStruct(const FText& InName, uint8 InPriorityIndex) : Name(InName), PriorityIndex(InPriorityIndex) {};

	FSelectWheelDataStruct(FName InID, const FText& InName, uint8 InPriorityIndex) : ID(InID), Name(InName), PriorityIndex(InPriorityIndex) {};


	static bool FindRef(const TArray<FSelectWheelDataStruct>& InSelectWheelDataStructs, FSelectWheelDataStruct& SelectWheelDataStructRef)
	{
		for (const FSelectWheelDataStruct& DataRef : InSelectWheelDataStructs)
		{
			if (DataRef.ID == SelectWheelDataStructRef.ID)
			{
				SelectWheelDataStructRef = DataRef;
				return true;
			}
		}
		return false;
	}

	static bool FindRef(const TArray<FSelectWheelDataStruct>& InSelectWheelDataStructs, FSelectWheelDataStruct& SelectWheelDataStructRef, FName FindID)
	{
		for (const FSelectWheelDataStruct& DataRef : InSelectWheelDataStructs)
		{
			if (DataRef.ID == FindID)
			{
				SelectWheelDataStructRef = DataRef;
				return true;
			}
		}
		return false;
	}

	static int FindIndex(const TArray<FSelectWheelDataStruct>& InSelectWheelDataStructs, FName FindID)
	{
		for (size_t i = 0; i < InSelectWheelDataStructs.Num(); i++)
		{
			if (InSelectWheelDataStructs[i].ID == FindID)
			{
				return i;
			}
		}
		return -1;
	}
};