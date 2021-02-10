
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
M69FIMcs096AyMFW4dMFlz3hNbrm5A6sBRs/cL0gKHrtq55vrVffeSFYgmxgdx1nDRhy8Go6DoAaPM894dwTSaA4/YwTzyR/WhpX+R2gSKp/zku1BJ4I/IngUJx8JuEPdYFcNb6zIzJD8Jp5cZq/2EUavJlz1/9ef1UEwUkdNSMHDXzrPfSkcjEPZPaFqh2H4RkSATSP4zeCFC4YdBWnqB34VWSrqhudaDKap2aUrWBEa3AWN6I75g+NQf0MNc8jVKxXlrSK78oPQPaAFFnVqMbIyig3DzVUytGsSBLIn6HVZvt6+qt/RUX4/ICIp+eO1Da+ooYgDwX4X+40oZooycLX0/BdddQTNPgMB9iDANp0pnpK4iz/enks4JMdxxsfZCdutEiC2HTgEHCpFSFwbrP+iiZmlp1OJ/ARWhYVoXXqh5vvAbFBmvsr34ZxhV0DkEJZnJ1NgdE4wBFO04LeSOI9gDntAbHKq5O+orkHfurxa1hqD4jhQShqwl/Lj6rNlEHXvrm6cnAMNx3MPg9IYEZuYbogO9kAop2fxlEIB8ggzyWEd2tj5+dm4Ofla2bHKXhh6hxdY+oN7If+H5RhprEh5QtVI9g73Wv3D9pwPhu41/g7zVPXZV3HSRGY6W0sluGhDTRczj9K3gGu
*/