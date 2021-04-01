//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_GET_HPP
#define BOOST_COMPUTE_FUNCTIONAL_GET_HPP

#include <cstddef>

#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/type_traits/scalar_type.hpp>

namespace boost {
namespace compute {
namespace detail {

// meta-function returning the result type for get<N>()
template<size_t N, class Arg>
struct get_result_type
{
    typedef typename scalar_type<Arg>::type type;
};

template<size_t N, class Arg, class T>
struct invoked_get
{
    typedef typename get_result_type<N, T>::type result_type;

    invoked_get(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// Returns the \c N'th element of an aggregate type (e.g. scalarN,
/// pair, tuple, etc.).
///
/// \see \ref field "field<T>"
template<size_t N>
struct get
{
    /// \internal_
    template<class> struct result;

    /// \internal_
    template<class F, class Arg>
    struct result<F(Arg)>
    {
        typedef typename detail::get_result_type<N, Arg>::type type;
    };

    template<class Arg>
    detail::invoked_get<
        N, Arg, typename boost::remove_cv<typename Arg::result_type>::type
    > operator()(const Arg &arg) const
    {
        typedef typename boost::remove_cv<typename Arg::result_type>::type T;

        return detail::invoked_get<N, Arg, T>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_GET_HPP

/* get.hpp
C77QUIkYW5ueb6+8gMYOFf23dl4uRBHxX8T+PmuAuab75UQuF0b5DVep1H5qUWOFuuHUbqpaWILgmzZjtTslaQpxyt5LnOGlEKtDM0ez7U5nH+YJTw2RHYwSPjU3Rf+J5w06W2WN8MD0Zh8kud5Q7wfmneXx4qOo2tJnXM/yK0rf6km4RpyDDPWLewkbDiPI1arSnpaZdjBerIzq4GS6dNZS4xSjVsjZ1+jn18bbmfjFPeRUksVo6/xk7p3lIqTllDi9DbGpJ9O+TTkzWAgvqT0A8jGlECCcevv8rmkD9t4kVcWVIRNy3xEwkUA5S8GRgZ3kkCkK5bd7UwCb1EYZ5yLHIIK7z42gSb6j3EyFwsatOUXuz18WTuvhHPDIRXWjrtuCWS9w6buBn9dH4V19GapK7M1Q9lDKmSgwRgj1OFfiIY24w4HvZbNb4D3SzRFskZuD0nm8wny5AmTm3xl+CVPAVInIUL2jE/i5q0YHEbV2CBiZSUELwoc57OTsx7Dccpq9svvn9NRgzSYxPzvRAtqcVMBcK6Y/h8L/foVA956JzWephYJeA4Z0WQ==
*/