
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
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
*/