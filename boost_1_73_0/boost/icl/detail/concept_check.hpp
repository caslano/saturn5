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
vDlcT39yuLU3GxKXWzoXPYP93rXlbrjueX3QDtkcd2DjwvUiQyCAH3I7iHdr8qhS7wxD/c6HcyhlxQEJojz3qE5boq9TK/OsMMoOnuiRaR1beqyCGLmVwhQ47Qtpn9/CnY9O3Qq1N5Djmz0+YzL/NWGCoKQIPGte7yyS6htQfXpWdyfofgFFZwsSUgNYkozyusdyKK6UcCqP5yf245uP29HOriwV/Z/j2pX/mLz8DF24ZktG
*/