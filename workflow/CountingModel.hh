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

#include <vector>

#include "strs/ReadClassifier.hh"
#include "workflow/RegionModel.hh"

namespace ehunter
{

class CountingFeature;

class CountingModel : public RegionModel
{
public:
    CountingModel() = delete;
    explicit CountingModel(std::vector<GenomicRegion> readExtractionRegions);
    ~CountingModel() override;

    void addFeature(CountingFeature* featurePtr);
    std::vector<ModelFeature*> modelFeatures() override;

    void analyze(MappedRead read, MappedRead mate) override;
    void analyze(MappedRead read) override;

private:
    std::vector<CountingFeature*> featurePtrs_;
    ReadClassifier proximityClassifier_;
};

}