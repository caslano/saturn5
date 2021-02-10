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
YLiqO1rqMrYuRES9sWegt1csIZ7BbJ1+enhqU/oRyTL6GczW6U9XMFeiNLPgWUkpX+lc0K+sRanYoZCls7gctMJyGydyyX6HDBRneeVwWp77TFJdZZ3LZhLKNDHCflhzLTmJiNaz2OuO8QzTFNALLBNB2MUbG6jLFsL1JFZva9rFsy5klQTdiGNJyM13Zla4j+vlPMY6xP5OBi/hch5ooztXt83nK6173TG7mHd8W3f+Cnx0ZdZSjavTghAWjmKlo1LcFtm07t5nbl1fPNatuKlvpRsLI/efzvL786qeP4fzyKWNb1u2M6wXCOVaLwG0/tqDsAtkdLJc1bMD/2ruDQI/irfT78joFTq1NXr5nDVe0WUPhyF58/K0n26N9kRTX5bg9x++NYr/e1sEc0ey+Q3Zid0bWvNuOwaPmBZbOkJs32Q248kyMrdmHQ+BO9y2OecofbfLVpGj9P03IHpD697tBpkV08dI6qXRudme8SK25QaMUEk//f2WWLR9KVIyvw1fkyN15/1Njtqd9zk5anfb7+RI3ZZhFQPKFyZ7a5FZck/7C7N6J918ukSotbRmdzsenuFa7N8ZzNa9+0uMwjipu+/hC4TutH8v0vpuax5zNLQwp9rL0rttp4npax9s7yWp3nX/037etOcC
*/