#pragma once

#include "CoreMinimal.h"
#include "AirBlueprintLib.h"
#include "HAL/Runnable.h"
#include "VehicleCameraConnector.h"
#include "Recording/RecordingFile.h"
#include "physics/PhysicsBody.hpp"
#include "common/ClockFactory.hpp"

class FRecordingThread : public FRunnable
{
public:
    FRecordingThread();
    virtual ~FRecordingThread();
    static FRecordingThread* ThreadInit(msr::airlib::VehicleCameraBase* camera, RecordingFile* recording_file, const msr::airlib::PhysicsBody* fpv_physics_body, const RecordingSettings& settings);
    static void Shutdown();

private:
    virtual bool Init();
    virtual uint32 Run();
    virtual void Stop();

    void EnsureCompletion();

private:
    FThreadSafeCounter stop_task_counter_;
    FRenderCommandFence read_pixel_fence_;

    msr::airlib::VehicleCameraBase* camera_;
    RecordingFile* recording_file_;
    const msr::airlib::PhysicsBody* fpv_physics_body_;

    FString image_path_;

    static FRecordingThread* instance_;
    FRunnableThread* thread_;

    RecordingSettings settings_;

    msr::airlib::TTimePoint last_screenshot_on_;
    msr::airlib::Pose last_pose_;

    bool is_ready_;
};