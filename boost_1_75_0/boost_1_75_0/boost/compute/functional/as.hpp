//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_AS_HPP
#define BOOST_COMPUTE_FUNCTIONAL_AS_HPP

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_as
{
    invoked_as(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// The \ref as function converts its argument to type \c T (similar to
/// reinterpret_cast<T>).
///
/// \see \ref convert "convert<T>"
template<class T>
struct as
{
    typedef T result_type;

    /// \internal_
    template<class Arg>
    detail::invoked_as<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_as<T, Arg>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_AS_HPP

/* as.hpp
Dipt3K7dvk40XT7HOxR6VUNCcGOaIGGZVu35hnMXnVqgcYTzC0CSSNH3P8jbML0Wc9dKQeIVH7h3zzkutBAm6Gw7cTARDNknHSDo1Dr6jUTGUJN22SxS22GGsjjPc19i2N8AnNKSdFdioFlowfOl82mFi3rTRkPX9GQtrmKe9zBWH9KdrqR5Tiu7RIRBd3cDTVCBT8cd1zR2vTBvpTyWYdqcRfnJ/apzyaEy1gr+VXenq0xOD+lE3NicCjlLuIdoMKrliSl10XKI04RL31EGWvcjnmuLpxV+QDY4NU4uyYsRy5bktd89uzZ4mkZsLwnUat16mIz40Wm9LOcV+wxmZr3t2mauB3swUd4LWlP/ybv5W+5bjfoNoUl87GsU+aHFBXrwxdWJS/EU4FjwlIHKb4OVoP2oqFeBr8u+u32Qa8b+mlM7NXHy6t+rrD8coKjCJWr+8SSJW9XxnKe95se6duYvNIosYk1n7pmqjumE+/mo6yvKx/bUY5+tQzZc9iQY441/RcwaHH364+HagQ3QXbTEksAoYu302liByD42tOGbXqL4X51eFREefQCaW76BfSrQ7wQYEYMNtAzEf3/XOxWU9JBu3Gr3W17681/pBnCiwSiqgPRX84dUo+3u836J3J0CcVm47FpKQebr/LctWis7xwIg38T26x3gneUYUFC/AMD4Wqt3AazaU4avUN87lD7qn+WNftfM+nv4
*/