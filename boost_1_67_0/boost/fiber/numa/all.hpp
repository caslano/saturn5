

//          Copyright Oliver Kowalke 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_NUMA_H
#define BOOST_FIBERS_NUMA_H

#include <boost/fiber/numa/algo/work_stealing.hpp>
#include <boost/fiber/numa/pin_thread.hpp>
#include <boost/fiber/numa/topology.hpp>

#endif // BOOST_FIBERS_NUMA_H

/* all.hpp
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
*/