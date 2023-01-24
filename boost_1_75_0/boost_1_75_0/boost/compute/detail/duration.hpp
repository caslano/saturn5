//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_DURATION_HPP
#define BOOST_COMPUTE_DETAIL_DURATION_HPP

#include <boost/config.hpp>

#ifndef BOOST_COMPUTE_NO_HDR_CHRONO
#include <chrono>
#endif

#ifndef BOOST_COMPUTE_NO_BOOST_CHRONO
#include <boost/chrono/duration.hpp>
#endif

namespace boost {
namespace compute {
namespace detail {

#ifndef BOOST_COMPUTE_NO_HDR_CHRONO
template<class Rep, class Period>
inline std::chrono::duration<Rep, Period>
make_duration_from_nanoseconds(std::chrono::duration<Rep, Period>, size_t nanoseconds)
{
    return std::chrono::duration_cast<std::chrono::duration<Rep, Period> >(
        std::chrono::nanoseconds(nanoseconds)
    );
}
#endif // BOOST_COMPUTE_NO_HDR_CHRONO

#ifndef BOOST_COMPUTE_NO_BOOST_CHRONO
template<class Rep, class Period>
inline boost::chrono::duration<Rep, Period>
make_duration_from_nanoseconds(boost::chrono::duration<Rep, Period>, size_t nanoseconds)
{
    return boost::chrono::duration_cast<boost::chrono::duration<Rep, Period> >(
        boost::chrono::nanoseconds(nanoseconds)
    );
}
#endif // BOOST_COMPUTE_NO_BOOST_CHRONO

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_DURATION_HPP

/* duration.hpp
24M7YedQz8/qe4Ohtbw3fnAFgWiX8Ki8XYPymD23g6C8xwJrAeg7qwXBVZqFjdc6AGiQ4fCbuZNBfCVC3G7SIP6fiUG8PbPRlVBmzT3lNGL+iI9qmixSA8K9TYFBI249+5G9s8CM3vw3GjSQe4F3iWWLH7c2AVoHEfdWDmqzcwqCOsWbv6XM3XlpeZ8ykL+hi8ssIIITEP57EhDoVu9E7X0De6/g+2Z5DL3vFDY2QGlAjLpiXU2T9OmFYMT5OgsTHBgtIxCDPQWw3BFsWxEXwRZwg/qu0Ol13HaGKUcXi0Pl0SdI4XYZ3Y1KyOTujBHW1pHAzJrRPWcQDRqYBJEOlwsbYWidCl0C41EuikPBEodMJmyMK4PBGhR72+q80Pr+aPp/XV+usBFPW4YyvRaN3oHU0CU+7L2y3MZ5Jnk78X1jmUcQ3Q3QkFAG37b02tAFwv1O4oXCDVOE0X05TGBoRDCVubss8+6G3xnzgRUCbvlmT8wGfR08+M28fPh9cr6JHk8PfecbrjD4M3257Gp+PLy7ZiDchJp8WwA7Q4AQpsc34+P3bkDttVubFh+auoH9GoXlmNYBmrmFWrdk+ql1iy9Z4QXcL6Ibh6+kj/rBOrz35sUjIDssvnbtxZKIF/+0+Mr6qi9mR7x4yerNW8Ae3xbx2B1+fHP4sbAcfdbCr4ZEvnJEvdJHvroBXgEAiSoA/9VFvDRHfdcU+erk
*/