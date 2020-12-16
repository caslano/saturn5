
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_DATA_H
#define BOOST_COROUTINES_DETAIL_DATA_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/coroutine_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct data_t
{
    coroutine_context   *   from;
    void                *   data;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_DATA_H

/* data.hpp
LahJXCPF6JKNKcpyEUGRH2BGp6ziWY9DxwKBJ1tyQiJ1CWsMMMd4/vqNpT7KI20r21ZsYduKLWxbsYVtK7bwycUWPrnYwicXW8hlsYUcFV/EmSu/T/Yfd7Ln5nW1V5KdBRV8QYXzVP7thfK3P+iILRTPlFjwqcSCTyUhfJLqRQRodbUg7ZLmAXtVTzFpMp9MWjzr/ib61lMEaTLvSix4V3IRvAucVzNeghXCuxUy70J4U2rBm1IL3pSG8sakDWF+3zM/VMukDYXWkbx4vEQbLtMs/GNpZf8o1ZP9Y6mFfyy18I+lFv6x1MI/lob6R5OWLI+5ss5ItOuMendLNNmPllbWLYk2zqKPLAua3YKWe21gPSbFBWmFBm2KRJturNF4IfHKoK2UaGug3UEf2fI8DFonifahQZPn8aVBu02i/WL0MUuiyRih1AIjlFbGCBLtrMGDiVJ7VQYEaH+SaJL/NmnVLOrVMGh9JFrzAYExXyvRrjbqzZBosp8vDfXpJq2N0V476V5J/01auwEB/snyItuE0ovY13HkZ3pdxjsRdWcciq93y/7YjG87MwabHl0HI9ry1x4EXrj+XagNcVvYELeFDXGH2hCTFka/rzL3uSJIk22D28I2uC1sg9vCNrgtbIPbwja4LWyD28I2uEP0W+KBxTx6yDQL7Oy20Au3hV64LfTCHYp/TVpvuV8LvXBbyLHbQo7dlWVWqhcN7Uv6aCr10U/ut7IcG/emXKAcm7HoedI/1vL9oyTfoTLrsZBZj4XMeixk1mPh6z0WPPJYzN1zEXF4ObaWklIW59FFhOnfJawZPeDC8lqV+eK14Is3lC8mbQD9NMUxsNwmTeaV10KXvRa67LXQZa+FLnstdNlrocteC132Wuiy18Kney3022vhv70Weuu10Fuvhd56LfTRa6GPXgt99FrImtdC1rwX4S/cXnumLhz6fre1PjWLOJ8++SzkxmchNz4LGfFZyIjPQkZ8FjLis5ARn4WM+CxkxGchIz4LGfFZyIjPQkZ8FjLis7D3Pgu58VnIjc9CbnwW9t5nIUs+C1nyWciSz0KWfBay5Ps7cgLBANt9Dhvd47wyVWYhU2UWMlVmIVNlFja6zGKuZRZzLbsIG+2PWwMxqBmAhc7z2girXLJ1/MpGbomQz2AYdQJXAzU9NgfAzG135Fg9ezMtVHcMmqw7Jk3WHYMm645Jk3XHpMm6M+0i+FYhD+zx+rI9VjnmoZJ8VN7r95TfaYMTITvxXc9d1+rUx8kLrZ/jMOqbe+Ah9S12xInlL6Z+8NQC95lyUPm+cx/FsNCl6Ra6NN1Cl6aH6pJJGzwgQHvk2iAtwaDdJNFknZtuoXPTLXRu+kXkO/w6p7+nK5AqqiQz11fQNfH/f///9/9////3/3////df+q8G+wyne6oi9gVF5N+oCk++Kkq2qOJ9Plw2qJciXsxSxOcdQZnf8u6+Pyviz4vxvQ00sfIvilixUBU/bFPEuzdrwv6NJn6pq4ghnVSx6idF3EUdZ1NF1Kb9JpQOlLaUEZSnrlHFnARFLFuhifk1NDF6niqWPaWKq99UxU48bH327dKpdz1lDMVGGUvJoyRQkiiZlHGU+ZQHKY9Q5lDuo8yjLKI8THmXspnyPmUn5RPKPspWyqwHNaGt1MRlT/F++2s0sZRNy/Ao9sbYTHm+UBOJjOej4YpYtZa+L9FEB7sm5u3mfZiLVLHyak1EDuHsw42BNhOuZG6UveCSXgWq2JejiMfvV8TaA6rY0lQV7zgYxxr2T8NVMZCNnl+3KyL3BN8gaq2IW3JVseJxTczk/rlzmNNkziyeUETqLr4V3lMRyZNUsYEc77FC1f/t346/ayI=
*/