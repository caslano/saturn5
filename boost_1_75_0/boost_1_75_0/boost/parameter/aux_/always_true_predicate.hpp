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
u/G9S6uo41DzUJNDIVixaJF5Uj5DrszfooPmlx8+AstIheG8BrawKNUIE2PyluuKQ6Yjic6GDosThpoC2H8FUMECxGSej2cddr2pKo08tPB7t0tzFAgrL783v+wgRQQ8bw/8IauSsDN7/1LmO42sw9sH8XJZLVoJWydRC13Z93kRzTNZJ7rrzFabXve0E7mXt/ehhfYlfOhgNbOCst57R3HPl4pbr2AEKuAPq+xI/wdRBGZgZLcqShn1LUvvgV4xrCWAorvyyJBxBX6EA1O4aFWWK2SAyEHAU+AZcNvT6oF5ip5BCY1zS8jkq9c3XbC8qRuqHwqWzdmyZQc3new7EicSxn8cDmBO6CTDLQdOPpWFz5DcfFu+8EZZsz8qUxOXgucL2hGPo0EtSqDrPvLbGD0glcswx0rjje+5VJFnbe61Tk7bxqkP5IZ6S0pO0jvY5G7bdjlcNuPhvHycUvEyAKBly5Qpr3GQFU/pvunTnf9wY4snP+/1B8fResUjnBYYoV8HSiJFM4r3U2RaWq5+M7liWHJmx+IfMEvPc9GK2U4hOCTkpbjsOJacKCZW2uJXhEPn9+IqinFCIYa2GtNOieHGx+Fg2Xe0mtxTeXdGSiLXGzJc/u3EYLPLtjXnFZYtb1fix93XZbsgj2DHAxnmZer2Kvr0b52GsUa8TLboLeoT1BJDE2cSspz54Tyk11bvZJk99wWVke8fd4sD
*/