/*-----------------------------------------------------------------------------+    
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_CHECK_HPP_JOFA_090913
#define BOOST_ICL_CONCEPT_CHECK_HPP_JOFA_090913

#include <boost/concept_check.hpp>

#include <boost/concept/detail/concept_def.hpp>
namespace boost{ namespace icl
{

    BOOST_concept(EqualComparable,(Type))
    {
        BOOST_CONCEPT_USAGE(EqualComparable) {
            require_boolean_expr(_left == _right);
        }
    private:
        Type _left, _right;
    };

}}// namespace boost icl
#include <boost/concept/detail/concept_undef.hpp>

#endif



/* concept_check.hpp
7M/B6YTKbap74y5sC/9ChctaVNkebfrRVrfq6vCdcKG5zt/Uo2Xm05CLy1uUiivWR6KuhTDpmcVCagLYme97CMSORSrhEycogYK9ujKFbxVpzYSQGlF/J1JzAZdz8c/VddeDFu8DVSuIqrtGCb6ZKjkPOT3XrkOO9I8E5gJ/beD4zA+t7PDBDtg1YdTQHh5e3jnwugGnaXGa195ru9gn0Au8kn0iY9wChsPxVR2L8egEnuw6fn0FPT0x99lwL6itnDtW7DX9355zI9Vwz+XJ6i3DbwATOinQChszsRKPVt/URjxfV432EgDTAeRu9zk+MvtQcVZ6c5oPrHS4Mil7Lonfu0PhgW/txLDvlk6S8S0KPTjM4G2BKZCw7fe2O68IrfXSOTn3lso4UflFHg7Msgm+YgO2O6BAWyVFsfcPQsi7qUGHhhAO5cjGhlQC3MPiB630O/pkxyN1uC6+1YN3XWPVa04bXZ6YwD5b118Jksk3r9ryUoO+wYlNxReOqgZs2pW/5D82Unebc9lolgRXTMIxBojXz+CNehPhLjqqNiC1+o/fxw56r7DVMqFWxlyeE2/LFvDPCZirmriQ+g5X6r7k2MVXckjUTyuXEPNJM/JpuTwb+gqYHvedd0fRiuKBXWBsC+j5cb9rLnxl7stQSrgRvnB2IHN8PyGMqOtonoP4kiM1LrvzzbjgObasrn3xX3dOCPDNcLWgwCPh
*/