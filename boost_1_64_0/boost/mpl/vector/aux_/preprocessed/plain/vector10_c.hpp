
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector10_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0
    >
struct vector1_c
    : vector1< integral_c< T,C0 > >
{
    typedef vector1_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1
    >
struct vector2_c
    : vector2< integral_c< T,C0 >, integral_c< T,C1 > >
{
    typedef vector2_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct vector3_c
    : vector3< integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 > >
{
    typedef vector3_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct vector4_c
    : vector4<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >, integral_c<T
        , C3> 
 >
{
    typedef vector4_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4
    >
struct vector5_c
    : vector5<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 > 
 >
{
    typedef vector5_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5
    >
struct vector6_c
    : vector6<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 > 
 >
{
    typedef vector6_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6
    >
struct vector7_c
    : vector7<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c<T
        , C6> 
 >
{
    typedef vector7_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7
    >
struct vector8_c
    : vector8<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 > 
 >
{
    typedef vector8_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8
    >
struct vector9_c
    : vector9<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 >, integral_c< T,C8 > 
 >
{
    typedef vector9_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9
    >
struct vector10_c
    : vector10<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 >, integral_c< T,C8 >, integral_c< T,C9 > 
 >
{
    typedef vector10_c type;
    typedef T value_type;
};

}}

/* vector10_c.hpp
//6gH3+4fTfVPk3Hi1Zal/BcKx1h43Bx4Hv57E/3jV/PT3s9PUi9rOh1esDj1sNCfDvwWdEbO8Tr5fB34nf8IuoDCWM8/zZx/SZ1L7i4w/5Ivt56HBOWj+myxiu72Peuht/pOrnGK/V1eTzVPhNPmn+kcx/qJz/xki/wgWK6z/v2tz7MuFI8eyYeHkfn6BS36bxlQ9XVn/Occe6d12cUwiMrm+GXd+HiMJz1Zh99q3wgdPrIUP1LQV17OL/u2Ihz3cSHT/Ul2H85dNuNI/HhI+XlffH3ofT6h+UH75l1jXUNXxTQw4rE686r+KjvoPupryff7f2Osn7PxY+dn7iErpQaJY72jOi7k9dO5js9BS74b29+FzhqvPub5ouTI9XdVqh/B/eV/i5+y2c5S+jOZ4n7p9NXb4B31CW6+DHz5cXKJP76MJwqX3ffKb5sNE711v8bEedtmM9T+YtXqDOKj4kb6U/y8z0v84mlBH42+qX7F0uOU+/J0y9/EL8U/llCZ+s+zc+l+uQ7ovEl63kD/eUu6+UkPqRJ+oMvowvdFIUX9LGO6DTn403Z6owhdQT1ujz69Srjm7oVrm3TN/Oi+FSinqr+W48PFOXwaa6h+1R47q3y6W55y++3PwBf7MRvrbfm3nihvt68jbH4pL7bteLg6fR8OL1Fnl2zWDyaKs6Vx/LxOl91Kj61n/6bLnkm0/r+LqjXwqHJ8vDD8iS9uAlPaxrq876QX1PxhGb4Yo73Cu7ZmoxnbBGvK/15bgTvse6H0UvpT7U/iF/d+H8BPLBC3tpfnr2Czs4f3fyYfPKw5+NjSgju+f2WL2GMv1fPKzmfXpipjkT/Ltjb96r/ViarM24WX8aYnxB94Uj75159jXhodY15HUCPn2u9He//wYuLt9g38Gc2ntFwvXmaKw/zr8R/gi+1WtdnqRtF+9xB4vGD5m8En8DT8ASdvvEM/O1dcTlfnV48zfgN/n2H7tSgvmy9dfLHrz3HOs2iE3TSeSbhNX/DVZfJf/B8knpixVt8J+PxLPyyZr71MFQ8FW87XqHHvKAefQRdxPk/KfSC+hn25fvW05Xe+33zUGK9m9eUq33PWO/RHfSF8GmU4XlfGrfz+Ufu5rvcqD7yX/n6AfHpQ7oJntgmfzYeA7dcF+ZfcM6FfdT8mbr2QfCInyniaDH8nex70p40L0/oY9QvUOfcjpSRnos+F/e2cRknTxc5LwIfj7ubTnGj/DXBuObZb5n63nvKv3TctfyUuZ3qw3BAYaBD0BfWT4VTf3Luapd1Yh5z95a37dt0OG3BLOvzQfWJv+DjarjuJPMjD7TdQSdVF1pym7rFefIpvb/pKf1P4llNyLrmV0v9yv4L+gxek2djnU+WAqc8oK9rKd9igf6+5fbjRfLSDfJohrz6Cp/nlmh+Rvg4uEfD+mnEdxo+t+9niBNz8NOTjG+Le034WVoS6GnD6EzL6JV46Tx4MvUa+2Crv59pvj/iA5+oX+4n+T0bv1WfzU8zjsvoo/JyxV34vP6F8FHqpupgWSXO93S/SvGL9HQ+1e6brEt6axd/X/XxdG28aONSut9WeXu0dfGb/Squ1f7q/OPP+X/V1+akwnfO22iIte6utR7+VI/taXzkgXi+z8UP+NxDjOMx4o28VIu/d18Ep3xLrz+tt3sp1E08d/Kl9ru8mn6GOtbNdLodQX+7/5dIHxyPd3VaD3S3ghPwpl/5S++WF2/By5vMq/cvyw3ppzUf071Pg/vAS/gsV9hv+m3X7N1zz+c14zHiSgqdL+1aec49DKnl9Ih0uMQ9w1Uz5d1G+/pHPJf/MWsf54jRN7P9jHO/XXdOtL5rOsYB8t2H+PMa6/U=
*/