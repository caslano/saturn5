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
SnnYkqk7jclUJzySBE5ykMhe6gQFSSDpRJ3sJNXMiHeVNAGkcJSuSJwY2yDgsWpJkCE2dUw4WvdanDRbt6pr8MBi6rBwiq5WHANbDCBelcXC0uaMkerbIN6uosTu62x5WL7NhersaHe6ULJHQLquDkO03AbPUzH5z1iO5QBDp2qFqK4rcTSAiecH3uO7IJFoSTZ6/vFZhSiunmAVzttH+2EMUn+bvM6BmTM6tTOQwXgtw2RRuDq289TpHtzr3PIrBZMmp3ZgAowcsCExgb57H5I6rRlQ5wFiqUbqD69GlTJOck7fW5CPAowXrZbU+KfjoezrhNgHKdPuZc7+9LKrlzsYlgp4DdZ6Ouf1F0IZqOeOA9IfpXAF+rApo2eqSlqmpzuhr+l3xk6RZRyZWa7Vkm+VkpkHgwMpwXmcViMs+7HHaAlNcYpImAP8GIA+Qz0d/ZDKjVebkUsD8/akudm8PLxqtuf/6+Oi923StYEH6bR0SQpYcDBO7d2Az9yD9zx0HdPbHiW7wHwx9bMYm9thq9uQl1q1WVNKQzEhSl+j8MwiY9vC+N/g9nLBxzHh34dKm4Szn5RaUhNbjq5vzIpt1BklevzAsJ0PoTSoTkK3HZ7dkXYw4yvWXNpTzPpJ7mH9IbijTggb4venauruv5m4595mtme2ohWo8WY9fbrjy5z4bHquYE+zO81qz+xH8mD4LaaMldC3/SlrTUst
*/