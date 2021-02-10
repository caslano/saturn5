
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

template<> struct not_equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< integral_c_tag,na >
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
aUUMMEmbozZ16aRuSgVMYhgD+xI/F20ONoZtwXPI8iLNNhwYvRUY7bUwIVyYszChlQcBzIhW/WD5ULqyv04Xd3NyP5+T7DWAXhsRX1hTJffVyajQEwWw4uI7IosA8tNeySoi64SvtulzMiMDwYzwpNjlM1Iky+06e9/MSP62/MDvcscTdPBmuZHn0omI2IutlLYiQNgeh9EBD6lXSorGhbyjrroABbbji8E426J8DJnTWsWAvA+PT5jvQ2BNWeMaraxbJbqZRlJS6boumwNqew0bEr11ROn0JeNFmkdTfy3PtgXtra86PA5UwBBCHv1aW6OdrnzzsdF/dmTc/5/l7nCmcPmJxhHxe0dZAAUews2p3vu36TJ+abdmjI4Efvjr//MLUEsDBAoAAAAIAC1nSlL9NQWWKAMAAMIHAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NTY4VVQFAAG2SCRg7VVNb9s4EL0TyH8YJGjRLhDq07JjSMa6SYAau7GFyN3jAqxExawlURUpu/73HUpyjCZBm+55LzaHfH6cmfc4DjVXOmWKzwi5WFS5bEqmhaxYQUKB4YyEW37YyyZTM3K/TmIyXy5Xn5bXtyS0Tieh1YPJBSS82fHmUomMk7DhdXHA44xp
*/