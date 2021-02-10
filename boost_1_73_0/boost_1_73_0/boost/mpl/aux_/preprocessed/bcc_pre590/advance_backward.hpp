
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_backward.hpp" header
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
uMiMX7DK0pw8s0Vlj6y6+JrbQ9Op/ULpEH6ooGV9IurOeEVUQuClzNyD67Or+WR62bLGnGNBx4fu4U9N9b1JWFFku9lw752qqhwSd+MQJOZcxBgbV/wVNTMwQqZfa8zHiTFamw4N7Vp2Gpg/mqEjKGU6tE3uOqRp99DudX3sLvmA9boebw/iTr/nDU6wH/cDD3uBZz9fIt9/lkZPLEM2eWizscxj7939H+o3UEsDBAoAAAAIAC1nSlLO536KfAEAAFMCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjQ3VVQFAAG2SCRgXZJtT8IwEMffN+E7XGZ4iR34TMrU+BB5YUQY+rpuN2nY2mU9UPz0XgdC4tKkd+2/v/vfZYrQU6Y9JkIZWzjelrj5ck3uE/GYToSSh1zJrUSoButywwdVTlUiBv0TGMTxSXwaX/XjwfnZFUu3V0rupOII7kqDlnre5ChU1iYs8NissUlEQTWr/zJQVlfYWoBVXTqdA5kKIXM2N2ScBVzrcqXZPqTT+QOMEvBLU+/E/F5uAaowJUKIR1HpPmXod3B6cUzfFCUi16QF8Eeu3QA8oqCFJgjNc99LzxfeQe64kqFr9hiIwWHmqkrbvLU+lLL79DJLx5Nhl19OXqap
*/