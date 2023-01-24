
//  (C) Copyright Matthias Troyerk 2006.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_DETAIL_HAS_DEFAULT_CONSTRUCTOR_HPP_INCLUDED
#define BOOST_DETAIL_HAS_DEFAULT_CONSTRUCTOR_HPP_INCLUDED

#include <boost/type_traits/has_trivial_constructor.hpp>

namespace boost { namespace detail {

/// type trait to check for a default constructor
///
/// The default implementation just checks for a trivial constructor.
/// Using some compiler magic it might be possible to provide a better default

template <class T>
struct has_default_constructor
 : public has_trivial_constructor<T>
{};

} } // namespace boost::detail


#endif // BOOST_DETAIL_HAS_DEFAULT_CONSTRUCTOR_HPP_INCLUDED

/* has_default_constructor.hpp
VKSRVbO9uKgIKjLDZEQbfIkBmv/Js9uJR78+rldvHKZmyG08kClf2dZA6Y2/Lb4pGVANTwkd+Iok7eUqb8r4JCpHqohKzBVL8VKakP41fTWjjVPdIj59wxYkLmOyRVsjxG6Wjl3yyU3djC9lkamCvSegO5jrds/njMYZMXVgtFx/w1y4fUtImNN1u3H7UubNpcYOZ6rPHzTTutTuX48+pLumdOnY217y2eCn+bCTsJ1p3rzyc3WXSbvlicnuMvcLV0HYZXcBxUZ28seb3q2NmVhfnn49OMBUZ0Jejn0XAmtfuBfaKG2PkHZcmql/UoV2ngdkoOv90X4QjipK07Ll/4MeOKQjibFQZv6dmACYYxXtBDlz/PAKiBeTGFmZwNGyqNq67SMd8P0je0Esk9u1BZQGOPZJZ87jPi+SRJBMMTw9+OvhyarMe1wgcUCYLR2x0Ipv0dIw+kTrjOxV6a+I55wQr7ERs4+B9KfEdaWVSJ0LSfAKLosXt23HvI3jO5kcz7S4UmnvCwHgbUn5ydDbDi8a/rFWOAiHfTgRw5KN4aLzoHms4U4S7unttFoFN5B6z3tsr4aw7PC31BdHOdekJ3uhTKzOo8qvWqd4Itn7FY5vUFf6gh1ljfGnAK/UKtFCE92Sw7EGPmqSk6Gbj0GMcMlHoMGfCGvnCm/DWxU62QrIjjoeEUsyDqzwb3mBzG5CxZ0l5dJ570AXr2an
*/