/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ASSOCIATIVE_ELEMENT_CONTAINER_HPP_JOFA_100831
#define BOOST_ICL_TYPE_TRAITS_IS_ASSOCIATIVE_ELEMENT_CONTAINER_HPP_JOFA_100831

#include <boost/mpl/and.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_element_container.hpp> 
#include <boost/icl/type_traits/is_set.hpp> 

namespace boost{ namespace icl
{
    template <class Type> 
    struct is_associative_element_container
    { 
        typedef is_associative_element_container type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_<is_element_set<Type>, is_element_map<Type> >::value));
    };


}} // namespace boost icl

#endif



/* is_associative_element_container.hpp
kVjrPtbBObhM+sruuaeiDprAvoasqzaFues3Po2iVXqYd0NVBHbHoGUbEY6d5AEZvyrjkAF70XZM8NXiu3U9D7Wxn8vxVjaVQrFiMbvYmXAAxCBaCT2wcJDztwKY+Mr/1Swmky3sQP6us2bYy3qi2F5ZSqTDqtpl/Cy8f4RTjTHMeeL0F2QZzuy3pqgHlMoGNd42Y9Qh+dixbxlLbpZXsPEmyCqGUCdmB0yHH9bFudrQOvfZFP7mpFt1MUOeUgVv3stnB/un5N72HREBOqR4EXwieHPjYktqS0NjtovWKTxc8OMVoZYExbl0UvV8UJ7c/T4hkMhc4sV/jG2poCLr2Iv3uB0VmimYE9+tqRVdrjf1AIbcGKq4Pt6pdSWQrwzeF42xpjoLfrsK9PdkSFdkcek1tCwQtOmWxkI2jZPeR+uDlSM0i9LbGA7jSILaQMr66KNB2l45+AtAQ+TRmrYm390Y9H/OQpKkprJC7duEh7ZnWikPv73XrVudZMOsLEDQqpvBACS4d0jQ68cPzQ0GJKzRxPD3L61uYTd8B8swN6Ohk5RWOm0swJW0gA==
*/