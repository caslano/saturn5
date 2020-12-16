//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_KN_HPP
#define BOOST_MATH_BESSEL_KN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/detail/bessel_k0.hpp>
#include <boost/math/special_functions/detail/bessel_k1.hpp>
#include <boost/math/policies/error_handling.hpp>

// Modified Bessel function of the second kind of integer order
// K_n(z) is the dominant solution, forward recurrence always OK (though unstable)

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T bessel_kn(int n, T x, const Policy& pol)
{
    BOOST_MATH_STD_USING
    T value, current, prev;

    using namespace boost::math::tools;

    static const char* function = "boost::math::bessel_kn<%1%>(%1%,%1%)";

    if (x < 0)
    {
       return policies::raise_domain_error<T>(function,
            "Got x = %1%, but argument x must be non-negative, complex number result not supported.", x, pol);
    }
    if (x == 0)
    {
       return policies::raise_overflow_error<T>(function, 0, pol);
    }

    if (n < 0)
    {
        n = -n;                             // K_{-n}(z) = K_n(z)
    }
    if (n == 0)
    {
        value = bessel_k0(x);
    }
    else if (n == 1)
    {
        value = bessel_k1(x);
    }
    else
    {
       prev = bessel_k0(x);
       current = bessel_k1(x);
       int k = 1;
       BOOST_ASSERT(k < n);
       T scale = 1;
       do
       {
           T fact = 2 * k / x;
           if((tools::max_value<T>() - fabs(prev)) / fact < fabs(current))
           {
              scale /= current;
              prev /= current;
              current = 1;
           }
           value = fact * current + prev;
           prev = current;
           current = value;
           ++k;
       }
       while(k < n);
       if(tools::max_value<T>() * scale < fabs(value))
          return sign(scale) * sign(value) * policies::raise_overflow_error<T>(function, 0, pol);
       value /= scale;
    }
    return value;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_KN_HPP


/* bessel_kn.hpp
mkl7RU/aIR4MBIXKPlWAQ5drxDzRXc1D1FBfqy7RHeU19qGzWlewKwh1SWailm7O+TxZB5f6Zxcs3tJazCtB81ScOXA5Tpkc994jnRf/iSsnuH5bJwNcqp8+w9i+bzqP8pS9qmKAG+se2sI+pORz0K/Y2BdOP8TBG5JaJt1FzcHua8zZwy1YY145wDvg86KKw3PkwW28i8WT88q6jXf1OTCFGpSN5Z+tWZxWI03+a+m8+M+9E8q2IpvbtPRE7mrJn07nUXQottP0uVJPWdftttJ5lKf49i/sUlycieZXN+V89mBG5TeS8DnWjy/ucrAkA+mDrS8HOHQNBtfjgbqMFW17Etc9yOdAVm77QUzj+f1kHuFzISuvn9qPTudRnhInPM7nUmDCnN4TfA5EYt8J96QAB65ey6QT4EDBoec4PaHvePF5ZOuyTtBpexyydeEUvyJ9aV+Xou4LDnHk5pMG2/nR3Q4PbzsPj5mNTn/xGpalf2sj49VnRY9ZOPJAh9QEb9/4AhvHzop+vvsh53mYgQHOcebXdHvQEGlzFfpBa4w6D3R1y7N5w/uhZ8ZzyUYrbM/nXb5v+5z3A8ZxJW/W1ecpPi5HXxS7W+I45oUBDsVbehxoB3k4GIL+OKd4uRcFeNR2a1x5SYBH7dA+PvcKl+fb2+YrXY5vb9lXBzjobqM47QCH7Ehs+7UBDuzIurvvTRbHGeNkLpy1xjgaudA37Ot0DERnAnE3QmujVBtdcAvd4DKD3DhDLMare1izIV7strXMQxwyzaRuk+mcQhmH2bTPzo/hopssHS/+F2519P0FGVsCfMwmwZD51GaI84BRe7jN3xA/YF9zoHw/fJrNgT8ZXdUm93LZnFS/l/2w5mGVA35J+61NF18HATjHx+/U+DnXZ3A5ect/UqOhY+xf943858LR43fCh0uOz9G1/knfZW/p4XDmOQT0K1gWxMwJfpLPjvjceALN82Cacoud7A/ziVdgWd3K48FyZd2irXDS5XWOYRTGNUe1rX3ZAw6H7vHhenp4tLFYw5wFe2F6/SSreaihUf21lbOx0atldEEd8uCy7kw8zNZxdu9kYfruB48G7krOp/JQQdpaZpsay8XeT3MDS3Ryfikaz4cAoZD1BsQs8/bNcc8MvyYhe/ftVC4Eo8bdzEwaD3a1x27j5FgutRF9fpukjeP4uF0DSwhlrXEG/3BbxzxLbZU1qquN1myhUDVc4qfPt8qag8uxR4wqx8gBnti88Ho+70CIZ65u8dzZkdyvbvNgz84ZWRu3ztgmeXRsjisDrAvaOEbNYF22nHzovK341dVh30zhzGss6qVTOOapbT26v8ZFKjynfBDjdNTY96n9h2hOwpDxc9BPcPp4BSqIVS4shMi54MEHmUP5y164eQxjJOq9Uvb7GYOY93py3vqAxgPte6zg5creoD726hbHFYS8K97weH5eX7Q5dSevpM1bT2YegXsMy+NlLjbB2OQ7XGwvY5keY8uJkOV7JozFL+hVSuglqNE664ngce810ZEYMwRvv5Px9dCZ9dxXEtxpMrLmMf5rwtF6lNS/yzrCL82c53H9W4xFKN/Tg/b3GI9vb2BD4HH/+4w3sFmFsQjN1PfqSPvJxNT34zxspOeQUMQ+7YceBzEQsZQOmZ9YPLzpmViK+NCOcOgDEHg3YwJZqvMd+Z8FOKDocxntnzPnnJaZ7INdOMTvXLjr1BHcbVDYJ3q2ddUEO46be+fnj+p7dq9G2Oh1nPnk9+5u+n0kHvFRl7R+pzdqlG5eysYRbVg+rpeUp69h1v6J64rFcNy+ViFBsN+/WgBHLcpl9I26G63PPMQeuLeQ9Tb5Xd5LRwayr5XPeDg=
*/