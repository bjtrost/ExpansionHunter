//
// Expansion Hunter
// Copyright 2016-2019 Illumina, Inc.
// All rights reserved.
//
// Author: Egor Dolzhenko <edolzhenko@illumina.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//

#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "common/GenomicRegion.hh"
#include "workflow/ModelFeature.hh"

namespace ehunter
{

class CountingModel;

class CountingFeature : public ModelFeature
{
public:
    CountingFeature(std::shared_ptr<CountingModel> modelPtr, std::vector<GenomicRegion> targetRegions);
    ~CountingFeature() override = default;

    std::shared_ptr<RegionModel> model() override;
    std::int64_t numReads() const { return numReads_; }
    int getReadLength() const;
    double getDepth() const;

    void addReadInfo(int readLength);

private:
    std::shared_ptr<CountingModel> modelPtr_;
    std::vector<GenomicRegion> targetRegions_;
    std::int64_t numReads_ = 0;
    std::int64_t totalReadLength_ = 0;
};

}