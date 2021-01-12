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
VyfsmdEqlZZCuD83WtHs2dHYfs+Jxva7Phrb77nR2H7Pi9baY3MDq9m8wGo2J7CazQccje33YjE+By+mz8HD2H6fk33Kyvu8mJX3BTEr7wYxK++LYtb3vyRm/f7LYjYOfEXMxoGvRuNzmzeKWb/6mpjF8XUxi+MbYhbHN8Usjm+JWRzfFrM4viNmcXxXzOL4XjQ+V/p9MYvjB2IWx01iFscPxSyOH4lZHD8Wszh+ImZx/FTM
*/