
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          less_equal_impl<
              typename less_equal_tag<N1>::type
            , typename less_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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
EbaE/4Lt4E+wC/w37A0tjrh7AC+FdWESrAfHwTB4BQyHV8H60AYj4EJ4HrwONoa3wCZwFWwK74fN4IMwErrjSrt64kUP+8SLplqUuFK5rrnBdbOV6yp1+RlfVyXXNUK21fW+Lku5rtpVrp/rIrtJuX6uSwjgugQkTa5rYRAv3rou/QCeDyNhNEwLt9QUTysxt7UXVxuKqf15x9Ru3Pa/EVf7S4qpjT4cXutxtQmHQ7G1RrG15cyj3IjsRU4gUf/iXkCuRsqR9UglUoWE/UQMLZKGLEA2ILuRE0jkv+n/yAxkKbIe2YYc/HdonmboCB2hI3SEjtAROkJH6AgdoSN0hI7QEexxjub/Z5UWnXn8fxzx/Y3O5/v/9DDmWsh8n1HjkzImTUzJLGVDHLvdcc1y5hRWeq4ZkTIxY0yy6wIO7Rptr6zemXKNa66Ueo3kY/NcwwVjxo+cIBcp+RyRa5TtDHXXxM5QrklPGz41IyVdrnJfk+t9zYTx6e5qWTrINZu8r6FeOXnaBd3k/0+o/3/lhHEpyT46iw0Tsrzsk56BFdOVvKZR9xVyjde8KtVGcl1EtpdOyUkZSXKVx44r5Bqvrcnlog6i07fZHp0mpkqTKXVLzfHokzLxyjEjUlInjFD00eJDlrewuOcrJtaT9S2Req5v+9oeNy1k7qCqjN89S/TzdrN84iW21dPPD6tuia0Ny8sPaM+11tQ9jrofdtimoJjN5EjpXW50mH5e5nbqmWhYLtPTAihXnfu8PExvx8Ex+Fglf+Umw4iBz3UdSB5ZPmWdCjO24armurLyA5nL67JfZKaP/ZQyM8L19tuB/Zbq64fx/JfptT9yuN52O8l7g+TtfQMGZ7+tBn1wSH1j+1U1NyovOBsWZJn3wfX19TZ8hXpWGtYzcDu62iiigd6Ou8i/SvJ3DxpB3sf7u+v7YHkDQxtSOZ+ygryHE3LM++DhBnr7VWpjlW+Zp3H/JkfobZcagz6St+cBGFz/izS4f7dFGNtuaXPfsoLrexk13L9RDfW2+w22S9PVL/B+5+rXyxvqbfc6edskb/XFAOMFtMeiy36d4w3Gv4bG9qtori8vP4A4JZf9Kmsa/wzm9e9Gt1UGdcSAfsv0Gv8a6e23h7wrJG/lpSlo+x0zuHcHnmdsvwP68oKyX9gMc/utOU9vvze0sUlfZtD2C2ust9/eeK3TS97qC2WQY58lXv/8KG9sbD9bc4Pyghz/Rs8wf34caay34VvoF2tUzyDGQFf+qU30dnyb/BMlf/Xl1WHGAPJ32bGbwX1c2cTkGdLCoLx8/3vqu5/BNbwHxjbV23Afus0wqiMmDKTt/sPeuYBHUV0BeDGB8AiQQAIBIoZXCS8NIbwEMUBAxIApRA0PDSEPEgjJmmwwWGqpoqKixopKFTQqKirW2GpFRYmKSitqVFC01EZFRaUQlNqoKP1n9+zunZ2Z7EOxr53vO/zM5O495965987MfR01TWs6GfOwfyJtu0/8wb4H9jU8Rzg6m+dfvU85DPY9sKGFejy/szH/XtHe1XzSF8p74M7Oxrx7lbjrJW71oy/Y8tfVpPylx1i8B5roC6b8rWmhDtfGGPPvtWT0mugMpvxNcD/nY415+Drxx8RL/N6P3pCex9tM3qfX8K8xH5FYg86gn8lxLbxPH4g15uUbpDXFmNaQnsvzuxjzchfxZ0n8+o/s4Orzayb5uKuLxXPFVF9wddqRb52PaV2N+bibdK401Rt8vd7Y1ZiPb2tthsSv66QK8vm8yyQfE+PM87E21kRfkM/njRdY5+OKOGM+7tHaL7N0hvB8PhBnzMeTEmmv4s328giuPJ6YaMzHgniL98RYM33BlccDLdQ=
*/