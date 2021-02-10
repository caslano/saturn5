
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
hDUhtOT+bEJhxBJjX7w1BLBWoQFqC0ej0gqJBNIQJ6IiRaHg8TQUxPxSmCrGzzkfXkxvy8tZPuwCz6Y3JV8LE0gTGF9R+hd3et0iJOT36FS9ga4uEHWgoe046BiERnj4g2hgzzc27LFi1ftSgNbZYKXVE0bfOXhJ8yzmgF1YH3L4C9CA3REJ45M5ZacWeHCaD+/Pbm4vp9cDdiIltrS8z/cHbBAjv6fbPhZGwXfFFvyFAb77DTwBUEsDBAoAAAAIAC1nSlLVMP/LbAIAAEkFAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjgwVVQFAAG2SCRgnVRfT9swEH+3lO9wKpr2spAmpUCrLBqincYENGsKHY8mudIIx64cp6XffhenBIaAoVlW657u9+fcO4cGS5PyEiMW5nKh6OsetxulszJi32cxi0+Sa3Z+lsyY6y7MyuXCoJbc5Gt0jXKrEjULvSdM6DU0e2wPEtRr1G6ZZ8hCjSuxpTjMlyghU7m8g5r3C2wQ7tCAWSJkuOCVMCDy0oCqzKoysOQ6c1OVYQa5tFm1ZyIie1BaCRZm3PB0iek9FJT5tWPwwXQiZpThAoIuy/TmQbv1BoBjGBxDs9pDvfp+AJPUQBCA3xt2D2H/f3EvgME7
*/