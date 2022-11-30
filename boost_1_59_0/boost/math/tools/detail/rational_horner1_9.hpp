//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_9_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_9_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((b[4] * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) / ((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((b[5] * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) / (((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((b[6] * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) / ((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((b[7] * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) / (((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((b[8] * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) / ((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_9.hpp
XzjzSrcoF2EzJ4RlJHTidDo9QNSZ3JVIobvKZ8gMqlmxYi3l+BJGfGvrMgYVgB2VEW9LgxepxB7XgA5OGzITpKc5W7ikHrSCU0JAKZlMrRuYtZTcFUFoPIWwYOTbscRVuOnsYP3aU7IaDqkSs1hwicesN5hJrPMFzzqLyzl2O+KTYdTkzb5m9yOZaPCJzgArMqIRBiB3EWXiOF1l6Q0AeTNJkGSrRgNI/HJW6PHP1G3MVG/2dHuRmKCXGiNnUyxklSEtdqq9NFjY2FBeG6DWvfqtOGQCOwSNg2XrL7pCLu7L1tD/LgECD989jo1mU7Q71mm3kyqOxTxk+Kg1+BehsztqDmiH4d4DUaWaveLUod5yQN1bNbDZBkEOZupLl4Mx+qvef/EBXxc6ZDG6MyHOxrSa9pH9ztkITixPzdNNSAIm1DCIJFc4X6+51LvviZJLfHyAPb9GQgt6Szfi3TCYWNBVVcKfKsp3ghlM9TxzcmQlVTybCQOCk7jSeskDPmIIDd3GATPBRMuyzat2bagrP20tC5qFr3heRukxCZUThHSACEArCoiQ6cVmqO/0L4jjBCB6kxvI+WJ2X4L4gmaVTIqwnR0R75JCDFQXa91MbkKodNagw5sQHJqK7UXewkDCPj+2TNBY8PlpxY39nOJ06LbwfG99lS21vr5I8i6TRZQlri5P90ecnUxR6ICH0+3S93w2nYUcuDAqvgyxLV7F7HP8olJPZUeoBLhSPVR1PQufAhIo6J4ya7QXN3Wdd9dcE5s+VzuffzLN76gxNmKYQg9q2qicaq1b3EA7WyGp/cesn6YETdWzs1WDHU4TIdVbfH7CZbG67bo98iFaUvSM9QbYx5va7Qx8Vm0L0MIRSIHe2pK18J3F5H6DEXFyicDjKn30/Cualk1d8eqqbfwkEH4D9SprlMif+alk4EzQPVhIob2IFSc+f7M+D7dx7tik+YkKXRvZhLfPtjni6pYkJ6ft1taMWrhNYu1p/psdt4glkUGhfGDI95xCajiSmmU3cv/Yx2GjxNjhhZq+vSr6Kp4JBCcNKJs8XBRNVdsz2pSaO/xLriGyzYMt1iNkjIUkQzgx21wwhkPnAXiIX+xTj4cJLXNBmk6WD7UHe2iGC94YlpLRdKrR8ijrTK98h2girKT0KHAhfm34DW8HQrthCaUerLMgDuIc5rn6zKUl+PZuKvfEYxpkuNnAEHL0vPXokvrqBLPEdWw14UnTwf4yvPxkSP6sLC3X8mOzVTVOa2f36bv1L6+/Bd3M9Se9sUQzqBXsNxliiKUoMDDRndmWS7CJ0qyxiD356y57oad20Y4QRYiOr+8001muo4yc6CqcU3XjROJN9q7lybFJ4vKRxNieML3Tt47foBkVZNv/y6wrmbe+cG1KCg5xDZsn9YvQtUzeMMbL+ks9/wD0VPD6etWSV/swvtlodauVsH6plEQWsdCv18LE02ppCAMP4FGEGHdTwcWDYVvcQkASq6CDflqiZ+i5Ckw86CINjdI8r3Y26qZi8X2cGcUZnfyvn+PRy5YjWcZ7MsqZCTTOLWgVQ4qEZYcVi3ExEB3guN9Y6MjIernMEv8k4lJqD78CEFt7fuaErvvbMVDhk/nW1sMn3Ne83tFj9PCZ9FwG7k+TwhG5ykZP8Ql6WwZgvPpa5TO6yS8NvoMiGLRW2JQvGzNc3mBG4K2ON7dAoDz0ooXwnL19A5r2vbC9bRMcs32dIyZXCkEqb9JnKc6PLi2T7sub662gtfMYnPS7ZRyRbXyE3j4HkkcH3AY2a5CuM2zhn6+D9nSbtazzu/t5zRiseuCth9/vETuTpM8tnoWXxOhTZ7+7CC7UmShdW6OdNWyPEfMMKV/h+zTQ55WJfeKEG/KcQA+06dO5WObM6MmTgQHJAgg8+UbGIQU2Xu50uxMv5FpkDlHnpur8oYPWWmmxY0UvfQQs4qRcN4LvkQz2EM2LwUil1igeWTWhTqpmh7LNs2KMI7bTT1Pd/DmWN/HOopaf3fJZRCbVMOE7T+rJSzB6I6uJFdzf4DNrvxaM/r3NF5brFRFSJvvsIWH1FTNqotwWTQ47XJUjmjGmW8tgiSJzZicYmhP3E8v1QnuxlEZ+7G6hl/T84FDu0geqiJp5aY0VjQWlqZ9z2VFky0Lhtua5wDzcdeKZ6G30e2mWewg45ATIgjCZVAgwqPJoi2b38g9aOtCYIR6Pquf0ZbL5djhEbVfoBrC+b0uxXUpNak2qApnwymTkVBXad40jRoH62IGEbhsouTi9BOpG5QusWWFdjSuLt4A3ReJsu5aMCh9/PB2GTu3d9zKKpovpAexWO6OdjYUEaEfaGYEeoaJk+WL9rQ3A5tEucXBFCT8lpovjaObVcOej1k07ScHnU+kgXcWxi3D7qblN/AO+PKAtes4sIrKta2Ib+iniN0HXfYxq75BuieXiMmoAr1jm23dujoOuJoN2+pw9uEcTE5ZONJotpukNKM6Cn0TelaSGbI4c3QN6QIGwg3RveoPMSQtfOJtpuGH9TWsQWNCSqgmX5yesujPGVmEPDwfzDS0f9BojDd419KIepJw7Sskr+bkK2c3JzM3RWPL0s7QMUnEB96HaXjnH4pp3XitJkNEh+/BIleyipQEC6Gf55Hqm66RflLN525QE9aeG5UIVuDYZm16xKAnrSQ5HDUCqBj7KI2WIqi1BP2qPw6rGN3+m9IxijaR1xL1r0p01lrl7hrxjYp/G3pkdH705MAM9qC8KB7jujkDmB0RFo+pdZbzH01J+oDtSoDJX7HR2VCyGBnh+jzrqYpJYGY4lG3El2jc/I8LLzaWym9c2DdxJFo3KfOJJuDbhyzFkK98+5X8y7EptgJS7XP4o2aW3SEKaMw8ccMUB99KOSCaX8YzM7O4GpHHU7nxU8WoYb79K7o3lvZ4GtxSBeZNy8WxkqftJrsrHSJm82AfqxXQPBShECOPQx+5m5ZymXu6lu6sjymkXnaFFczRwD8kxAc9IyjOk+Aa32plaqrqt8cHUCtVz7FUO1Vida0+rst/0E0x0okOuqN5KhqoK4/DhNubw8XbouZRwDeN0m9XZWDUXmHOuNW/52zWyNFLRswm7z/wwLf9av+kMgtpbX9EW8pneVMjKsUdtTp1zbrZSp304tRnPvOsp8IgNXq46dSzeg7yspHb6NevYKz63JEin+XI0nRV5dJRgv8m5Teo6H1lL6Bha+ixDewOTWCVYR5u2ngUULc5pp+/jxQFnnv+OU9WaORpnlfLveA97/Sp06siP29U3KyolN5xjJ1w9MMO1mExiOH1jkotWJKApgVNo2Mdh4bZhU5wWPhJQS0TtZ/mJvLCZal6mXTgEFO2BGyjFZYRgeDLai9yNRrIYP9GiAMkEtdxNdSuY1TPc651rIMtLTfbbhQ0GOp4dHq8CNTbzOpUC3pwrxYUaqc4GPhqx7mpu5yfeowNz3o1MEKh5GX5+0g9rCNKlaM0t442xZWKO6pdE9tRp6LH7WjGE66r2S5CLNXA7eXYz3py+VMFYMmJg9yY0idHvxXaJrao+pUdtU4QLNKJb7z8tKs+LF13xyCf2ARzBgPuL6NtCwg0l76f06VZcpnYplAJD1AED2d0Bjf6sR80Lb/a8ESd82rJTW2c5gGqlPm6uJigzz+b3tXzTbglcFJ1hZftZUNavjLJqGkJ78HaY81CV420Httk9E0dGI1gqB1jegX/b12egYLTGSpd3n98Xz8pKmCyHcMwnOV6mvNHsU93cQHGncJWQwZ+pIlidEO7QS5Qz5W0N8V93VRXRBbbTi3CLOm9QbEi7EzUXDDP9CRuT1jV+UorxBXjgxjz80UYV8hdVYV5CwPg0nwgkJDeFKV2eGY/VZiMvwqedZXYAvwR1rXlnm0DTrzim8CfC4RsLPkhGNMTEQfjndkeTy4in26jalpdmYIxiBxjbcrz0I8lQA1x6yMQnohlUxJEJRDIfxQC1ch5iUqunjBKJKRy0lao1aDS/LZRm32KRyuhnCgpV+MbUP97bVuYQEMlnsaV1bp4gGqi49Bj9knGaUkdphuQTk2nWuCVzXkd86FT9D8gDgGJX1typG/B0F2ba5ONDv53/RfRJRxbN78PcXG/eKTCh+MCv4Zp3lOW8hjseU1UaGkQ4SPq4l27ZjhJzThp5Gl/uvU1HzlZHxvI368itu2YontbRMoFVFXSsfM0nCyhFm5YhN4F/PcTOb6prZNSJK6X3it556Tdk7BXA3SYRYDw+oacysjkToQ8YJtJ4WKVnTaGkpLHVqFzSPAUsQr43jx6PD8IuOZBg2snTlbgkLQTOnK1wuqX+JpwWltMQ+VVF4tZVHRaPiNhccx3u33Ejoay5K6T8Rwr8h94QPBhK2g2pB/2a9+KSZb0uFhEeAD8yL25yqJ7nE7nqD91kHtDx1t6AyVPa7zR9w2z7pS2sF5+dzuU1ASvAucfZR6WVGxncnzy8qm6OobWwxkOngX/BJ9IG5C3JI6mAzadufkqWtbtNWR+nhhtr+QXfF2OEbRh3jZEOotE3ZDq73YGkrpYlzCXHIRfQxNSNF2OfNoqXa8xCMF7QIhQ38krfzKGXWFljvmdfORfv6wRH2rzchyecOhEJER8/R3o8y2+6WxdV7FWluR0rnU4eii6NnvWGS5LJj/T8KR+KuSvNawcliLgFm6w8HMmbFlk6I0EvcZ6D3cX1S8q1YJajpAb1w87eiYuU8H14iWNfc48LzkeIxJBojWxulEadd169O6pNqELS6zEVx5ldIap8KI9GiGgK/GL3/ihQsU05vQ3AwAaCxhHd/KanAL+aDY5a4LfmQCB8v/mGg2zAQz2fMOfJZMpw22IPjWzp5bofhkbIGwh3phYndGkvr1ntU9xq97TemQ4lnuLDXoK8s61zajSSSdbuBq+Gkgyu48iLzmGQz4AOWVB5Jycf+g5ufYECmUtBBXBctP3AYWMY/xOnOqawFH7qH3+VnnYRNiszdyDwSHCvqBeRnwoHuomeNu4gc6k3lmdRob0KaimeKWZvabsO3rT6e6iV2dw+jKBovvriFDgQNwA+8+C93g5K3NmK6RYLfhyg8K07UH3rX3dk6gjwO13F45E3/xftRz4IKTd0Pe23yWZdn8rvGl5uqh6k+3hjcM9SGxdT+pyz/ag+pLpreY9X6cy5dPBp18anAs4IY0LGE9woESnVnbfh2zm1KkJTKaN7TrFdBuhVh/XZDvFMmyIiwUI7XnGtZd6+xmlQMwNUNHWPgVFFdFX0hfn86R6XYD5vlm9Az4iz6aybTqbKdkl5i7gNuZwaDpIUc8G7lMDr99SzZyTUUQqRzAx9VxJedEdmCCdJzkQSthUhOLkJ6N5E71v4faRg+SUF+nQ3DmWHTGREzedRjJOexbxizUmxfMoOE9DsILFSpDKW6LvijBGkYi6JB608LP36xN6H4wsbVXU0a5nOTzt8H0itXdvBvua5t0wA7jPQ5JWM92d52BXyiE6C3c5xMdJc9yYL5/KRYiSPdxcMrTfSBYovaFMtpScpOecZrBTF33Pu6aIOMS8XkAUAmisZOg/LErw9GQ6yW3zxa9vZHYraoSpATcCC9F6bjDIgQJ5dRPERy2eQ+DmgYnoUgU9Z8dC2jQo+3DwZ/5LMww7fbkSEJfdA36B7r0zjcsAXlHej3z6x4XSZOLTCMYadF7qTZYeTvneCJ7YK8GqDDiywkoDKkSCwjutQyaCsCkhIRBeYj0kkglu0tLe9hCWY6Rx1Hop0TOPSsTlOOPTIz6RD8KGmFPrkDUHYPuJIeF+WHZo34Qp8AynyNKSyXciVR/aNCF5z2T+WRtikIpPVszDPduuaQ3CEpTb7XDKIsEnJn7ZqY1DrdyUkHqsuzftPOvC5YPOAKFad9cz/Eam8CnVlqr7/h8UV5qym01IVg5C2oQbnVYgGAyl2B5S/qwcMT0uy6KNGMmndgfSil5fuSHp3iK9tIsZ9dG4Kdv09lWXpqoQuvKe1OY3sijbbdP5eq2U94Yy74+jdRqezLTPPtlrezq6o45QtEebkqLfddXiwIBrb9D3IdvQVEwz9K6IgoVtZGpKRaEl9vn/ZaVxx8ECKAnpDC80bB5veqepZNOIe6o9nJvVh/U5eXzO0Gggw9E2Jj4WpnSh9bg6bdqsQN9wgRDP5FoIJCkOGKtZF2iCe4KtEv3Fl86zSAPSOYb6sd892U4PP6etFdFEOp/mJnq0mqR7Aa9OWIUoZlbVV78jHpqdXAEAJ0oAIYYANmbANnyhshNoIpx0IPt/i5a+VzPEjj5gJXGIzn+ySmj/TLlgXERUuz7Em2Z51ryysZbrDrCQ9cnMrSYFKwwlYAZQXyz6SfeHorRF5i/UGKrm5hMal8OJJ2NCr78GG1ObIgyggoET8Jm8ctvJ5yGPUwbfLDtk9zIPiZOzMxuZOhVs8a8URGRzMqnKvVI8X9XEbILHm6JsgP5PQXBMzoyzpVWe2UVNKTtarYiJhKQ09Gq0KGBMZNvr0IvnKAd6CB+oKtgnTfVx9VemZ0pRW494jumHovjr6uBGMTJifyOxerAZJmTemEEK7+k0b1lkvFe4KgqtOBq/+/fx4pxtgXd586eBd8LcdPsOSCMX/Bf8UQy5US0SB2zPTiNrePX+S7XAkM1cY/c++E1XXgHMNlVhCecz/66/O+oAX3pywjmxj8/t31agGMDbm9j1lv6tWEE3lDJV3LNkQC31xmkkKeg1+edOOdf6xvBoT55x3MJ/Ii2Fv83OITuGfTT3Vg0SK+9LYjivvOlwARu9XJVYrgjlXoSOYJakQt+NK1/CFN8C3MmQQv+RnbxzUMrtkwmTEcSga9iaQs7ehgsqBZiWO+ppdzusgBPM7E0n7qmCb+B8whjbBEG0X/unNgaypWG7j4kUyBVETBhdBczDn9jENsN2wgXFmk/FtrPzdAMf+DjCjtA+ewFEumFDQTlZfd8JsNMuB4YoIsT+7yfrnIR0GHOSu/EA5sEdBFYTsGDfl8aqdle72ybchmyuvkx/lw3UkoTyPhL6z3AO1UZKJX33O9Tr/a2nWkjS1TQPcd6SXpiTXDMJjfpMDAtFfv6U5T23Km46DOhUsaC/2NBdTv3t2pVkQ+QKYb3OjCy3VIlWFLt6o75l1S/ssW9MWqJ0kCGjcXXvM47oCCe9cWvRURQ174kVkv94BzV0UuYPsSnwGKI11aH0DOsmENwAz/OFVc7LK+ADSJroSeFVtbRg3t6vhzFjdLs+Pc0XPFfgOShWrVnpZza8gsgSNE3LaHKpkB9KNgNahQXVIsoXMdH7R9tk2wZQp9shR40MKVc+0gLPxRoSzKpC3F3V3ZTLXSoCyPXhZYVCZ6FgcEyc/Few4PucxNy0XTnFoOFDRTc168tURyia9QGV70KOZaLqVveq99w7FBjb7xLxFYyyqmvAdkJJBHJAymPEtRbHZXDjGyMuLgbrB3CIQnJfiqtxM7Gz4GYvKTvieZmzYs7U5pQ9VMi49nxfqzzFGOBNPCVuEW0J8x4M+DDLq01q61r+hmbgltcpfLAQYN0FEi0PalNcTs5JxS3IPZCDayxd+qV84m41yjbHn4pP7rQLfPhhIP2fkxSpuHu7gGHu7dj3x1J/GYSQD5tqHDJRqfQ+KrSuR
*/