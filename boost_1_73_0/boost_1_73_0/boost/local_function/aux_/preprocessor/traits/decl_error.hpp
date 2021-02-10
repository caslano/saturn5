
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: `[ERROR_message_text] EMPTY`, EMPTY iff no pp-parsing error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_ERROR, decl_traits)

// Expand: `[ERROR_message_text]`, EMPTY iff no pp-parsing error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_MSG(decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    (/* expand EMPTY */)

#endif // #include guard


/* decl_error.hpp
xh5CM+SrERBQJMUSPOHayN9KGR+7hZAmE0zkN3Epfm8gkm1kpIOBkjthllHajo4QMzl0ktXECHv5rY/UMm2ciJ6Xi4VsUnes3ual3XXrHww85MIQQVGVj9EAqoXSQDk9Gb8fX15H/grLcsida74YHkMvoYYpiMGwScn1/ag71+zu4wQtkhZcY7IphPGQu9tu+OYdfp/P6Sl3vIC4TVPE9V5o6XDf5cE5qyGQvVrsLKSqpY1OXgoo+6vios4w9sHtvSogAx61tpjLpYYUxskO2GXrNiRVy6BSDQzbe0kbJPJdldJ5jaKKP/ja6ET+dmzdLoOAhJ0x4dCzog6AVOOsYCCR/K3ULg5I8RiWb4+Oo3qHYdJrtItIr7swDlVaXJaCRgxRgFi7oHAGaKl8jS00yg4gHN3czvj15Cf+7vJqwm8ndx+mISbgMmdQQUEKkVJ5CaqUdopGBFVV1sD2qrxr3+Zh/X0U39NUWFXhX6O12z8adQKIdTOCot8zsZMZpBJx+TSABPmUzjb7dhbMivvewQVY/Z38jTwQnOjo4CAkbYbNRZ5uVepWjKpUVKkFnASYp30dCdqLEzM0bJd7UXvrzqkpDvWs6aFDErhpo4f7BN+bqmhaJmfbyT9qD6w47QGBpTO6j5wkSVW0RSCv
*/