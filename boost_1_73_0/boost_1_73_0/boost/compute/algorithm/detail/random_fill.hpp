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
QxCrAX+uDbekwkDsail4eUT+A2/68hb+PPNdI53IqQJuDLF+QHj5C5LaUFtf/BwilGLj4/Br/P7ym887phomwyDObjFN7sbBKbBz6kNHnsMbpB72De2nXUChS95CZKvpbJ6lWRCrbRBf4yehCtmUHFcet+u86hPtpAgLOmiHomIG706wno3uF5M7j4ywo1HNDuHgj07szTgbLdL5Mp1NA9/+pxAG1Cmq8FekL8CCnaih7ZM9WXCoiG6ctYdby8xDs+PKYb1N93rW23ncykm+JOkkuU4n6XIVtK31H/UT3V1Wlh3Qt8cQX7Spi/HyfjHFl2RyPw4S1Foo51uZbi9UI+W5b2ihmO/LTnxHGWbjMZJJNiNDrhd75PNWmkV49mEQkXOtL5zZl8NxHm1Z8p8f74XBv1BLAwQKAAAACAAtZ0pS8l154MMFAADmDAAALQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9jdXJsX211bHRpX3RpbWVvdXQuM1VUBQABtkgkYK1Wa2/aSBT97l9xxWrbkHUMSXe7fW21lNCWLQEEpN1IkdBgj+Pp2h7kGSdB6o/fc8d2AiRS+6FUjR9z5z7OufeMg8sWHf60nxewO/rub+n+L/HDtdk0LfRXGdrHNyyX36j6h42X
*/