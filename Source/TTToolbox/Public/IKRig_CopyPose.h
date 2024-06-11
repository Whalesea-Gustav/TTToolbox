// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal Engine includes
#include "CoreMinimal.h"
#include "Rig/Solvers/IKRigSolver.h"

#include "IKRig_CopyPose.generated.h"

USTRUCT(Blueprintable)
struct TTTOOLBOX_API FCopyPoseBone
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CopyPose)
	FName CopySourceBone = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CopyPose)
	FName CopyTargetBone = NAME_None;
};

UCLASS()
class TTTOOLBOX_API UIKRig_CopyPose : public UIKRigSolver
{
	GENERATED_BODY()

public:
	UIKRig_CopyPose();
	~UIKRig_CopyPose();

protected: // exposed members
	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<FCopyPoseBone> CopyPoseBones;

protected: // UIKRigSolver interface
	void Initialize(const FIKRigSkeleton& IKRigSkeleton) override;
	void Solve(FIKRigSkeleton& IKRigSkeleton, const FIKRigGoalContainer& Goals) override;

#if WITH_EDITOR
	FText GetNiceName() const override;
	bool IsBoneAffectedBySolver(const FName& BoneName, const FIKRigSkeleton& IKRigSkeleton) const override;
	bool GetWarningMessage(FText& OutWarningMessage) const override;
	bool IsGoalConnected(const FName& GoalName) const override;

	void AddGoal(const UIKRigEffectorGoal& NewGoal) override {}
	void RemoveGoal(const FName& GoalName) override {}
	void RenameGoal(const FName& OldName, const FName& NewName) override {}
	void SetGoalBone(const FName& GoalName, const FName& NewBoneName) override {}
#endif

private:
	struct CCopyPose
	{
		int32 CopySourceBone = INDEX_NONE;
		int32 CopyTargetBone = INDEX_NONE;
	};
	TArray<CCopyPose> m_copyPoseBones;
};
