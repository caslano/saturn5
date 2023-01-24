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
xolonksfzl0s6K5sMpq6lcEcaGnqagxsYmJaJY3Ggnq2vTudQpG+8/o9n6gdKUM8rWhlkGBgh4jwnclF4VXrWnRFNQPsjctOgXr+sK4ddmpz20ZPsGgsEFMkkiykQOdVCqGoRouATUDA3qhFNh2iJzd+A0wYvjh0P8cBHXKjLBIUlSEcXpcDhX2eGJpMz0NIFdc0arNfqxFTD4cFuhcnljpNh+1FT9q1mlPtNszAspPQ+BLDScCDiqy9THmx8TuFU0caKnOkbthehMO3aUXCKFZxpskd22sMkhwxj4EhBW9870SidT1PmMBao1cSXFrjGqJWmIx1U7U72NHyjDRgnYfAoFs45IidJggFp7kQT4sHuNdq9EpR8ynE4NsFdPKBS9MWrGBplUW58YzP0std6tcr5WZpnIvclDiSWbKUQ1EzhlP2gWawZ71M2K3hksThxnwbKQeaI29/7vgOfOvunPlfcyW43ZMw6qGbmJF4PuBwf9dieRyeshYwO5HrzJEXPyNWwWpGSWLAjxA03Oo0OeNaRyQI0QsX/1Qwc7xGMcGkFa+U190JA16qTd3WILV3aHl2klphllFW0TCL7fEn67+r+cOyEQEB7A6LRHAQXvtndKwhIjp0z5lwHS0JkWw+6m3OSoER7qws3GMiTLhNMZfg8wZQdh0B4ie2LlhgmCufBR24vJddhkLiZhnfQ6in0zIx7RAWSm/nz3hF
*/