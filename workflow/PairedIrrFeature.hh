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

#include <memory>
#include <string>

#include "reads/Read.hh"
#include "stats/WeightedPurityCalculator.hh"
#include "workflow/ModelFeature.hh"

namespace ehunter
{

class GraphModel;

class PairedIrrFeature : public ModelFeature
{
public:
    PairedIrrFeature(std::shared_ptr<GraphModel> modelPtr, std::string motif);
    ~PairedIrrFeature() override = default;
    std::shared_ptr<RegionModel> model() override;

    void process(const MappedRead& read, const MappedRead& mate);
    int numIrrPairs() const { return numIrrPairs_; }

private:
    std::shared_ptr<GraphModel> modelPtr_;
    std::string motif_;
    WeightedPurityCalculator weightedPurityCalculator_;
    int numIrrPairs_;
};

}