//=============================================================================
//    Copyright (C) 2021-2022 Wageningen University - All Rights Reserved
//                     Author: Gonzalo Mier
//                        BSD-3 License
//=============================================================================

#pragma once
#ifndef FIELDS2COVER_PATH_PLANNING_DUBINS_CURVES_CC_H_
#define FIELDS2COVER_PATH_PLANNING_DUBINS_CURVES_CC_H_

#include "fields2cover/types.h"
#include "fields2cover/path_planning/turning_base.h"

namespace f2c::pp {

/// Dubins' curves planner with continuous curves
class DubinsCurvesCC : public TurningBase {
 public:
  explicit DubinsCurvesCC(const F2CRobot& params);
  /// @cond DOXYGEN_SHOULD_SKIP_THIS
  ~DubinsCurvesCC() = default;
  DubinsCurvesCC(DubinsCurvesCC &&) = default;
  DubinsCurvesCC() = default;
  DubinsCurvesCC(const DubinsCurvesCC&) = default;
  DubinsCurvesCC &operator=(const DubinsCurvesCC&) = default;
  DubinsCurvesCC &operator=(DubinsCurvesCC&&) = default;
  /// @endcond

  F2CPath createSimpleTurn(double dist_start_pos, double start_angle,
      double end_angle) override;

 public:
  double discretization {0.01};
};

}  // namespace f2c::pp

#endif  // FIELDS2COVER_PATH_PLANNING_DUBINS_CURVES_CC_H_
