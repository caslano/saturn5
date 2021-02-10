/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_HPP_JOFA_100410
#define BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_HPP_JOFA_100410

#include <string>
#include <boost/config.hpp> // For macro BOOST_STATIC_CONSTANT
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4913) // user defined binary operator ',' exists but no overload could convert all operands, default built-in binary operator ',' used
#endif                        

#include <boost/detail/is_incrementable.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/icl/type_traits/rep_type_of.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_discrete
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, 
            value = 
                (mpl::and_
                 < 
                     boost::detail::is_incrementable<Type>
                   , mpl::or_
                     < 
                         mpl::and_
                         <
                             mpl::not_<has_rep_type<Type> >
                           , is_non_floating_point<Type>
                         >
                       , mpl::and_
                         <
                             has_rep_type<Type>
                           , is_discrete<typename rep_type_of<Type>::type>
                         >
                     >
                 >::value
                )
            );
    };

}} // namespace boost icl

#endif



/* is_discrete.hpp
3TXdkwS0cWqrbeuH17XzAcFcNcpQEnyjCkAvhuwTGtCMK0iuXFsEbU2knVwF4ODCBBhKV2ZcVKdkWStOFZMAVY9gg6iRqxw3t1JXQAojEAz4EU4lA5dGG+SHU4mHmWzwD4uCCZ8V1gQJKLESfL9HS50jWqbBH5e3xF2mpRTnZ3OCgBYBkxMxySIHoRPXRAHYYAGsK51zHH5DUYKbaxjtNrrYgO+xRbQirlLsWQ81hbpVziNFRBvGQ5VBStBDhpmGhmtk0BQ80hba2EnoICq6a03kBCGm5N8Y/Xh4RT2CB/ECHddgPVFsuM0RU00W7y7m80yZrXbWcH9vpdOcdK96tCQFDJUCbtHefJcIsVjMx2JeyiY2xJ/K5cpZL25fRbZTbvLWlJUqM360YxHS3ucI7d02JecV2vTuGvUkl089kieQemAFOoJh3J5+7HmBmwtF0JmAIFFld1x9GWkLAYEPUCu3bcBLXQzk67RqNpLfnJ2+fpnq32NkvWWJvbmenF29H5gSA0WWUhdx0bPPCHIEu/dXl5PFp8UoXb0ThSRc0J9A3GBWc1cF6ULbHLq1nUeWNTBxNJ/9zmxhzpWRdIw40lJUdq0LilGi5E9uwJlTK+WUKVTGHTMLkXTpavcExzm7PJvfnF888Tc00YDR
*/