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
Z6M/3rBbK3kITZN2kI2W5FzlPnI+p6xMZIOe86AkSp/sORz97wGA9dgU4jetn6cQcUmqberd/9Jr+h1gG0rJA2GfPoyQyaSuq/iKJvwI2jdJ/EGMhylTEij+SEPbVa7G16IrapN7a1+6Bb5HkEOF0hCxcVPbssuh6aukw8+bDjIu8wud6WKdeqN9xzQxmXXEqTNcA5a0SvN45yMmcPEVLUr23aW9h8uh3S2wimYkE8+PvmjHPj98i+5XLKw+fs+S9SbrZOKdom5SxDqtcFQaD0bMyphVQrnaQfbewGY2q5sJecR6SQLwmf9o4jd3aAq5lqSKjT/lXbyMqtIQddbk0LyI4japQEobrjVniDPRNrXpkRGDCoLheKLzMIhQ0P3R+xbzcB41Dz3o9FcJbIe2rVL4k3kr2Hi5BINzl4OP56Tvgj0d9uwckRdFBSCNLAY2oooaOovEReB5VD8g7YBeY11L7OWis8oyibtbwZlLxPxuOtfaYElsVyiQ+lJH5FSdQc0JK9TbjR/e33911ADzpeC0CEYfnKsaMCiiu5AzqATBAM6Gjn6ZdtEN8g==
*/