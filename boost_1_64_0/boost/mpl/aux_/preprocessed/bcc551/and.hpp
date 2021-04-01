
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
L66QC57nSOUkaOfk1ZLEu2ChES4s2ItzzrjeOw9Gj9YYntO90cyC9ZHAldmBP1Xpr0lIS209UafVGE3oLO0x7xnYQGXZpCongBb9D2TAKNYTTJCCsXRzhyyfG8Bcq+acaq9MO+PG3FXh73Ko96jq7Nppt+LBuahg7eVasrrXLWHDZxRNraxHqutyIrfgiXDt1H3jUHSd7wRiq4oGBZUln5PfL3dBZmE0sSv/PhcwhBjCDZcGE4aJRbdfUo28gLDaBFpSHSqa52azZbEgP8AIkgkT77RYcVgZ1t8dMwrlQin6qlk076Dia3+drWyQJ6YRwyoz2XUS7vNDnTpfoa9AGc0DaypxGfbVVRbI/rUchmKFwWKO/0ktHn2o2LhdgmkyG97viJn9eVW/2NzCLLyDcEOpjP0Mr0Ob151/LYoUfMYpgcKOpqogJQOK8syNhIIgcHO/33UqV5n3C6SWvVroVqgGq77S0KXeCmE1gM41CtG8lSXNTkcCrgTJtbr8R0zkRx4znDr90z8zCAXMIIbrtSaGqqcr70boZBSCn5qZEkP7L5e+SHDyHik40g==
*/