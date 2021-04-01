
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
ag8g2xd13U66Ydf6XB7D/PU0waek4u3Oqf+fFXzUqcX30HVbAibxzzD2Ayrbwc28gYUXKvKIYeYCQfAo6pR9W7jfDROQ6ICYgan/fOaCPWUJ56EvNRm51lDcy+gJ5OB1mcUjKwfqTEQgQhZeeLtt3VY75QcNKTVLv8mZanpgJ8cPGp0I1aj9kawFrkxAqcussToBMFaZSHt9LTYaPvWLb8EdIack4CtoMjJmJF4dofrQNZtprHC6mjmQsJQ0i5PJpDVwJwWL4V29XZBgGQe/kwCRg7kZ/JsKBjwLNgAim21LqXojSa0QcQ+fBVPpjgRD77XAnmyxYctBeA5cdR3A9oo1FV/2mOUYbDbO89U5G2cPcjeqMGkT7v5dk4Jx2yIXa7mzj0TaSeYggxKXaXHEM32NCjnIaSCxe3CCaHCZsMTidoLU6f4IXoPJSSy+Ue7MuCwUVh1MwuAh/JST7F8rCtS7xdCR3kg4KMtLYE4qm/ojJn1gTrCCJ/+hH94kVsfXexQ0hZgWRiERd3v5AeHtCGiDUYaDFd9mBWyDg5Jd3/N73oHER4RyDpKpRA==
*/