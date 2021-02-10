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
QHszyP/cPyhDDnf4CwL/TtG+Cv1P5J+CvPb1wD8L84cywDlCCbzPq3CWLv6wOabezS3Yoc+YZPvjgLo4sPXNksKyVj/mkvQk9zSqhhFjLd1W9gxjdlgxK3vSoVyWS1LgMzqTGBlJYWROK1JIpqWUmtMOqLfgywHbMTGszUZHuzTVPxpot6BsrwLf6WLYS59e6siDn458liMP5J17jtznjiy/syO/4zvyvQuzFU/SymFFqsi7mR+dWysc3vfk7s5f05Pfc43NXXlOvdOrV3HNBtxSL06Qae58o53SXIo5ZZxsgYF6fIFI3RG28Bna2a33UEtnyWlr95Kr7vH8b616JjGvebiyyX5j3R9MYcu6H3yHsL9U9e8B9neP9gWjHzDcv0L5d4/3d9D9LYDPb6ASRRM9dd+N3+q8Sk540OB1Eu9nbqHZbqdP8STg7SvqOf4tA13vthZDraYmfBmGy4Z5qfb0VgcLhstGFtkbYE0iP/J9ly2ZC5tapw9r94xFJIlgzO7YDnhWRKfk9XeRmVJfLCvWlBBH8Ge5tF/BMmJndzdfRmgnrVNeH3AySSIefy0nOQmw8+4tCUM/xL5DWTwQjUJiOcTBqpD57pTkrwWhP7t7/ecfX2H5h/3SHnw4SP7tvy0Q/y+GY+XvYUyz
*/