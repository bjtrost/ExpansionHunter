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

#include <memory>
#include <vector>

#include "region/LocusAnalyzer.hh"

namespace ehunter
{

class GraphVariantAnalyzer;
class StatsAnalyzer;

class GraphLocusAnalyzer : public LocusAnalyzer
{
public:
    ~GraphLocusAnalyzer() override = default;

    void setStats(std::shared_ptr<StatsAnalyzer> statsAnalyzer);
    void addAnalyzer(std::shared_ptr<GraphVariantAnalyzer> variantAnalyzer);
    LocusFindings analyze(Sex sampleSex) const override;
    std::vector<std::shared_ptr<FeatureAnalyzer>> featureAnalyzers() override;

private:
    std::shared_ptr<StatsAnalyzer> statsAnalyzer_;
    std::vector<std::shared_ptr<GraphVariantAnalyzer>> variantAnalyzers_;
};

}
