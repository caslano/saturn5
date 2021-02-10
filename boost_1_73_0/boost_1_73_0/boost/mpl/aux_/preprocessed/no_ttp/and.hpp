
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
sksDW6M1dNuyKdttQuP2UvagyOPY1LGMNYmbv9+xnSbQgpAYzZs3742kCB0Z7TARqqxzy8cb7jvbZi4RszRdDBssnlOh5Cmj5Aj+Bktsd9gGrsxQqBabas/ZTJMey2V0HsJFGML8D7jOmco6FLeaMIZ0i98hvIJHu2NEFEJ0GV9exYz9/TcVI28Mvb7ADYHM9RsKsar0uATLGDspeejMgm6qEms6CDJDwICRIREFUcPwj1DVeoPJ0SPkrd1AXlYIXUkFdFi2GVRIhK3jshENytjNRtfZSBdL6c/my/R+Efs90WL+lMoOZadrkhCkUNm1nP4gfP3n6JzeCYI1cx051NCvp/45+QydJEJDjh2s9jwIruqxvd8PY2z4Bdsy30M/CdA5KwUqcJgbFNrBCrGGiSssTYTaDVgmaFpL1tgqEb3to9y+tz/95U9vD1IPbxh5YmYdxfDFqSeeeZjB9ZrlxGC2bSX9l7un5f380RPXxmDD12fyzBM3tqb+ZR6wXlMRQ3Thibv3Bg0DojAMDOfLeoue8D6ZPolV8uhAnn7uf1BLAwQKAAAACAAtZ0pSDDe53cQBAAD+AgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDU4MFVUBQABtkgkYGVSYWvbMBD9
*/