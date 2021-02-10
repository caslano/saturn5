
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
onRogueCH5fCwhOigr5datdn/DXkxn6OzsiGDFdCIwz5lKzny7Zy7HvWu1g4qOXz0kEhyxINye4BfG3MbPQr1B0efzqKgiY+FBAe14PHdYjvjpEf066azB3EN2gbrWgL6pZabwy+0g2hbA31ZXatlEbXdCmpnmkhlGO8Mdrp3E/3bp7MqHmtVrVubY+lw/kcaGrf8I+omwqPCYSi9+MeG92PwQ+u163AerDudiN7SBOY9MKOeP177MfdJOtRxzsaMuLd7DpZ0LgXw9EoSbPF1XBynYzhEgYnjKMx2vgdj5k/Rntn3k3TT3D39j4UMun2v+UvUEsDBAoAAAAIAC1nSlL8DL/hWgIAACgEAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NTkzVVQFAAG2SCRgXVRdb9owFH23xH+4oqrWTh0pnXho5UWrgGpIK2SQrqpUrTLJTfGa2JFtypD48bt2+Np4IT7xOefm+CTcoXWZsBizE3YCd9qAW0gLHqYrBIvmHQ0Y/I2ZswEaJtMUMl1VQuUXRMp0jiAVlHLeu+5CJd7QwtIi6AKypSlfqmXp5IuTFeqlOzsnCjF3yrmm3Uo7IEcxL6VdQC6cIFWlyFJq1aHRuFSFjhl/w/VKm9zG7C5NWDKZ
*/