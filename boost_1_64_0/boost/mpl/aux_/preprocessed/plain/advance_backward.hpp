
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
A7nzCso+yoAO1Is5RaPIpYdSynPqfZQSSkFHW0P9TmU5djbFs3NZrp1IWcVrbpc5twwZMmTIkCFDxr86rvv1/5FJ1Tr+3znN+H+LRJ7hzs/cOtgMPzHN/79B7f+fpBv/j38uwvr8f3cEXXn+P5E/i74Bor+/brz5C5rx5cU1e3JVNT8u1V3jP6cZV17bThAv2gluodSh9KWUuHOdTW0nGMemGjc2o+z92V3x/dVucCcXCsPK2yREXSbGNqOOtU3NLOtDsNiG1+C1I/i7gSLHayjW29yWkHrPSKosrtl62ljLn6svH7aWty8zL/9u7UZbhoWFbetQMyB6vHsXV2t5b9Xz6qrm/wOzTPWfPde+7pEuUcu2N5+4r/TRWkfN+TZ5ojhGxbFrzx/q8udssbN8xBh4LdAVW2IrbIUPYmtcgAF4CgPxIgZhPZ6rDbpjW5yKRpyLwfgThqDpsxIq8vg7DeJ4wltE+4gDDhDrU1+sjxM2QWdshi7og82wNbpiJ3TDRHTHvuiB5M5VzlcDO1w5Z91yjXlrOiXtJQdD7ksyd5UhQ4YMGTJkyJDx/46/I/8Prcb5/37W5P/bRf7vIfJ/V9xLUlO8Tpv/h1rM/+dS7fl/sMj/yx+HWN7vnxFa6Xx0pbr2gRNq+4B+njnLewJ09xik/cPvw59tzoN/ezXfM8ghuuBSTEThC/mzhpblwXkGsa/EPszDepTpFO08cQ3RFRthK2yMD2IT/BKd8RS64EVsKubxb4au6Iah2Bw7oTkvRQ98HT3RdOx4ofEK98Gvq6QP8kqZU8qQIUOGDBkyZMiQIeNfEtc9/6dU5/X/C6JPvzb/TxT5fwJ+Rs7dp72S/yePNK9KqDn3r38Nuf9ENkjy8EzWR4z1p8vz6+vyfCddnn9Bufdff51f3Jsv+i28jVPN62mZz2dmGizumS5kgS24qYO6bIluWYoyJ4ILebgpkmuzTYT7WT9jnOWYiEkjkizaReIMIq4wL2JmouW8iAMS1XkR6/ZU5kVU5hg816PiXIlfUKefK7GQOv1cifnU6edKnEedfq7EidTp50ocQp1+rsQb4yvOi/hT54rzIh5U65R1fo86/byIa9U6ZZ2fUOuUdc5R65R1TlPrxDqrY0zq251EG5Cp8upjTYpj1EV3jLqpx6j1sSav0j5VqIwLOVaMSaEZW1IztsTkcRPEtlTnL+TfGKFCu1ZDzVgYmVQYxb87oakL1nw+tPMnFqmvZyx/vRL19YIN4vO2gw3txGfiGMWvayXjRQTrxpoQ7WnaPjiJtQzmcPBmWbTDA2zPgt7KZ0p8lILNnyU37fdrlb9nRPuiuj+uaUwRq2OI6McMEdvFje3hVqvse6jY/D5EO6T+e0gsmyCW3ZiuLntMs6x+m/nfUPam7/VkWcxC0zaLu0e/zULK+mX9w7eZ9r3F2ld+3ilernlv/7DzTiD7o7Z92T6s99wVzjti2SiW3UJ9jxVXPO8obfH1GWPCrOm8I9zG+hU+r2yTsfpzjvEazjkFay3POXk8Lj/n9CioeM4xqnXqvLYFFc85pWsqnnO+oU5/zvmQOv05Zy11+nPO49Tpzzlz8iuec8ardco6D1brlHWOp05/zmmr1inr7KzWKet8eWXFc873K//cXLzW5jYapk5uZH1uI93ncY/uHHJCdw45Vsk55Jz2HCLqTlVyziixOGdUPuducSXnjAu6c4a2L2PlfQer79pI5X0lq9430do1n81Zpvo2GatcC87Om5a1NTP16Qbvjq/6taAz5udZMq8wz+5X70bHagzImBcz9tnyazji9zYmir6M2ms4q8U1nAJ0x7XYFl/FEnxNXKtZhw1xPfri6xiBGzABN+I=
*/