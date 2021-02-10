
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "or.hpp" header
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
owe3EQHxyFzSCED+QNU0NIm3YUKiaP+hzL5Q/pHJVxQ2jvqnAaO7/xPgX5AA/109HTQEq2M7eId6Rb4cukSZPNBEtoxAdjLoJ/o6jeVybFwslzPH8Ngm88HAeUOnjLdrBEql8MtxiToJiVn33LVQDvXh3LVOCY00UcTzoBTQTCrI44ARjwkJJqzSBgInEPWTbmvQn7ZcQKPimUA8T1DAQex63wfNPnRBIB9KTEx2rKCh6G0xBF/ej8dSBl9QI3r3i/GX4cAdAbgpngxuaCYiba30osRe28lkaWbc/zJbDMZ3uA/9ke7A2baogQQVnKBNFkaecd51czl76FtRuNH+rSuYSL3S9jXYK8l1fMe4UIfyOAYmSh7blnWpYTmz9qUmcHa3cK3Gzx+RmRXxACjR1hNdAaFLJiqKkemhqr7mKjJHqDoqSKy30Z7J128abYBdhYs6Oeykgh2kQYPdESA6sdGxzhvg2EEjQNKKiXC7R9onIluleT/yHRAJRR4Ke1UGXIG7p2Jv4YwrTnkEKBKW6zJ+U9UQu0YhkiLKY4pBsgGANnrDReWbfyZeVR1b56vNHQd/e0Am3wOHJvYhmHYRq3W5GiyWzt0UjFPKUnj93noPEF4ReVwVJL5NxjfJTNI00nURMFrPZp7nJmg3
*/