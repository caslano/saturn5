
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
W2RNDy9dWGWA+LtbeABv3ve8FoQaQuu08M3b+k2PziQ2FvvpWlyH9w64BJQs0lVS+hGNn8xjh2bVsNZ85FLvEZWIHa93JV/xiiT/RKWf+8WgAz9DmfnH0aPw+jD1nXfPq/882dToN9v+uxcOuJSuwiuzTB4mGiUG3leemef3iu7YtJz+Ssjv6uQUb3bfTiSI2LJxUsjwl8cEqIGd0eUCfQOFJD0LPUNqUCJT1VKSpzIR9n/Gd4Kjd7vC7mGFGFN5wHXItbTfVA7iZzghsjlCCh10dw2Kxj47+Qmk/uOIaW83mLrRP+SF6FLGSsvzSM1eIXEa8Qo/3nO5xtuxfbnc8e7tv3VmVYrDHwN+zra8esFB4ndfPu5feUhByO5ZFAlf/QkLModIFYZ/7B//yJCVjj25jrCfUcLNCouhuIf3I4dtBeIPOEQI4a5Q1snoRzeSm6O8oSjSn485oouYfmP4Pvd9blgQiRnJgE8E2RshXMB7n88XsnYybtR+7+8pWz+3UnvJdwU2XUh2YBaTmFMMhBS1YP2QiCD/s2a73q/npndjAYx+6r+glv7KK+iNpNIdFOZv9vkHUN7QWyEUWNTw5+Cu8nKtGMHqQiQrzyWl441XfK1uXk5unBXPJfuH0kMNo3LK1FlfSlJ3cANgJaka4UyvNtwVebHj6KqkfLJ4B5+3P5GoQek+VLjz5swdhMOGpdVXPyhoUYg6JJ1V
*/