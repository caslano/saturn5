
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
4ZWh2E096yEEKebNjSw3q8L847tZnqgjuFn69uxQUX+DlZNBl8eU5tbWJve6Jc3DQ1732xNZ6/QvWTJxp436SUnh2VLhb5Wkhk5DCAuzlfWSacU/HFi8usfp5rQe144YE/2xWjBF7s8KxXM7vWBHTxYwsy56ywm77rQ2Kb7o/9ESxNjRdiJ6ZreujqjZIeL3pTgE7fWvrwnsxtxRrD8228+z2Si1/OEe+KN2x3m7Qf9yvZ7vvufxzeOMyo5zo2swI8J0fa5CP6vSo+LhF186r9+J7SeZn9cfBN3rmzHuP3682Cth9Mu9dVznQBD7OU55jn9Zeylkvrh/MtPcqM2wbVx59itPXUTcMzcSLyCtIK9graDZvOZ81Xp1hnTcmdlpZvhTyRpml02xwORhi12N04i+gLvyeWaxBh/Okv3WAUmhE7XRnz6b2OKVG0p5p48QqYNgleR5bdSbEyH0CUwPJNYNFA/ii4LrH8mzUXfCGx8NKasouZHIXuO+wkMJ5bDHg9EIVY4JBtx9OP/kQMb90WxMog/f+cL5W+TD13Puc08qZDHX9A8w5cxoGgUkaSrUjKxp+xwHKvbvV0EPNH0vC4ZM3++6c6Rsisy9Z877qIvjisal/tDzO/fPGf0ST2fHmpbL15HwbLjYUBjuh1BYtTJNFpnf9sLkuaETt2FQaEhC5qAJ3wpEhiScYkuuZhiDTtUx98zQeyIsNFc0
*/