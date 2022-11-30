/*
 [auto_generated]
 boost/numeric/odeint/external/vexcl/vexcl_resize.hpp

 [begin_description]
 Enable resizing for vexcl vector and multivector.
 [end_description]

 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky
 Copyright 2012 Denis Demidov

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

namespace boost {
namespace numeric {
namespace odeint {



/*
 * specializations for vex::vector< T >
 */
template< typename T >
struct is_resizeable< vex::vector< T > > : boost::true_type { };

template< typename T >
struct resize_impl< vex::vector< T > , vex::vector< T > >
{
    static void resize( vex::vector< T > &x1 , const vex::vector< T > &x2 )
    {
        x1.resize( x2.queue_list() , x2.size() );
    }
};

template< typename T >
struct same_size_impl< vex::vector< T > , vex::vector< T > >
{
    static bool same_size( const vex::vector< T > &x1 , const vex::vector< T > &x2 )
    {
        return x1.size() == x2.size();
    }
};





/*
 * specializations for vex::multivector< T >
 */
template< typename T , size_t N >
struct is_resizeable< vex::multivector< T , N > > : boost::true_type { };

template< typename T , size_t N >
struct resize_impl< vex::multivector< T , N > , vex::multivector< T , N > >
{
    static void resize( vex::multivector< T , N > &x1 , const vex::multivector< T , N > &x2 )
    {
        x1.resize( x2.queue_list() , x2.size() );
    }
};

