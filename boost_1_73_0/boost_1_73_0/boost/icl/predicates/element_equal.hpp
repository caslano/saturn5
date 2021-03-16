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
nZ/2sb3ykQjdLprt08vs0w2W9oml5caMt4MBMTE8SFInIPQVhybE7B5GzEhcbWl3W9qzCN0hccSMAUaz5aP/hK87QvdyaB+E7uLQbEtbiNDdHHolyZwsfD/JnCz8wvJtsaFfrAQCPB6hcXBR4DwhnWykJZQ/wZTSwnhELAOCV2ouVwl/GJpkO7N0vmsx8TnDFco/eqHq7R+9UEUvaMscUxLYUpCSIksRn6IlyhxNrLaT9B78fCqfAByn7J3SyM8=
*/