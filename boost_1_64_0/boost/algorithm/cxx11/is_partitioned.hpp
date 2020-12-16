/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  is_partitioned.hpp
/// \brief Tell if a sequence is partitioned
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_IS_PARTITIONED_HPP
#define BOOST_ALGORITHM_IS_PARTITIONED_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn is_partitioned ( InputIterator first, InputIterator last, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param p        The predicate to test the values with
/// \note           This function is part of the C++2011 standard library.
template <typename InputIterator, typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR bool is_partitioned ( InputIterator first, InputIterator last, UnaryPredicate p )
{
//  Run through the part that satisfy the predicate
    for ( ; first != last; ++first )
        if ( !p (*first))
            break;
//  Now the part that does not satisfy the predicate
    for ( ; first != last; ++first )
        if ( p (*first))
            return false;
    return true;
}

/// \fn is_partitioned ( const Range &r, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
/// 
/// \param r        The input range
/// \param p        The predicate to test the values with
///
template <typename Range, typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR bool is_partitioned ( const Range &r, UnaryPredicate p )
{
    return boost::algorithm::is_partitioned (boost::begin(r), boost::end(r), p);
}


}}

#endif  // BOOST_ALGORITHM_IS_PARTITIONED_HPP

/* is_partitioned.hpp
5WNtM6vH2ibyft0sf4rXQPFn8ZSCQ2ULpcZcEkDq2jKnX4ezwCsEJwbKnAE9MRauJS5ZKyDX6olxYZBBPbFNGOS7emJ8GOQ6W/v8FRrQlN3WMmclYXlJgPvFsqXMWYVV5UazHtaqQmXrj2qm8Qs3Oi4MbttPjq3Oua4vRlZ047avrH9djr8aw8uvJ363vScvMjRgo0b+x+8zND//OptpSKcaNtFnNt6DleXKDZcg3zdsEsdceQ+h47RtS+TRF7+j2Sd1GtYCPh+m6zS9vtBY1uxQlrl8HbtKFTQU0mqVPUxsA3uH2XFexm5p22ekSso4wn5gMVtntiejACtypXO2b/uq7LpYlRPgqsSKZmzbDzuBeGpmYSLSkyyXbICrXiQo5mkBWqnsNHJnYv958id8LfjzIg0QE5HyQxdN97c1a30e+7aR+dBsBPq4n5pv2QV/de6cavKk+uGUKTwolrWckI+Em1i7mE8Ryvp0dWd8yO3fTU4foc5zZXwIfQsdZ4FHp7MXSEvYeZbbwp4hr7MYJ1o1SMUrTsUmQ0nTpys11Z6H+PaZ6FrcSmzvxs3WjEDT+xP92K2/Fb3FZ3jsPbcOXWM96Z45gf1/Z91nIOQYXp7WRiylbx9XVaw7rW6heX+gywSzRXXkXphVCrV5OR/cnYLI+LEuy4jhmqtBCfKfuGWRs3vyH3DDF5oN+41J6NO1sdKq6ayC2f8DeQGV87HbG5JJ+g5lS0ODSjuDhFAVONJ253w3ZSrRdi7bAQkTQfkzN16G52f8g6KmwBdpvuX7MP08VStWZ8sWXu7vFMt9JS3Mjdzo9T+oam7mTBv8YAkTuI1uWkq0OKf4EB+ci3bdSO1yez3dGLFfQbbN8h8KmD2nh/DfWqtSUuGh4E/4s4FfO3GMrXQUM57dsrALG/0WEN9JRfyCfXJn8lNGlBjyZwNC7IZ7asI6i9yIhPmzmWv4KXtdu+EIZeVheG/j8xXhwu17cuHmgkVwxsGQCzdcB6DhGYfZQp06le8vhPtv+53w3xYk/23r2H9b0/mRJych3gw4Gv74crXwGzpKwmixUnfl9hw+obly48brFpJuGfhSQ7uFO3Sj/WjIv8bZl8CnTFlsL+Ffw9uZz2pH//r7F95/sBOii3+jM+r0iaGYBeTpo0zsPFyh26pIFONZz1pT5Q2IwJpYdREaClHp8xFJ2kIrNiA2506laF+DCggbtne09BT/s0GFkZYFFG244r+rG28mck95M4H26PdLXdSqkWfprRp4R3ir2GcaE6TudIktXC3gJJAasWGPt5VeJBwW17v6HlBV+FHrhHfaBrH9H+/f1dQH/tiBDBTsngzoBvRAJPgdjzXW+pZV35VB58zgNwK87kKQpNaTbnkLnyuxxdIdjXnolltjSbuEXc0zeudJ5bFC/nx8eBIHyLDwBnkv9aZnBjl0uXSgL+mLRjK1fOOGrr8Dq4AVzi7KuCzs+ffas8snNZIHgn5giXf3dWXU4aphF77Pmjr00RSs2J9yxb/lcUFTjcHZfR4PjkuY09EQCeMLZdXXPJJb8X/bpn/vT+6QYSFz1DvS9MG+8bbQYLt1j5rEel7TXEPV8gZZOlSFcbawRD0A41zP4/wdj5qIB4FxZuMZmISGX7vK942z5vE1BjXVOxokQEQfd2AoTnh9BXGgdnAZcWYBQ0u6ITQ5z3e3itMVC5Qt4faOTCli/2HcAu0Gb+eZN3TtiZAuKkDuOlsPnuLo2kM82vF4kXhMw2N341jEC5mnysqmKot4LWHtCdZHt2BDuVhVjP2KaCG2/mi8tS4mLCLGga7CARsfTfyqMi7r+0LTdVkHfQTn3xoaQaDafLrCuGtKPMWidcE=
*/