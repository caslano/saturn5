
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
+secv495eaK24ZTu6JCnDf1x7WuXN3nvjHOFUnXy/9Fr84B+/+6VMch+PMor0dsveN+Uz+Rmx4c/ZpcivhtTYBkZ/BlqNMRai9zXQi+o5KcPoC86iyxwpLcFjGN8IhuL0FHePkvJ1Zot7xf4TNiRuLmsGpXgJ6IIEwr54U2ehx6IIVw+0w8snMWGcFbGbz5r9aKK+kcGem/2CEqyE9MkGQBJE+q8NKSoB4JTZszOU+8EyqFCxsjYRtjDh3M2J02onoMQtW6+DnFaBhW+M7QC0EpyniFPed0Onq/VF/GbFqYGs9YwALpBDBIDVwpyUNdiOR4SFc+H9fEbLq66182dLIK92Q40WbOUk75PhcISUNyW40Mgz7jL6HWT4j5oGtdflUeSJv0eGdXwNM3yIxc/wX/AJKqt7pkOvBHRYxmwhU4gN8gsyyDB1w1coXf7noOIdP3RXpcVQc6o0URcW1i3rPDCW5ZEMnxVcT/O7WE9UGcDktqeXjKpq74WYz6kpDtCcf4pOglQbM5MFiHkKBh1HxY+gMj9SMiZEKQU3lyeH+eIkQnB6cns9QQeyg==
*/