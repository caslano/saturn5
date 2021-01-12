/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_ELEMENT_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_ELEMENT_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> 
    struct element_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return is_element_equal(lhs, rhs);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::element_equal>::apply()  
    { return "="; }

}} // namespace icl boost

#endif


/* element_equal.hpp
yzbfwr68at7G1zSNMi9v48qoZly9tcGlpQ/35gMy2BuxNmyTteE2VEOsm4j1fnyn3oGJzpTewdKB6BY+G9gqpW9h6da09FYUu4UTE68I+51aHiaNNP6HT4v/JuK/WWrYpDVszsK/Wa2OfPpxqWAz8N8k+H/xUVPfAdZ38HT4byD+G6X0DVr6RsV/I4rdwHkQSkrQBTm1PNoOX5+IroceG36OLQ/BYDgiKPcZi3uxFe/I0dt0
*/