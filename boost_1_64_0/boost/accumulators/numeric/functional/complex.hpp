///////////////////////////////////////////////////////////////////////////////
/// \file complex.hpp
///
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NUMERIC_FUNCTIONAL_COMPLEX_HPP_EAN_01_17_2006
#define BOOST_NUMERIC_FUNCTIONAL_COMPLEX_HPP_EAN_01_17_2006

#ifdef BOOST_NUMERIC_FUNCTIONAL_HPP_INCLUDED
# error Include this file before boost/accumulators/numeric/functional.hpp
#endif

#include <complex>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/typeof/std/complex.hpp>
#include <boost/accumulators/numeric/functional_fwd.hpp>

namespace boost { namespace numeric { namespace operators
{
    // So that the stats compile when Sample type is std::complex
    template<typename T, typename U>
    typename
        disable_if<
            mpl::or_<is_same<T, U>, is_same<std::complex<T>, U> >
          , std::complex<T>
        >::type
    operator *(std::complex<T> ri, U const &u)
    {
        // BUGBUG promote result to typeof(T()*u) ?
        return ri *= static_cast<T>(u);
    }

    template<typename T, typename U>
    typename
        disable_if<
            mpl::or_<is_same<T, U>, is_same<std::complex<T>, U> >
          , std::complex<T>
        >::type
    operator /(std::complex<T> ri, U const &u)
    {
        // BUGBUG promote result to typeof(T()*u) ?
        return ri /= static_cast<T>(u);
    }

}}} // namespace boost::numeric::operators

namespace boost { namespace numeric
{
    namespace detail
    {
        template<typename T>
        struct one_complex
        {
            static std::complex<T> const value;
        };

        template<typename T>
        std::complex<T> const one_complex<T>::value
          = std::complex<T>(numeric::one<T>::value, numeric::one<T>::value);
    }

    /// INTERNAL ONLY
    ///
    template<typename T>
    struct one<std::complex<T> >
      : detail::one_complex<T>
    {
        typedef one type;
        typedef std::complex<T> value_type;
        operator value_type const & () const
        {
            return detail::one_complex<T>::value;
        }
    };

}} // namespace boost::numeric

#endif

/* complex.hpp
GJUt8PKBKtaw4ax8soovpRlVXwmpuwOplCcgEn1AOo+ANMm4ztIQBNs9hvpgqhwACQy/iSrKFR7qeiaR/ugS1rFFOfyVin46URRVjKo9UuoJgEwc3Zw7EzriW7vqKVbBjfOFyg+eie6DDI3uitDjLF5zg88tp9Ikqeh+A8PvblQlOxh+7UqGz8xxwwVASWGqc+GyiztODrsnobwlSL7yfeqqJLQQJUuKD6Qbpq+MCySr1HvXcB9Imw/tsvBP+9Pv31dY50EZzEOsw9LezP7HPDtebeOLAPWcrgDHQPvc/yakf1zSq95IOzAJErWZHaqSHFrqPnCOgwMwaXRAkgTMsQO2JXFAqR2wQgLyrYA7slZv2kmug+luff4Vrx+dzxyhDisXfrcdxo8gxc8FDmT/rdxaWnhdqbtRGjrTzyjT+owDp0AZSeFOqhFLEpsmQ4HvyUr0pkoFMsO/gebmg0P/7rPhxPqdb9Uvj2zoqZNRPyltp+oBN22eTqY6HA+E0VetSodgCr8IIrWkxqxJqLosXnH/98k/bmw+nw4H3WzB/1op3sIKNHEUPC1YEofFknR+Bhj4OuWZPcXiuWjhqLaXDXSdYLFEHcz4t6hfX1/z+d7Gir8wwxv1v81pVuP18v3Be2NuYvq3OP0tB0h/Xzw9WAxOPn6fye3+mjY3ob8c46S/Mle+p7trpRyQ/Pn3Fv/1uMqfvO/eenvBwfeWjf9zmvdXDta5hPmmj4I8lPQlSRp7CYIOPyRau9u7bkolbcvxsPvR8RE3eKglc0s2tMerHptiH/hopzuBK4+dvht7GfADNBFHXqfZBcJPcPDt6Vuo5l2L/FsxZ4PEkXUN0dW1at5rmK+p++cyCp1pwqtO0+xnDmY2+tgor4+pLeg3e0eXb92T8YyrRWTLIK4ZC0aoSsAQriFfmZOjpWPG6gKoZs/rGj6tPpiua/gQ1XDatGY1bCs1XMQ1nB/WTUyoYd/91dCgK7hHo9wWEQ2H4T4x15Uk6PuI7wEGxBArZPsEjDg6eKlK3kccWpA3fqsaU8mEjZlhhL3Zsogvfipb/tORDomQFGJ2IzoipWXCt9BlHCbkJF7QZYvGvdw+aQRmxfZX5LtL+yvhX4vfd/hlwv/yf/ifpn+zGAmIdoA7epdwhk85D2K/crNkBeoYtEl/CbsWdelE7livSVYIeAA2GK6lNUb5546WsuuegPG960NcH9tWxRbk7ThLS0ygp0kpy6CKTd9skZ3gVoTXbIQExTXvGaYmL6nNuBFA7yrxGQ7Cyr9LDrkJPc4GUWYtDvJ0n0pWChi50Q4K2XBJ/BJlF+SD1vTpFD59gmTrRjuMMgqZkSCW/pjxceD5HV1JjV3Lv3PAPQhuCCl6/Q4fl2+nAc7Btn3guEL2PU9qWwu/WUrYSAKFs77rRMdNlGjtGE60YIHI20JngY72vbEjrh2sQ8KPHgdcpLqLU82e5DfJWHp0WApQgcJ/OocxelSwIsY5d8+1cq7UOSdKzjMpZzblDEq5vSRnd5/oTCLkaAlJ1bd4fyL8qByca/a3DYCu/CMN1TV89BqgN1DbfPYYxCPPmjwkr6kXp2q6gkq8QTFV8xGjTl/MV3kbe9lgL5ZF43ePEUxhed2q2+WW3rLnx6i3rPmfbOZ/rteotEtd77elRqXEo5UNkxW0lK9F08TMx8Rk6i6WPDHxlky1hKQIILHh2XyiGkRYH1pIf9KOhVunrvxU9+fWZO7PSx+1FuHfqvXAXOEBPaJQIIekqiK1Rd73JO+Jdt771cKWeW367TlEygl8HjWSz6P85l/FNHuH6zQJILH0Hn9krEcNHGLJksOHW+axx11Ct6ZCvUpYa3oCLJHEgPA=
*/