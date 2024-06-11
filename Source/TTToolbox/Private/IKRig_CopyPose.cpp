// Fill out your copyright notice in the Description page of Project Settings.


#include "IKRig_CopyPose.h"

#define LOCTEXT_NAMESPACE "UIKRig_BoneConstrainer"

UIKRig_CopyPose::UIKRig_CopyPose() {}
UIKRig_CopyPose::~UIKRig_CopyPose() {}

void UIKRig_CopyPose::Initialize(const FIKRigSkeleton& IKRigSkeleton)
{
	m_copyPoseBones.Reserve(CopyPoseBones.Num());

	bool errorsOccurred = false;

	//! @todo @ffs sort bone indices
	for (auto& CopyPoseBone : CopyPoseBones)
	{
		int32 sourceBone = IKRigSkeleton.GetBoneIndexFromName(CopyPoseBone.CopySourceBone);
		int32 targetBone = IKRigSkeleton.GetBoneIndexFromName(CopyPoseBone.CopyTargetBone);

		if (sourceBone == INDEX_NONE)
		{
			errorsOccurred = true;
			UE_LOG(LogTemp, Error, TEXT("Failed get get bone index for Copy Pose Source Bone %s"), *CopyPoseBone.CopySourceBone.ToString());
			continue;
		}

		if (targetBone == INDEX_NONE)
		{
			errorsOccurred = true;
			UE_LOG(LogTemp, Error, TEXT("Failed get get bone index for Copy Pose Target Bone %s"), *CopyPoseBone.CopyTargetBone.ToString());
			continue;
		}

			m_copyPoseBones.Add(
				{
					sourceBone,
					targetBone
			});
	}

	if (errorsOccurred)
	{
		UE_LOG(LogTemp, Error, TEXT("Some constraint bones could not be set up, no constraining will be done. Please check the error messages above."));
		m_copyPoseBones.Empty();
	}
}

void UIKRig_CopyPose::Solve(FIKRigSkeleton& IKRigSkeleton, const FIKRigGoalContainer& Goals)
{
	if (m_copyPoseBones.Num() <= 0)
	{
		// nothing to do here as no constraint bones are configured
		return;
	}

	for (auto& copyPoseBone : m_copyPoseBones)
	{
		IKRigSkeleton.CurrentPoseGlobal[copyPoseBone.CopyTargetBone] = IKRigSkeleton.CurrentPoseGlobal[copyPoseBone.CopySourceBone];
		IKRigSkeleton.PropagateGlobalPoseBelowBone(copyPoseBone.CopyTargetBone);
	}
}

#if WITH_EDITOR

FText UIKRig_CopyPose::GetNiceName() const
{
	return FText(LOCTEXT("SolverName", "Copy Pose Bones"));
}

bool UIKRig_CopyPose::IsBoneAffectedBySolver(const FName& BoneName, const FIKRigSkeleton& IKRigSkeleton) const
{
	for (auto& copyPoseBone : CopyPoseBones)
	{
		if (copyPoseBone.CopyTargetBone == BoneName)
		{
			return true;
		}
	}

	return false;
}

bool UIKRig_CopyPose::GetWarningMessage(FText& OutWarningMessage) const
{
	if (CopyPoseBones.Num() <= 0)
	{
		OutWarningMessage = LOCTEXT("NoConstraintBones", "Missing constraint bones.");
		return true;
	}

	return false;
}

bool UIKRig_CopyPose::IsGoalConnected(const FName& GoalName) const
{
	// always return true as we don't want to connect IK goals for this solver ;)
	return true;
}

#endif

#undef LOCTEXT_NAMESPACE
