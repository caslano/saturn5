
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
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
*/