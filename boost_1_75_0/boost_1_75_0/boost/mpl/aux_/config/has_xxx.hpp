
#ifndef BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
// Copyright David Abrahams 2002-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/overload_resolution.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt, 11/jan/03: signals a stub-only 'has_xxx' implementation

#if !defined(BOOST_MPL_CFG_NO_HAS_XXX) \
    && (   defined(BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION) \
        || BOOST_WORKAROUND(__GNUC__, <= 2) \
        || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840)) \
        )

#   define BOOST_MPL_CFG_NO_HAS_XXX
#   define BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#endif

#endif // BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED

/* has_xxx.hpp
ntCRlu2S/JKjqn3Gbs7gjLmqZqGy5STGaxmo0iOLxa/SkvWz7MS64UYPrytzyVd8A52waTvwUDitIfv+4uxRN1D751hqdIs7XpXd5hFyrQNJwjmxdevPLNPRo5vJ9Hrwcvdhz+YGQHeB9ytngwNzUviwRZ5cnL2uvnV2B7eVsMX4/L2ALv75MiuTfTMx6lj7RmqGLSt/OCu8Vw5hy1rNQ4OUYqtA1ZTI7Mj+hm/BzDoyfCzasl5gT3e25cKG7LDAWKE1Vux9XVlPXXBvRMyUNvRdYtWyKhNwToSjQUthrdvZB74eHCYEhg43tq4L6+XaATEvP5HZ86TcCQja/AzuFc0E/AX+ek5CuBzPHXcBExU4yNONrzss52h9f09EkaklCAM9ggK2IWYa9xWuW92ldufz3seyFysLNcwNyblX1Ynu9i7eYK/YyNgmmPDd/qGyBikuEnoWuT2xZjGangDDU9OSV7Kgy4z/zWoq62DI+LhrmRd0PoQMBocN04A/J5y/KV7Obsh5T0aEft7tYLl9MJoIiu4SsbGdhTN5mD+AFCGDZ3nwp+oN1oIQ/Hx1rKeSuNLYi+sM3wiN9wrbAK0twW09FWg13c8/M5n5+r5pfTjtG3xxxq/SIzqSHBDR1d6U5x/0kFOWm3UzpctTIHsc9FZJcQUzUdlko7jMFOvrB2FrSKLkJKPCBqKaWRLpZsroe84C7FS2bFetKrzp
*/