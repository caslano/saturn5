
#ifndef BOOST_MPL_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/lambda_fwd.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   include <boost/mpl/aux_/full_lambda.hpp>
#else
#   include <boost/mpl/aux_/lambda_no_ctps.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#   define BOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS
#endif

#endif // BOOST_MPL_LAMBDA_HPP_INCLUDED

/* lambda.hpp
N2vzL2zFTzmYeziSn3EiP+c07uMifsnf8Svew/18iN/yJX7P3fyB+/gji5Z2QtQ+UWkexMYswpYsyk4sxl4swSksyVksxctZmtexHJexAjexIl9nZe5hFTYo43hnAmswibU4kXU4k3U5lw24nA25kY0YqR9oykpsxsPZkv3YihexA1eyKzexGwuVcz/Lw3gqK7MP67Mvz2R/pnAQp/E0zuFgLuAQ3sShXMYR7FXe8cq5HM3b
*/