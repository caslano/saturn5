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
79OumPzMQiSeZ2tW8iKeBwj9FvxOhswd9zoZSnc6osxRurvRZErmTrqXnIehycKeubSyV3YvFI3yqvK2PtnSxGpX7qW0uj4WT2ldSuqr0noEQ1FwhGWBpGCF91wknBLLqgRcbxEgdDDZCfR8q7dR1kqBZmk7s4DyliYUWdYC4PVaC8Zh6ldoJ89qr6zFKaqlbc6DyludoQwd7tZabHYvmta1pl5ohkkO6C7DvdeLm1xuaxbJ0tYWgeXtzdG1+Q1Xorm3RqfbQS6azxSwtN0ptqWtzoPK25whbvMWJ1lwgxCCNu1nvAcZlKhntE26uWj1DaQSeUvwLZd7RaEK+UugF3Ml2/ief+8Hj3iI1nQc7AvZQfOeoZGB7ZMxSJ3YZODNHcofvJli0w21s5Fnj8lHcgyfYVxjpV/3auNZGPxqYbpJeJJ+PiSKdXdjKvjhED8wTq9xXnbhoZoFZ2r28lkUaeJo6W1OrGrRxpNSSRBVWhDPyCQFD8m7ZYVv1e51Zen35dKUw8lRoPRYb5IOzYoGoTuL6/z4z2n9Y3rQh5WEoedD6aQPO2YmXmcOmmX0miY1Cx17+BbY+HHO9MwajKxwaDHGRqNENq+4JC38ihBoqGccE0PiD8tIEAV24mDaHJZ/S4968wcQuHQN/Sa5
*/