//=============================================================================
//    Copyright (C) 2021-2024 Wageningen University - All Rights Reserved
//                     Author: Gonzalo Mier
//                        BSD-3 License
//=============================================================================

#pragma once
#ifndef FIELDS2COVER_HEADLAND_GENERATOR_HEADLAND_GENERATOR_BASE_H_
#define FIELDS2COVER_HEADLAND_GENERATOR_HEADLAND_GENERATOR_BASE_H_

#include <vector>
#include "fields2cover/types.h"

namespace f2c::hg {

/// Base class to generate the headlands.
class HeadlandGeneratorBase {
 public:
  /// Get the regions of the field without headlands.
  /// @param _field Original field
  /// @param _dist_headland Width of the headland
  /// @return Field without headlands
  virtual F2CCells generateHeadlands(
    const F2CCells& field, double dist_headland) = 0;
  /// Get the regions of the field without headlands.
  virtual F2CCells generateHeadlandArea(
    const F2CCells& field, double swath_width, int n_swaths) = 0;
  /// Return the headlands rings on the headlands as F2CCells.
  virtual std::vector<F2CCells> generateHeadlandSwaths(
    const F2CCells& field, double swath_width, int n_swaths,
    bool dir_out2in = true) = 0;
};

}  // namespace f2c::hg

#endif  // FIELDS2COVER_HEADLAND_GENERATOR_HEADLAND_GENERATOR_BASE_H_
