
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
RJqBTGlsxKCbJRFzer2pEY4QWgXDpjcQy8PjYspIvlagqNPojVAjIvg1HsICKrQIpW7+ojrEzGPjB1Nslr5K4eMoULsvwXfuWFSot1ic0QrCwfs3ROgCrLA4UBh1HFSFavWfGf7PmtKZIXjXjdSk17UOFdomVXFCASVK/2yR+jnLphR/nIsW4IQFTePgaP+wCKKRa2ztfnPbLRaaoPqfLzsI3kaDUGa9lk0xYYNVNOtXr6JVO9n4YBUMAqTXI/TZwSY6T2h1uYdAFmTpqSODMEFZqKSD74gNnLjK+BMmtjGWEmys8UaZesLo5wbHOgefyXHjfAq/QeqxR2I+uFpSebofz7bm/aebRXY/e+ixK6VwQ8un/DS4FlO/e9ver5f9aUHBj7wEfyXLjz/7H1BLAwQKAAAACAAtZ0pSy4iQ+6UGAAAnHgAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDMxVVQFAAG2SCRg7Znfc+I2EMef8Qz/wx6ZTNrOgTGQQABnJnNNLje9XjIXeg996QhbYDVGci0Rwv31XUnYmB8B0kmnD81c5gjy7ker1Ur6Ru4rKlVAJL1w+oyPBH480PlMpKG8cG4GgzvzH3y8GjiBEA+MysXnnyR1+u7Stu9a9yO4p+kj
*/