//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_RANDOM_FILL_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_RANDOM_FILL_HPP

#include <iterator>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/random/default_random_engine.hpp>
#include <boost/compute/random/uniform_real_distribution.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class OutputIterator, class Generator>
inline void random_fill(OutputIterator first,
                        OutputIterator last,
                        Generator &g,
                        command_queue &queue)
{
    g.fill(first, last, queue);
}

template<class OutputIterator>
inline void
random_fill(OutputIterator first,
            OutputIterator last,
            typename std::iterator_traits<OutputIterator>::value_type lo,
            typename std::iterator_traits<OutputIterator>::value_type hi,
            command_queue &queue)
{
    typedef typename
        std::iterator_traits<OutputIterator>::value_type value_type;
    typedef typename
        boost::compute::default_random_engine engine_type;
    typedef typename
        boost::compute::uniform_real_distribution<value_type> distribution_type;

    engine_type engine(queue);
    distribution_type generator(lo, hi);
    generator.fill(first, last, engine, queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_RANDOM_FILL_HPP

/* random_fill.hpp
kEkfEdGsyT4EBo/NXXbdbDZWYRTyEelrygdPi0czJtk1iXVH5GUImioYICopCRDRUcWQTzBqQl2SGsRcb2tLICP58qekPCY93dlt5fh1y/WfuCQcGfc3EkJ67BbQiarUbJH8TyFT1DxnxgaQc9U+vife9TAwQT/WFdgZDUxZ+vULOh13Wj2FTnjgaZvNAfaLor2r6ev+2kvVbnQ97mDS+5e085RNpOgZhZwP3DCPVoskXLBxAbv4t+NqtG2KvbtNRkhT/AX7P7LGzOCbjOrAOWzMDaPmGMqWFehznY1LWsNLFO8dkbB4ZGZoZm1DPb97tyH+Axnr0gczI9kxHzETaQI9bgRgxnG1SYddsCI0aoSRD732uG9WfSOipqUHqACOXatSxRhfgLB0JLQhxM7yM15kujuZ39Y1rQtXNGbys1zLvFLJUfGMejfJo5bJpYh9JRF4KGlbZ40+LTEahrTLXcQ8wCdywbz7JvA+gShdkKPB3FWeF0huEMewzy2WSeJVHuRpGvfOFoOWu42UKP2qrkbc0BllZVM17azGwR9EOp6RapxJDTiWMYT/Ug==
*/