/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_STD_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_STD_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> struct std_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return lhs == rhs;
        }
    };

    //-----------------------------------------------------------------------------

    template<>         
    inline std::string unary_template_to_string<icl::std_equal>::apply()
    { return "=="; }

}} // namespace icl boost

#endif


/* std_equal.hpp
hNmVZZ6xgugZP9UeFfQYvfurx3gKzXXT1crM0yso5e5Mm9rMnjLTztXDMecsY2B6XRJV9hfV02vyRFGk6dFMOb8XA9JYOSlTptupmTLdzgCSKS4GHnEyOMzKFA8VuZniiSIvU3Z22mSKUXzbTDGK75Ap5pSdgOQgZY9McYHZOVNcX3bNlGl190wxp9wLSAa3PTLl9jF02HHyO9YLuArYJ1Om130zxTi+X6ZctrxPptxGth8wBXnaP1Nc0/TPlEs=
*/