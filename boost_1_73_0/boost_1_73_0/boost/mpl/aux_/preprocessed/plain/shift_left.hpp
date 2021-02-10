
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
aJtl12o+T2oyMfJL/04+Jf0fg/7B5y15t8YhyWaqF1WW1KvD+83ulbaeLv+3cfaoni0trKkNWmHbpaorSKb6GqHGkh4Ggh2Yrmj5bfKQlrwCnVJV1Fil6OqIRpPbTQyNkXOpMjDKSfbWIkp97QqwmW6qsxWk7SEwT2BJAaCzebS3Few8hsND2B+sJy7QGBHNa2116krTHXJo6uPmwHbEsTY2hD+qqCNepCnOqWtLbm0O3RlWVzYPIXgWPD34/SyWi8IqlyPpqr7vCuE5/FeG3eH9975u5jpSZq6Nav8TfpmoLebmL6Dr/F4wDOM9LxmG8Z4RwzDec8QwjPe8YhjGe14zDOM9bxiG8Z5jhmG854RhGO95yzCM95wyDOM9ZwzDeM85wzDec8EwjPeMGYbxngnDMN7zjmEY37nv4gp3dUUkN3dwRPL27hO5uZrnJ1BLAwQKAAAACAAtZ0pSMCU3VugIAACbXgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY1MlVUBQABtkgkYO2cX2/bNhTF3wX4Owgp+jIgsT2sBZq6wdo0XtLWdWI76ZZhAxSbiVX/kWApbb1PP5KSqHsJs51479vsgqmTyLJ8dXNwfkcie7nI8mmUiZOgF6/vE/nfQmy/
*/