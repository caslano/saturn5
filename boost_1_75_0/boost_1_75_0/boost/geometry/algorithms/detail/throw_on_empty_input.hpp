// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_THROW_ON_EMPTY_INPUT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_THROW_ON_EMPTY_INPUT_HPP


#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>

#include <boost/throw_exception.hpp>


// BSG 2012-02-06: we use this currently only for distance.
// For other scalar results area,length,perimeter it is commented on purpose.
// Reason is that for distance there is no other choice. distance of two
// empty geometries (or one empty) should NOT return any value.
// But for area it is no problem to be 0.
// Suppose: area(intersection(a,b)). We (probably) don't want a throw there...

// So decided that at least for Boost 1.49 this is commented for
// scalar results, except distance.

#if defined(BOOST_GEOMETRY_EMPTY_INPUT_NO_THROW)
#include <boost/core/ignore_unused.hpp>
#endif

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Geometry>
inline void throw_on_empty_input(Geometry const& geometry)
{
#if ! defined(BOOST_GEOMETRY_EMPTY_INPUT_NO_THROW)
    if (geometry::is_empty(geometry))
    {
        BOOST_THROW_EXCEPTION(empty_input_exception());
    }
#else
    boost::ignore_unused(geometry);
#endif
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_THROW_ON_EMPTY_INPUT_HPP


/* throw_on_empty_input.hpp
rfGwiUF6oFAQeO4R1vOU4suq/X02vLVxG2H8L4zvJSP8MM4mJCqtx3K+NAUrZWqVtpXo+dowDGtoO+f2tFyLzvuAzucAnXc76PzbcSGbfUTHNjyMhgxnvD0Hiy62jimx9Fu7KHfvG54aTwhPvikH3RQpWojLSI0Ul09hJV/OTofL/S64jKSX2anaSnpZg83PJtLaLpSU1wq+vT8IoHbZY/VwccZvhkoHlJeHp3gP54RZtjvrjDqwg1GuZ63hth+B0e7ODDxFaqVyeYayU83CWr76Ekb5OG6eHirIejI85znCdOJyUZjj9mZD5StFXD85qMipeVmD5TlkhpRPGsV+HWjhIdv84ScUCb3KdKhsg3KgiO1XG3VptzFTnNI025gsnpqhU9A/axDM+flJNX87GSuVyDQl6hhYuGO1JD0yR2H9IA2R03lIhvCNpKYLX8pv4Vbgs6qAzyrvwWepXwujgTT/ZA5UnodyBUqCnx3CVCo8YoT/Ux07UNpsRGZHhhnHbvN2HCmQ2gWrn8HzMkjcbC5zvyqJO001Cs8y2i9HDwzx73Wk21zP6tP5b/ln1YUi+QNbt2n9MIoX/elr1kpYXZqDdhRNXofXSTUwWYddaljbnW5scq/1NHjPYt9n/sE4MIoE88PDpGhe7BopSBZ24PhZUpQfn1m4gOjDGMfKqLVH8+gJE3XAV8uizSsiiaienyhIFKrxtRYd/yqs
*/