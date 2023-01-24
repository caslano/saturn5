
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
template< bool C_ > struct and_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : false_
    {
    };
};

template<> struct and_impl<true>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : and_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,true_ >
    {
    };
};

template<>
struct and_impl<true>
    ::result_< true_,true_,true_,true_ >
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
        >::template result_< T2,T3,T4,T5 >

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
4BJBiHGn80kXBhTKRHHjZaHyFh2rpEqqZpHUAtPRsgU1u1/uUqWX8kn79AovVj8cMEgOJERFVg3+dn58w/nudP9rkO9h67M1EX8yzZNUAs5T40Q5iYdDuCxV3ebBH1FEamvsIa/5We+EGkRZOUuij7jJwg6kuojkZqK/j+lrkizikNxG8AVoMPBH0+7gPFkLEMTmPjFzmCXI8G9bblTh3tHhxdoNuQ5ZmjunNRCp+lJyEK2Eb8SoYqGM0AJaqsYNe2WpdgrfjX6XH1CXw+Ih7o74cFpT43JXxbHeNE3A6DHzSSmXuFqJUw2USJ8gnQZIkmH/c+lxxIhtotErQDI9YE9J4CMFfk3CtQOOj98fxqDewQIJ33O3vAbmL1vLK12+/HNt9HPkUO9WH1ShrW4AI+ZyrP38QuyGQmvN/KH8H3ReG9kJ9CV45PN4u4c+3d28nYbbxs3Dg52FW4UIn41AxN7ePDXIBaf4mhba6xK2Bwq7AsVe0UFVJa8zVF7HW8wtpSk3K1xw2nYxaS5mDKu7p+04ZaWFYuxGx1+fiIUSyUAia/vr1JG7h/f8d4MbBiJBT0vVxWFSg8EogygAGlHhUB//mV5bvfMvx9EFAp7aqtNSS2WULiU2qyeq05fqnu3pc5c7YDBNDlGaZ/tuUsQQq7ZCUtTmtqz2Zg+ApiSPd7utxEsopd5wzrvRtThfDv2U6lKXj8mAu/RJzY7j
*/