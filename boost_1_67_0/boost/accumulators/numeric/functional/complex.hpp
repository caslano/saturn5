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