//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Copies all of the elements in the range [\p first, \p last) for which
/// \p predicate returns \c true to the range beginning at \p first_true
/// and all of the elements for which \p predicate returns \c false to
/// the range beginning at \p first_false.
///
/// Space complexity: \Omega(2n)
///
/// \see partition()
template<class InputIterator,
         class OutputIterator1,
         class OutputIterator2,
         class UnaryPredicate>
inline std::pair<OutputIterator1, OutputIterator2>
partition_copy(InputIterator first,
               InputIterator last,
               OutputIterator1 first_true,
               OutputIterator2 first_false,
               UnaryPredicate predicate,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator2>::value);

    // copy true values
    OutputIterator1 last_true =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_true,
                                  predicate,
                                  queue);

    // copy false values
    OutputIterator2 last_false =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_false,
                                  not1(predicate),
                                  queue);

    // return iterators to the end of the true and the false ranges
    return std::make_pair(last_true, last_false);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

/* partition_copy.hpp
T5aX/4iOTEvQ6x8RH06aAsjCJY/OUwbCELaizVXOB8w+bCy7lrf4HSJPfEe6JDh52KQ1chY8HSfNJY/tcNIwLi1M/CSXXJhZ5AyOWDrEH6NWhR1qDc7EUjYTn9BMpOFMfOKoXtAZ9tonxJXGAVYeu9aMeWiPmwRLQ9gSrDKrNY4L89+Xx5icKO1nNA0A55nZ3B1S0D2i9agIlEqvrgP4MJ9Yx8MRn1gtGRSwylp2Jifz20CRCztkxqPIhVgMTH+G9pnk1e9leTlgy2E2tFRlHo+F8iIuSShM58x3Jm4BEehBBwfnf04STluIxbxSFXO2JvdUzB1CDALuNWWSFihiHMk17z1pIkomj/UGa5p7kvjaRFFrccJJRoHk6RRInqAlNMDQIgMMnrmTCyOhlNsDsN05odtbnVukK+m80pLirKNeaU4JrKwI5IgEqzrBEUTTR7iRpPsLUI/H06MsRrAB2xOaoSjXcTbhGSrmVjByLjJhoRmNylcn6LRb6pXcjRL7Opdc0vFrBn4C1eU/c1CNJmUhVItdEE8QeBLQVAvvM09wSXy94juJFDdT73XG8jqUuvMSGSepW2IDWdCTci/1bkMMhOAnJcb9qOeEGx/Pc8IlTvpnrMAO8wI8zOMpQ6l+mCtwmF/RQsOjcIzM7+4QeWXgoV4gaoEal/PdyA73wReYEWQxy8uGSAdLa44ZiUePxqL9X7qwnOxOgffd
*/