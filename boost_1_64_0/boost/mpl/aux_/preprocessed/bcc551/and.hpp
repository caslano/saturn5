
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
pIwNoXz/5PEfvz8a1dZoom83MEW43R3PnzD/UaOL9VMeJ/DDrgSyKcKx8KzrFi9UGdgyQ7dkOREogvYBScXxMUQPWC5HyFprLnhqVllko0V5twyS1fVhYU7TTX06jLsselR4bduvwVu417qWb4XrqqrPXD95UdvlVgOFtQHC2sBg/4CgHwh0A4Acx16tV22pyY5vWceaxxYRitqEC0AfgPRWN+ttAQ67t38cZjVVMtzlDcyp8vXRj7B7zJasPuruR9wBXvxd9uLuMn79Kcpm4oy/7dnkOBXfvpb5Gz04WHeq39d2nUTkZPoWXymz/Y/WVGf/sHKTG6adsR8S70wEzEdJ6n9Ks1sSebC3UWo/KeZ1Lc51l0rBzxxQrSsT6FH+dVps8IDLtaoce2XTq2j0JvGq69iZ8eq8kKDfjYSsEsssVC9z1NtyAkpy2xQPptSuS79dSCx4VmwiXbGdCVmfaBW6ezq2EGT+PrevleovDeovmtxLJr5gMi+XeMPHT/dbxnzlNXiLkfJu0tjfZFDt9+2nythYiiI3C1qCqwT4fYIE8DhU5aSGD4sOVmcY87y9Sx3QS3KidnHky2QH+KjxHI8bcv82Gty9PAZ6znOBTRDg1p2PAbH17V/Yvn7R9XgpHlpGw0vzPbKzeXP4sMBsMkWXC6zna/5VUOLw1FjmvefrBw1DChZPa6VARUNVVyjv2tPeTHXNYS37AM1Lv6FZ5R1EdgcTMeh05pD79AL6VACaVFBhUwFkUuE19VTYLjcIcrkisuZYiopD6rpKRpWq1O9pMR/O0mI+nF3f3vzQntxTe9+pMaNvgQl986vRtNj/cXEmm/akqUCQG5FHN/c/jybns9FVYtykhCBt4RXlH0Y3cH7dTo5qwfju/OoK67GnWprfXH72CHD38FNc8diec79OI9JF3q9TSaJfgWBvFYQd03aJLUJnmMEpeDpe3R4msWZ1Mh7J7aP18tOuWXocQFLqLsbdJmVkP98R2ZwiS7kx/n10NcMGRk5hwxiff0WkMpvg5v76OkksL8h+TzXSdsOP84vrUQUZt93HhbCL/ceSzjSYff3B+tRJnH28K6R7kw6QmzFGF6Y+E+5nlzqkuEDNOnoYT8c28kUB32NBwmQ8k/2iU7UwGhhi41RUp+OOla1FF6gLl+U+x5G2Sy7G348vUcjt5LfxKHFs3Xop+3KPsZC0Y5P1ct3sjxPZ/yLjrrbGGdlX2KYOM+nyJfjRKhHeSmk8QVHfTj4WiYb3u+vzjzPMWI4yg7Oi3JBg+jtXnkjsHH3aZ8h7MIFk1RqR4RAxkDh5Ip8XSRxdFjrzEa2EHNCJAfBpAXRJAWPEKTHeJNnDFVqvyexjl5OoU2mz6asspy9ApK8/dBQpukGRta4jlBnmV5iQ0m39DaxaTwdSXUMc8Ehdh8CGi+z7BfaZ+kez1PBpWCBEGFGzNaf+wTGtmt79dH7p0FgIVprC6+j7Vorfu5Z7Ku7M0SG5oa60LNtfkOEuKZ3c3iDUXyhDiPe4AvdoFwqAS17gFplqFD94pQkuo2Tc/SOSNIVIXwzl/IB0Xt9eFgyF3W5LRsSv9AvLn6ptpe5Ts1kqBXxjhkrZBPOMp/LJL8r8lBdZ93mnEqGSFyJqeCd9w7P0nReC9A0XkvK7LKT84gqR/zRKoeMXTAjT90ksmNSc1a6HFFIqE/itbR88p3P37YE+zqC8TgWnHVJlPgHQUm7yLyK378+od8d7apM3AWzwdGtnmjrTplZyzGeWei6oT++R+HBAfVCALjTX2SNUPtXe7B3DvrEOMS8oloGbPMmbyoqAfQl5ltuwGXf3E1ltuFZBcjmHcclM0ZoVp6V7iMod2pbiXLk=
*/