//###########################################################################
// This file is part of LImA, a Library for Image Acquisition
//
// Copyright (C) : 2009-2011
// European Synchrotron Radiation Facility
// BP 220, Grenoble 38043
// FRANCE
//
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//###########################################################################
#ifndef TUTORIALCAMERA_H
#define TUTORIALCAMERA_H
#include <linux/videodev2.h>
#include <libv4l2.h>
#include "Data.h"
#include "Debug.h"
#include "SizeUtils.h"
#include "Constants.h"
#include "HwInterface.h"

namespace lima
{
  namespace Tutorial
  {
    class Camera
    {
      DEB_CLASS_NAMESPC(DebModCamera, "Camera", "Tutorial");
    public:
      class Callback
      {
      public:
	virtual void newFrame(const Data&) = 0;
      };

      Camera(Callback*,const char* video_device = "/dev/video0");
      ~Camera();
      // --- Detector Info
      void getMaxImageSize(Size&);

      void getCurrImageType(ImageType&);
      void setCurrImageType(ImageType);
      
      void getDetectorModel(std::string& det_model);
      // --- Syn Obj
      void setExpTime(double  exp_time);
      void getExpTime(double& exp_time);
      
      void setNbHwFrames(int  nb_frames);
      void getNbHwFrames(int& nb_frames);

      // --- Acquisition interface
      void reset(HwInterface::ResetLevel reset_level);
      void prepareAcq();
      void startAcq();
      void stopAcq();
      void getStatus(HwInterface::StatusType& status);
      int getNbHwAcquiredFrames();
    private:
      Callback*	m_cbk;
      int m_fd;
      struct v4l2_buffer m_buffer;
      unsigned char* m_buffers[2];
      std::string m_det_model;
      int m_nb_frames;
      int m_acq_frame_id;
      bool m_acq_started;
    };
  }
}
#endif
