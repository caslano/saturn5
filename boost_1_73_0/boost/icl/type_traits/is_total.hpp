/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_TOTAL_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_TOTAL_HPP_JOFA_081004

namespace boost{ namespace icl
{
    template <class Type> struct is_total
    { 
        typedef is_total<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_total.hpp
Eb/ZxNY2Rh96joHozaEnjVOa5urnfL9GiVmKu03yVSNVnnMrpiZjjc2tvzSeqirbFC37exuyBJ8HL1VpNJVqvUFZkTZ7ERx/37s5fHbnmCXKU2ymhe17DC1s5SY9TRuCZpW2yb1P24B4M087DPjGWYs+4HOfF+xX5wUzZLo2yunkul3Qom6eSNcv3nSalynOaJ8ix/X/wy8UH1SbugfUvwb1b7/6t0/926v+7VH/dqt/u9S/
*/