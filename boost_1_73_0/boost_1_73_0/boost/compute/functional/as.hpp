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
9SGFYqRsnJAUWpJm+Ys4oj5jLeXvyuqOHj1S5q7eRScYqhk92qy2gHHkeWN7aPTJG3cfum1Xx+y1Jb+NKhmFDBu30oQIne8/inV4RUd1zzJDhCa56f1I4gYU2sOPLWe7z0kHWXMpqb2pFeRl19bkkoWEiuCO4qZ1fd46bYlurhzbkxDfgrjQJdLV2U4OAbmbIHPAgdrDDgfGNeXBaVLBTNUakQlUgvq7Obg7+OT2uh06koKEc04bmBfMgDMxtcy3KYzf/V8Q4t/antchf70m/+8beGUSQT0UcA060dwKZOLutHbr69eX3JWy51bE42kDYlD0eF/6Z4+mwXDRz0xDrq9sWyRMdelI3l0jH+ZQkQEZpVpkOgO2RAd4kJGQA44BjprY6sf4nPJHHKYWvnQiWa7pmo1Ip5Fl7NKiPB2r+8jQEELKw43rm32uaSt1Wz/FKaSJQzcMdfPxpnV20To7amAxVU0VTl1TCD7Q/lTHf1jYpOrptnZGo2JF8F5T1I1KZlhVEG+PNuc2na7/EWynB9+6oYgbapocRuorIpfYRJrUEHtXgW6v531waTg5t8kTetZyb3ZHmQzdxapvzjko9IEUjyuDotvZpzKTdO+3rk/E4+bC2iyIqbp51RSa2wH6SoOhS3QIQ02bXO5R
*/