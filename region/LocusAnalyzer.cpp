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

#include "region/LocusAnalyzer.hh"

#include <unordered_set>

using std::unordered_set;
using std::vector;

namespace ehunter
{

vector<RegionModel::SPtr> extractRegionModels(const vector<LocusAnalyzer::SPtr>& locusPtrs)
{
    unordered_set<RegionModel::SPtr> modelPtrs;

    for (const auto& locusPtr : locusPtrs)
    {
        for (const auto& variantPtr : locusPtr->variantAnalyzerPtrs())
        {
            for (const auto& featurePtr : variantPtr->featurePtrs())
            {
                modelPtrs.insert(featurePtr->modelPtr());
            }
        }
    }

    return vector<RegionModel::SPtr>(modelPtrs.begin(), modelPtrs.end());
}

}
