/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004

#include <boost/config.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_set
    { 
        typedef is_set<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = is_std_set<Type>::value); 
    };

}} // namespace boost icl

#endif



/* is_set.hpp
IPBBLKB2rjYf6rtZbYDOlsHv9358/QZf0X1CwP6JiiQ+aHpAQlZtYmoxEzyAZEBFY79mbKTRwlislJoxuuGlhEfNfn6GvePWCmsUpAtgjLgkenSu3uT/CNkMN8wRCqLqwQ76qWtSKC/DiKFeSZZHeZvwzjXsgAz2qgykU9t9rT9A7Ahod8kpffA8BvjNaXTmhlp8uyLMiXT8h0XksrD4FCyn2qVNaXOFMRCQMVcATdj/arBn
*/