/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_DOMAIN_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_DOMAIN_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(domain_type)
    }

    template <class Type>
    struct has_domain_type 
      : mpl::bool_<detail::has_domain_type<Type>::value>
    {};


    template <class Type, bool has_domain_type> 
    struct get_domain_type;

    template <class Type>
    struct get_domain_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_domain_type<Type, true>
    {
        typedef typename Type::domain_type type;
    };

    template <class Type>
    struct domain_type_of
    {
        typedef typename 
            get_domain_type<Type, has_domain_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* domain_type_of.hpp
0xg9eDZkXVRA5fCzdsD3z0F53lWC9cuoVw750XPQZoGd4RUUF0G5d0M357z0STDkpeUGLvM08O38U2fYvxztizo66EAb3LyV1wX5bqcK/F7yjfE5317SF2V1v8WFNvn2evptpLm8pEAKGVurz8QenX7i768gz9MqpvgD56D8N9SvJFjehFTO5NPwvrFTA74gJFHd4yP8+0mbJznnNLlUMniwt5Xw1lE7te4Ftg6AaB3hxuTO9SpykqYrK7aFQgYB+DmzYJe/kR9y9XZ1kYkCOVn3YA3MeajWzTdnYW6vIHxLZ6OPtD1Oyo/C07EOfGINxtq5v9KQSxY1Lqrlz2yaS+2FAZ02b/GiGvbplL6lFvH3nzXo9NbqZvwN2p4JePZby3Uaeibi8/zZPVVYD350o07HYrG7xu2pbmpqnLuA8mxG/3PckaTzkOGL+wJdtfiWP9xLvkUvEfA7KzFv/N1F9SP2NxLc3nFon6+pwVB4RaSDxV5xj94hF2TcsILIqK2vpZ9A8Z556MMrWtgoUNU2InPzmRgHI/YT3qbq5mrKPEjwu+Yirj/6uyK+ligY0NbMhS654v2OuauofQbcwHTo7x+N6/OGpZ0YeEeQvDcz5xu+UMhLPFi83N8P/L4K9KMbf7CyCXjWw1DOTqprro/q7Px7c8jYzM05uBzf6ydDCiT6KKGXkz65DfOEc/x4Xne0HwDvGoe6LngPyCWt
*/