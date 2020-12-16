
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
QgXBvyHLEPIIuwinCBcJgT5MJxgJRYSDhPcJhkZ1DcGEMYQUQiGhuJGnjzLP4Bk8g2fwDJ7BM3gGz+AZ/lcHb8LC37v/P+OSrFS1B0DDb+4DMMXPYOm/IEXeFWQT6hMyCWuUtkct1Lr49h8+zla7dUvIzl6SmZXkehtI+X66pQ1kIAspa9G1gVSn0XDc0u70gb5MI+v6PvC8pa7YX7EZHsZ1pLvEmm7aQYfEZZkTr0tzsBv9BQxqzTrN/QUw3oZxaWvupJ8NaXuQQ4EzNNXkb0lWglHtsEjy7WvO97xkZbL0rWRfPgEOyieQ8d5qXz+LyKSpnev7pPvFFtZvqp9mvIoyTM5YbOkHifZBjCfSLY/0u6Qr5wbS/4lsM0tfJ2t9yNNi0zKnGCc9jJMa3baJlR3iANukPpbghn6sv425zapun1IijlP3d3XbtK+mrf9nQebtUf33+jX7FnmOS0pGc34eV8olUfpq0fXnoOmrisblzKPpM41m0Jb255S1Wv4Ut8N9tqlsE812SjbHcU7iYLrNtsg1qHFQsLZtjtJqSZsjeV9UC29XjtX2armymrjcDHUHY2ldu2pnfYXV7qgrS9n3MnNzLPtyrmmc9Fj7BvukCds+w7oPk2bGrf1U+KPsh6Z+nyRf89IyExcxm7YfOspdXT/Y9sWzmHFNX1BsCJv2S7HSx95iMlAfs1Apj5KOlvIwl4bL/eVc67zLPkHeWQ+zgEvlkZSbnr4UtW3ozl1n327qTvJb1NnJd+qluao7bahO6NqrHje1V/2P/n63p63U/0ZbqSS1rVSnVw+WHOhdr0ve2+91OTVo91f/XW2ljAa5d8JsQozuO9LNpI5Bc/TDFhiCLTEUW+ON2AZHYSBOwbaYgEG4ENthJrY3f8e1ptz7yD2REm+kqS2NOgTLd926Y2sMwQ7YC4OxLw7GfjgM++MYHIiTcBBOwzCcjTfiPAzHFByGORiBy3AEbsKReD+OxodwDD6H4/AoTsIyjMSTGIXv4BT8CKPxR5yGjcjcdGyKM7EDzsaeGIsROAfH4Fych3G4DOPxVpyH6zER78YkfAyTsQQX4KuYgh/hQjyHGXg9ZWnEJngTtsAc7Ia52AsXYz/Mw3G4FKfiMozBmzEBb8GFeCsuxQL+K8QVeDuuxE24Ch/BQjyAq7EUb8OXcS2exw34JW7ES3gHKnXr78SGeDd2wXuwN96LobgFx+D9OBkfwBTchgvxQczEHbge/4j34k7chg/jPnwE/4yP4mHcLfsl7Q7kvo/7Qdkvh/K3NyqDn9S580dfbI4tsQUGYQB2wTbYF9viEGyHo7E9JmMHTMNOmItdsAi74j4MxqewJ76GvfFN7IPfYF+8iAOk7cYgbIuDcSiG4SgcipMwHKNxGGbicFyMI3EzjsL7cTQ+imPweRyL7+J4/BAn4T8wGptSJtOwF07Hfjgbw3EOJuFcTMV4XInzcC0m4u2YjE/ifDyIC/AopuAJTMVTuBAvYBpexHRsIt/59EMjhmM2zsUcjMclmIp5mIX5uBQLcDWuxA24CndgIT6Ot2EJrsULprq9ct9qup+NITRV694ySF3eBngAW+nq8PbAZ7EvHsJh+ByOwRcwAUtxAb6IGXgSuxDZm9gD38L7Ua1bh+/ifvwbHsAP8Bh+iGfxIzyPZ7Emaf0Ya+E5NNWVlPtOuR+N0dWV/EzO++bvKH4j+biAA/BbHI7f4Vj8AafgjzgTf8ZEvIw5+Avei7/iQSTigvcUZH/2xlakoxa2xdqYgHUwGethOjbALGyIljpF0kbXTz0e7L8vmO/53t7vXm/mv6G+TLDne3v/UXVjrnW9mN9aJ+bfUR/mf+l7e3sbU8eEULs=
*/