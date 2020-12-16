//  Copyright John Maddock 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Tools for operator on complex as well as scalar types.
//

#ifndef BOOST_MATH_TOOLS_COMPLEX_HPP
#define BOOST_MATH_TOOLS_COMPLEX_HPP

#include <boost/type_traits/is_complex.hpp>

namespace boost {
   namespace math {
      namespace tools {

         //
         // Specialize this trait for user-defined complex types (ie Boost.Multiprecision):
         //
         template <class T>
         struct is_complex_type : public boost::is_complex<T> {};
         //
         // Use this trait to typecast integer literals to something
         // that will interoperate with T:
         //
         template <class T, bool = is_complex_type<T>::value>
         struct integer_scalar_type
         {
            typedef int type;
         };
         template <class T>
         struct integer_scalar_type<T, true>
         {
            typedef typename T::value_type type;
         };
         template <class T, bool = is_complex_type<T>::value>
         struct unsigned_scalar_type
         {
            typedef unsigned type;
         };
         template <class T>
         struct unsigned_scalar_type<T, true>
         {
            typedef typename T::value_type type;
         };
         template <class T, bool = is_complex_type<T>::value>
         struct scalar_type
         {
            typedef T type;
         };
         template <class T>
         struct scalar_type<T, true>
         {
            typedef typename T::value_type type;
         };


} } }

#endif // BOOST_MATH_TOOLS_COMPLEX_HPP

/* complex.hpp
nQL0QBl0/akG93sVdxq6FgIddvzokIL78wDcUw3cIbUs43a60sbrJ9q6nVR5ECZxyZ4i1GuFovEpUNVXL017zfnlCvJKGx6nTNI4i5GZ1NTx7PDqpn8ofMc8OHbUZVyIlzqAVfyn5j8B/yn5z7j8yfnPJP95Kv9JJES8cR2X1DP8Z4L/hPxnjP80+/0XPrTJx5vV+5WyChPH813WGJUcbs50P1PLeTKqvCwIau4afBEieB2mMSvaG7H4PuVVXl6GNcfOLSJU+BedgDnopy/n+53u1AugHza+rB/E16a+L+veiyaXVoAiv8/I77CYIf6nsP7Oyu88Qil9n5ffIZ/4nf97WXyf605OTQJR+EIVc+K7xf5rdW4S930AFbQzQOv1eWDjg6MGfeg9CWjrYE6EOMKnq6KeGFK+rxffnxKcTsKnqd83iO9uBX3NKfk+Dr8P8+9ib0zfNopvoHdanRb7wHH4Bhv4HuZisl+uLaJc8Ame/JcW5qYn+3oe8P1pgIdWKMchMThuOX7z314Fu4sqV+9hL8GYOc3nd5yn1fPBdUET8+rkdH8sSdquDZwGM/OSJMl9301BW1xSqVpc6mFO5xVO1L1Nmhs5DTYlsn9grN1N4jtMx4JA+kab+Xe+LslFifafWw0a9BVwNi95/XtIem8OgkovKnvQeGefNo35kHkX318ITyEdmWDZ2Br/eFiPq5FHeZb99/dfq3Pwx4bkuPqMKu9EEjhhUcKKGiyKp0x9DH5ZxY7WVRhnUVAxYUCAWDmf361ic8YfWJIwTXnIgmkIcwFl0m1QfoZ4OedVTpjFlcN4WcR0CQ8eMnwW6Sb82eDLczf2ktRhvPoEH2pTI19Tlh0/0fwQ5EGeejETa7GVt33GfJymsV+Wfs14s66Rxu3anJW6uev7dclg8zXfMd/WRlRswQrPLfIkqJkwKViZmiYDaLrz9lWeEW5cmiepx8S9NIrvNutRrpXBY2FSp1BRCXva0irY2ax2MdZP/+hL58dHwji//nI1dgCMY27zMqSfAcf5+IYjnh4FgjCHNyiYOXiFlhDC9DZqmOVVOH8tLXGfYIT56WYTIwWRj5GtCobvBFGfTOp4biM6mvShEMKcva2PQQcYq9Nc9xn8uPfUGAi7EIO6dX1TINKh/Zmk91a0/f5u/D7TAdFLL0JGqod7NfTV5UH1eWUPYVrqU8YjJkx7fc7c18TYaX38foTR64vKeu4gYuQ5D9/RHoDfhT4b9GMYwshMOq0aBtZUygW9VxxSMRCfA7qi5jfygTbdTOf9D1IxcP3a0nee/WAFQ51Hyhg6LOlSdx3bj/zBSky7H7pLDyE61jl6oaM189BDCWP2j4+rNCwqRA3rzr24Q33oYS2YuUUNc/sRwmBNoIam0ocQg3kQULFarxDmzofbGDGTKjrT8SNsDJ/aASJ1y4cfaWFw0NEoXFpR8mbjxelRy9vtNoYvDSrGf5SO6baU0X+0hbHL+BgTY5cxPmpi1i7j/DETb5dx/riJoTLubTCPRQze1+xv6lD5jvySdmQUabhoq/3ipSeR1h08Dg6NEYbGAaXN7iC6mfbtjyMa9l95n3P5CZw2Nc8tTOQWid/FTj+P9MefyDF8MkK6cke170mc9hzeMLDTlXJwbiTcK91WHK4DhDsQtOAoXYoJknAcPrWKGwHFr2EKNH5Hdaa5YJEXh3Kv+VMLo9+X35mZdHnzRnq4uYkx9HALky7v0+VeZd8PNR2TOEmiqqhCpuzi0XqbeI6oPCULqrSuyrhkyv7dih8+pvK4KauTwA0SN2eDms7wx3RW409Y6DtuwB88BzQppi/9W/VU/ppVvl9AMV2mnzr0fdydejm93HVSL6o=
*/