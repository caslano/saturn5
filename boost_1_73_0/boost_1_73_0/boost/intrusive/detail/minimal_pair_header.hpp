/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP
#define BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#//Try to avoid including <utility>, as it's quite big in C++11
#if defined(BOOST_GNU_STDLIB)
#  include <bits/stl_pair.h>
#else
#  include <utility>    //Fallback
#endif
#
#endif //BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP

/* minimal_pair_header.hpp
BQjZYjVCKUYFrc+KK4yiizzIhVp2wdhNiZmGVXqRxlOCduXRXdDuEPF+uxwAL/hjlEy8Kb+wEDK0JNxBCw9D/aYn3EpIoUuCbJuCYcUbLOyj261v972xNLocdVvULVUt9mM3tGoFgLL6Q55ry/B8FNVt68svFJb5i9dCS+YlkOnobU9fuRdrPBd+ClxTZK0DWr1Ggsijrm/f5wZ8DwjECcRVD3GK9Tp3gnDOHfLpP5Ffg29sW19vHBAGqKtvJIWVJEoK9zG6L7Y5/TPpEdR0vHW/9i+xexS8xqtoYeqgjCxHqWbh947gvOC84DwjqOi/bT+dHvwOMMdlRPJhWFLbwIEp1vkUI1qBEeXPaFBqmHBSGawKpl1yS5W4IFQvMftCpCkiTalemsICsjD4inoCjb92y85YkuUh/dt2VzbAFrfUzS770GqumDspLYUx6q3SeUnwWfC54nw2vB/g1LV/SkgfzIVg2OMPE8aFV9N7lY/24d/pKo7uES1wWB4SWRpyx7kB3wOCyoLKFadymA1TdbnXtYlVwlfT4esYjyeRH2hkYbLwKadPeR+sI5TkJf0w5lGQPdhCft2f2EEZqZ/gory9IzICkRGIjKCkb4yTL/FjBBvvG2POIn0xzBUaZtbcp5iFgiM9Z8tljmGh
*/