template< typename T , size_t N >
struct same_size_impl< vex::multivector< T , N > , vex::multivector< T , N > >
{
    static bool same_size( const vex::multivector< T , N > &x1 , const vex::multivector< T , N > &x2 )
    {
        return x1.size() == x2.size();
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED

/* vexcl_resize.hpp
3BQeK24x1Fa2Y6HykLXqdi2IC+VjQQCwAlCLExlhob5N7FXFnatQrCY5Mwl3nqmXyKUZXu64Dt1k8vdr7Nd1gjvfRpGgvHzGn/DxCP2xXTxuoseKO69QjW+kLYOgGy+fiLZcmFqGNvDMPLWVufW9ryb3vmrY+6q+9x0xNT06Sryai7YXc3Dnq+m1mxvFsWBLuB1EbbotUjtpyAeJ+KKCogTBKRWKw6pnMVe2MhdIshxMEK5E+zFD+Kx9TpqeyG3MiT1durddLCwuj/AfpsGEUH07RhvFGL1PsE6q51T0SFhNVvP0M0VgP6o9KPyC6F+20f8pF8VfzJNTeKgoZLHXLUNH/HFrVgEBU9GtVPRiJJKK/ni2FbiZqC3I9ha48tB2A3iirgthUAWAlKJ56b1BLATeSB23jQwpu4G10pFIH8WE6CckYlVKbTAr+jMRLyIbnsEDxKLHTTaTlnCz5ahghnKH6z92vrCpaA70/BC5O1J45332uj0UnyWZUhI7zDeOtwklNnFpJQtFNqmniFTMlfC+14iLri2AvrQkcdFqiYvGYbmo/1cjLjp9jVYOuOhTe+zv5iDgon9gqSsHtTXyZGL+PK+Ygckwq8q9FhZ1KPdaWTRbudcmfGQSc7IFzyBmYs/HYiZyBlIQhH8vZDNyWakIIXiZ9FrbbcRfr5ach/8JIi+NjnjjZFKwWj6F//30qGHoTlyPGpsJXSqOR638WjgBFYQIR/2xaBa/Dm5ZL3uLR9HVw22DffqowCPiQGYUx8Jnw/grViUdnRqyfUG0bNQO2g90LARUZEk28C67aHM83S3Pc21CZ04MQuvp4j1r7T/wjARoUubkcA6INjGHImnIrEhD7Hv+YqDXnM1nszfMyR1obwhbvHxeInMeFAMmHY+4sRqGUz5vAF6t2j3QHo99FgKyslDluVf3qKy81Muv3EPi2zy48fHMqxHVTYAiEWEXEJ6ff7bbaery82tKesUb/95Nb8xkbrjJhlIv796NBsGYzAPzgsBbYcroQRmZGqpJxvUctkL5PvbIfB+sP7Rj0gpggba926sC8zvbOO7OUQP92RCnidHG3TZgAOVpNxW4RWUh8Iy2eFWuVykGkk15xKo8YhOhTmUWCjoXLZvnr8TLUqV2tlJbptROofNwqlLrhVNRqZ2nuEsWJNzTxOGm0X2D1ssYb+/Hr53THotP/OU54V8KC27v69FbvlBrObUsItl+/41Ge5BUX1DHrcdYqXzq6yiJ9nRwz+tJJxH3bECArCIH1ul6tg3z/gJxmo9naOQKOh9yBcJUfpDN9ujHWgu/+ZiqduWjfxRufb8/MhLotbDJ5/N3jUT49/kYmhDA164+5Ez6HXTwvzY7B+/n17NNEp5j+9RR+0JsOq2Y2wLr7FXKreq78fJcn/puYROAyCTFPVlxT1HcU+VCGeHbaPGP/rXMm4fo4b24p71Q9fkpdqzMniOt7mfNVmoalZqXixMA/0vaKfdII9xcWLTQCpC7r+hhC+BD18vC4+Aoc7Wzig52wx0IR54+jJ7bNBKPKjhhXN1F0/HwijjY6G3w3OzpSH9TxKgah/dXV/CCN9E4x3M01pQPR0Nx8yJrQUus0wItAQVRcdA/MGM0Rer19BW0iHaVmp1KTZNSswezgtV0R7IZHC3Zk/0Fe33e9DOhuGunt+sC5urFMl/BXirz7JSnIukXI5j3PnIp8zTy10SeNpFA8eP/dkoLxGAwbCKTV9dB1Lo+dVpVqcjT7sP+QdFyrQg+F/ccRN34A2jKOctrMhlyQ67Rm6RvFkNfC1y9OBpPt9cXHikopYp2vwZS0KcjXxr6NNfYJzMeofJrGaIDZnxZdvPzU7IIhiu7+cEpmb4POoZrh97Mp9qdRkNLaW8GYFd/BOitqsladJlY7TTVXoekbyjAgxNQDj3mNd3vx163lep4gbTcSFtoHqr6kbPAiLoikgzsq8IjsKcuETAFV0Aw8hNX9KByNYNSTQGeDpv4xbucJvLbK58d4COf6lPRqehounAqYuXT0Oq+TWho1EPF7nnRCSkqNNGhL1JDHoleBG2FzfzP6/vUrpHo+NHCP8TZgK1OnVmAFmixhVakNBfCDh8JKB3oh9V/hn0qtlTCTUlJDLSlvr/yB+VPxnEW77bXUbTNBto/lW3FByIXFd1mjYwtus0SsSVcbcSql32uqiFcyIEphRHK47XAbMvMYbDpo2ksgYvAYAPD5mhnpVYFdp3XJgLoRZ1FlW3Ry5i7JGzxBgRsdqNW458nACllJdxTKHR9pTWSh4PHlL0SpwAmAZSivsvKy5TySUpVmVI1dQE2JuZ/xZN9qhbT+q33naZU+PZkyfnkP0AfTxwB7GN7fQ3lpSqqtEUzA/wVVLtrEeKVylP8iRsRFuAc3biTDtXr6FBdfCOC3ZM7ieMo3g2MsYEhgftsHDbb15UFr+JO4Cth+Yqq5tnrUc5avR6jx6uNAmgtgFBQJ1p8EoiEt3hdVw+ZDySy7oCzFB90pRWSIh7agkNwMwbdNPo0Fe+OZvDrEG9P35DWiIDLxgbC9nAexo4vCQXiNR0hL1tWhqkUUFWLeUFr2vCcl3DaGjazNlYcVvXo9djGky+LLPAHAI412EwFmibe9yf0HhjQoqBy0tkteczhw5lBqgN5sWlwkuvHTXtKmy5SvPS0OQdZXWv4IBRgx/mCS3D+x7+aNBuowAhJ3TKZUazfXOvAgt50LWRSNM9Yob6pduKg59lhc5C9pTxURva8knOLLZ6mRicF+AfPIdn12z8lvzc+bELTtquOAxP/UJny0OTEnGk6HSnjwQI8Xj/DAI93DuvvVnhEqZpUVFUKiAqI2KKq2fa6FXQBELNMh5j/ekWHmA0AmwAwF0EXAp0EMGYBMA2VpxBeNBmAEWSSPm0EMid3nQVkWoeAzOhWBc6B6QcVVG5t9Sse6MJWpfJ5Tcv1fIEbeLitBUGLAqfw60pF21OFrxe8XpyomQjHsrh2bagZT1tcIpPICEAD9rqncRUQKybcUwkXbXq8T02BdCTC2UYI52VAOPFaW0jxNCoVO5XKLXoS4LpXsY12p6SfP2mkjXshbFzM3ecTpEXnaqz05RRJMjeJSjUsWOrnH05BknlHI+1uDLprfBFj0CE0h2XayehXGMvBNDjMgXl17Ep5Nns8FwseR1V5etChBHMYzE25xesL6dmSx7KgpWC8N/bPDH9IhLssPJJwbTELkXvc0+RTKjcprg0D/R6J5iifrVSuBSR+KVvaTklgAZPPt0ZsRfOJGFpLJrzuMm+8YpOfVTwfdzV5mWurH4bm9fP6/wAk6toAL12GGDBycbG7LJpRVLkpakd16nIy5KJuJFwbaDEez5UTuWG7U3gVNxfKWVuxXbImiBOfK8RZi0GRQIYvC/ZEbe1Khw8CTi8+IOzs8UB6FqPk8vUX4Tb24iuY2rP+SOSOWM0mOKRXyOyetF9hmsWGhoLedC3dJ2xoQwXY0JcPej6WebaQIdNHsEc7i7E30HbkeqIf6gvofgsmTUGCeRd6gwXLwpRqy/cFHrK0nTvTyQy4nXnaaPUoLmnFVgB35mkCjkYZxTwHlaCFVexRYI1d+5SARZllDSi36kmpI6PYOGJsKjZ0WTcTaeraUNgUMCaA0usCXf48tO/zJyHlSjbHWgAHiYNic299uz89K9acUdCKW67Zq0EP0B1zLSxkhVbZHHkSQ8Nd49koFrCwWVbF08FutSkV9EUP8OZrTZFRAT0h6AQWLGE1G5hriz8kDKYrtuFc3PBvlFKWpMLRt75jPIMb5+el0Cc/OOOc8gWK/v3imzrTEyfriETmImiP/2Zzn3oOxe/A+OkigANwN7Bc0P1uPKJVs7CP3mPW7KMHRH4w8o9B8XW+saJPqjL4H3Y6UzlIyngVFRS73+tf2kzv/ebOPlWcWpjPnMoqO++DxkT9HFbhCKINHnYxG6Olo3BMfPI5/OSAXlZpvFdyfPC9oByeX7738V19GF9ljf7eoSqZ3xkYR0aRnVlJDvGBrCLbj3YGwAyKvlHKBrUVv0PtA6/pwO5huT6mz7+PY0phHyeeY/KH2ZVqRwr/QtHZ5aIL80V/Q34tJWlyoCyxYMgM45sif6+ZrblX86B3yjKF4mQBcb1WENcY+dkgTIF//FWAmYH0ocgH/iuEJdEnb0lYghvJmbTSaT69sIXXvoTYCVCTiz8cO0YRMR9/kdDelNiuMgqcW8B2OSgFWg6lS7bh7+WI/MPZBW/5Cl73hvx4WvDvvIiOuGJMuIuWLELwkDNH9PtEI/1OCpDP+LXYAXRM7xZ+8EbqHA+kEBKYkk1DD/S+AuSCOXByrKa/oKKjoKa3eF/UUnwiMloDkwA5WmthpGJvOVN4uKEw5bqEU+i2v5eu7Us+ZQWA2ytThSjiSukQXGLFmAk3YuQ//KH6Pv5JMwVWOFK1m/Ntg/1zGkuvSIEvdhnppbxhI2okshA7SNUW294hevM14cF1CYGbld3o5e+OQ7qtZ5umGRghfCar4YA4Fn0b/VYO88cvEwQ3m4uB6g+SMOa5bSL4ReRqNh3Dc5D/a54fq7/ssWlRMt718mWyYrQDKOB6FbrgRAscrP+Qld0cVN9BmjkoYrwB2iyekRfNgttqlDCr0ff5G5WfqkBiPCC8bc/QfN6BvffCfPr5RdvozLWiTesFTTSd7wsPmsP8zWiP4AuivXJt9m1MYssWPv+NVF6bvPIPtBSdjwzRLw/WT1/7/FnkZ2xG7uD8S1AUa+qP9V/40CL7K0v4qwtN6sT6PfCnMYOSfqC0AZiHCwubilw2+xNNccsbZvkAcA46/MY6MmNNWcaCJgfeNWbKepQejC4u1S5ytYvR2kf2EQqGNaiAby+GnzL4eRp+tsLPC/ATh5918PMn+DGZrdq/tDSrNd2SkZklxxdr+hhTr34VRjF1J4wiBz6gfQj/jpV/x4i/8F34fQHUvAR+roCfa3Ym8/Oh83vC9PIVGNpmolKar5ROVkqnkDu8VSnNVkptiRIHaZBKc5XSvERJDikISyftHmAvkboVby7qY1O05TU0NHCHJ8wvD9iAmn7WZop+E2Oqh6IjY7UOTK2rdmW8RpTg8Qw0LcpGtLuETK1DPjIYx3MsKMIOJI8sGR995rntvT4CkCvcr3hOxd1TE5ntODarNhYKCKWU58oMrGehBIT8nPmmKg7mm4a6aV8Ju2W20B4NK//dOvNc9mLYH00EvO+MejZ7sfMc7+enjeO1fOV/Pd7z6j+2r/Xfevb+a+s/ETqm82jRi7jZguuOkaUew2NXLPUA4kTXb6LUqbApVOS2RUYprn44x+Ku/i4b/PLyNy/twTQIrHwim8rmW3C1gvnpx5WF1gXp71cp820UGP/25Pgo/pjBv/qXvz2H/Rvayxnl/+dR/4+G+tPPVr9xZ3qKfCP83PQtv/6uTzV7ydm42MvzRqOqvoxs2Evp9zz6jaLQYe2I2FJ8bTC85Zxz/Wcb1p/v+nTY9cfJWH81MHar8Dv1+4Fh1nX/1ONBSZTOJ15nPrzGx/8mtQnkq2fOJ3/SOKP946/Pqc+5+uVfGvLVDSNvOebKNiP0VQJ5pbjaIplLD1AApIsY2Vuwx6xp6P/wsfo7DLYbdvB9jU5ToYrpPXUFhVLTLfZodeNXt5AEnmKB8r9YPqc4SxXZzOMIAR3dBoQ6sFOBpLtUCzeFYJ57h8jBUpogf/LGsP4pMN5vzTTQSznDyZeOc76VIp1FHsJxlzpYSXbhkeqp15g0SSLxhPyeLXKp2lG8tJtiPdd9XZWxnmV/A0Dj/SCEkwFkpLIdQYNfdg35lU1gq/G2+IAheoXyNBbB2dg1CbkbzDeN7228h2SloR370Ed5I9pKKRvR4ZtfvN1pSh399v09BoZT5JMaKO/GFNf4NXsdEfIEyQDFSzbAR0OYThPzhlHhWLZsUZrIIybvgSFBsUe6CmWeo+mJ+DxrmtYCpohZQ/WBau6IT5vBaEfEK7qN5DiQwH6fHi5KvBvO9ocCgQC/6zfOZH8oLBk0VdFdUNEHNPmSw+jS7eG+9HfRUaKSQxdaeNdNvcQPesWMAdOKof4GlAhBSyPNZNfEIG8zf44YFu2/gvwA3DDMwYF1FhGbRO2+4+nVxegNu52GeMKD+A+MtogepMpNSq2FMRoxQIZBS8d8eRhIaLJgPZDv8ADf0aFkkh6h3DI0taUwkwdi9sdXQi9c3QWuPlbRW1DRb840By3IksDuxp59+rpzYNwOAe87HtDtH4cJlvoooa+maHaqVCMYby8KXL0b01mVkidhE8B8iG80aTOXAXUQLcU9VsU9b4BzKxqIwAQ2/ZriVi3jMswTu+hKVX0NOMNlNpmaVWwDxAEX+1GsroVYpWIvi6FoLKhXA1g8TEuI+lrWG8nWyx/DLIhxt+pFMyvRJOZaXNJKnHPY7C/HVsazZRhhD+XuOkqRQVKHhmLTjX4a2796Hvk/z4eeueILVTvfyvLRVH+qFJ4p7pLhzWLPu30tKijmN+n7n3/JoE88L3oJG9bOy7a+c9FL/NeG8+n0xnPSG0Rf5fM/nEhAwzlJStonxEEO0svr5LSRxqL9WTI4PjWKCEJ5FORPcbUWNvn8RtMmsTX5DPwafKqXElI1UdMsh42eChQNK7FQ8qmDm6fBnVJxOF5xNG4z+RVPGz/+yAlU8pVY0l1t6Z7DrOJgeitz56e7etMPsKqJ6ZXd6a/D+UlAlv4eHhzuEsVtQZdIoQBrgdPTjKFGYLfZKIoHmSJVo02utEaK1U4zRS8TKUWB6BjHXG1oBJUbNoe8zNUaANDvyoUWmAez9sFT+B2QkUzGtWNSvIuYPxsgAVBT4RG0+a4qUaosQz8cCBg/qws/lu9ypgzvc7CxLn+IPc+qDelDSCMsIlht4bfl9aqxXaiqMQ0NKCblT8fZanwDT4HDZO9EyqgbmZosbyPscIi1AZrM3eQ0FbuskQkDX3Orh4p7Fx2EITSRuklGXhtsHy+EofXqwu+Jrmuvw9v9NXOTZfjFkHqIAt32Rq7jTXcLr7XfPU2CLmeQ//5uyrb0tCbc5+lSuM96RdAvq0kEAdPnMcVgcUyFx+qP1E4l+6xB4/Xyh9egtGbG05q0xia+tSUdkaO7+N+LDrC3AIN1mp/pIXlqbAdNfmQMU2RbJdZKtcOQbxTlpST1ExJTGFLGuh518GRAr1TolX9gfp7Bs+Plnf+B/du8UetfLjqlwr6an0aZL2njCjV/U2TsnOKTi15dUEWbg0zL5GIZ4lVo/R+r938JJkXXhzAkXm2OGwFMe0nvIJITVepHAzOcdj7HetSh8d4w3NvYN3uIsjgqtJ+tGAcnC0i9FzYKjwtD/QS61amyo9FM4YQhuzsWTryVRERhocCvD0d+fnZ7aD2Mm2bVLoYDgBop1Ee0BI/WeEWvP0QmapfEdm0SYzbkO27h7mfEOTzFQrErMbFZn4IOlqUakRSWYRgBQgiSWgWllJ8Us4dlHa8wdEts61Xl5R0v9arnCHM+AG8QfrYFZMpx/HoILezFmL5su1RNwtuXHwBulsLLyH1oiVL7ozXJ5ZyI5B0BkXsgEAYQCOfFEQhzN2hAeEW8AcmOsFnx9PGHfkW0zxjoZtjMFbqLWGcVV/Yveror
*/