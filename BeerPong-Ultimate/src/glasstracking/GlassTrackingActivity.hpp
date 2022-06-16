#pragma once

#include <opencv2/videoio.hpp>
#include "GlassTrackingActivityView.hpp"

class GlassTrackingActivity
{
public:
   GlassTrackingActivity(GlassTrackingActivityView* view);
   ~GlassTrackingActivity();

   virtual void run() override;
   virtual void update() override;

   inline virtual std::string getFolderName() const noexcept override { return "glass_tracking"; }
   inline virtual const ActivityView* getView() const noexcept override { return _view; }

private:
   GlassTrackingActivityView* _view;
};
