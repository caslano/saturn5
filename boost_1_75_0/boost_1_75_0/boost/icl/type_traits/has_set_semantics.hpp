/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_HAS_SET_SEMANTICS_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_HAS_SET_SEMANTICS_HPP_JOFA_100829

#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/icl/type_traits/is_set.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/type_traits/codomain_type_of.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct has_set_semantics
    { 
        typedef has_set_semantics<Type> type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::or_< is_set<Type>
                             , mpl::and_< is_map<Type>
                                        , has_set_semantics
                                          <typename codomain_type_of<Type>::type > 
                                        > 
                             >::value)); 
    };

}} // namespace boost icl

#endif



/* has_set_semantics.hpp
yN9fBd/I+fNnqQ1ZH1gGnGsU2umDmZKNiiLzJFQ0tlCNd+y4P9TBxjGe66xH261oEp6g+JOnINbeeK2ApwMQcnxTUf6oL+RhAx/8yHOdq2y/UOBvXM7PXBwk9Eqsvzj7YM956t1zqR9eRephRz105XnJ8D/Ob2G6EviKOui9xekEuUR1L5oxW2X43dAjjjs1PM2rB3ziWdiLoS4Dnky0FLed+paZGZwXKfVoWQ7VQ0de+VZkVYTqSOCiLuhy560rSX1quhzfVdeE8bY9Ra9XQoeFT9dxqqC7Tp1G9A3Hsmea6tHXtvyDPeOOaH0tdQHa8/yfsH1zc3uX877pdKE+370ptFzYxwh7U7khQtueSAcFsg8vRL98p4TJxmqJ8cz289C+y5aEV5C+6PaxvUi0X/VeFupgq6eQMbAI/TN8J+2/zWRW80b82hegL+5ciPXvpZ36N2MUegPdZJDyHsfe116HcpeOZt/PcBvHAXeVR9uAAnlb6Hi4pEh6H/eUaN8/D/R33xTpmpoGfYMb6wjDXhHp2iyCmFBxI8275RAHKvB7zwN+2TGc2aFrHf4wLeOBOuhV94OhPuyIC0bBe6QBvkn+OYj2RHns6+RCPP+1G8kQ12NZwG+bjzYoOHVxyCdtbgfNQ9tncIOeuE+granHmHq7o4Z8QViItCFX7dFzEZd84fd83YUHF9nKBu7gWIM9r86mj+W8aSp9dm0z
*/