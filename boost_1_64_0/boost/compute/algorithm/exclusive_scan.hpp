//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EXCLUSIVE_SCAN_HPP
#define BOOST_COMPUTE_ALGORITHM_EXCLUSIVE_SCAN_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/functional.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/scan.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Performs an exclusive scan of the elements in the range [\p first, \p last)
/// and stores the results in the range beginning at \p result.
///
/// Each element in the output is assigned to the sum of all the previous
/// values in the input.
///
/// \param first first element in the range to scan
/// \param last last element in the range to scan
/// \param result first element in the result range
/// \param init value used to initialize the scan sequence
/// \param binary_op associative binary operator
/// \param queue command queue to perform the operation
///
/// \return \c OutputIterator to the end of the result range
///
/// The default operation is to add the elements up.
///
/// \snippet test/test_scan.cpp exclusive_scan_int
///
/// But different associative operation can be specified as \p binary_op
/// instead (e.g., multiplication, maximum, minimum). Also value used to
/// initialized the scan sequence can be specified.
///
/// \snippet test/test_scan.cpp exclusive_scan_int_multiplies
///
/// Space complexity on GPUs: \Omega(n)<br>
/// Space complexity on GPUs when \p first == \p result: \Omega(2n)<br>
/// Space complexity on CPUs: \Omega(1)
///
/// \see inclusive_scan()
template<class InputIterator, class OutputIterator, class T, class BinaryOperator>
inline OutputIterator
exclusive_scan(InputIterator first,
               InputIterator last,
               OutputIterator result,
               T init,
               BinaryOperator binary_op,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    return detail::scan(first, last, result, true, init, binary_op, queue);
}

/// \overload
template<class InputIterator, class OutputIterator, class T>
inline OutputIterator
exclusive_scan(InputIterator first,
               InputIterator last,
               OutputIterator result,
               T init,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename
        std::iterator_traits<OutputIterator>::value_type output_type;

    return detail::scan(first, last, result, true,
                        init, boost::compute::plus<output_type>(),
                        queue);
}

/// \overload
template<class InputIterator, class OutputIterator>
inline OutputIterator
exclusive_scan(InputIterator first,
               InputIterator last,
               OutputIterator result,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename
        std::iterator_traits<OutputIterator>::value_type output_type;

    return detail::scan(first, last, result, true,
                        output_type(0), boost::compute::plus<output_type>(),
                        queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EXCLUSIVE_SCAN_HPP

/* exclusive_scan.hpp
jZM7JAdkfWNdaX3LJL1rHOkt0bjwC9+XuFKtNpr+xW8F7b9NKGJ1zXLfDmumv5F1mX+bVZRQaPrc3m/L2RD0GZI/Te9ZKc2tObzPPjypA99GpfgkPyNd8/MNq7vG95pcW5HyV+ty1rcsZK62yFrin2O/keC3P008Zn2WlGXnpBR4xLU3sTT5RYlLnyN8lpWXRz1HCiWtCeGzRkUuP8Mi9ctWRu8tPy4oR5jhvcZy5T5mMRXxvuyrFp7DmCz3som64ZGP3t+oNbprisrmr5TwiVfc6pj0lZv3+2+SvORxNlmWtD2eMVH5qFgWfebwdpGlTqnfl+WeF+pen5F23NTqkZIlMjwVpa5Y1IvdSS8mBeR+iC5WZB9KicRVXC79kIZ9g4RdlDyIFV0d7Y5JXuGZ/Eq7LNSzC4fLM26pxPG5xJEZtSa5pdahOyWOScn96OuepLe7ya5KWJIU6oPzHeWwMtQHa7//W/F3lPba2Sql1t4Pw/tQbJBr30qebH2HtQpXJjXV/FRLuvclptJX/NifZN+b0NScv3dc7vNkK40+sZfmM1xfH0djfi3PkTxfqjWIUxcLE1dYFyR9w7o6ebT1t+SxVgUH45Bfec7vED+PReVXtggyfed5koaFVtO4ejyLenxbEnU4ei97s+fpcamXw9Ue7ktaO2TNHr4H5b6Zfscvsj5T5xntap3XfZrekbLU8qMGvydhs2PGPvT0Adc4+krfem6N43hH0vSnGscRzPM0kRlt9gu8Xuxb2al7LD1aQOuGKWPThkeIXAurjdhj+4o6SbuSE61w3/QG47t+Vmjf+lUxZ7o01zNLm0AM3yPmC+XfInvfi58WUXIbM4S4R763zAx9b2XkuK58WsIKMcflemuNB2pYJl4Ykf1LdHyM53acZM9C6lJo/xrdx2GXyxh2D6zI0DGsjlf3mjGsjmHUfb8ZH0aPPTjDxrjLeEJkD3mMeaudY14dWzvHnfX07I26GRKXyJSYsTb9v6anwvjT/lj9jjWy5WYfPZOfmP0QBshf5oj1HLfPMedn80z7c9T4dUUpJ+uULl20zPP3jsoPNntUfin2l+PG5voOmMq3N+3uXbF/EDWeMnky7eYLkXlF7CUmzjOsLOOHLpoh+qqiiuKF6q/UyE30GKuZsR1y8WOopdkWHwKN2h+vjjnDqdz0AwPfD/pcqeewhOpoGwr9eki/Yc5QqjrJGUrb5D7ZUn8fIszo/Zf2utTf/XG/WaiPLvWiqaNOOstJzlfyqK85kDIw5w1l8ptoOfZ58pto0RIEzXsgs07hPZB/9fsetX2vwOM9EI/3N7zeE/B6r+Dre0/je1uD7p+17Pyjqd/cOOHhn43+wfhrN1R7vTfi9V6K13saXu+ZeL2/4fU+htf7JLV/T+Oo6O90zkjnuEr44ofttBGdGVz3BwfB7nAwDPvbpv4Guvgbpv6Gwz5whPqTM2jUXzf1lwxliwJdp1kXroAZsCJqvXs7eAFsD1fBrmo/Cgck6O81nS8gXNENdsXd0vV5XeB42A1OhflwGpyi6++m6nrR8+HZ2JfCWXA9PAdWwnPh3bAEHoRLYDJxLYOpsBy2gCvhSLgKToKr4VS4Fq6G34KXwvX8r4Ib4TvwEngYXga/hN+FKT7SaRMuDKYjF14F8+G1cA38IdwCt8Kr4I/gdfAmeCO8GT4Cfwyfg7fAt+Gd8O/wbpjLDfwZ7ArvhWPgfbAU7oSr4APwm/BB+D34MPwB/Dn8IfwF3AZ/CW+Dj8BH4a/gbrgLvgAfh+/CJ+CncDf8O6TZynr4p2EX+AzsDWU9KdwHZ6t9EXwVXgxfgz+EX8Bb4N/g7fANeBd8Bz4D34UH4HvQTgzZ68E=
*/