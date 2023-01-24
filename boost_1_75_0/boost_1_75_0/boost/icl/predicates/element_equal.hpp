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
36JpnJK+f+sTEzBYYMND/Xn/7Wuz8Y7yGRy6BbXvcCplOR/kGkNgP9Luo2u85DqCaCcmkViNq4GkIjdmDZah/6RnBqf4BSvRwruYuNzc77SqLbBQpkGE6m+3dwcj1Rw4wzluM8wafIktyryb0lh+24/gIZRh2EkOgw7otOCw3civ7s/+E3JyOcXDXqID/+6K/lzyNSxhjPNYNvDgdn1D/RZO4INcC/3j7b7dIds4jnXhyV/tTwKy1vvjS1lA/M7tTg9/sXD8hVr96F03WGuoib5a+dpS47etwe00M89Wef9ftQjvD8wHFjGfilDEiJ3BlEyL93E/ep6s5+xNpGlGqflEu7/Ie23WFdCtbPdLIIcyP5Z2gZE1eGd8nM/NY3RvR5t/ISHZe00l/vQJSmpTBAG4VvCCIpgPu8onzyKtUjPZ/F8AICzf0y+ixY1xdpLF+wdHWMpAFG2URqAYn0LL8C3WByOsDMBXjEN/rvorw/MX8GcG0d8dF1zAaKySUR/ICZGirP6Uv0LFWc2ccbDVK9dT3U8XGloCCDrgvObqLMxvr9zD1mOxjwwfSWtTX0HH+U3ktMhx/vGn4KNUvtaMM5xHx0P+zd+SZagqznFugS/lnPx9mcYGNOhHCqF3mocDgzV24LaPRZv+6ef16Bp8Dw7wG8cD/1l2C3HMgwKerR09k1LnD4Yw2oA7Sf3S9ZnAaXI7ad0cXM7qIKKi
*/