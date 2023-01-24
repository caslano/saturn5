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
FV3x4tFLgq/mQRvzcoGZLAr3xS2ZCHM/i/wSB4M9UFWpB6AjjKaSlLGWFkZKMIDxDicbSgIjbct9/xYEYVD+t55kdnJbX8yk1z/W6jnPUHb4b7ERzf4peSadbXge3rhxx11T85DG0ZtBkzYnAjzeULYNc6Nlp/EvVCDcd8nnAqe9WehabmI5OqRLAqTs1RU6WRqgluA4ezmg5q7OYKHOY3Swf69BpAy9OdHihE9QfNcDnVs5Z1ZLuWdicIZuBnlPPoAaGy/BxclOADTu+ly6AuuSrrKGyrsOqRVXZV3p63SymyR43xkzhH2ygxNkDs8p5JrIOYaJUyO7OLItiA6GX7wUFlGVkWsFtjFmk3J5qSonbIY7yjRPwN08VS+kTSVZPiH7U6zLksC1xXcf5WJa9JR39nRVHhmTRaKNq92Qn2S/WhkYn32RdOHFqhw9epF3tXP1wrVkFp2L3Hm0L+ZZevdzHDfJ9iEv3jDPwFXJ6CWwSkKiuOsTaGkz5hdPJlZlFZi8f0Iry2hKcN6baKDupBzTFwv8HvcVgUTPJdqZfyj9iB5ojzDQYv3/G+qi3BykgHr6KSAPnft6gmYaEdqNJxHJDpy6JnHDCQB5XJm4R3EG30RnkOTleoMe9ymTmteqOGMFcVT41uGOI9WT7aSA06iguIVf9SGkDyjeKphUYnS21ylGr/OWeibOqJIKeiDOwZAdKfdMgOfTGBnF
*/