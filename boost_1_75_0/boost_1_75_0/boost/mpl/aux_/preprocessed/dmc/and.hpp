
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
WUO/VUQRmvpxyEZj1OE3ggrOst1MvyWFw9cSFY7jXpbqkiaO82LSFrak1/2xIpPzk1f+XPlHivak4XsWjvqRZoKll4hJtHcWYlnxvqav8uncsz5bUPaydMtla1iB6DPuzq5XnnazAO217XAvnCuH4YJBs/1bLDfeALeec/6nL7s5A8hX5zyMfwqg8szcDRkiVtr49oEngGqme3c9Mm34IX5cbSNorXdXcpiI9VzxzCbp6SXruW4cT0DpFW7yLTtVekfQm5C8Fji8Odfi5jH49+h4mJadv9+rHUVa1uEgMiB3nSDJt/vwwCCBBRrcY8ZCYeqznZcNXCEWnZ2Fq9DL0ZvHLnkKmJJLKcAKyjwy1pR0epezNvA+kibui5+8j9/SCeEorta81/1YFMBe7pFUB3H44XwMSbrsv5aF9+QYcGEwGg4xYnycXwmHhOgQI75PjPzifs4nRXQbeTA7da4mMXkegg0pYAIhl1OAR4Ph1RIBd94qBj0E8cakW9lAY6Zg5a9CBcSLt5mINuzSGQA47fwt0otuq4HLwtPrwevhPtC5ZqPW82HRmCu0HtSMltZYDxljr2fXFsfSsmVo7s6VyUbzt9P64bCgJB6cZVuHKg4WYtDq3f/kF/m7JoAwSO4St+UDaINghfJUJUCjYlR9+53g728BctkpwQYt2aLDNoCvPURgso3czUS3QyI5uIaDxNMQDktgw+qUuFWi
*/