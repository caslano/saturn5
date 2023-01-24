
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
flL0VevY4XwA4ADPKVjZH+6kHIJnDhivsbBCHrngviaGxO0FzfTB5CH+FM9GRcz7QRgSG6hXnHuS0mfqEx0+2Xb5lghMXovfc0Wok1lnHjT9aswy83z6+OvookqFZl5TRFbmSecbtD6JmODyegT1IySDLcLE4kD/aI5qdSavwGv6joTo/q3VTDryNElkIhZQii7iKzWZn2VB3DZDid3JxIrLnQaPKoYWirJkNZAp8cxseIGkoCvdJfudJG2YKd9OBwNA7qZHz8NVa15xrnTfNDvZfLkNwTYpwpum3bR+9NVicByRHeWGJWXhtyg+je4Y9pLhWnitohilo7qgUk0n+xgLo9W3ifCwvcygVCF0Be03krgRXg1WomSsBPzt9uodpL1BbgVli+UC4WE8H9ogHugHaLkhpjDXYlGj9D087eVcY7Z1tizvzUifhcgAZf4n3Q0Nl16HWLdOVEeb8+HTkkMjQch2kOiPJ9e2w8B0pT2oZ8/80kUlmVvlcrI8EppMfJh1PVTJCgSCpiELO44O44vohvkhu/PXQrdZHbxvatZregvDhfrG3zdvRJ9L6zuPEYx1KU6d5fEjV3O+HBPp2X7FdNLlJQ4syMEj7RN5VSdMFqLr7n1OlEJuy1at0YSvLZ76SdN3eNceRmap+odSbU295ZmY30wYWc8NhPtBYPKqzazrcUGwpfIRc+i5Gizoq7Cgo7tIgLsJtGl8
*/