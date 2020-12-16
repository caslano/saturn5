
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
mzlxxbgW78YSfArX4bu4Ht/DDfgxXoPf4bXYlHJdhy3xegzFG7AdbkKOg3q2fFfyHSrHcQZ/9pJ/h9vKcbST42iP7TAMO2IHjMGOUt8RmIGRUq9dcTF2xzuwB+5BIz6OvfFD7IPHsS/+gv1QKVsMBuAAbI1nYW8ciEk4CM/FOJyG8WjCRMzGIViAQ/ESHIZLMAlX4Ai8BkfiRjxH72tt8LbKf0s7pd7XWv/2ydW0T5YTDurtlPqmb3/b1ljj/6fnFzbI+P941bP/tslvjpcILaQvc72y9l8z9b1cusmUqiwE5so6ZN7+U5rb38uVkGaeLBwWYF1Lp2Ztv2C5T5JnYGWauFNS36vKWniae3ZlmTqiWe9X87yq98n9nIznlvRs7mF3yL39c3LcTxM2UMay5rbHbV4UzaV1D2f51nLcqnv6Mf7y/CrV/SuvU4sK0mdmaO/rZUy19j42J9NcKrmPVd8Ty/2pqr6k/mQNP20dbJP1ED+XOviYcJ1SB762daAs7uZiHbSwr4NrlDqQ9eEs5169jpzUgxyb5FZrPWiPOVh1TShrQ6VKXnLsmnXm+tnM25gqxz6JcD1lqmzh6NgLXF5LcAJpSPZyrDXHRRmsZfJ18IxGL1n37XzOSwiOwE3ES26pLtP0/Iz0Qus6aCkoWx3PbOPc+KvOjfN5AezTfo785JrVrs2p/fy2tK4ZWLM2Zzv19SrXe5hqn7xX2lm051mJGyn7lAf3qc9/dM1nxvostgrt2oTWZ8MVOfg+Kbf5fGy1ab/ZVnN+rM9vszmv8hw62+8WWdNOzuMMubamEW7k/cUB5vM4PTfv4lTyTlXW0DS49N3iaD1Q7Tlpqf0MWb8nX5a1OtXfpY7WoEuWdfiWS5mXEW6izIZA6/MC5fOglMD1tTXtvv9UxxEs5bF+biWeei3EfQ7WIbyZNMsCHa+FWN91GdXrQUY7WI/vFuJVOsnTujKfC/mq89nj43jdyarAv2fdyXgH6+dtJb4hyFl5WEmvHmVRXwespae5Dnc0tT/ft0eQkqYMMfVeC1K99qRvM/vznEK8eG1e1tPrSn7q9Dc0c7y2ZXJQ465t6dfcvhwm3p9nWw5OZ33KYDmfu2RtRPWajPOb25/PnhSkJEi7tmVRtuv59mhlv/7kcQfH2JcXZdp8lOU73apn8nK0fqfehq+34bvdhr+/v3n/KXP9TYsePVLxdd4YY9DvKxunDX+bQe7p8CVCJGkE4GaCQdrEW+ByDMKV2BZXY0e8CmOwBAfitTgaN2I2Xo+5uAmX4o1YilvwFizFB/BmrMBb8RG8HZ/FO/B5vBOPYYVB7sXwOSlvEO4gqNc1LJPy3iflLUejzfqGo/FBHIMVeAE+hPNxNy7DPXgFPoLX4GO4CffijfgE3odP4k58So5jP+7DZ/FpfF7Kf8gg91H4uZQ/FA9K+V+S8ldK+V+W8r+KnfA17Iavy3G8IfX+Jg7Bt3AYvo2j8F0cix/ghfgRpuLHmIef4jr8DK/Dz/F6/ALvxS/l+A7LcR3BR/EoHsBv8XX8Dj/E4/gx/iDHm2eQeyecKsfbHE2WZ6Q2kfHQGIjBGIoh2AXbYA8Mxd7YDofj6TgO2+MF2AEnYSc8hq09LPdHyn1Tdb7x/NkXLeuahmAnbI/h2Bk7YzRGYG/sggMwGuPRiMOxF56LvXE89sFJ2BfTsR/OxBjMwf5YjAPkOjoLN2McbsPBuAfj8UlMwPdwqNTnMPwBk6QPZjiG4AjsiyNxAJ6LU/A8XISj8TJMxstxLG7HcViGE/BxPB/340R8BS/E73Ey/oIpaPDgHGIbTMX2mIYxmI4DcTpORBNOwQy8BGdgMWZiKc7GWzALd2I2Pow=
*/