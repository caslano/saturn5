/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ICL_CONTAINER_HPP_JOFA_100831
#define BOOST_ICL_TYPE_TRAITS_IS_ICL_CONTAINER_HPP_JOFA_100831

#include <boost/mpl/and.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_element_container.hpp> 
#include <boost/icl/type_traits/is_interval_container.hpp> 
#include <boost/icl/type_traits/is_set.hpp> 

namespace boost{ namespace icl
{
    template <class Type> 
    struct is_icl_container
    { 
        typedef is_icl_container<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_<  is_element_container<Type>
                     , is_interval_container<Type> >::value));
    };

}} // namespace boost icl

#endif



/* is_icl_container.hpp
iemebWkR22aFtr9rChxcSElDBxuwp48cKd3tzA37G7eo1tL55DYCTkrP6qdu7fKwlLCzbtJN+jR8pT3X1rU8yKYHTCtK8sCU5vDW/57BvPjptgiLLwum+SoQa/QePXY5TPsfDHLKzPcNkSRbwgTH7b2V4xDosWcz02u8BroBDtws+glcH4rBfDesVX2u4Ial1TLj5AcpaQs6LSL/dmgsJ7YgK9gk7HUBGDJAeanwFypUPN48o6fnsXoVvvGWLul0waS4e8IjnhnAxhCtH9z8e+GUXjjMGSuYE4RSX5z2J7VlUaQkqFTvWSvQSYEH58vXm0fGxLyMaQRRxz9WWwo2bN1il4sGxKnIgChymd2Ah9+1QiWNM6QjxqNpSpA5bQWvilHtruN8VATa6cLwdO7bt7kBHuaOiaruDfc1XtO7DaFbwhpaao0ik+bo0b3PBYJgsX54Hw4+RdcuxJ6SoferH1nwYd/w9LTs1RNp2gHpoX9abMflycDc7Jwa8hg5oJZNWxMoTXOTAG+U1qS1nKJCXx4aEkpah/sCkRw3c7jlZOziEZWtgjkmvC7/Og==
*/