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
c3Rlci9wYWNrYWdlcy92bXMvY3VybF9jcnRsX2luaXQuY1VUBQABtkgkYM1a63LbNhb+76fAOp7U9ii2k05n27rpLCPRNjcyqSVpJ94kw6EoyOKGIrUEZMdt8+77HQC8SfJl2+7Muk0kA+eGc8dBDvf/vJ8tts8e/YnUnwg/+FQYo7L4F0/kZugo+o3p/4D1EZ+PMTlkDcpv0R57HOU3tqtQIsPlJ/oeRY8x+kiy0V+HhPkxoq9YARph9ovFXZlezyTb7e+xlz/88D17wV4dvTrqsUGcpzxjgeT5mJfXPfbTRK38bRZ/+XIg+M89xiWLswNDKpylgoliKm/jkjN8z9KE54JPWCzYhIukTMf4Jc2ZnHE2TTPO+t7oynFPe+x2liYzInJXLJmYFctswmbxDWclT3h6o2ks4lKyYgp0EJ+kQoLgUqZFfgDenElezgXRIPZxJgoW38RpFo/BKJZsJuVC/Hh4mCzLDNIfTopEHCbV8Q9mcl6f5ApCzOM7ViwkkwVbCt5jBNlj82KSTukTCsHiYjnOUjHrNdKAVT45LEomeJYRLeClXGixOQuMenoExhaQOJX0IYpcEKvbWTHvAEKPRGW6LHMwgh4ANCmg5h5b5hNeKmB18oqF0alS8L2maeSdsCKHMGzbCpgT
*/