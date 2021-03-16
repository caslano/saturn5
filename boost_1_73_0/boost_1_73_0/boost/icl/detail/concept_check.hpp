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
zqlXWuWnLYQifX3wON9TM33yp3P9LtLZRGbMKOsiKO9O/pdK6OjWSFI/mnatpHOp2d69qjWSOjKnKrWGTtBXOlEN1FFtdKO6JkFUeRHTo/AOFXIyWrYfzH4B+8wu5zuxaLMtrgLvIUGkm3YV6S2KdmNe1ifcrFbH14aZXIniEq34/V0UXPPR9FFRVWR26giGreV/G3bgt24HH+T2Ek83Ikhd2FBIK8r8KUZUoDMtppStIKp3Cos+dqd/pbZVTmE=
*/