/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ELEMENT_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_ELEMENT_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(element_type)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(key_type)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_element_type 
      : mpl::bool_<detail::has_element_type<Type>::value>
    {};

    template <class Type, bool has_element_type> 
    struct get_element_type;

    template <class Type>
    struct get_element_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_element_type<Type, true>
    {
        typedef typename Type::element_type type;
    };

    template <class Type>
    struct element_type_of
    {
        typedef typename 
            get_element_type<Type, has_element_type<Type>::value>::type type;
    };

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_value_type 
      : mpl::bool_<detail::has_value_type<Type>::value>
    {};

    template <class Type, bool has_value_type> 
    struct get_value_type;

    template <class Type>
    struct get_value_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_value_type<Type, true>
    {
        typedef typename Type::value_type type;
    };

    template <class Type>
    struct value_type_of
    {
        typedef typename 
            get_value_type<Type, has_value_type<Type>::value>::type type;
    };

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_key_type 
      : mpl::bool_<detail::has_key_type<Type>::value>
    {};

    template <class Type, bool has_key_type> 
    struct get_key_type;

    template <class Type>
    struct get_key_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_key_type<Type, true>
    {
        typedef typename Type::key_type type;
    };

    template <class Type>
    struct key_type_of
    {
        typedef typename 
            get_key_type<Type, has_key_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* element_type_of.hpp
Pl0beb21M37qIMbAI3ZWdPGTp21KQYa5BzT7O+RZ1yim2ntC+SmFAyr+Ja0/A1qdjdPv1W/fI2zQ0TZ9bGZPXM+K6E2qPHwDfKvJy5PHkBesEy/LfDjSEVWqrE9cmMKSseMg/EYri5jbjY7O2UU3Pcy69IQNzR/J6jXWexsqLGFAis3Ya+vXU/+R5yt0Rv4X416uzVdbrgn18F/H85+BjOvK9oNgDJnH9u2t82xBW0fTFu3b3jiKXv9qzejfRJ4cOzBLGzTm37WgBoLFshPghtILcRqrDHuDysx7epJ72VDImQsxvKDMAAZWMNG5AHFAIa+vLs/wzCjqrQwrVSINqP5yJaeBqSWo3TSOWG0yAi8rnmlvcu6g/AntyguxUaGWf++lQEd3omF/tzfodBhqFBXXO5KtFzBZa2rO4K7XNIDVP2g+Gi+IW+PaN6apMNj2uMVqjXt3bC433nzNaFsZhDRMLGwmpfF2WZMosBcgc48q8J152gGLLvhBkD2evHFd6tk9194Cy1sVKyxBXd6QvF/KjOtUnO8e8Nfuc7AaJ/mPGSrqFrUl28bBGg==
*/