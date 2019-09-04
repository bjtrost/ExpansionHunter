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

#include "locus/GraphLocus.hh"

#include "alignment/AlignmentFilters.hh"

namespace ehunter
{

using graphtools::GappedGraphAligner;
using graphtools::Graph;
using graphtools::GraphAlignment;
using std::list;
using std::string;

void GraphLocusFeature::process(
    const Read& /*read*/, const GraphLocusFeature::Alignments& /*readAlignments*/, const Read& /*mate*/,
    const GraphLocusFeature::Alignments& /*mateAlignments*/)
{
}

GraphLocus::GraphLocus(string locusId, Graph graph, const HeuristicParameters& heuristics)
    : Locus(std::move(locusId))
    , graph_(std::move(graph))
    , aligner_(
          &graph_, heuristics.kmerLenForAlignment(), heuristics.paddingLength(), heuristics.seedAffixTrimLength(),
          heuristics.alignerType())
    , orientationPredictor_(&graph_)
{
}

void GraphLocus::analyze(Read read, boost::optional<Read> mate)
{
    list<GraphAlignment> readAlignments = align(read);
    list<GraphAlignment> mateAlignments;
    if (mate)
    {
        mateAlignments = align(*mate);
    }

    int numMatchingBases = static_cast<int>(read.sequence().length() / 7.5);
    numMatchingBases = std::max(numMatchingBases, 10);
    LinearAlignmentParameters parameters;
    const int kMinNonRepeatAlignmentScore = numMatchingBases * parameters.matchScore;

    if (!checkIfComesFromGraphLocus(readAlignments, mateAlignments, kMinNonRepeatAlignmentScore))
    {
        return;
    }

    if (!readAlignments.empty() && !mateAlignments.empty())
    {
        for (const auto& feature : features_)
        {
            feature->process(read, readAlignments, *mate, mateAlignments);
        }
    }
}

list<GraphAlignment> GraphLocus::align(Read& read) const
{
    OrientationPrediction predictedOrientation = orientationPredictor_.predict(read.sequence());

    if (predictedOrientation == OrientationPrediction::kAlignsInReverseComplementOrientation)
    {
        read.reverseComplement();
    }
    else if (predictedOrientation == OrientationPrediction::kDoesNotAlign)
    {
        return {};
    }

    return aligner_.align(read.sequence());
}

}