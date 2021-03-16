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
UivaZwXj6YGRh7XhQ1lYjb8lbRhMwJpyeDj9MtBN8mXAS6nVZuMjHlo+tt03dcHNEZIuSdQTBO7rZJnvmqfm2Dct9PdjIGtrWjyfJ9tuuh9vt/qYqcxFDPryxKEDybMsmXe7UFODKRxjcxsJiGS3y7u9KHc0DO2UJ1qsJsXoSBVSS8KEt442H1Xg5fpQ3NR7c0qp8C2Hwc486UTvMwIRk7GQIIhpTtHFBbCb3AskyvLuuSjDDEfC4uh10mU5p64=
*/