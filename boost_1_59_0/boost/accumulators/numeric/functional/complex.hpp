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
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
*/