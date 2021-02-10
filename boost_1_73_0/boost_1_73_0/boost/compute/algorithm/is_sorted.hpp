//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IS_SORTED_HPP
#define BOOST_COMPUTE_ALGORITHM_IS_SORTED_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/functional/bind.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/algorithm/adjacent_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the values in the range [\p first, \p last)
/// are in sorted order.
///
/// \param first first element in the range to check
/// \param last last element in the range to check
/// \param compare comparison function (by default \c less)
/// \param queue command queue to perform the operation
///
/// \return \c true if the range [\p first, \p last) is sorted
///
/// Space complexity: \Omega(1)
///
/// \see sort()
template<class InputIterator, class Compare>
inline bool is_sorted(InputIterator first,
                      InputIterator last,
                      Compare compare,
                      command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    using ::boost::compute::placeholders::_1;
    using ::boost::compute::placeholders::_2;

    return ::boost::compute::adjacent_find(
        first, last, ::boost::compute::bind(compare, _2, _1), queue
    ) == last;
}

/// \overload
template<class InputIterator>
inline bool is_sorted(InputIterator first,
                      InputIterator last,
                      command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::is_sorted(
        first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_IS_SORTED_HPP

/* is_sorted.hpp
7gAucmXI6Mxei1oSnguVyNLIlIShVJqkViu8qJJsLilThaSDk9l5PP0rpOtcJXmLc6sbMrluipRycSWplolUVx6mErUlnQEB+KkyFpiNVbqMoF6SlfXatDBshCiMJnElVCFWUCcs5dZW5tVwmDR1AU+GqU7MMOlCEeV2fc+rc1izFrekK0tWU2NkSHw+pLVOVca/CBEWq2ZVKJOHG7OgsEyHuiYji6KFg6iSxrsgad5GK+STVMF6ZfnH6NKwtutcr+8cRFhboKypS6hDWHAu1Qh8SE2Zytqdd4HotLRRdiH/Tso2tqekS1hFg9Gc4vmAVsIoE9KneHF0cragT6PT09F0cU4n72k0PW/xPsTTQ3BDQWtN8qaqpYEVNal1VSiZ3lH+Eyt9cUScz+VareVSlonmMDyjwdOnNGouG2PB6yf7AxoUasUHaT/6/Xn0eGvhWJSNKAZBND+i6eh4HDzE20MaQXriRcfDXw11e5y9RJeoF5CkFqXJ2H/eVOWlA52fT09m83geRO/oF1UmRZNKesNaPBXzt0FkKuzGNDg4O50w7kOndvoVVwiPaOArIvSCMAG+Jrmo3VZnAA12X8M1kTpLDsfzg9N4tohPpg+93NlFuX1ppLHmnqu9e5pWsnU8xWOmwZyVZD+d52Cw
*/