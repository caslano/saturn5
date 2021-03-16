
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
7wZSTNFmIM0i9wBLDR4hK3IDcC1wDnA9cBnwVx4R3XQD8H3g/WTf4PWPtAMfIPtoy4PAbsCHgD2BjwFDwCeB1E3PAm+l4QCEjD0PhIy9APwNcCvwJSA2tpE/AVvJvof/OCTihY92kH3gTmAR8PfAK4C7gbOAe4ANwDeA9wD3Aum545vAF4BvAT8B7gN+BnwbmIehsB84CPgO8DLgu8AK4HvAJcADwEbg+8BVQKxGIjSEUMdIG/Bj4GHgQaAP82I=
*/