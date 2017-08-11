#pragma once

#include "CoreMinimal.h"
#include <string>
#include "CameraDirector.h"
#include "GameFramework/Actor.h"
#include "ManualPoseController.h"
#include "Recording/RecordingFile.h"
#include "SimModeBase.generated.h"


UCLASS()
class AIRSIM_API ASimModeBase : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refs")
    ACameraDirector* CameraDirector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugging")
    bool EnableReport = false;

    UFUNCTION(BlueprintCallable, Category = "Recording")
    bool toggleRecording();

public:	
    // Sets default values for this actor's properties
    ASimModeBase();
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick( float DeltaSeconds ) override;

    //additional overridable methods
    virtual void reset();
    virtual std::string getReport();
    virtual void startRecording();
    virtual void stopRecording();
    virtual bool isRecording();
    virtual bool isRecordUIVisible();
    virtual ECameraDirectorMode getInitialViewMode();

    //must be implemented by derived class
    //can't use pure virtual because of restriction with Unreal
    virtual AVehiclePawnBase* getFpvVehiclePawn();

    RecordingFile& getRecordingFile();

protected:
    virtual void setupInputBindings();

protected: //settings
    bool is_record_ui_visible;
    ECameraDirectorMode initial_view_mode;
    int record_tick_count;
    bool enable_rpc;
    std::string api_server_address;
    std::string fpv_vehicle_name;
    std::string physics_engine_name;
    std::string usage_scenario;
    bool enable_collision_passthrough;
    RecordingSettings recording_settings;

private:
    void readSettings();
    void initializeSettings();

private:
    RecordingFile recording_file_;
    void *xinput_dllHandle;

};
