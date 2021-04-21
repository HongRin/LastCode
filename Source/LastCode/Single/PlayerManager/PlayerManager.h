#pragma once

#include "LastCode.h"
#include "Single/ManagerClass/ManagerClass.h"
#include "Structures/PlayerInfo/PlayerInfo.h"

#include "Single/PlayerManager/SkillState/SkillState.h"
#include "Single/PlayerManager/QuickSlotManager/QuickManager.h"
#include "Single/PlayerManager/Inventory/Inventory.h"
#include "Single/PlayerManager/PlayerStateManager/PlayerStateManager.h"


#include "PlayerManager.generated.h"

UCLASS()
class LASTCODE_API UPlayerManager : public UManagerClass
{
	GENERATED_BODY()
	
private:
    // �÷��̾� ����
    UPROPERTY()
    FPlayerInfo PlayerInfo;

    // �÷��̾� ĳ���� ��Ʈ�ѷ�
    UPROPERTY()
     class ABasePlayerController* PlayableController;

    UPROPERTY()
    class APlayableCharacter* PlayableCharacter;

private:
    UPROPERTY()
    USkillState* SkillState;

    UPROPERTY()
    UQuickManager* QuickManager;

    UPROPERTY()
    UInventory* Inventory;

    UPROPERTY()
    UPlayerStateManager* PlayerStateManager;

public:
    // �÷��̾� ��Ʈ�ѷ��� ĳ���͸� ����մϴ�.
    void RegisterPlayer(class ABasePlayerController* newPlayerController,
        class APlayableCharacter* newPlayerCharacter);

public:
    virtual void InitManagerClass() override;
    virtual void ShutdownManagerClass() override;

public:
    FORCEINLINE FPlayerInfo* GetPlayerInfo()
    { return &PlayerInfo; }

    FORCEINLINE class ABasePlayerController* GetPlayableController() const
    { return PlayableController; }

    FORCEINLINE class APlayableCharacter* GetPlayableCharacter() const
    { return PlayableCharacter; }

    FORCEINLINE class USkillState* GetSkillState() const
    { return SkillState; }

    FORCEINLINE class UQuickManager* GetQuickManager() const
    { return QuickManager; }
    
    FORCEINLINE UInventory* GetInventory() const
    { return Inventory; }
    
    FORCEINLINE UPlayerStateManager* GetPlayerStateManager() const
    { return PlayerStateManager; }
};
