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
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
*/