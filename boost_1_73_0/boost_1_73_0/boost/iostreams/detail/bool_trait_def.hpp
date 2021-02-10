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
JtlJqD1h4cDTweUBmgA2PdBlpn5CThbUotyRGbyRLolK3pUqmHSp4LrnoRGZ9IiPhxgfVndIIeFVpkSBs9u44QVUNe9BpRMH3p+WQCNux1uzqAKhffHLTkLtCQsHng4uD9AEsOmBLjP1E3LSVEvllnm/5I4UqCntuvHcJZ01qGf2/Jv8jVQpRMcdqJJH5DD/M2cKDb03TCyUtPD5gSeCURN2na23oLOF9airrbKeM9PJVN2phkufEs51jtnz76qYyHFidooYGm51WjR4O08JQCFl6mqM9D1rKUSytrw9jzognOshlIbeGyYWSlr4/MATwagJu87WW9BZcz21e0V6p3KoUF2FCwX6IO00+sH5/lvycZosw3QdhaK/Yr6OZi/bt8kszEYMu6NgIBR42VOv/QNQSwMECgAAAAgALWdKUmtO5P81CQAAqWQBAC4ACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDOS9zcmMvY3VybC50bXBsVVQFAAG2SCRg7Z1rT9s6GMdfl09RVbxgmriVy840ugmSFiqVixpge4FUpYkLOUuTKk647Jzz3Y+dpGnLWlImil3nL4EUJ7brOI/98/95cjn49th3y/ckoI7v1SrbG1uVMvEs33a821rlu+PZ/gNd
*/