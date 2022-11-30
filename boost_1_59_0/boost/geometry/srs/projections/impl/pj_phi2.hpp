// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_PROJECTIONS_PHI2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PHI2_HPP

#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry { namespace projections {
namespace detail {

template <typename T>
inline T pj_phi2(T const& ts, T const& e)
{
    static const T TOL = 1.0e-10;
    static const int N_ITER = 15;

    T eccnth, Phi, con, dphi;
    int i;

    eccnth = .5 * e;
    Phi = geometry::math::half_pi<T>() - 2. * atan (ts);
    i = N_ITER;
    do {
        con = e * sin (Phi);
        dphi = geometry::math::half_pi<T>() - 2. * atan (ts * math::pow((T(1) - con) /
           (T(1) + con), eccnth)) - Phi;
        Phi += dphi;
    } while ( geometry::math::abs(dphi) > TOL && --i);
    if (i <= 0)
        BOOST_THROW_EXCEPTION( projection_exception(error_non_con_inv_phi2) );
    return Phi;
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif

/* pj_phi2.hpp
DX2lLihNHZnJqHujSpiwmJ4cndTRJVf6u/EjrDFiC8Y+dP9ijP8ia4rtcUWZ6I0Kcd5AVqaA9lLOO7w2S7i9Nkta3maS5Xo3OTQoc2HPwA9gZzroJG5n5FZjy6YZP04entIJQGCXOIayJY28xlyc7GO4Lh16WIiNauJl4Dc8aOyZpAAk2R7uIUf2RmhbuLJ+uTLXGPeOuMJYUMwRrYTR7CXBuU0RApNG1vX2I4RCYBTaEA+BBsWjO1GubnNbJMQVe2+2ffdL8GoxjBAVe2E5Hd0F7krm1T5VCdRNy9yS5xhIEHhQkXYA0A911YB1eaGxu8gk/4szJrZST+G9++hhU8lXr9OSIB7DZICwYYB4NJycVgUPew2iZKlC2BLi+dexE0am49bgnTao5ZhJ0YRqCCVoibzkhVjqAEEPGwrnPM3z8ALp/CYwoIMXMlwwK5Tu4isJ0SgSCdpxcygAShXoFSZiTKlK39mQK6lS7IylWU/CuOtwypOkJ70FA3riUVdjJ+JFG9RhaHbDpbYfsaAGWdRPsvawcY3GmfItffry45iEKWPdgDlJTxsOKwMvWqmgTkhIgR4Scp8ATPtzu2gTQW7WHy6zYZVFoTMi8WUT3oHobOLMXDhRUY+X7HgcS8IH/FHIZAtvN+SqhQcji8OTFJRWjS4mfuHC8uTRUtqvyqy0sbcW0Zw8v9Zxx/JVdKfIfMptU6J5f8RGYozP/uUPb+O2mTV+89fz/ePwzOIT1s7P2vKdg7cImCIab12xiBDiJ3aMge4QDc7QWUrVS+lwIiW2rVbjcIywMlfalClXDkMoMYQwBdDjFUJIatemCLIuyHoK6tsWR/WW/aCgmZEUCHKJUTwD1ZISBcxR/8CCDg/dLbJE7tZaj9lW3NSEnUWtt+geI3Rd5RT+B6cv857oJRzPqYbYtOLxhnIiDcxzXIe1PNGGwtA66C9oxeN1iBS+XBnLNlBhdOtSbnLqy7BAASW2JQRrUcO7TlGrwpACaIqyaQNCPdZWBGsMiW4xTsGjjBggrNmzY7h69SZwnXoKN9uY0cSflpRiZWCtbtwX0JWR8BirPKmKJSJsGnWrRAhC7pDLW36U73C1p37UqfdvQQ95t39M6RKFkrxRUHtDw+iRcvpNOJFIDUxMbyFmFq2Nj6ZtSujH7bHnn2wjGYlluQeolsXV0sGwOjYYQYX8LbAVT89W8t3KfBP1Y9RWxcrKGbjYZs0uHxrvIFr3qrUL9eV6IEiMwwxFOXiv68H/2BQgp87MXwBSnHJt686vQm2FW0pYgOFGwjhHOicA8v40oYhsY18OQxPO2I47CouB76e6C6PehOpkS8nHu2TPO0tlBIQM2PKNRp8Y0SADUuL5IEjGcXDRkSmDKkLwZ5yEHTXR5ESDdi9no4dCPMGEHCVHy9T/4W0HtwDEcRsgqus8y8FFYBCAlci+EwQEzr/LWq0ziBv7AhO1gUnM7G+H7PPHAcDgfoIA+radx+TbnuMnTdARePLZL0dXnBIzmYkhpCplU+cuKbWc0CluNs/PAYSBTD965xTxMo0BHaD4URn8E6ndQBmYIfaY4ibCBV+/BNSyrzWvElAPjzGQoDJj7N/fG2kx0nLsw5WwroaHNUm1uen5XN0JGqHY/TEmVbuXuTCST9TQXdhbSgsaCfyYP/JELjpuvK9BZTq36pdKS+xt5gG7RiR8El12MmPHbxd4OdSQAAtrHiIV2WgvhVS3HbC4qmhfq3o8pG/vwqtqCSi7qhzY/w6OF+n7hk/2EHmBJsPLQj+AlQtUkQ3HGBEKp76uOORvzFhuumlfJc6H7Upldp+uD6QqP7Hg/TkJ4ka7j7pKiQPzulceuFz9uRwyvG6LsmcmPvbNhdI6JJAHP1HWLGoHFjc3Y8p5CY8PoKx3epiE8x8ANoDJfx/79Qd4Foq4sjivr9R2Q+aTtR3ycCJ21q8m1w6uyBhkO0f6zIjrXRF7Ah9KZ0O5T8YZFBRP4rETX4H3aOuRmWo8KqWUG3uSxP5lePcI2owktexFF5r3EvvRMHjwE4DOfPqYRdBKyfcLGu5RNnJaOQO7AYnlS2G8vCXiKk4fpPMgfG8q57/psFHrYRExSrCyoRn9CXtc4IAaHI7HDaLS/Az8L4+fONj6nDjAFsOdwZOkSytxah8on5syMDnjaItNihoaBs7nkE1dRZRFRuOHsVMMdRVu/E24+x1tyZFtjdskm1KdHa2CPKzRkIco7RiftqIdawnzXS2dzGV17J/bsT+BPufdu3knda+P9y97DYJV8W0glNP0Bg7f8U/w4bsf3bzbHI13WqLH9SWM3XzNSeR38fTZUynKuaGF7Iaer7l9DuAT//JZ1MqU2EYa1hZuTLGkkybzNB/gIEWAK3Yeitp/wgPmwRCErvNUQH7P0yXWKaq3ExrBE22swsk2OQXi0BwYHmhu6p5RVetH+8kuGPTDNS9DPK07Dhnu5shGIdrLFnm+Z0GnHMCzWZRmd8DOIIYm95vnqvcgTHXAhDSWIR+kCXTU2+GUs6FcdPBI/3SYGs1WUsOFNkQYEwgmLBuAC0hvf+gUoQo52OT9JA5MiYoDz6lOkg6YNbBQDQrYjY8PwOV/9mu8r4UdQwJSqRMFdoku6UX9k6hlh9tPQF+e/xsu60FW+SLsB5H6oSC8cTdXpkeB8V/eP0Q+39GIDZTgfgjquOVyIKBEftOO0qAsaRAtRMx7Fs0ZfSj9nXIg/fmeSXfiCJZGQfRsLhGzJ4o1kOlqhYn63XcWM4k0Eo+Wh3nmOiV7cCF3N/AkmlKB/xnbaUz42JUHDX4Bebz7sMGm/aYvY0WW+bmUMWQFImJedN3NwlN72q/NU/ue6vwT0lf6yHj84wnxceLP0fget5ZT+/3XcSHIwb0JQhBLghBE2YhXsS1cugJbxBZTInLHAuId74ai/7vLIqxc+yJWGdZS8iHWk4KUuE0W1bUY1rOUddhUwKdg5kBKv2zOH2M9voXSY+xJ/JCIyjoE19oYkxdBBXxT8NLrw1t3LzwqCmaTyBcm7R1Q628SSF6g6mCYcTRQzX0ksHqU7E/2yLOJ5eSFeLRvIRJ2HTzkkrP7jAh7VK61yzwsTDq5Kk44uSITYAHanN87gpvzO2WhfJpfD/fLNIG1dWzwvqOu6hC4GPZcWjb1krC3yReaFvY206wfFJv1p0UDNG5znpwJf5svXcb3+x9i/FNJbxWezIyTYyczcVlblKDIgjIHiJYAiqKnLGGlOW2enC+rQpN9R709UTKjO5ot7gRTkKjNgq9O8+v30a+hFH0kxNvMeEuUJA9Z5/Z1IUDsebgyz99P9Pf16do0pRrVTLBVHZt6gBd3JvLiyaZFS7/92jQtitLfYNWqRbWB8FxbyOlXp7I8mUyL7gOKBI9w6mHkNeQ5HnmQ1oSpLYds4TnpXUELbkrXth0yVG838gpt4eJTZeHiXnh6ypRmbp4vKNBtgW5D7qF6rKZ67CVJ1d9he+5F0h/RseMXo2qEP6liFFpoeIEFqe9xbCrMy+9xrLnHMJJ8ciQwq0O4aABFIDmVrSEru+0IVJPLHfgBFPnVSmroqdjOxvrXSbiGInKtcLKy7nW6WPQCYZ3wAoov5HMVEkTgOiWUh5xA9jL/BL5dbuOCC2WdyUv3LRsKA6+MjrnnDluEowW+AmlCIGQJ2QdeJpLlQK1xUaOcGrkFEGgFc9wfXrNyM6xJv5ggtD5vlWxq2YRW5Q+0GLUmy7EgZ3d7IL8FMh8Paf3xtcqzxpz3a2jeL/cUT5PuNufDRlz+AqFJCVNi78AdFJVNpMMwXpmuT9QcSCzZeTZ460w/52iLGI1AqZg+BEGBClIpCrme6dgGoTTk6vacNqfY2sqhYg02r7/kLImZQE5HLemFBhj3tQV4nstQjy+waQIp8n1c7CMacjoq8hl7uCmpcf63p8JXP371U3YQT8fAZPWrlzmwGuSvvj1BucixA7bx+RrpExK3JLLnMhhpE5JbH+S0qvD409sFRc409/C3/4ZUBHM+THtl8KkiDng5SdrkfwZfNiMu4BHt5OoHI/CGPnn1wULtZamkcAeZal3slVbYj3uATBcb90lp+f9aZtW+Q0+FR6XzJsldWkH3B6dSjgK/2ZXS7AuwpyrICBneN7NdpZ8L0dqSbm56JTxLsKKGYdh2OQDexQFDBlbNO+kwKimyci77d+Glc6rQV1tQAzFyIdnREiEzpfkHMl6JqbSJXyGz4VvRgmeQpBm5Z0vs8vNLW1ArslB/I959wVyzuhfwfIjcHhFsNlsFewLPDI/tjZ+lupoMPFj8UBUFN96Pl1I99XYc/7pF4GqVaj1jGSIz6LWXLT3EjABKkO/ZDEXpUuUOMmZrD9sKfUamC9eFroqK/GOOla+QAawO94foQ6i+M3/rsgD5kxgvj6j2FFulye52T0knOgUp6dTdSn2nIF+kHJ8nZ9DXoUX6MHQ7cRaGuPMJxzXaTve+SX9vbHf8V6u64CDE5W+9+y9Yboa3uuy8H1Qv89R3OhoXQaN66g86GucZSGhhmd+deDjafEug2ydh4cUPToVtS9g7Kmlocrgn4nDFrTjk9M8G8PbuEqQc1gAEIb6qq1CGVjOS3Nng/S37CLppvIYksXEZqKLi6T2gVFcQv7qCTs5WPEW/dGC24unklSkmLO2gcw+SV0kkM/2KSwo39aREZaVAc5KsVEogXIhhSJGuNiFGcATj8S9NTvUssN9/tpkoG+NseBqCn4bCp/o4nn6CEWwDzq8F5MtNZlTmBhD2JjHxqOQNQ2o3swhttJoq67Cigj7D3E6it/Io7csJaT+rbjTwWMawwBJAu5O7vVqZim5gVLqKa65rudX8uqe9L/1cT74Jjzg2fGZk5uCxrrfXsaGtuLgCbamNVFiKPBq5CLtjbeu1yhcnlVabLoZs84B53TeTbqCELJB7GnrFFHGO1ruq1XQYDvl+1nMqHvbQNX35YqOkNyTM1c9Hcwpmcj/bCYAERc0qfcSBHY9D+OpF8m4StiVewykDos9O5pvRTXxxANZjx8pz+KXvLrr0vbKF/z2Jf1J5sXQWWkkqx+WypDeuHhJBR1jQ+n4V7f9SNGsfRcdfixwr8cKDsf4pOqrAT+EncdyxDwEgMpgnhHQIK12Q39KQUawSmN7iWYOJYIyvwQQp29Q1FP9CPGP9GeS7PGtwvDkakWv1o/EzXoIizABvVCIMoZ/EMTpWkunrVYjVzCzyKyRIuGFABJWHJyi/UPb67Wb28+JZmAnYpyN5KmnUAPX8aiTy0hgtyGMJ980aYZrhIcSys23VU+buT59n4oVmqzQJ/1KkXPwTpTHQ9zCknml2twNJCaOSC6Hohrs+ts/JuD5UWbeFs0IYFPr1fDk520ReXIwdXJDz2chPOE+EwT+AvBXxCf3xxQFhL/7sddgBdim0F2vTaSt7hVjktLdx44fh02Xsod29SxtDe/9HtPc7Vu4gqCASACYQvaOafRTkLxykIA6yqYCoiQSYB2M3J2Dt3ZOHWl/luN0AE//lu4fwlKLprUMGHi11vAnB+k70FrWTOb7CCxLX/qIWjxW6B9OWP0RL9wf1FPMcGm+Hdody6E5opOmQQaQFHlikMEDTZSzv1nYEGNtwCO9JsAWQF3tdibuXIZLQjtLBgHQe0RLmNfy/W6OuA3mEjz23AZV6nAgr5XAJQ9SL4DPWRC+C921A6VRCDsZ6QlnHpeoXoV5ZQ64gjVMaJghyjlYqNrbD4vkfXwAtO3sO0Iuy/WiLVUpVCydUtrqTjmiiJ2v8FAqZzSGhlHlts3JJl1V3IrdlC1l1K6xw6vxcOxuCLoyFHzsmi50YTdmGevnGLbIpMPm5DacGrM3n8LW5WpuTa6/2iBJn2oQo0wagB/s5AqaClgJLjLV783NgiTe+Q1YUIMfcgLE0pooWo3CNK+ATGo31sz+3wUIxBmXIIQH9yCZJtc/BWVGAy3Eoxbiiz1d5NNQWIwtFZbwQAJpdf5LLgouTHY8lKZ7GW1VhQoCP+2LuwwIWXryTE96IqmHBziLqcs+GqOaY6V2y8Q0YfPYbq/BjWGDG20ip+cmHM/p0TsdhOpFM2V2zHiDFYkJzC0D6geeihtnB2gA0NJGACXQUgOp3mDln8ySb1vfJeTDmPJl/HAH4iEaM4xyGOHP0Pwd34X0aUpVk9yXi4HE+1vo6RvLjTQvQys2Oxi+w3vQ5OBWvWL1uRBXhcBo4Gv+KWUyvI43RXb7QCHLihDcEdg0n1STO31rkW2At3TW8YT6wubvwZLwg0enj+59/bWh7KxCD5t1V4PP30Se+wU9DlKsJAl+jn2/qer0BFfeb8fq4BDZpsM9v6jvoDiySCY9dxEufUOv3Xztk0AWMVJbZYSFzO9REdRtMIZ68i2hLHls5lh/iPwDb41SN+iV00mzrqEyOs/QsoTxDzc7gMQtj+tlP3NJHIGMyyQWoaXGhX1vL8fuj+DsS5i+LMXz6mOj3xJMVPWF+x/KPyopghg+JDZBbyddqr49HkJKlkVnb7yhpnALxUg5KyaRz0USBp743ABti+OGMw7Aal/H2jhr5Ndvr89cP9XcJCXPtE8oQ76lIVOauauUUanKllGvbeZlnhFzstQ5TiFmOPj23oAcEMudFl4dRn2MZCjG17ezmL2OSQ9GnAiN0V50IC9epW+RlAc0UmAaJcejWthpLRBLDQOYPJDTYlwSFBhK1lIBZCunKHy3nYCwJDy7EHKVHzCsFUP7vPqPyO1YW41XRyBUxZU9704c3w45cU2eet9FdJa3BlX9CKvdUTpMn9xVZlbE/IS7yjWozHahG9Z88pIkoj0FXqSsQCn2lrsI4vy8GpBVm5bdK8zykqyif7WMBDpmlrupKhvSQKqGcByn6umc9n5chy/TPuqo7UQ2Lza/jN5XiKpyRe5N0+0xnmUpLAeuaG/eXmQIcWvIRVAxwPms7IyAptjTjaX9hXn02JHFs2gkNlFI6lb0+CY8jpfQilNjVHcRfuY8SnMlSJOu/2dFOnZyZP8N1dyp7X02HPXlaSnN4VotNH5o/I2uZrqlY7bBtRTIlBql4mv/ENCo2/0M2sd/RGoeRYzApLQ+VkNNIMdH14ytJCm6tA2BwxzA41tssSoflNDkNjsEN4D8zCvTl6hhQf2eaUaCW1ck5Wk8D95+rE3I8HZCUmOPJAYCyAOg6Auo6Y44INz4Gd5ocEcgaBxoox+loSqomle17MF1wbCrLy99c/502e6r7w5Tmas8NLUMdT2zWNvd16ooCU5SA4sE/KxtB1sBJB6A7qgOgeTsr2wdIpTTkCNI5mNaCaTMHSts3IamqmTlaybHdv4bHVNK0QhtEobv5KZQerY2hoQwowqzcCX0VtAhPfK9HaxUylSYFS/PgcI6vT2l+EgJMxQp/AoJo26VS/X88QWLtRap9x7B47b1Y8yzNazcbIfc0jdBH72MqSV6aA/ldsP2P3GsRPF67dFRb4MzfK33jKbTBSl8v5vdIX/jKQxlY0MXDSNmDCrrX9Ct9UK3vpq5m/bRq4tUchKkv5qkxKbLeBwcYLqyyL4ZopTFT1ulMFLMP1CnsrRNArwD8EIR/50fhETQdQR/7SaAIwKp/EuhQBM0/I6jdDztfCTri9lS4auaW
*/