
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
bIQVUwuWXqd4kyRY/IU7YSnDek8/MP2Nj0L6xBzTP1mSZOkvfHiuYWqXoZcWmxCwVmwJFkpakjZ+IvluuwznAM9Kuc/Jmeg4+6YPuhZD7+GTriYEDtKSsHtNbohiJFlVT67qfMYnwhw6a0fjUseYj5qajpptDiPpAWdVubhblWzo37xQ5pefyfx6dKnFS+m7nisAuRQ7Z7Lpd+NAGJz1puJnbztUTogxA7q5ekkOzCY08kbtdkJucojjKXnCxlsMEjPGZsuiqlfrbBbarouyZk6JE3Cqdtvv8YMxr6T79oDeMxStJY22o+A3dsLgG5HEC9MpewH8I2DD/MqqRg05eN2eAY+3G8FSGZvh/0IieHEGxrfvjjzDZq8HNnu9L6tV8S+C26ah0R1fsasIomDYkYKzEy87P9EvUEsDBAoAAAAIAC1nSlLSAFkGFAEAALMBAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzA4VVQFAAG2SCRgTVFda8IwFH3Pr7hTfCwZyGBIKIzhpuBosd3es/Z2DbZJSa519dcvpmr3ktyPc849NxGEjgrpMGZC6cr464DDydjSxWyT52kWTnhf5+ztZbv73K+Z4BNE8JHF5mwOr41CTZFTJTJRhMQjKpR0tOjB
*/