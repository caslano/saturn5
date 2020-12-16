
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_impl<
              typename greater_tag<N1>::type
            , typename greater_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater.hpp
fVQdyzTSlZK6fdTXyr5ZZN+HUmaJ0oWSa++4d7fPHu133ztvy5FwqTK9TbX3qpk9Px195rnwJ31zJ2Y5b7OhXafgflsL7Xffu/9eHnfrRC5Umx/tuiH329isN9XFfHBpu0n31C/LeqvVqS9mexa94rxtj/Y7993vW1u7jslpHZbUDcnvd/Qn1DvUDU2WuqE49FW1JQkiREm8VhJP2tcw2LcBiWtk+VfJ8q+W5ceqlm9sZPlhqvkWq5bvON841XyVjSxvrGq+KpmvQxPLq24k3ZGq+eoaSXe4dT6GRZJuo8sjyHzdNOYbr5ovrpH5JqjLz2E+Z+tb5TCfs/zVyHydG88f35MyXxP5i3KYz1n+jA7zaeWvxCDfEThV5lO3wfKR/dEXW6IfdkB/7IwB2AM7Ygh2woHYGUdhII7HLhiL3TAeg+S9Rpb+vqov4/l9gk9fL0M4IZHgrM1IKZ/tQnmvdKPvlN5y4Ld5r/R/wzul9x5o+r3SxwI9qJNz773SJ4lzEHewnfonqPouc/H90scOuPeO6ZPMHziW8YP/3rum9/X1+s3fN11T/p9/5/RR1vMswacfxxohgVBC2E7YT6glePbn/dOEGEIWoZxQRagm1BF8BngZIgbo9aD6oA/6oA/6oA/6oA/6oA//qeHXqf/PzSzKUh4A+Pfq/5W68i/IaZjcn66UuvKfsTWew1KlfjDDXFeSn6wkbuTFfUUu9c90aGbD5/FziZRmlPvkUm9QorpPXUSg3z/zfWoZJ8W5YH0m30gh8/5AeSbf9sx+e9Uz/Ln5GcnUvVif81cWXij3ui3r6928YX+HI5T78eb1ZTWVFXatPtnSX1k8SzZK+wh1WiUaafUjrTi7tFzra8uSlo+/fVojJK1gqS9Plv62ZhAGMm9Fmimt/JwMy4acq/Qul5+R2XQfg1rr115V72XMyCyQadbtyCQ2ga3vLHmewC6vuySvAVIufoTB5LVtesO8ZuaRVxfqpNXl45jX09a8yjMUko8QWfksKbMMwkLlGYpZ1rqZ1JxZ+QXJRfnJuRlNl5dlfx/I0oloLYPruNlGfLt6oQrPhvXy7Bvk05K2a/1uOq634zryp2m4Tfq2W4uLWMca2zqm5xba9wPZv4ljfMpNDY/xN5Q+6rLN+alhnYNYv5zUtMwcyWMt05RyITGKRtrSyHGbl51hPY4zyVt+aqbRtP3kON7WSVk3Uxd5cvxbytQ8ftRyPphrric7JmnlphbOjkktZPOapx83zSf5UvUveNKyvFkzB7NMU796G8j/efOz+IYe2ayvzFsvyzayEClru/LOkrrwaVLeU6S8g2ary5vd2o3yvi638fI+qi5vVRkNIkf5hayPrKP0h5jMeTKTPxuWucQ9bi1fWWeNbVDjUOYnHMtW1R5KjgfTso5plLUn+2gG5VZMnC05qj4MZR1yWAnK2O7cGih16h/Jsfs+4RalTjtPXc6cW2flufC9RZnii5RpYbZ5fc47lpdDnsiS07KpU62zet+oljxvkTxvkDyH5tvleW5mQfbM+S71h6jOt5xzHY6pOtt4WGPHVL2TPB+W+vuXmjEf7sPF5LnOlmcWopwhjYUUSYM2e54a+/PKOQ3fD2TLj+RR9hM2ILuJlKtj2cu6cUYpsnzvn1Dtl5byuIn8kjtrez3z95mclxz2R/W6+1xizvj3sr3OEMYr36nJ1nXPLsrMNe9kbmyvKH9b+0Nvaz29/B6Senoe97T+HpLtMtiy/QJs08Is+2UgKmVDXth/KRuH/Vdz20sfotVs47as6+2MnzStm5SdtbwHm+bb14rfT8w3XllWCvM12C5hSvk1OCcek3JMJXjIb5Qr/EnTvhxlx2/6u/4=
*/