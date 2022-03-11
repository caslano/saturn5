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