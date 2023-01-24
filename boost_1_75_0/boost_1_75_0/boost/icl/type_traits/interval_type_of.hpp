/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_OF_HPP_JOFA_100910
#define BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_OF_HPP_JOFA_100910

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(interval_type)
    }

    template <class Type>
    struct has_interval_type 
      : mpl::bool_<detail::has_interval_type<Type>::value>
    {};

    template <class Type, bool has_interval_type> 
    struct get_interval_type;

    template <class Type>
    struct get_interval_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_interval_type<Type, true>
    {
        typedef typename Type::interval_type type;
    };

    template <class Type>
    struct interval_type_of
    {
        typedef typename 
            get_interval_type<Type, has_interval_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* interval_type_of.hpp
bETVZ3D+DYR/lOP6D2LKXFLX0+Vne/rAu/sc8E4/FJtXy3DCePtV8F59JDZv9bJIT7AXcvHNJy/CN49QjH1PdAsTpW1ainaefSf1q3lCddxbtaMafbP4clMV03MguDdm24XQi10LzG0AhhlKayDS6w2Wt0R7fYGecud0R7lxBq6cX8BRjumgPBhYFvaGV6mlivkGjnLdPitWQrxXlZuv4lBzDJp+vmGYgaNXbwg82rUbaraB067dUHMNnHbthlpg4MRrN9R8QaZ4xqTMwMe6doO813zbhqomKP3O2exfGr9LUdxRbzeyOapqIWa2GDdwDBe+0Xw2oMigSddmCM9Y7qqg74lxA0aWhue3XpTit82NGqWGfMt1GCMUyw0YRgNjvUcss3EVRgw8O7wk4MWrMMh3GH1FuMJCxItXYUjtyK/CgKqLhadjpji2fEocJfSpWNdajPsCunaebcIX8Gl57sS6Ea7HUEcL7WBzPYY6XuzX9tdjqGKbmq/HEOpCuBqjBWlz1dg0em0GGSPW2zLEzjBKiXVbhsGRoXT5yZD1lfNzhEx3iDdhGLzDNF5+IUaW9ptffJGn/RYuuBD0B11ZKFbkGy3Esgo6Q7vagowZUY9ERH1ENWyBXn75sgpWL3KoS3zXaCVmkFEaR8K76H0Go011yZ0U6ZkcrTzCZRT5Gk68iILqCY43XURRKtaZ6WWTY5db3+ouFqZEkx/j
*/