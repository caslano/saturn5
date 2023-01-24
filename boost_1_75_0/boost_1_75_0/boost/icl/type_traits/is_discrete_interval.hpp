/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_INTERVAL_HPP_JOFA_100327

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_discrete_interval
{ 
    typedef is_discrete_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_discrete_interval.hpp
9fM+Yqcitq9HOTszd+kTL0zfdkw9FRnPUJzhVMfIadWeLTEw/O72hkbBpBhN7GwohK8cnMbd72VilJDtufPevPcyC52D/275S6FTeVAB/wHFIi08ut3lNZDAtYxFU76E6fp5zH4nml3F0RSJXGGIzUgz/zRvbYcJm+VZpIVWgi31cMjjD7DCWZxIdcQJrZBZaSiEmdsMnWDf+oETrWz9x32Gu4VEnPD7c82zpFIIHldxM4tyUv0aGkuLdGtQ6jn8KyhJre+Zx+tgnuVVVqd/5MvBiRNjHDjZAZnUk3Vdmjvb0gdwOfG2/C0oQczeqkoVqFOl0A+o32MO3Ho553zy8kiN2aXe+pbTtqRgr9ci+hwd8tSvvCfBMkO46T7OznQl+ReoPDl7+SSpPGxxuyjnbBE790idoC8J3OMgTXrmAzkzbz07F1Fhi5u/v5L8A1RxcTry2YDAR6JfUdDwVfueaZYWlxB05dMt1XyemjMtcOxztO/TLcs3FrKEsHzgi6F8x8RRxjqwqg5u3mQlOTtMj1p9J/czcetDkDify4AIMH2sLWMo/+RNChLfgEc/3XorvDlzsilkJYG7HKTNE+X3DFlQ7ElXiAj9YoLRxdg4JSoMk5+uwSPWI8qM4Lvk+z9B5EctP0PQotx/Iu3p1o387Psx11rKfsOZP9v2c5CadHGahisF6q9omifq7soY4NtxQTlR8FOQB4sTFDkO
*/