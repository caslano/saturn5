/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_SEGMENT_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_SEGMENT_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(segment_type)
    }

    template <class Type>
    struct has_segment_type 
      : mpl::bool_<detail::has_segment_type<Type>::value>
    {};

    template <class Type, bool has_segment_type> 
    struct get_segment_type;

    template <class Type>
    struct get_segment_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_segment_type<Type, true>
    {
        typedef typename Type::segment_type type;
    };

    template <class Type>
    struct segment_type_of
    {
        typedef typename 
            get_segment_type<Type, has_segment_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* segment_type_of.hpp
h1cOM47n83ZTdb3XyHtexjmTsQLW1FZRvydav79fXk3K538+UtSQFjEfBng3qQ+wJtLqblYmqdWvUsHe1nkBnvjiDPJZN6r2uXULyfZzXhzjwoZyfJC7a+J7euJX9xLapQ1B6mVDIx9Pvz3rAmHJ3GoW6i74ExyBGo1dlsAjadjf5nfq4GhCcuFKSCmKTI7iWalDtoGhQmGPtNpMSL9LBBOP5Qka50NuUxjGyamTL4NQzF6842qG2ZTzU6Bj6aZrpk1TtVTlNvlpb5VV1W64Mksg/QEgY8raWWOehOmBW9g4e3DdcunHPnhDlGqnJXvRR2E2JzUy5mj8BRB30agtoN2ktN8s/E5p2VNFEGUfYqRRANIWpp55LHQJu16upMqk3A/+mDxunQ7gtDM9DdbQ23e2qotSjAkn2H64X0WYHw20DwQFz6lsPznDLVj45BSyLbXqNuXbi6T+efO0xjqgXw1NLqC9A+8VHuqdjMyrQ/C4CG5x9faJr8r8dmiHJvzNPzLSGV2MJX628IuMFAwZ6tUE5BxLGdIbjOi3S4cladmSMSRykO21X+fl8eB3F/d1umjtOkKfC5krF4972ot5K53QxfUk2T2iikyvJ96uZaytmaPyENfV48VK5E4SWCKIvkFtysPs/OayMfPB6bsrmLVMfm3mpTP+I73IqINO/uHzDhDY3Cs5hIXfEeA1sj0Ii7sduZXJT/aizEqp
*/