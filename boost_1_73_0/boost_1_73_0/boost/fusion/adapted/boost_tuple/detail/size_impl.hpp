/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_09272006_0724)
#define BOOST_FUSION_SIZE_IMPL_09272006_0724

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template <>
        struct size_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply : mpl::int_<tuples::length<Sequence>::value> {};
        };
    }
}}

#endif

/* size_impl.hpp
cj6ezsIonAej8XB+fjkZhKPpBJ5D5/QFBNWK6f2yA51cLrn+8Hvvtxe9Z7TAf0UozF1k0HKl6YdIZcjv4gImwaeh9z3n1yewoGaIRZ4vRfwFUlfvIpHFCqwm5vGXDAVVxjhvi6vJdLYYLbxfZBHnVYLw1pExe+95siBPjMVZoo5at10qSxU3m4Z4ZimBwE8fbpRM4JiIqRNhxdEbz2GNFXl+fK8u78BxRmzLiXTfuZN/GAMcp1URk3++xdlwMZiPZnzcmwmqsoBSEXzmH7XcvXyQjWtQz3Ns29uAjcxzWKLbcbSLqeedMC2Rsom7dDrZKETuDeYwPmclIYJehOEM4qwqvnAvaFGYtAaRsl/hkuQ64VEx+MgSPXK+DUTOqaXaUM5x65DgsxLEFJBS6fbbjJPSrKo1u9kQ8euOe5jYsyAMGkq5NOA+mIYLW3mkTb6PA7+u6FehGCYM5uPzE+5uygM1qe8tMRaEBFpOu2yKJHFeRFlqVWpJR9ljrQtsyXmPM6FFbDm6SOnhoYizBhBIi2vCOkqdHHOAHfUickslcYVOkoOJ5eD3uEp/Ft4DhElFihAzLj7KolOsTC2Dbj/ViI+98CYteVtbU5PFtgnl4G5kLBG5ToWtr6Do5o0W7ifeuNRS/dfCsuzFStPE
*/