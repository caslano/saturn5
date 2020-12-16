// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_IMBUE_HPP_INCLUDED
#define BOOST_IOSTREAMS_IMBUE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams { 

namespace detail {

// Implementation templates for simulated tag dispatch.
template<typename T> 
struct imbue_impl;

} // End namespace detail.

template<typename T, typename Locale>
void imbue(T& t, const Locale& loc)
{ detail::imbue_impl<T>::imbue(detail::unwrap(t), loc); }

namespace detail {

//------------------Definition of imbue_impl----------------------------------//

template<typename T>
struct imbue_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          imbue_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, streambuf_tag, localizable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct imbue_impl<any_tag> {
    template<typename T, typename Locale>
    static void imbue(T&, const Locale&) { }
};

template<>
struct imbue_impl<streambuf_tag> {
    template<typename T, typename Locale>
    static void imbue(T& t, const Locale& loc) { t.pubimbue(loc); }
};

template<>
struct imbue_impl<localizable_tag> {
    template<typename T, typename Locale>
    static void imbue(T& t, const Locale& loc) { t.imbue(loc); }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_IMBUE_HPP_INCLUDED

/* imbue.hpp
U/tP1vngWciiJMd8Nmnfh9d/fvLShMfLlXxtTi974XKPtVxVmPxUuNz2ltDcL7ToGDW2yhNz3o1IeMKV+9sZIX6l+ES+99CcaxVT3pk5vt2rM97egMHtAorPSyvWtJymKr+1GNDg5ZHfNuiH9JL7uTnRS2vsGHltysXVb05dXe7PeAOSPJqxd8SMny/c9eG+p++Nij3WcFthcljx5TlrufPWyc0XtTquvyP5vTwX1p/rHAzJTRrTwVLgULCsdh0sBw4CK/HvGHAEWI1/V+f74sFMsB671wczwCb8W4vHSuOdgncsxyMYdh6svj+qdq00GAiWAbXrZcHKYDl+Xh2wBsuncSyfNgargC1ZPm0LVgNTWE7tw/JpP7AWOAaMA8eB8eBkLVyOZ67ez4HHOJ5avuzneDbgeCaA5cHmHL8WYFWWZ2uDLcE6LNc2BFuDd/P1FuD9HN+OYBswCRwEprJ83Qacyb9ngd3Ax8Hu4FNgCriRr78K9ga3gX3A99l9O3g3+DXYFPyW3bW+pRIWOzaDHQy7CHYP7DXY2pDpesPOg80r6xWQ80jGWwaa5bwt+H0Q3A0egdVlvlDIdlVgW8Lq8l/XhIIy4FaWA/3uxu8kPA9MgE2E7Q2bBTsHdm0+GfE0OA+8AmqyYizLi31ZZswGN8JqsmMOmAt7ATa/HJkFxoJzQF2WXIa/18Huhr2k+WuGeMHGsoyZBpvFsua8fPLmJZPMqTYvKHdGw602rC5/NmvulUGHg9mwZln0YF551JBFo/A7FrYZbFdYXTadBS6C3QK7G/ZIIbJqS5ZXM2CzYefCroTNYRl2L5gLm/Yd9iyCXfudT571GZ+5HeYOyf/wrIn/f1z336ikMGSqHbz3359ZvFrHMnRQI0sZukuXxHHxdQrKVIYuphndF2AlYyHMostYQY2KLjfDr6VM5f12BqTrKzAekcW9iMkS0EKuQjgWshLLxml0rYvogPvNclFZls3D6PqLGONIGLcooj24EtYsZ4dzHnUgv0M1fadIh98QyDYKyzYfhpMtINcE3Wa5xixnD+b9H35hOfsqy9kXGlnL2VwriiRnXyhGHbhgXQeMOZuYxtr1ElZ1gu8tXM7+ma5fQj5LGG8tt6oPCKPocvaFgnXHkIXrUjznieZI1WDYScJhrkNGeqaSP1mU5TjG0+9nRTv8mwT30eA0C3lb+7O67hfhj4adrn9bC9e9dC3E9MxhxhxAZ7pWU1TEPZGohzaqhz45u7hy9oskZy/avGLV6QEj/vLkqodO7D/84wSfnP2fLGfv1vt8fv/NhQ2H3ZpPvg1nubYky42lWJ6uB8ayvFs7nz62Pcu7SeyvM8u9Kfn0sqNY3s3i62NZPzuR5d6ZLOcuA+uCazi8l1heXse/L/K3ihc4Pb9wesrCXuP0NOL0NAXd4D1gCZZvy7H8W5HnFyqxfNwcbMPyb1uWe9uBHfl3V5aLHwA7g/3BLuBg/j0STAYzWQ6ew+H/ieXfeeAD4BKWg1/j65vBfiwXDwB3svsHYAfwKP/O5fj/zPG/yu4JPnnZJy//Dnk5+owq2pzxyco+4zM+80/2zgO+iiIN4LPvvYQAAUJIQqiGjoAQpPfeUVDgBBEJkFCkJKZQFJWmgiJydyqgqKioKKiIqNixo+cpenqHngXbHSqeiqiI3nn//d63m00ygaCe17L5Tf5vZ76Znb6zU8t2/VLf/zOmzflZxv+7uXN59VsvVau6Bk70m6ce7NbE/fjwvvXkucHvtQU5Wcb/fhgtcoP5fqhi+95Td5zAflezbd96Khc8A2D2RD4EbN92vmyi/72JF2Wat32Of1C+wJPHcfs8f1+++NxZfw55NTGv6vQghGc=
*/