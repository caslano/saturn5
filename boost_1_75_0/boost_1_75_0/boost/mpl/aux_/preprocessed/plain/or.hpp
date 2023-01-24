
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
+V5NOasXfwJn7FrRqglFsyrb+3NzZJhyUAjGY73K+6/o3q4mCIovDQHU2OPIuAwRryYZvXsCh45gaEIAlO7MMETm6xomExcWo78O2z4TDUbvyBcnR+/SXc7cz3jrdgrpB9CuGLSX+emAEnfnjJK4Z1fraae02aEC3ZHCe4VdDDU0bOto5MQ7gk+e91+zrDeD2VaN5jaxIbp02bAtQR+i7ib0I6N25WnKYt5ZvHbjph40413Ko9WQ6RaT58189TSX7ByNJp7vLO+eOm6EH0XggS/kGxfqzgFZHO8uKy6IY41CjJsSeM+6crNKuOg6j1cKefOyIB+7ZJ3a6QzD6kN/R7PIyjV91Ffr7KbLkl2FjHOu0DkBE1mzbWUDWRlX9fEFGKb9iwSnsxLp0v+8zZbv0RtMqctcthzuCBvVpdPv25DlEQKjxL9pTQ6DqZPqjziaobkE79fpNwD1orDNuZkljSZa4vikCXfo7NEqzAbs+fUHRBSoi+PfXtR2jWMzhA0tzYEqlWdK6i+OP4OIL+xxnt96WLHMZe00TxOsvZ6hMdKJUQsj6RrusgleSH5EXr7QRk6pTfGWF+KpM0VmF+uMcECxrgwkqm+yp5zVxe7IcpA0ROkdaf7agD3sJL7R26xoEE0ScXvp5NbbAwkc0bwTR5LvtcNdnfCXWURCJIUhJn7HN1zIEfsnhtHZ0+/RBjjmIE9x1/EsvLX/Zniq
*/