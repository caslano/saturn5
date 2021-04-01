// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_ALWAYS_TRUE_PREDICATE_HPP
#define BOOST_PARAMETER_AUX_ALWAYS_TRUE_PREDICATE_HPP

#include <boost/parameter/config.hpp>
#include <boost/mpl/bool.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#endif
#else
#include <boost/mpl/always.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    struct always_true_predicate
    {
        template <typename ...>
        struct apply
        {
            typedef ::boost::mpl::true_ type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename ...>
        using fn = ::boost::mp11::mp_true;
#endif
    };
#else
    typedef ::boost::mpl::always< ::boost::mpl::true_> always_true_predicate;
#endif  // BOOST_NO_CXX11_VARIADIC_TEMPLATES
}}} // namespace boost::parameter::aux

#endif  // include guard


/* always_true_predicate.hpp
n6+HoQwi0ki7ZgrHq7HQR/PstGaJ1P+gyHKAKNVlOuU+md9U0za4tvTaa52I5eRqK4YJLzr7guWcH8SxU6W5ubTy6lUM4iGIFDNynpHg1UWcD5Zeo/+AuxGlVK1XME1o5rOW6Zcx049BF4MfArgk8fC48piixyhKdWJGiIteROS5wUfGD8Qmuv1iB3oOZtkUrMRWKE11zfH/F4VrAct6beTRXp6OgEAkXwi/v2ofruNRdUXYKC5hnMRo7qJ8sGfKfTsfqUkp4FhKmgN+MnZlDVlO07ByLDKG6GRqszvnrIIuvqen98TxJzpvH5sy7JZWOYo1OkjLy64NmU03d5uto8gW8xXlHskrQ0IrAOBmG8rGYW/swxcbmpVtTHQGnbnf2WJiDI2lbBeT+2iyD5+Uc4SHZXKzhYrBJLX3vOuBMSuS0J4WBtXs+6aBvoX2uswOh2Lq1Va/0pc/PWERLaPhWwpqmUt5G87mfAZL1y8ofM8goFWEQBxj+gC/dDaUAOrbRWBSOYlWhIihq1LNZXNjS1b0n5jUx+g6sqyxLHoG9FopPT4lIzMWCLb3pg==
*/