
#ifndef BOOST_MPL_EMPTY_BASE_HPP_INCLUDED
#define BOOST_MPL_EMPTY_BASE_HPP_INCLUDED

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

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_empty.hpp>

namespace boost { namespace mpl {

// empty base class, guaranteed to have no members; inheritance from
// 'empty_base' through the 'inherit' metafunction is a no-op - see 
// "mpl/inherit.hpp> header for the details
struct empty_base {};

template< typename T >
struct is_empty_base
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_empty_base<empty_base>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

}}

namespace boost {

template<> struct is_empty< mpl::empty_base >
    : public ::boost::integral_constant<bool,true>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(1,is_empty,(mpl::empty_base))
};

}

#endif // BOOST_MPL_EMPTY_BASE_HPP_INCLUDED

/* empty_base.hpp
ZMr4LQtegcQ0QEsAGmnzqXFw2ZhTKZRYaXs4nDun1doBmBFLQx21UPPkO8F6GnHkx7Oxf3XuX2LcxeYJ4d0zi+5ZGPYxPa3jxVUv3J5TvH/OTvAyxFuznNbGQDfF040HVH3cD723uL/B86nn434fT83+7RTPzUcvxIuNd4O7J5hM4X12if/CXowHCzwKvRwPQIsNVuZ8ib0MD8Z4MfW42QfYE4bub+mLp902oXDv+1TowkEmJsFxIUOMw14+2wVK6awfDZZyT0Ua/Fy8NB7ES6NWK+OlCZldxgsiEC0mkUDJNIQYlQyiFDh/mfFfCZ9vzavHsdYwaL7lKYjfvgLdS5QeQfoASzCkNArKDl3/ql3fXrt+1Yv/tF78D9Jvl3Kw240ZUJO6RZ3ZTR9l0YG5YsUIVDUGg4rxqzWfj6xn8/lkaAVsmYfA4HBhN6p0rEjrbD+edCzkpiRhnf00hDZQVpFtk3RrJppiJDqk+fOM0zVgV8TRCyB2SmoE7MHe2w6ougFQhaQMiVwisUlRJJRG5t4rBKUTBivIRCjKCVmzAgAzqcGORsYVPA1YBkliqmr3cjZ6f9b3Bxdz/xyP+22ay9hwK6VouTV8clWyGfXeT2b90QXuoQgSDIStiq5BUIEGWuY8DqzDrfbx5Lrn
*/