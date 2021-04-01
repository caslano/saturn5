
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
DIfHUBLYq6QmMopHWqawyWr+NmFiGQ8ub3W4BtZTXtIJxC0Cu2LjEvdWX6DcVr1xDSx0LPj2zj5H/D87NUwp1VPomiNZKV7OWuVvRdbKBEGZaYiXB0Lw4JogBeTM6om5GZfrls+oGxacW7HRFzyDPysO1UYAt75nYpppQefG6tmEdRKJUct8nnArdPPkFqUgM+QPy+ZSq3in2vCIvpkONDL2KciU3bTkSNJa9MsL8tjqbTyzl8DsBX2TJQvsCb9pjLUagAK6OeULwH+ep8ArmW+9cyhstqPV6l8IOt6smXNjzeXSSXLVcxD1WfWK9iyQ+eK7t3FSXI0ooMUcWOU3S9FdT6d7XCIaOObbUp86WQ4IlhppvE/3RTw8BpOAe1lVOz1FKwyV5XPEz8Vbp3AhGJdlKKI+TyuXuAYFwhCVYd3mmq3VBA1VRIOh959YxTS2LNl541Fj6grEVdOG5SxQovWCW5sK1bR+78yX9f+oJKXTQtXonvc0vdwW0rLOsmOi2IJt6rbB4nYewlXTm0a42++HXPu7Df0Y3SQpDL55/fvbgkJlR8Q4WNV+eA==
*/