//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IS_PARTITIONED_HPP
#define BOOST_COMPUTE_ALGORITHM_IS_PARTITIONED_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/algorithm/find_if_not.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the values in the range [\p first, \p last)
/// are partitioned according to \p predicate.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class UnaryPredicate>
inline bool is_partitioned(InputIterator first,
                           InputIterator last,
                           UnaryPredicate predicate,
                           command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(
               ::boost::compute::find_if_not(first,
                                             last,
                                             predicate,
                                             queue),
                last,
                predicate,
                queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_HPP

/* is_partitioned.hpp
vqePvTArt6IgZ1leUZaOu6Yf4r+k4HJ7nNE43cR/qPjnMmPUccbhb/p81VIjJzP+9nNEZcXpp2hPGbCftHXyo26T4FBxkzxonzD9hOtqn9B6OK71kOwnY7qTetjhrQdaV8NHbmEx1W3PCQhHq7HrQ+Mm+9VXuWOthvr7P+8aLafiepSD66lbuqkDruF7nmjZdsY1LNvDnj4VsmyyNEnG81TJdx7Tc94CTNmIG5D3OY3Ie7Kv7Uo+7TSl/2teNzVvmNfNnnnPSfJaXlauy8lC3guNnyxlGiBl8sQorCo1aywJE1CmuY0oU7D7kaz3g+vgZq7jaG9FZwVtb1TAScpZVVEUuowaN3R7w99Zvnn/ZvlCtDdTtvEtGpbtVuKnnKRsokVHy3Zzw7Jp3GR77PCbv7aE6m/PL0+jbDcHls2ME1wjYB3Jp1o2uX1atp74ZJiyyTDpUUknz6LuTnm6hmvq55er98fnd9Yp54o+vW3EN/rk4sVu65Prp/ndqCn107z2wqThk635rdSeY9qMzq00vxqun71WrhHyfa1XbR+kF1iHKs//K6aFx67vNjs0T94aZAod+n1Gw7Y1772Pi32edbbUIG7wumtkrZXfvHHZcv4zerISxH8174E8ybzxcDfxAt95zVqso3Kt3choopF3tJB3oU3Uy3rCXoSJa7Hc0cfkPUfD7MI+GxPXsr09dpow9pzyw3hPXTdmrRR17Zj/Oet6pyoSjPL7HvR9z3gqZazRxmrrTxzqbK8aLkr9nO1V/U455/O116GO9mqez45n1caWDfObTuCPAvKbNXbWhDEzx03KGjc1M2viND9daDlZjrWtmkfbP9f4T7b95R7uoq5GcP1LPPcn0p6PWaeo/xijC4xrq1u8cZPrfa3P/D/dtSnB10aEWpty5vRghVqb8rSsZXnnD7PXX3rZrGXbH71hzKjytyeFWpsSam1NqDUrp792JPgalNNfOxJ8jUjINSWyFiQf41szxZxaviHM9vv7Ir+/J/n9Pc3+W95N5Bw6i76gf+/ydGb9+wFdO1JrvhNSBkxmgO6pt1UH0+9gKnwX9oXvwanwKJwOP4FZ8H2YB/8AC+ExleX/ES6FH8DL4IewEn4EV8E/wXXwE6N7Sr/l6Te+zADdU5+pjPs4TIKfw7bwhOb3b/Ac+HfYX90Hi91ew3JE098s6TvXsDyoawMe1vQegX3g9+BQuAeeCx+Fk+BeeDH8PlwrdlsmLd+WYBO5jlMm3VXE8dhhNOzuJ6Ov03hPSTynjH6m5ms2TIfzVRZ/scriF8A5cKHK4C+Fa2C25i8H3gnz4T2wAN4PC+FuuMjOP98FQue/k+b/bM1/isY7jqnXeGNcEk++gR7TeAN1LcYQvU9D9f6kw7FwOMyE4/10si2E58Gr4Ai4EU6A18KJ8HoNtx2OhM/AUXC/hntew/1Sw70OR8MPYQb8VMP9VcP9U8M10zNCUqHoloMe9zQ4AQ6FE+F54m6vWZB3YdhL6s25ZuEBE07fIXWuXRQQ7in/NRCNDHekkeGsTY0Ll9KIcLIWVMOdFaSd7NB2cqf227v81rZka7x+Es+5tgUPwgMoe0hgCoyA3dTeS+0fw0NmXsncVNNrAw9ocvW6ZukZ2B7ug/3gT+Ag+AYcDvdrv34OXgR/ruPWAbgcPg+vhi/A2+FBeI/GfwC+COvgS3APfBn+AP4K1sNX4E/hr+HL8Lfw1xr/t7qW53fq/qm42/UsczYYFaSe79N63gUj4f1+9/EjEy94e9zhZnz9dayVj6n5dWyj9NexJkbWw/idFfOlr4H5Kta//LefD/N1W+OynfZUjzmKiTvE2hZMNmYT5oeY1zGRv2G9EWYepgY=
*/