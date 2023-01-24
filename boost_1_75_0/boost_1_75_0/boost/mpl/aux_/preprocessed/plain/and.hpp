
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
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
Gnh5tgmdGhlVxUw8VEubhCzuOzi3LDT5ZK/ap/9IFxqW/EiyeahTtn0+lmPh9VXGW12JPW7NXMHTIw1tNLDjCXRLdeqf7AHNbrrBArYmGTD4+U9aPFCvyrDPsVUMBnzyYSA7SsHUpsuAjKx42CVyHfR2YQS0eg0fm0OzP2evEQpahpnwuxQ0FHbZB8royLC+Dfetm7K1Bt+ufJ4abXcb5i221vvYUb1fDc2eKKGqK2obXJ4jwBwcF2qye5Pv/QfIAktuVxkosWc8QqVNX24x1p862Vztn6ycxjuHp5jmK70a4ADgMVgdJxcAzG5mZWFTOAUIEbY7YFbLhWWP1SZhQB0wPZIwP1s5D6NVJWlp/Kx3XCir3F5Qdjz5UWWkfjm3UK1n0NHqwdxSnVyV7WqqYSBgDTjZaXP88/ejXJZHfRjWrgZmcuzrdW0Agx0t6TsWdfmaszqC03f0XeRgDHwmsGq9nYYva50jax52DCeXRp4wwSZHvqa/kF/7jBC+KH9bfU/0FgVYhhFolhYyDNqvvJP0C2vl43RemPywuJX90aMe6Y+9z+AcU2qzgUplMIdnO142v9ZPvtMy8Mpf1JzWhUiALr45/AwH+8DEIHI+c2R8KvdnoOjDL8NH0ewVlrl3E/3H6mPVWRESw965Kxs4/WMc+Tbs1a63WKH254K4kC4vcPs2h1aWoCl2eYhVyYoQdGGzdadhnnIT4s9/
*/