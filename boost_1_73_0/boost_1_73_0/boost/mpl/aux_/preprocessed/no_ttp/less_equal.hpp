
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
dHMvZGF0YS90ZXN0NTk4VVQFAAG2SCRgzVTfb9owEH63lP/hVFRVqpYGpm4aUYZUMVaqdQOl6V6Ray7EIrGZfUD573dOaNG2pz1tL7HP/u7X952TEXpS0uNIZNqUlpc1HvbWLf1ITIti3n7gdlJ0G48Eytq1RtEtXowf8/vZvFjkk8+TfJILtXX1AqU/LBwyXGTJKWKWdEl6ogcP6HboYq+XKDKHm/rA90tJskucDK4G8Lbfh9mXSHyShCkUW3wD/SF8szu+GfRhcJ1eD1PG3H4tIjG2htBQfI9mRVUK79sjg4q0NSmo2no8oYrDhkMSPlNSUVNHIhJxaW3MNXZFcIleG4VAFYLDH1tmCtzWeKC9VtjVqipU639c8H/A1pEGto5CMnnjWgfPTl/VGiywb1UfiYpow/AXswdkbQ3aw76SxAZsPYI2nlAuwZZwEcbqQmQBNhK1fno3/MD+nSkgM7LhGf5t9mCvqWLtSnToQBqOxGI68OS0WfkwzeyadL6QKds0DOqKS5PkfDp7KO7m6XlgeD7Li6RL+orj7bGvdqK/o9PlAQIhIEviRGF0wguDSnp4QjRw5itLZyLbtVgOsXGWrApd8CODkAFeBI3E1HpK4Y86IvHIxMU3K86dhiRxYy3IYIJhjYB36GRQ
*/