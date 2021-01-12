//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_TRAITS_HPP
#define BOOST_COMPUTE_DETAIL_ITERATOR_TRAITS_HPP

#include <iterator>

#include <boost/compute/detail/is_contiguous_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator>
struct iterator_traits : public std::iterator_traits<Iterator>
{
    static const bool is_contiguous = is_contiguous_iterator<Iterator>::value;
    static const bool is_on_device = is_device_iterator<Iterator>::value;
    static const bool is_on_host = !is_on_device;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_TRAITS_HPP

/* iterator_traits.hpp
i+CD8Hy4z00/fBFeCF+DF0GP27+GAXgdbAaXwlbwStgXXuXGA26Aw9TedHg1nAuvgcVqfpkj/ms/WNeCwJNi9IPP0nw4GybCHFgPzoD9Ya7qbxxyWP3pqf7EIUPUn8e0H/wbb1CPe2FTuA+2ho9rf3M/7Aaf0P7qAa++d9f1DtuljIl7+d2o+XK7J+huB+wH74OnwZ1wEtwFK+GDcAncDS+Hj8A74KPwETc+8GX4W/gRfBKm
*/