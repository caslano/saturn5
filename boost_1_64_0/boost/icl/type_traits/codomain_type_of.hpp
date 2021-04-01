/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_CODOMAIN_TYPE_OF_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_CODOMAIN_TYPE_OF_HPP_JOFA_100829

#include <set>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(codomain_type)
    }

    template <class Type>
    struct has_codomain_type 
      : mpl::bool_<detail::has_codomain_type<Type>::value>
    {};

    template <class Type, bool has_codomain_type, bool is_std_set> 
    struct get_codomain_type;

    template <class Type>
    struct get_codomain_type<Type, false, false>
    {
        typedef no_type type;
    };

    template <class Type, bool is_std_set>
    struct get_codomain_type<Type, true, is_std_set>
    {
        typedef typename Type::codomain_type type;
    };

    template <class Type>
    struct get_codomain_type<Type, false, true>
    {
        typedef typename Type::value_type type;
    };

    template <class Type>
    struct codomain_type_of
    {
        typedef typename 
            get_codomain_type< Type
                             , has_codomain_type<Type>::value
                             , is_std_set<Type>::value
                             >::type type;
    };

}} // namespace boost icl

#endif



/* codomain_type_of.hpp
9z0WFofq/v0ZzTuQ08/28upzHeXjvUuRdMB8DPMlqFC6Drp+NZBUeoO0eOoGOHwPCedgn+gpWL/FxiBdQugI3B880aeB/R9wVQ5toELDEZyPdJOA4BBL5+VkxGRH7mX+u3n8YCOotLbkGNPWSNFOsYJVStc6gVw/fCsW56NlnB+7n5WH6xPmg55igOCTnjNKyiHUV31ahU00jk76duuTs++OHXLEYst/74/4JSE9D/3pcw90HgbBQjGvhvmGuzRwiY3VfxqusvvU+zQEAjyyC/CpeYyoVmugA04+GtAa8ACLEohI5HI4Bzp1cyl6LVFp2AqGz+vRwW7IYoaI3OUM2Ge0gcelWLv7yOz3Nq0IW6oCbYaAyesHfMIh1q4OPXmrtHQ1wxOavfAkL4ichkhPKADrxYNQQ9XqO9SkJ3BBp/OjxThZVysTpYFaPM5857doC0AOEIUd+GlQaj/QhQ3cnnYnWqT8OOl0mvaLJubYPO5VHkK4D5Ge1bW1zVves2DiYnJ6PVgsAM3KkuXys1n+rzno4MvD0L1VdCRpiUM2QQ09VVIsycgCeKGYLw==
*/