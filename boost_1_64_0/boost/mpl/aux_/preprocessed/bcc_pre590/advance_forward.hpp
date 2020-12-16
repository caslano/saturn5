
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_forward.hpp" header
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
i8L9r4g8Mk/hxzGb5PlcMoZ4ZeSR/uFPIiZz2n4aMXSkEPerYp6H97468tCgF4V/TcT8vfuvJb50bMgUW4nrNOnX+bp7Jl3v6XJu0w1GL6a7cHuVvbR/pnQ36RjsRs3cSgbOl5tCJqsZeO9uj09mNn6/8PRG09ahm7VeRNuwOtar3KKY7KiGsTUwGsNqjRcbKZN+q9ZNbjfqGFuz+nieVdu1VRWk9dehnq2t2PfBb8DopwG025zWzuyc9Nt9DdHJyX8HmF4jeyc0mo1DkaShu9zyuxJ8fB1ZKC2/BaefDfyko3vdDR0LI0m7x2lN2vyY9tGGRtltRJu2+6AXWt9Uk7z3a80kzHof0HrO3getZnx0M5TV77ROM21Zfwg6J5HqOIX9sNMlzr+3mrleh/2I0jl+/Bx91Oi8Dcy8/vLQwGipPMIzfovtjRp9bm7+Y2lfYeO9q2OO2Y1k4b2rY4+338HjMS+KjuNS72vYuPwp7StsFM4Tvbmd+Ea+J9fvM7nFc0L+vH5frd3oNGrVKQrzqd5eTJbDOtHY594XT8fMrQV8xjJ6T/n7iTwbMn0eccDcecShrs8j9lh5rH9sWdk7jzjB3XnEKabPIxY+upijKnth+0zOI/Z19w59zulLh81T/XCvAiMtG2wWelB5wZ8XcKm8WDsacESY7r9hyHSlRfgbJTwUOMLYOOa6wpJnk9ijKyvV1U1jT1xRcc/NYq9UVOT55qEH9WaLQNdlu6VjBgwNz1+qvjlsFTH5XrN1xOSsrBdotqxUHvMKmfN4m5SnsCCMbUMuhezisF3kkXU320dMFzTH4YUpT2HBM26HNJeChu9FvX14MvGzacfYFxc40v/itBcFzuW6U+SR8tk5YvI9bZeQcTeQ7rurZvR9iMpuVVatu3npu0UeyfeXhIxf6NPZNP10oOtfGnlWdTozzHYPGVUZZi+LWNOEyWX58iSjsqZr94i5nJ8cMp5D1s6OZ76n4uWReeYseP/cy71i7t4Pr4yZez+8ymOD/WP98tvv1RGTPv5rIibfgF/rMf+98rqQ4fnw+lCfrnZq2P/nDQHT75y9Q5ZnVJXturU3prm3h/s+nsf89C5JHsyKmORBX8Tkd87smOF3DvN9FV++dFFp0D33mM9J8oa7fr8kl/q0v+Pl0uhy8+tl8dIB/S6em+J4Fx+QYDrP32Q5bdhl3tSjJa8uHhhzVxcPilkRND3DDlZseMHiUty5xB7UPXz6/XhIwiOPb07noQmPfk/3Jzg/SmQt4Ly0Rx7zCGugh6+w2bAG0x79uCdfqadPHvd7G9/8tC9+3OP+C9J+eeSjDBemfKg7QwlGBYx8OMzxaq2WzdBa5ZlWM89ymfO+SDzmlyOd49PttCYmdB1cbD10+maNqgltMAy+JMWbrWYtYz6c4LSzX5fnEC8NuF6DNuIzfGBgdrhlFBlTUVSbHPUY7lbJ3Vquss87LbXOZcwy/ubISUG4ywJmBpQadTMj2l673HJev4ZLcf60sPYUP1opzBVaxwaKFFVct9LxRp1+x+NeRypdVrcwO0qzRp53s3ZxKd3vaMdazcy89Vw7w/2OcdxMB8+zShdrII91urmom+WdoiT5QuKVkEtNobr2liRHHiGMauRp5FQhsjqFMR5ypAFthjy12CPpxH3qoYf6APSqovzLQk6R4GsnIoZaiXKZVDyfQcyQt6s8JmtnG7GOSsvXHedxSgldtzrWKcNzxGUq5m7/8ukEm2mbude1rF6pcpk1Yw/lhIlZ27aJlnjwgLFflvg+MxGnpza3aIRxfORB8hFGO+Jxm86dJ8+adVM21AVl1olY0/VPuzHLTsBzeo1l2Fh0rbu/v//iCeIzH9g=
*/