
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
1c83aAITJZ2xks5EKc9JsC+cAkfAqXAsnAbnwekwC86Aq+FMKGtKybsnvkj7oV1T6gux8yVsC7+GPeA3cAZEsThdASyAQXArbAR3wavgbtgEPgabwtOwGayCIfDvsAVsrLRz8BrYEraEsTASdoaxsAvsDnvCYbAXlPH28n6IruRLO96+TUPNOH85rnUNx5VqjjvocVyuNka0atf3cVV+Hmc57Z/dWD+Pi/fjuDgkRT3OeB1dK9fDENgKXqeZt1UserNM5m09L3ovwCbwRdgMHocR8CXYEb4Mh8MfwwR4Qm2n5dkZdjVpp/8o6f8VhsALsDP8WKMf6kP/t6JfJfrvi/4HmnlENtEfajKPqFr0/ynl8gnsAS/CAfAzOAT+C06T+R7xXzEmGin6KqjGuR+ueMSXoRKTOA5qvo/6PQckpTzweSA+5oD4Pf/DXv7dzAH5rud/+BtfONDYwnWNKewxD6TGWMIe80H8ngvib/xgf2MHu+eCmH4/rnOs4P90nODv61wQz3kg5dAkHrBfsYC1c0FKaNvKkLPIRSTy6yDLCCQFWYccRE4h1UgoCz72QKYhNmQHchQ5i1xGYmmxxyMLkCJkB1KG1P/+e3/f0vf/gowrNP6fbxfqN8HYBsZvkN1i2P9j9ZuU8+suIXTwNzsv1/9vkAulz0r7DbLExF537MV52svNs4/JtGfk+9GP58MeG+b24k3sjc3IzMvPqJs9m4m9HthL8LRnX1SQXJC9ONW6uFb2hoi9YPlm3l3sdUV6YS/F015hdnpBLcrS9Y01vx15yyYRtQ9S9hWwz6MM7CbjBnrjU4neJ2fPfMKcsVMnzAvYL+133vNir73Yi0J2RvDO42GP4s5NtRfmZyTbV9hqeZ5d5Z4oTXYrsans7EMeKz1sMndGuWhqZctVnidNxgl8TtlX623lXKlrZnAjc3uWCr29K3XNHG1kHDPTj7IMFXvS+A2oTf48v43/3THOwyO/V5nbj/ewX5v8+mO/3MR+HPZtevvJ2QUFhRn5gY2zme9xHcey7UjAoz4Pvdrow6poriEPH2yFi5ZmrAg8/y77N7JtIwXPuJeVYn8c0lz6sQbGsF9vH8nPTrXOKMxZlJHv3/wzcz/6s+1Myz2OQNmXnav3K6mx2blBTnj4VegId+k4Of58ewr0/LwtfhRI+eQhg5R23sMPaW9qXS5hiKQh37kkrq58V18p9pcjm5RYexr7hbbk/IxMf8b0aW2bxx0d4hHjL0PspiLXku+SnzjsFqnXpj2bQvM/LuETramHXIj669KsLsgcmO/w21r9N7Hv9pvY4Whlf96M4UPe3HPbmeX3X/zmqV+daPPdxjKLs8gzOmwm69Fr+zi3SV9eCWwC74FOPcSH3jLRWy56RRq9eHM9/TcG0SvQfgPyobdf9B4QvQc1fZUpotdd9LR9lTtFb5fo3QfD4W7YDu6BXeFejR8lPvy4U9LbIult1eiVil57E731orcBRsGNGr1K0WtlomcVvRzY0qPvutqHn8Wid4f4uUajZ6nwrrdS9FaJ3m2abzyhotdJ9Ey/eYleImwO58BYOFdNB/GRzlRJZ5qkM13SmSHpzNSkY/ORTn9JJ07SGSDpDJR0BmnSKTVLx49vmrFwoeabQKWkM07S0X4T6Cx63WAr2B22gT0knZ6wB+wFh8PecDTso/Ez7oR3P4eIn9eJn0PF3jBJf7ikU4SkSDoFkk4ItEo6rUQvXPxsLX5GwPawDewNI+Fg2BZeD6PgOBgN58H2cCHsAPNgrOZ6rRb7K02u1xRN7Lg4mC52FsNbYBZcDrPVb4Zyj4cZkp72m+FISW80bA3jJR9jYB84Fg6E42A8HA8nwYkwFU4=
*/