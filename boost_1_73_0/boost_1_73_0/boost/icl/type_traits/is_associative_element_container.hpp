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
RgZgnHCkWtUGHm//GVwg/+zRjdTXCKl+Z+nRGrMOpuPhkm3k2ADmoDYSpWHoUhU2kVGOZbbJnzIqFR1c9h+8vkD2wtnlGMlOeFEl43w3YN8ta4LHEhXsJ5at54W0AdFK4Bd8rsvisQPOLsoZTU79e0uBbpcGDrnoOec8snnXS1xp82qAUFijS0JiBhxxsoHZZQqKCblTLOE7FDx0VqSmoM48BWaVJmDlKihSGFPobEuMsume467ttpxIBNkC5DZqyYnc0aYET3JwmvTqbVzhxHYBpwHkMXilUxWXYsiW7Kht4e3r7dLnCkkVDwA59InSPk4Mi9xJCN2QcxWvxyIOJA9RwUnmdIUUKa+ltrPQQDkOe5GN9Q6VEM5g4BlCfOeWXoCWSON0SWFx/Zn083iBw1T/vb/mlPGddVMUIp0lYRg+vglp6zkD/jEBemtpfG+uiz1giGj96ZQr1Tf/FtdjAl/jGkyzpiLby0Np9YKYpbVQ41FypwZgpcigPEbQVJKXPgEGp0aqM3LMRkiuWRnMJXlBQS0FSh9L2qZoosDVGKOlxRWqzamko2jopAuu7QMqIDhn0SZEAIxHwNKW91tGhFW9cRzaBq+MC52jAqAmkjGHsJ3LX+BVjeCYm11bq7bbaBbjNwFVU95AbU6q
*/