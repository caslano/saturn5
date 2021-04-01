/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ELEMENT_CONTAINER_HPP_JOFA_090830
#define BOOST_ICL_TYPE_TRAITS_IS_ELEMENT_CONTAINER_HPP_JOFA_090830

#include <boost/mpl/and.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_container.hpp> 
#include <boost/icl/type_traits/is_interval_container.hpp> 
#include <boost/icl/type_traits/is_set.hpp> 

namespace boost{ namespace icl
{
    template<class Type> 
    struct is_element_map
    {
        typedef is_element_map<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::and_<is_map<Type>, mpl::not_<is_interval_container<Type> > >::value)
            );
    };

    template<class Type> 
    struct is_element_set
    {
        typedef is_element_set<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_< mpl::and_< is_set<Type>
                                , mpl::not_<is_interval_container<Type> > > 
                     , is_std_set<Type>
                     >::value)
            );
    };

    template <class Type> 
    struct is_element_container
    { 
        typedef is_element_container<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_<is_element_set<Type>, is_element_map<Type> >::value) 
            );
    };
}} // namespace boost icl

#endif



/* is_element_container.hpp
j2NTIWILfmxvVJhOXeX571XgF7UJGPrkdddglJKtfEByO9gFZIbWdvehvIQV/H4JvHEUZpV0kQKegyaqKoZ8eRbQ1b/Z086IOCwUmGBiDbfvjSM+zuxdu/O3curTnu8rcIEbrvfRQoaXh3eCEHPbNSdJtpc9sJC+J1cfolUIQ9AyQb20uEc/FXywx/CtuES1CzPiZH/0Df9du7zkdAslHOfJa5RvZI6qikhgC8m74kOnVpt5u+R3Fe1oN6HmQTZunu9jYDL0g1BERpelK4bWmkO3huATAy1yP/CKFC+79leF13dtRTPnONxtoGDbNr+JDhD8gmNdbOwUArvLnxqXtdAL7jqjjmoRRqMtuNmRKu1pUSxprqvULRCCjbFUqJDOpkylE0Xb0ByB/5eGCqoKNJ8EuKj8rRSwtKWaWbxQJ0gIm1Ho4ctoWSldPT/6fdv4wT8nmiPnzLQQuldvG2W0300r4CWqQjXoR5JAuBaRIIQ9zbh9szgaXiPUhffCl/8kpcg3r3KLdfOUSiMRkZyGRvDbuermCvXnx0yytX/aHjYlnT727B7fQ+2adw==
*/