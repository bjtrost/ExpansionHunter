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

#include "workflow/GraphVariantAnalyzer.hh"

namespace ehunter
{

class StrFeature;
class PairedIrrFeature;

class StrAnalyzer : public GraphVariantAnalyzer
{
public:
    explicit StrAnalyzer(std::shared_ptr<StrFeature> strFeature, std::string variantId);
    ~StrAnalyzer() override = default;

    std::vector<std::shared_ptr<ModelFeature>> features() override;
    std::unique_ptr<VariantFindings> analyze(const LocusStats& stats) const override;

    void addPairedIrrFeature(std::shared_ptr<PairedIrrFeature> featurePtr);

private:
    std::shared_ptr<PairedIrrFeature> pairedIrrFeature_;
    std::shared_ptr<StrFeature> strFeature_;
};

}
