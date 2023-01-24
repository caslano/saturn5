
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
rPl3QGj5nAsTajRrtfXWRB9KLSl7WmRW9O6BWnWK0SO6bX+hdp5GSk/utAD2pOj9IVAKIkfJJgfh0oqZxt33hsvk5jiy+GNU7Sjk7ZxKT8IKWHINJB8AI8kzg38MrlR4AH+BaChFJiZUywAD8VbReBKjAqJ/8qercq1FjoNZLm1srwwWPyhlX1o29YQh3VGEthyVrR+KTKRxnFMg+ZBs65w9nQx5lNE6bJoSHrF+T4KIYW3PQIdnK+yn/LjTeFQxywvMq55ZgB8iqkvtCgN7bV1HQLFGSjx4S+APPJsdtfvs/hHoLHQIWPVRETZ8GWb6TZX6c1JRbiedH33QXMwMx9RV2FkLs5OI90jCuaWx4oLYQqujUvu6ohVGnoq7OIa6VGIXbIPpfdajUdZw8TtbSh+qGxpWtofi95McxyEl2y90EM9LtrkytH9TnRgFi5uMI9kmVqpHvhr9VtzIkOx0hajd2ttkhAIEkD55Ol5PIZOl88Ma/BnXrqosdXauHYmqe/ddFbGNVBfdhmW7HsJEWRtCdjZFYXgj+As+rLpJZDtpskp2EqRKdFkfVSxbAwlW64YLhmW1lh1m/l78Lmv+OR2C62spcMbH8yFCsALTVp7h9+1vbkH3EZ0JjqShoskiH3FIFsKwNdpgDRQ/2irnujtDiC9H8EVpbf++w2tYqCqrKOzXZ8WhjJ7SIpkvFK7QQnfGlHp39/QYguWe
*/