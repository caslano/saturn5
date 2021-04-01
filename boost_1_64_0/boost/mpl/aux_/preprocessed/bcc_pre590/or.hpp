
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
ct3pYqJPozOgAnUcgBysgx2JiKYoK4vxnDQeots7Ec6VApqBbe1zzLPnB/jRE54K3Weev5IbZNm1VVhv7WeEQ7hfCakjkVCbJ60gGNNSpcve5E0EWl46SG8AxOmgUzNeckR9D7W5tjcL/ILjQL0AT7h89dPACEyivfmTK8kutuCGUOJgU9Nm/2VbiVc394rJH8osX8dbxOjj3a1EcjGLmgKaOV1j5Y8689Pgc4z1SonSLKOjAI1XC92yLVwVy+P662Yzthb+fkmYnNg3zMhrji0+ENPx1JtTlV2qVdOJkTe5Pcj7FRFKnC26gQwc2yydwc4RUNj1mmmxSYv/SKyghP18do07C3dNB3xXOZQSlnXX52/AYiCvMALO3trLq6fzxA0BNLSGnu5zOj1VR6vlCLNpSWJElb/19EUM7qzyJGDPCVdOyMj1LBfRhn7PiFKCYQSw1NRtcVDxwOkbY0edi9J69J/FoOHyls5CbG0Nvbc6r9thgj/OgRsKMog3/FXDWn4CZU5WZi7DyGe2syi4KzmvZOz+rIlwDhfGx+D5h7TgJCrM4uuOsxanYg==
*/