
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct greater_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_equal_impl<
              typename greater_equal_tag<N1>::type
            , typename greater_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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
IvSatmkyC3Dn3Wno1M/pD/rGwoBXX0bHUrKuqRPU8P8XLDgvK5POuOwNtccpG+YK7zduww98DB2mi+9DwX59PWr6QwNHSLQUsVFcQF/Ln4/7GexLfORZ9QDHEaUK4iquHV3g/db67nUVJaTh8GSSaYw3ykWjBtDFSyl9guWaymR1TAZRUx67QyFyai3rijVbUW1GjIlYmHOlM3rzWvriyxMp3AuKrKUV5YcsVCXmi25dnhEgloG4OLR89Pt2GZ5Q3NtM9KwDD/5Wr1sD0gLWP/91vWHUPqdrqAb/Q2FZ3G8X6VEY1+u8o0yf3C/nUnalcWJZUYS52waEIJRRd3CTeC07LgAzzERq7p/IvqWQyi2kOc3Y6o2wzpQppWhyQyJzqlUZa7I2Tr+QHH0TVmUZONh7KFhyJSTDl9Xij1rQ7JxreU5BON1Nocch1vfuJlUG9Mf7kidlioi5C2KMDGd3+6ZlTyMupwzxjng+INHhrKDpuXcoK1cQt+mKvQemssXFh2E6nHj9q9s4hfKSnG6828qCw2wGip48zxFMMtoUo3WkQuD1pfeukgp1kg==
*/