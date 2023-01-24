
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
eN/ymmrqqsui9FDd3B+G6hFP0vfSMiYZyHlkV/QTMsMQnZDvMOZWfQG3+BqZgjuDRJ7WmjR7LC/ZR4MEMR6Rsc/E64Zq6QA86d3F9U0kjH3RUDKnV8qmCNnQXDQgg0Qh8svN75p2nUPgPbG4ILwsQ8fZLoF8sYdI65fbP5EGEeofkH+7LICXOfaA/+9b+H/Q5PjeCb//d02O739ocu+ZDdL7AxJfqSozwWR4HDoq01jHkmVNkvR2PdLboOttP2yGJmbTNbveKEbtCasKageyA48/bjZgPPbhxD6Pdt2pJ72yCSr6BBRwICJzThqcuRPjg/0FkxthNmxAEceCTJ6M5/BZT46vtbkhz52W4NdPtBL3HLw8VMQ62451MvO+o8NBLyZQqdiBzfqcrQMDPL20Ovdom33tDs77dZi8Uz7Unwj5/xDXzZ6Po49fibLITkZ0Enjb/daU0Rk0N7WO3HEJeJlOphbJP/w6OzLq1VdllUkI7mi46o/ihv0VqWp+oZFrdW0PUAZs8ZGQEP72BqYd5z7VV14px/RH3dggd7Y2WsPPoXLpnHVhUe7lsc9feoWspwziJxk5ISWzElc1noSwc8LmoQwpKycbYsnt2247i5ZrlkDq3jTI+q3trjS0cDl6T08cQHMMSR2ErEu8VJYzEYUWHiJIl/N9MK5hqHrfDkYuWknAde8f+p+InuZd99yW60bTkAB3awjiUqiX
*/