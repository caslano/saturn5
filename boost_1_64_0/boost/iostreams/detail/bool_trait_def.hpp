// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BOOL_TRAIT_DEF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BOOL_TRAIT_DEF_HPP_INCLUDED     

#include <boost/config.hpp> // BOOST_STATIC_CONSTANT.
#include <boost/iostreams/detail/template_params.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
 
// 
// Macro name: BOOST_IOSTREAMS_BOOL_TRAIT_DEF
// Description: Used to generate the traits classes is_istream, is_ostream,
//      etc.
//
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
# define BOOST_IOSTREAMS_TRAIT_NAMESPACE(trait)
#else
# define BOOST_IOSTREAMS_TRAIT_NAMESPACE(trait) BOOST_PP_CAT(trait, _impl_):: 
#endif
#define BOOST_IOSTREAMS_BOOL_TRAIT_DEF(trait, type, arity) \
    namespace BOOST_PP_CAT(trait, _impl_) { \
      BOOST_IOSTREAMS_TEMPLATE_PARAMS(arity, T) \
      type_traits::yes_type helper \
          (const volatile type BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, T)*); \
      type_traits::no_type helper(...); \
      template<typename T> \
      struct impl { \
           BOOST_STATIC_CONSTANT(bool, value = \
           (sizeof(BOOST_IOSTREAMS_TRAIT_NAMESPACE(trait) \
              helper(static_cast<T*>(0))) == \
                sizeof(type_traits::yes_type))); \
      }; \
    } \
    template<typename T> \
    struct trait \
        : mpl::bool_<BOOST_PP_CAT(trait, _impl_)::impl<T>::value> \
    { BOOST_MPL_AUX_LAMBDA_SUPPORT(1, trait, (T)) }; \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BOOL_TRAIT_DEF_HPP_INCLUDED

/* bool_trait_def.hpp
v/Dc069d9zKQALN637bqJM53BAXUYiouRhNmMaVIYXtDH849/F1Vdnycbr2dM9EN9ZhCEZsIenSLtkxf1WXC7RA1C2eeWhvtMNioo/vMvWRLKYMNBPHJTXQK/VqUXdHWXq4x4fypU/NCBenBEV4kXDxE+P9BFPxBY+ujiHWi2UvpJkwPNMrh5Byn6R8u2zMmZbVKCnmosy1wK4HAWB1D8TFFlIHutVXKu6BEmPndGNkYBZyJLfvXU59+nyWjylS2PJEn62ODsS40mGKz+QnGwUjHuPSpaGoO9Xpndq7T/TKA5uvX/469T016DcoqJ8/deJZZriCrhmSh2tA9f456j/Mu9XVoMBDV/6y3sRvuzclDnlKoFuH8zFgG0Lh1ztqUV68vs8u1cMBklZ3fdws7jzmAuNs7VG29xoRNildCvIcOXuUwiRceBxBwx5e3pbSAp//uAOmx+rYLz7RpLecu1zpW/SZuoX9jVlo7ujZL6uRWyXfq7K0bzxag9DSqWoV0KUNF4Idfq6Tkm4vUTswV269Hq7kFr2M0reRPz1kvF9AhxweF7xU6q12rFA==
*/