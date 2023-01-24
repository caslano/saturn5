
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
gSjfMmiJZZdVmYtCGrPUYASD/n7bfnvKbhsOi/60XBuZzRfbL+9UIFuh7rlUVppi3GQ0mEI0bBiZNb6LG+t/HLC6b+Sqg+2ve3LyUHYQzu52L6GVPzQzOjo6DBfsFuNH3bjyM9uHJa+ZFKcvjSsIeCEyU0BYWaa1GQmZvmrUSKrQuUqEvyl9T2LQ863Pv4wcqnPZFPRH0SItcJE6I3EngrJBnjeWna/OebflJXNCsRLi70sVNSp6EmrEvHAa5Q+jjL5af9DO8e6V+6xWXrCIRJhY7SYHTJa0GtcwKPfRMsiXD7PSK/n9e+cmSRRk4wcJdLfS+GqnmeJolHaU/2Nd64MB57Miqc/MDoCg9Vx/PpiphQ2vZc4yL4cvmUkP3qZKXsVFxkfIuPZyAKn/fQP6WXFkDDctRyxUqzminC6POk+Tj40qoeBw/mxhHqkrLLDs/dVR3bWLtFuz4MfxKYaphzzF3SJ/leZdq2zVlMvzkUCr+2jeAMPyne97M9Yc1oIe2unzgd7Mb8ssB0u7YPkefRBJm9whM1I2/UnR1K8WFDCdFxvO67nNWzLjCWsgz8QffAkumAND5gPRvUT6aj+0yYC+7mzfXm+r7Wgg66oqp9AezqeyKE51UhulsChr0jInaoyd+b00W7VfyOmy8iWPL3h4+7xSD5cT1U+Sey3T5HjTXOyE+DsOP1dJpQc92/Bcir5k11l1e4HQ6lUE
*/