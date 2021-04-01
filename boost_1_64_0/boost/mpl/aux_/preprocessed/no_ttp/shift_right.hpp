
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_right_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n >> s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_right_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_right.hpp
9lYo2R/QjWO26ygkGmRhZVtz7VLVun4yatqXM6Z0pFl/T+PnFRI9znfq6Dchv4F8Xmk3fjYTqA/N4Pba43FATMY5N1S8jb1VIub5KLT50LTiRZjtJbSp+RolwaBW2Ugve4HqPjnv007JNcF7GZoVv9UEZh3xBkWv9ithWNyp3Ojti3LMCmuN021qp5w70plnjX0oM0PkgL7+3q9JZ5U7Fgeke+W8uz2FY6nAhZQppIxvtejn72bh5kiKHkoxb0an/WiX473FUgOeMn/SAFPdFOmXfQIBsFY6wY9SDBVofX9C3umuK8UpLgHkhNOpAXHrFhHYGRNd4n+LSkdtBXMaPIy4HIU3jeSmeeyObvsLHfjgq6oZBqbtaRYu7OoqK5MItJ6XJiI2V5vwOyywCjl5rr3GFvjy8Suhpjkmktka2BoNbAsGWjtiryyoKIqK/fKLAeLtu8OmBy6Yl0XsAKHn3rVtPI7gH6sM5EaaznYc1JtQcuaNXPK9/i6Fux8q/xnDas9JS1SYOrzb/PKV0MJKNHFhgQiW123hOpu8R4IMwJ8wkuytMb2BlkJd6Q==
*/