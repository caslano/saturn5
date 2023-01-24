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
AgpBZ2vXRajpQtmz5DKrI/S2jnH5gwpdbNC1+ztyBXna5Q+ZGo5f/MB0mRRalOqT9RcjWCcSWV8Vw1YGdaxid9uDyMPLMsSlD0L/o0p0pBLjpgehUGV6eY3wj9wmppseBCLvk+YwjlQfYzTdb3amBa5JypA3PUjyRgm8sWqZvS9G6EiQIuh38coH/q1CeFd4pkDUhcaVD+o4xfamB6ncrN9ILp5EL1di3/Rg7T8ij0HNjzUGsWdV0kcq0XkCHy+uMLb0sZ6GuZ7f6JDK/nbhYC//u7Yfe3jZ3wu0yxmy2G/9toZi/I55c4SkO/XYYpb2Tu7HcfnasQg1g/3W0ixo/PqtC8PYbz31/Ujz+023QRRZ5ylKEepIv4JBKK9+okKoc/H6Bcl+EI7piXab+foF0veMdjFdvyDKE69fIPKkWxdMekh/xnz9gmgPidcv8L4ccwlDkk37Br9VIYP9zW9S4P2D3qCAeuiLcTuDZCfHulqB93MxHGG8Plcch4xBTVKYci6RniPdXSi10Me1KxakPqgl6hfqRrxiQZzjLFcsCO0jXq8gvlM7csX1gLSsYTeHUyIdA/ptCWjzPptbEvh4EG5H0J5lmdK4nR/jdoY80zuBLRDmKrGAgj+lXZMg1qO+IDzcPAaMqxCs/otAY/UjLcNI9SPqQDO5WGwj+ZoE/py4PmM8x8aRvjRi0stCf4h9TYI41szXJIjj2nxN
*/