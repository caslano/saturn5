
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
ZOBqb1UlwR1K0U+LwessaNmEKC0EjwOZdm2Lsle1nA2YrAPxc1YBx4/zH8enSJp2vRa1S5xin9+wPc2QNmlpiGzmuhDUxcik0MevhkNLeiLVKzdWTtlFHR+RXm49Y+EBiS0arNRDkFTElGwqmU9nTbqtHz6TBbi5r5echP4ghjjUSI7ubKUTgnDkDFLQhhZnrGQNVe1Iv3oa6W8s/1F9xSfkmvnj/fUon7lPCtVE+r1ORudPeP8iOMMNlEd0K7ySPoDYUIK1i+Te/n1o1QrQuGpUUb9k8Q2kagy3l7TKpB6xyqTRv99/LYYhYewb3AMC951dtZdGHB7ucpT4IfvuhapkzdMSOC92yrhD8ui/0bG2NuzkGC2gkjGETU2V7n9n7mIhj1U8GHkY9HNpVmevhGJP7zFd7cXvKd8VsbmlliRlRRsDVlKMtpyZEchj8RaV66shycNpBYMpWJBYmY1KwiUcIjx38JdCpzy8xKpuD9Dii1nLHHk7K10cvhUDu35oxQPU2ElyPXMmleKDAsXMwIjwL+MxDB8n049S9K2WIee31glmsoASjyjd7g==
*/