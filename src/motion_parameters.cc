/**
@file    motion_type.cc
@author  Alexander W. Winkler (winklera@ethz.ch)
@date    Jan 11, 2017
@brief   Brief description
 */

#include <xpp/opt/motion_parameters.h>

namespace xpp {
namespace opt {

MotionParameters::~MotionParameters ()
{
}

MotionParameters::ContactSchedule
MotionParameters::GetContactSchedule () const
{
  ContactSchedule phases;
  for (int i=0; i<contact_sequence_.size(); ++i) {
    double duration = contact_timings_.at(i);
//    if (duration < 1e-10)
//      continue; // skip phases with zero duration
    phases.push_back(Phase(contact_sequence_.at(i), duration));
  }

  return phases;
}

MotionParameters::MaxDevXYZ
MotionParameters::GetMaximumDeviationFromNominal () const
{
  return max_dev_xy_;
}

MotionParameters::CostWeights
MotionParameters::GetCostWeights () const
{
  return cost_weights_;
}

MotionParameters::UsedConstraints
MotionParameters::GetUsedConstraints () const
{
  return constraints_;
}

double
MotionParameters::GetTotalTime () const
{
  double T = 0.0;
  for (auto t : contact_timings_)
    T += t;

  return T;
}

MotionParameters::VecTimes
MotionParameters::GetBasePolyDurations () const
{
  std::vector<double> base_spline_timings_;
  double dt = dt_base_polynomial_;
  double t_left = GetTotalTime();

  while (t_left > 0.0) {
    double duration = t_left>dt?  dt : t_left;
    base_spline_timings_.push_back(duration);

    t_left -= dt;
  }

  return base_spline_timings_;
}

double
MotionParameters::GetAvgZForce () const
{
  return GetMass()*kGravity/GetEECount();
}

} // namespace opt
} // namespace xpp

