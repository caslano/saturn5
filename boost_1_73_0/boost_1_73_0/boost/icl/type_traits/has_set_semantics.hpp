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
jP97mdaPJcUC0afNNub1y8SYhmzzgt4sW3eihzLwcOi9i3z73Lu0I29ku8qr1uOyciSDDVbaBCpLqYkryaIeI0jpNEitX5WeJgnxVdpS5dZzh1erOayywxogc6gSJLia3hEH0b1C6gbETEcjWUQ3cxFV/SJiIRdZTA+5qsl7oqDRyPbPnSBwPFeJsVFfj9EIkKrRc/8uXO+da/trrJ+ArYtZYNtvqeW3rXNl8DUZvjJKQ60W5P4y2bWHb488f638NF3KO6oaJadisu46PXadFWM9DKBmCf3FE6LsdOi90cx1E7EhdunhsPUkx/IlTZ4FvRWuOi/5L7UW8AkKKpVd5oVol3ESHhG2iJPP8TUXT+ioujpCPri0fXKe/0dZlYgjKzyL3tgnnm9HQ++UZN9YK7manMoio5SAaozyjCQ0i2/SJnffzwoeGHrDyPYt93Qj/X4xp+qOA9BboubBb6gnmC5VozReXosfGbPqV3OwRT4tqza4UUQOvJLpv1QfyNrxQI4TXTiDgxaGI/W7NUiPgXDHxiWPP5tHx4l5A4+TBM0pjAFk0UJGcY3yQqoLz+YQrFji3PQysXdM2F/1qDmgh+hxAUuXKNlSnRxtT2LeYnWmjyuFrzy+C57U+ax5XaoKcL3Ev6BO5hE1z5l5
*/