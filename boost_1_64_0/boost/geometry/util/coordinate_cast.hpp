// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_COORDINATE_CAST_HPP
#define BOOST_GEOMETRY_UTIL_COORDINATE_CAST_HPP

#include <cstdlib>
#include <string>
#include <boost/lexical_cast.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/*!
\brief cast coordinates from a string to a coordinate type
\detail By default it uses lexical_cast. However, lexical_cast seems not to support
    ttmath / partial specializations. Therefore this small utility is added.
    See also "define_pi" where the same issue is solved
*/
template <typename CoordinateType>
struct coordinate_cast
{
    static inline CoordinateType apply(std::string const& source)
    {
#if defined(BOOST_GEOMETRY_NO_LEXICAL_CAST)
        return atof(source.c_str());
#else
        return boost::lexical_cast<CoordinateType>(source);
#endif
    }
};


} // namespace detail
#endif



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_COORDINATE_CAST_HPP

/* coordinate_cast.hpp
sYsK6cCYopJCDrZoW8vBPqPHxB6ENl13CXxalpq4jG1a6MVeA7dkieDyxf2T+s9LoZvolxXH1ukmQCx2vmK++hbY07rBpqNaqqsqyksPU8oOCVTIffJMlGfsHC1s3Wfi7L4/yQd5MaXUCP1YUTXWOKI193kSZfM18pT84zwVKWSZnWXQm4p8tF2Gs7v/LB80q+bQoYk5VR/ycZR7Ptj1aNMuh/7Cnc+qx5L7n8jDLJEHU0vUhOdgi/JvuwJxxp1sLDDpMFcG/RHaIS0qEXN7QD4OGWXKh9z/Rj5ucskHV9xC6f8G9vy3BbvmsOraKmVqKEYaPD5u7CrElOu0ckmPE+eI+y3f/+Cu7+SynNUs/T+uxny+y8ZVtX0xHh2O9P8Ae6qNnVK1Ss59TBYhc+01sMO2cWlYYZd5AdgZG7tFbWGpZxn/ZhYeX+TgspzJLe0/we1d7OCy7UVI+89rEfN3oY3NNIaI9+cj4H5r68uNep8yjI3jEbWNQ/adhezXQS/SZcsDY7+W+79g11vZ+itDwDlkF/VeeD3sl6zvDvY5y+3g1tnkpo7NVubS/vUGxBGz9m9jK4DZxvsGsD+3tfdQJtFC6r9QhFEHu+ON8OmxlXntuJqyQBCHi1Fvb2aodxn/CXmods9DNs7M3/EmxOHtdOWnsnElEWc8h/V28IPu8tPrPKJXAUffE2Ww683G08vcy4DwPGf0iDKYA/6HA/L5z8vZdTbOWBQ6FT08MOk20tQFommW/Sh5/hnYvd1mNsX9zMZUGgFYfGtk+78FMUct7CjgOBA4m/v2L3RZV4K/bn+5j69WphIi9zLL+Ge34nELs5EtXoXgTgd3dQeXtP4MXGn/fhvKeJGZq7YlQ/GIYdSRe7ZoX+1gr25hhxMtSbKmSiv1XGMbypwGWMTMNPMZ/cbk+cfE1T+7bFy9vsllsinB0q+F3H3gLzDLzeizJrjJOxDHUuiJR08cQ2+xVjXFew7Vx+C2LzRxx5eN59J3SfvvO7GHu9jGpf3TY/UZZO7PTZDxP8DuWOhkc7Rtwa29C2fH27hcei3xrpgPbrxHcCuVLK3AOepXnn87B3Ojfqau3zk2kWLtv/PAXbBUcvUzvWjLkmWvRexZ7ng3Xo398rLM/eT7H7znTHJG08pUNZX7M439YBbcgzVXv4z6qJxqCI8Y6S+hY+ppI0kZRVEJc1/O0v4FefjwD/MwonAPhjyIsh9yL/wB+8uebZ4t2lc7mEe/I5ksZ0IKGVeAF+nnsfn8yfMv52IPqp/JqksQsn4MbqepPuvj/vooQwwsway7DzEVzcwoQRmZr4E5VL5/yqs0bQWH/488/+J+nDFiYiKsX86ZMv45mEebmRk1rXuEM5xNJLjFD+CsNTM3HachKZ5pYOg30v8B3LVNXGyoZzPawYoMbGn/Pc94usLG1g/ynEL/D6UTHHxp/w3+AXZ+XG3j2C+X8c8fxDlYb1u5XPF8pP0fuG9ZuWjafNy8h7C/YOPqGmZGedvBndll5ippWv6y+BTJ9x+4byyycFtUxnOnkg+jTXVamLThnns9klz/gVlj6T+aGW9cDTPEZpLvv0dgf2Picp0FKt9/YM5eamImsyy2jPL99yhsCxdamGkOfzDp/wnmXLOc+lso9+9cef7hY4iZ0GVmJljWmPL8QzD3MpUt17gvmBs/jvWHaRzk1pXMAHOZiQlVGHtcoTWfgI2ouV6pJWkb6Zz+06eBm2eu28bBmdOs+qTx9BgLe/DmNNPAX9XC559b9ILb97aZy/+Ojz2FWC/9bQwb9yGWs2Tk+Yfgfm6Sl0sXJ88/fNp4uthUt3okOuY9lNfAnWThKvXZhgaW+JfS/vkZnNdjfhc=
*/