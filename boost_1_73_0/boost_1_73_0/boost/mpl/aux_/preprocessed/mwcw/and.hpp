
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
ZVFNSwMxEL3PrxjqeRsvVZCwIEWp4EG0ek93Z5tgNinJ2O7+e2c/bAueMi/vIy+JZspcmUwlaBeaKMs39aeY6lzCZrt9g/bHs4Pnx5fXz/cnCDEU1LnMLuzRxsyg1cWg1ZQBN/hB6UipyK4m0IkOvh/oeRB+7R0FnvlqBCLIo6sEy3wQ+R/UwbTScKyCLjClxlSEe2I8Obb4rxUOBgmYfJpj9CV4t1vd3svuBHUV29aEejrtQanrlGJIWVrTdctMSjxnsYxzW7nFFyXX9FgbNmga6YVsCYc3RWsy7ogCLrKNvAB9HLUSQCnFVMVamt1J3BXU6ixSl4/5BVBLAwQKAAAACAAtZ0pSOsfdJCECAAClAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDUwOFVUBQABtkgkYJWTbWvbMBDH3wv8HY4+0AeaKRktrEYEStYtZV0TUm/sRVlR5HMtqkhGUuLm2+9ktw1sr/bG9kn/O/3vp7OIGKKSAcdMaFs5ej3jtnW+DGM2LYo5m8/ui+4BShqzlOqZCb7TCN6n7bN9uEe/QT8IukQmPDZmS/uljLIvxUcfRvBxOITZt4x9lhFzKNZ4BsNLuHMb2hkNYXSen1/mpPn6vchYXzCHZHIQuoBX8hkh
*/