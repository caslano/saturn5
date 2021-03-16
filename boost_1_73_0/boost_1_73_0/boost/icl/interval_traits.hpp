/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_TRAITS_HPP_JOFA_100926
#define BOOST_ICL_INTERVAL_TRAITS_HPP_JOFA_100926

#include <boost/icl/type_traits/domain_type_of.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>
#include <boost/icl/type_traits/size_type_of.hpp>

namespace boost{ namespace icl
{

template<class Type> struct interval_traits;

template<class Type>
struct domain_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type type;
};

//------------------------------------------------------------------------------
//- Adapter class
//------------------------------------------------------------------------------
template<class Type> struct interval_traits
{
    typedef interval_traits                     type;
    typedef typename domain_type_of<Type>::type domain_type;

    static Type construct(const domain_type& lo, const domain_type& up);

    static domain_type upper(const Type& inter_val);
    static domain_type lower(const Type& inter_val);
};

template<class Type>
struct difference_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename difference_type_of<domain_type>::type type;
};

template<class Type>
struct size_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename size_type_of<domain_type>::type type;
};

}} // namespace boost icl

#endif



/* interval_traits.hpp
Z3JUEDI5KjAmR16cO/lgacIS/GBpR00+rQHeZ9jHO3yR/bh8QLImYU9y8C29LJe98HkVGJKuASH4abZo8h5k3J1y3WDMVSiP1ZzHaqtnrQRejtYtyeJPX/Tuu34IuObwckyBXo6x2Wl+ovkUt7loMbUu0+6kVBfkaD5K4jWIQi4VPcG33nTkP3zs3xt/PKJ0el9SMV+6E2aG/6D1sHGyHhZ+UBJ8YKxvHHMsqZnDGkqpXTKmFo7llzvJszY6bjY=
*/