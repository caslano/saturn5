
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
6Kr4S+K4h1lq+z6ykBBLlU1ZNfu2QE1LvHWef5CbFf00iAyEpp+DBpatFQB8u5oJOE/4l5eHIdOqiqEKASBv3EKHQmQwtB0WrIuUGYNKykQaO2M5jTjIRKYhILaWhQZpbC8uLeeRS1LRaI88URHGNAxrVpQ+EnpYUuhEG4YHIFt0pWVnN6lhAIDv/2w0IWtgZaZVHKmLQlIXgUPI/c65hXix1J3H/gpQQfdjKFirQ3teV9o4VZgW4IiHmmfdGDrvSFK3y1CGY5jraLXlNiqd1FhfdWmS56Tb/iwSwWM0kf4bucpIVCE+zr77kuzDg5YpBaPpxvZeswGStuvGdLde9+kokwJb0obmrwfaCFWnJbudiD/BF/JjiffLtlrTCxXJ7g5XmeCoyPqQ9fNZDdKYlQPD3Ryrc0IZZxSOY/IpmUDaFShiCPlsYJBBU/WnBfooDdsDhig86DM0YzDw0g6D69yucuhE1UPFyWX0m8Dga3sfvHx0JJcYIo0ISAHlHpJam+rMBwPFHAlcz432P5PcGLvpgLwtEF7xjPVR9RoULg3JiUC9dDElrqihDA==
*/