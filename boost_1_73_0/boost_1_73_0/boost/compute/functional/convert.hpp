//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_convert
{
    invoked_convert(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// The \ref convert function converts its argument to type \c T (similar to
/// static_cast<T>).
///
/// \see \ref as "as<T>"
template<class T>
struct convert
{
    typedef T result_type;

    /// \internal_
    template<class Arg>
    detail::invoked_convert<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_convert<T, Arg>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP

/* convert.hpp
7QTjP/6bbz7QADKNdckze7HPOH11zbw6cuEzUGOwLVHdAbUfNUhxu57UFemc3xWkCC4ztUaRneFMZDVC1NRoiPnTygyGfWqLX+qjDHtXwlxPYWe3PrMVt+cNdq9F1V8FsJBRvQxACuozutrxHr+fUD84tryKsjh9hgeAxnS5w2FkoXf3okVBSdle9TcX+5shd37BClpPnGpHLBWeejspyK1qYw1ihkTwOyQ8RvDFAXON0Jg30tfLxWDaq3eojXy6kjgaMlibrMQP7hNk9ukdLfBdpUm6LP2a/gJudhwac5mXOPidlNHUvMrhgrzGRCdYzU2x7RYBt6PqeLNnAXRTZzDt33tlkkEaoKShC+8yrwb8VgYmtF8YviROmYJeX11dXDXF118n8tuPHl2DuLJprEpXqJ/LOwT2dkvVzaAVqMVKNl5smfKbLR2vPex4OoNw301Wb54dN44wrf/B1lkxn0dqZaktm60peStPN+5zlRC5A65TPnMYc5AA7YefudanUh9IRmVXEKstt7L9QkZA1BSraB7lO0JNuiRH04DPnUPdZub3XAEV/962D4bldpydlhfkONMbU2vBtZcZtsfrFvPZ2dZo2Dj76Vh6E+DzcNwxN+rr48ub/z+ToZHaN/fa6yI0WKufSjB3uC+3
*/