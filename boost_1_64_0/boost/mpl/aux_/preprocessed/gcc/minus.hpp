
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
cyLess9ZePfjbW8+WBg/tfS67iv/1DN81r93TkSsSfqDYCsZS9QEdleNXW8C/wJbwG+gM11cHenelXTvSbr3VenMkq6lQbrnJd0LsDmsVMXzT5V0y0z6eP4fyhikIzAUfgS7wI/hb+AnMAZWw+HwUzgafgZnw8/hlfALmAu/hEXwBFwKv3LZwfaIdzteEjv2ih2viB37xI79YserYsdrYsfrYscBseMtsaNK7DgodrwNZS6L9JUo39P1c1keFTseh+HwCdgZPgn7wJ3wEvgUnAJ3wQS4W/Q/AzPhs3AhfA662suj3uuvm9Rfd6m/i9Tt5VHv7aW/pBsg7eUSdXupI91gSTdE0g11+4d+Be/+CRH/dBD/hIl/wsU/EeKfC8Q/HcU/keKfC8U/XcQ/Uar1FWpE7yCTfn2FnmJvLxgCe8NOMAb2gn1Eb1+13x7zXv5FjcgP5sIWMA+6/PaY93pKlXRpsDmcr0qXWoe+LEm3QPRlq9JZJF24Qbq5km4e7ACvVKVbJ+lGGaSbLmMZZ8DhMFGVrlrSRRikmyr6LodhcBqU+pFvxfjeoH56S7oYKV8f2Aqq54L1hLHQVT8V3v21Xer7IWmfD6vbdYV3+yeIHRPF/klqP0u6SIN0QyXdpbAjHKZKV15HupGS7jJJN0qVrqqOdGMk3VhJF+9KJ98UQahBuksk3UAYAge508k3QWiQbqakmwU7w2R1e3/cez38RtJdLPXaQ93e60i3UOpvkdRfLnTVQx3pWou+NqKvrUpfqaTrY5Due7kvnYY94T9U+irr0HeF2DlT7JwFXfVXR7rrJV2ppFsOXddXHek2SLo7JN2dqnQ1daSLFr90Fb90c/lFvuOA9gbp4kTfaNgOjlHd56Mknc3gPv878ecmGAE3wy5wC+wL74EDYTlMgPfCRHgfnA+3wkXwfmiBD6j0VorexQZ654jeK0XvVaI3RfSmit40OBXOh2aYAVNgJsyGWTAPLnDr5TuJ9/KeEb0/i15ORC+AfWFjOBA2gQkwCCbCZnA+PA8ugs2hBbaArvWYRO8gk359nL+K3lMwBn4H+8Nat918s/Dur3GSfqLYPUn8NVn8NUX8NVX8dbn4K0H8ZRZ/TRd/zVDprapDb4HoLRS9VtFrE71Fovdq0XuN6F0iepeK3mtFb4n6+eMp7/W0QvTeLHpXit5VovcW0bta2mWZtMu10i5vlXa5DlrgbS69bLu8620nv6ehMAJ2kPYRJu0jXNpHhLSPC6R9dJL2ESnt40JogZ3Vvy+7vP/+D5frdwTsAFXrJsn7vPGcv0TFv00D6yb9t4zPD4zN/98Zm+/vuPzAmHz9mPyV1+FD5DBiWkY7RcxIMVKOVCLHkNbXMxYfSUXKkJ3IUcRUShpkKmJDNiJ7kRokanmQaSJiQTYglcgxpPUNQaaByDykFNmKHEBqkagbg0zxSC6yAdmDVCNBK2jTKwLj+QNbYFOP/1/4y4//V8I+KcP/z3rs/xIslVhcTBSWsUiwDYyAg5U+uZvtfScEXFbGDGpCR/oU92rvStIbxo109zPZ4z+mS2wq6f+yZi52xZyKcsQvk5hnsm/Rxkol5pl2vW8Zb79U+smuRoZSnrhVjj4pGZMrq+drxr36EIe9abtNq/Tl6hmtjXduQyRjznGNJabs2v7QnY31Y6wuJa9qA1tlpX+/xo4a2SWZaMd3yxj7PPFZDjKctKZbDO3Iy/CpT7Zpu4RbvPrK1QYkZqLhmP+7xJ7bkZGkW2doj6ur2af6+/GW+utvgqpfO0TVr51eYOGIxIwTW+eJE3ZJHe5ERpGfebWnrf6NMRWbNH6pMhj3HxeNlOl0KeNaCJFblGn1Y/yXVqf3sf8=
*/