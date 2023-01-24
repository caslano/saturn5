
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
U59oUy7BdXs0UELRRVFOSxdCmKun3sVqsKoCLq21vB5JVef04TxDIGx86ItYTWvtBei3+d96rVp8yqmNe0Pl0741erJMEi2H7PnTgaVlSIgpshfR1hbIs3UVKROBRwG/C5qf1a87FXtYfGNdqX0t2cnUxOFYCdxOHQQbm5z+SrwOxq7jvN1oawwJd7Nur15nir5bsRRvPzJ4Vw5Dv3GJedZhye+Ok7JLvEGCS0NTcUB8YDvbIkkSJ1+U7Rs9aM4oUd8SqBvb5er1bobzuNh3JQjZLqvTfEPUlyLg73g5jOMEr7ebzAncL9dkXLhfyw2SBh0dmwfvJPYhvnlpPj6ObV3CBs3N9E0MTYY4NKV+ggMCL+a9DphAR7u31+wanY4XKU9jsmxMUn5PY2kTEsjdrbrvjXs7j9Z7CgtV5b9WhDSQN+oDrsNXIrF/+fyc6DXrRnh54E7AWMzSTDJ/yYrp9GqO9og+WaXk0rDC9qi5vTcnJBh4LIqMPRUD65mOHaXPBnv8Zv8w93DkLS/NVeAxIJbYN2lKeFAVARM02FXO7llWCpoT0JtfXaWI0g22ems+PfqqJBTGj2X4xn9EzyWj+9J/lIHX7A8RF5ieaVWgJgOrahg0q3TkastjV7qLOVg8tBiayu39I+3UTVNXq++BCv8j9SNlBCl1cNrltdiyQMiXM9iXqgZeo/icq5QqkGkZ+UomLtOs3qrD7l3j
*/