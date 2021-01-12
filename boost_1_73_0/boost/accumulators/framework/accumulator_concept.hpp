///////////////////////////////////////////////////////////////////////////////
// accumulator_concept.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_CONCEPT_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_CONCEPT_HPP_EAN_28_10_2005

#include <boost/concept_check.hpp>

namespace boost { namespace accumulators
{

template<typename Stat>
struct accumulator_concept
{
    void constraints()
    {
        // TODO: define the stat concept
    }

    Stat stat;
};

}} // namespace boost::accumulators

#endif

/* accumulator_concept.hpp
oahGZVTFZAwYfwNpOoSVURLIGLviJKtID6rSfvmouFpLVbcZdIrB+DeJ9fsahCT2kHBhlzisiFulX62k/QxqTb1GnEBDjglZAvAsMCXB1HI8/YDhR1i1en+fV0r6Pi81f73jMB5jd4hP80os/nJ7aBVU/ZARw2MNa2HeS6KP+baBGHukrMtvJXQrtXS8SZwwy/gCuV+19g/hmajrAPENU0gZbEGlGihiPTSLS3wuuwRNK84j
*/