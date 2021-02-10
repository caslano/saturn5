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
hyUiwDKNN3sv5CAS7ypdNU62abBa53Bxdv4ehni5OBvAx3gdwcQLN3OerirRKU83QZYFcQR5DEXGB+Cj9gA28SJY4tWLFqdxCosgy9NgXuQcTQcZZPEy/+KlyAZfetGWsJIiTeKMw5cgXwM+pmtc5LDkHFBlzVM+38Iq9aKcLwaQpPFDsODkpJcLh7x5/EA+CAqlA1GcBz4nFqXdpOFbv0oS7qWAEfDCkDQDnsmVd86tBswaO58VWwOdwdS27vSRNgJJYfhbAsUcCSFl5txaNox0phqKPmGgGAaglq2Yjq4xwvqsO7dgazeKjSoWaiFeg22qxmykmzdCUZ9MDR2tNABgjQljotnqLT5RrnVDd34W5se6Y2qMyYgBpgXanWY6wG4Jp8XsWgNDV64NDcaWTVCK+TOwqabqijFA3ramOgOEqO9QRbVMpv00QziUgZEyUW6IiC1Uq5/CsVvFYRbatdE9NjMccmNsWxMwLEbMYcY0tKE4CmljDJEyG6CehgRt4q2YgpLq6JZJCmjasRXiYWo3hn6jmapGupZQcCwbBWesUhiAYuuMjFozh3AQwBKwCGNqJaiIPsUDuQgWmo2BmCgCeNzNRpV9gjr/MPxYREPRBvBR3qv+q//ep7LH7oOkLNRgud+8Xphyb7EF
*/