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
Sfj1mtPvRvWRV+jRFH/GS7HZyn+Z1fJR6puNqjKidguf4krP3q0TLOjklnIZE975hn66Oje6cppe/9z6Kd3qodw8i1kseVJmW3B2vkLr+yy+zKM40E8Hfpwt3sk1WpKAzJhQWvI6euNMdCxYiMvr4xv/gN0QumROa0jRy2t1F7zrM6pSzr1exIo/Wx2iwTUgvlMrV+A7t3JCy1af7F6A2zeC2GMKiQRYbfZtqjD6LeyGd3e3
*/