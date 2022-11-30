// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_MINMAX_HEAP_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_MINMAX_HEAP_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#ifdef _MSC_VER // msvc and clang-win
#include <intrin.h>
#endif

namespace boost { namespace geometry { namespace index { namespace detail
{

// Resources:
// https://en.wikipedia.org/wiki/Min-max_heap
// http://akira.ruc.dk/~keld/teaching/algoritmedesign_f03/Artikler/02/Atkinson86.pdf
// https://probablydance.com/2020/08/31/on-modern-hardware-the-min-max-heap-beats-a-binary-heap/
// https://stackoverflow.com/questions/6531543/efficient-implementation-of-binary-heaps
// https://stackoverflow.com/questions/994593/how-to-do-an-integer-log2-in-c

namespace minmax_heap_detail
{

template <typename T>
using bitsize = std::integral_constant<std::size_t, sizeof(T) * CHAR_BIT>;

template <typename It>
using diff_t = typename std::iterator_traits<It>::difference_type;
template <typename It>
using val_t = typename std::iterator_traits<It>::value_type;

// TODO: In C++20 use std::bit_width()

template <typename T, std::enable_if_t<!std::is_integral<T>::value || (bitsize<T>::value != 32 && bitsize<T>::value != 64), int> = 0>
inline int level(T i)
{
    ++i;
    int r = 0;
    while (i >>= 1) { ++r; }
    return r;
}

//template <typename T>
//inline int level(T i)
//{
//    using std::log2;
//    return int(log2(i + 1));
//}

#ifdef _MSC_VER // msvc and clang-win

template <typename T, std::enable_if_t<std::is_integral<T>::value && bitsize<T>::value == 32, int> = 0>
inline int level(T i)
{
    unsigned long r = 0;
    _BitScanReverse(&r, (unsigned long)(i + 1));
    return int(r);
}

template <typename T, std::enable_if_t<std::is_integral<T>::value && bitsize<T>::value == 64, int> = 0>
inline int level(T i)
{
    unsigned long r = 0;
#ifdef _WIN64
    _BitScanReverse64(&r, (unsigned long long)(i + 1));
#else
    if (_BitScanReverse(&r, (unsigned long)((i + 1) >> 32))) { r += 32; }
    else { _BitScanReverse(&r, (unsigned long)(i + 1)); }
#endif
    return int(r);
}

#elif defined(__clang__) || defined(__GNUC__)
// Only available in gcc-10 and clang-10
//#elif defined(__has_builtin) && __has_builtin(__builtin_clzl) && __has_builtin(__builtin_clzll)

template <typename T, std::enable_if_t<std::is_integral<T>::value && bitsize<T>::value == 32, int> = 0>
inline int level(T i)
{
    return 31 - __builtin_clzl((unsigned long)(i + 1));
}

template <typename T, std::enable_if_t<std::is_integral<T>::value && bitsize<T>::value == 64, int> = 0>
inline int level(T i)
{
    return 63 - __builtin_clzll((unsigned long long)(i + 1));
}

#else

template <typename T, std::enable_if_t<std::is_integral<T>::value && bitsize<T>::value == 32, int> = 0>
inline int level(T i)
{
    ++i;
    int r = 0;
    if (i >= 65536) { r += 16; i >>= 16; }
    if (i >= 256) { r += 8; i >>= 8; }
    if (i >= 16) { r += 4; i >>= 4; }
    if (i >= 4) { r += 2; i >>= 2; }
    if (i >= 2) { r += 1; i >>= 1; }
    return r;
}

template <typename T, std::enable_if_t<std::is_integral<T>::value && bitsize<T>::value == 64, int> = 0>
inline int level(T i)
{
    ++i;
    int r = 0;
    if (i >= 4294967296ll) { r += 32; i >>= 32; }
    if (i >= 65536ll) { r += 16; i >>= 16; }
    if (i >= 256ll) { r += 8; i >>= 8; }
    if (i >= 16ll) { r += 4; i >>= 4; }
    if (i >= 4ll) { r += 2; i >>= 2; }
    if (i >= 2ll) { r += 1; i >>= 1; }
    return r;
}

#endif


// min/max functions only differ in the order of arguments in comp
struct min_call
{
    template <typename Compare, typename T1, typename T2>
    bool operator()(Compare&& comp, T1 const& v1, T2 const& v2) const
    {
        return comp(v1, v2);
    }
};

struct max_call
{
    template <typename Compare, typename T1, typename T2>
    bool operator()(Compare&& comp, T1 const& v1, T2 const& v2) const
    {
        return comp(v2, v1);
    }
};


template <typename Call, typename It, typename Compare>
inline void push_heap2(It first, diff_t<It> c, val_t<It> val, Compare comp)
{
    while (c > 2)
    {
        diff_t<It> const g = (c - 3) >> 2; // grandparent index
        if (! Call()(comp, val, *(first + g)))
        {
            break;
        }
        *(first + c) = std::move(*(first + g));
        c = g;
    }

    *(first + c) = std::move(val);
}

template <typename MinCall, typename MaxCall, typename It, typename Compare>
inline void push_heap1(It first, diff_t<It> c, val_t<It> val, Compare comp)
{
    diff_t<It> const p = (c - 1) >> 1; // parent index
    if (MinCall()(comp, *(first + p), val))
    {
        *(first + c) = std::move(*(first + p));
        return push_heap2<MaxCall>(first, p, std::move(val), comp);
    }
    else
    {
        return push_heap2<MinCall>(first, c, std::move(val), comp);
    }
}

template <typename MinCall, typename MaxCall, typename It, typename Compare>
inline void push_heap(It first, It last, Compare comp)
{
    diff_t<It> const size = last - first;
    if (size < 2)
    {
        return;
    }

    diff_t<It> c = size - 1; // back index
    val_t<It> val = std::move(*(first + c));
    if (level(c) % 2 == 0) // is min level
    {
        push_heap1<MinCall, MaxCall>(first, c, std::move(val), comp);
    }
    else
    {
        push_heap1<MaxCall, MinCall>(first, c, std::move(val), comp);
    }
}


template <typename Call, typename It, typename Compare>
inline diff_t<It> pick_grandchild4(It first, diff_t<It> f, Compare comp)
{
    It it = first + f;
    diff_t<It> m1 = Call()(comp, *(it), *(it + 1)) ? f : f + 1;
    diff_t<It> m2 = Call()(comp, *(it + 2), *(it + 3)) ? f + 2 : f + 3;
    return Call()(comp, *(first + m1), *(first + m2)) ? m1 : m2;
}

//template <typename Call, typename It, typename Compare>
//inline diff_t<It> pick_descendant(It first, diff_t<It> f, diff_t<It> l, Compare comp)
//{
//    diff_t<It> m = f;
//    for (++f; f != l; ++f)
//    {
//        if (Call()(comp, *(first + f), *(first + m)))
//        {
//            m = f;
//        }
//    }
//    return m;
//}

template <typename Call, typename It, typename Compare>
inline void pop_heap1(It first, diff_t<It> p, diff_t<It> size, val_t<It> val, Compare comp)
{
    if (size >= 7) // grandparent of 4 grandchildren is possible
    {
        diff_t<It> const last_g = (size - 3) >> 2; // grandparent of the element behind back
        while (p < last_g) // p is grandparent of 4 grandchildren
        {
            diff_t<It> const ll = 4 * p + 3;
            diff_t<It> const m = pick_grandchild4<Call>(first, ll, comp);

            if (! Call()(comp, *(first + m), val))
            {
                break;
            }

            *(first + p) = std::move(*(first + m));

            diff_t<It> par = (m - 1) >> 1;
            if (Call()(comp, *(first + par), val))
            {
                using std::swap;
                swap(*(first + par), val);
            }

            p = m;
        }
    }
    
    if (size >= 2 && p <= ((size - 2) >> 1)) // at least one child
    {
        diff_t<It> const l = 2 * p + 1;
        diff_t<It> m = l; // left child
        if (size >= 3 && p <= ((size - 3) >> 1)) // at least two children
        {
            // m = left child
            diff_t<It> m2 = l + 1; // right child
            if (size >= 4 && p <= ((size - 4) >> 2)) // at least two children and one grandchild
            {
                diff_t<It> const ll = 2 * l + 1;
                m = ll; // left most grandchild
                // m2 = right child
                if (size >= 5 && p <= ((size - 5) >> 2)) // at least two children and two grandchildren
                {
                    m = Call()(comp, *(first + ll), *(first + ll + 1)) ? ll : (ll + 1); // greater of the left grandchildren
                    // m2 = right child
                    if (size >= 6 && p <= ((size - 6) >> 2)) // at least two children and three grandchildren
                    {
                        // m = greater of the left grandchildren
                        m2 = ll + 2; // third grandchild
                    }
                }
            }

            m = Call()(comp, *(first + m), *(first + m2)) ? m : m2;
        }

        if (Call()(comp, *(first + m), val))
        {
            *(first + p) = std::move(*(first + m));

            if (m >= 3 && p <= ((m - 3) >> 2)) // is p grandparent of m
            {
                diff_t<It> par = (m - 1) >> 1;
                if (Call()(comp, *(first + par), val))
                {
                    using std::swap;
                    swap(*(first + par), val);
                }
            }

            p = m;
        }
    }
    
    *(first + p) = std::move(val);
}

template <typename MinCall, typename MaxCall, typename It, typename Compare>
inline void pop_heap(It first, It el, It last, Compare comp)
{
    diff_t<It> size = last - first;
    if (size < 2)
    {
        return;
    }
    
    --last;
    val_t<It> val = std::move(*last);
    *last = std::move(*el);

    // Ignore the last element
    --size;
    
    diff_t<It> p = el - first;
    if (level(p) % 2 == 0) // is min level
    {
        pop_heap1<MinCall>(first, p, size, std::move(val), comp);
    }
    else
    {
        pop_heap1<MaxCall>(first, p, size, std::move(val), comp);
    }
}

template <typename MinCall, typename MaxCall, typename It, typename Compare>
inline void make_heap(It first, It last, Compare comp)
{
    diff_t<It> size = last - first;
    diff_t<It> p = size / 2;
    if (p <= 0)
    {
        return;
    }

    int level_p = level(p - 1);
    diff_t<It> level_f = (diff_t<It>(1) << level_p) - 1;
    while (p > 0)
    {
        --p;
        val_t<It> val = std::move(*(first + p));
        if (level_p % 2 == 0) // is min level
        {
            pop_heap1<MinCall>(first, p, size, std::move(val), comp);
        }
        else
        {
            pop_heap1<MaxCall>(first, p, size, std::move(val), comp);
        }

        if (p == level_f)
        {
            --level_p;
            level_f >>= 1;
        }
    }
}

template <typename Call, typename It, typename Compare>
inline bool is_heap(It first, It last, Compare comp)
{
    diff_t<It> const size = last - first;
    diff_t<It> pow2 = 4;
    bool is_min_level = false;
    for (diff_t<It> i = 1; i < size; ++i)
    {
        if (i == pow2 - 1)
        {
            pow2 *= 2;
            is_min_level = ! is_min_level;
        }

        diff_t<It> const p = (i - 1) >> 1;
        if (is_min_level)
        {
            if (Call()(comp, *(first + p), *(first + i)))
            {
                return false;
            }
        }
        else
        {
            if (Call()(comp, *(first + i), *(first + p)))
            {
                return false;
            }
        }

        if (i >= 3)
        {
            diff_t<It> const g = (p - 1) >> 1;
            if (is_min_level)
            {
                if (Call()(comp, *(first + i), *(first + g)))
                {
                    return false;
                }
            }
            else
            {
                if (Call()(comp, *(first + g), *(first + i)))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

template <typename Call, typename It, typename Compare>
inline It bottom_heap(It first, It last, Compare comp)
{
    diff_t<It> const size = last - first;
    return size <= 1 ? first :
           size == 2 ? (first + 1) :
           Call()(comp, *(first + 1), *(first + 2)) ? (first + 2) : (first + 1);
}

} // namespace minmax_heap_detail


template <typename It, typename Compare>
inline void push_minmax_heap(It first, It last, Compare comp)
{
    using namespace minmax_heap_detail;
    minmax_heap_detail::push_heap<min_call, max_call>(first, last, comp);
}

template <typename It>
inline void push_minmax_heap(It first, It last)
{
    using namespace minmax_heap_detail;
    minmax_heap_detail::push_heap<min_call, max_call>(first, last, std::less<>());
}

template <typename It, typename Compare>
inline void pop_top_minmax_heap(It first, It last, Compare comp)
{
    using namespace minmax_heap_detail;
    pop_heap<min_call, max_call>(first, first, last, comp);
}

template <typename It>
inline void pop_top_minmax_heap(It first, It last)
{
    using namespace minmax_heap_detail;
    pop_heap<min_call, max_call>(first, first, last, std::less<>());
}

template <typename It, typename Compare>
inline void pop_bottom_minmax_heap(It first, It last, Compare comp)
{
    using namespace minmax_heap_detail;
    It bottom = minmax_heap_detail::bottom_heap<min_call>(first, last, comp);
    pop_heap<min_call, max_call>(first, bottom, last, comp);
}

template <typename It>
inline void pop_bottom_minmax_heap(It first, It last)
{
    using namespace minmax_heap_detail;
    auto&& comp = std::less<>();
    It bottom = minmax_heap_detail::bottom_heap<min_call>(first, last, comp);
    pop_heap<min_call, max_call>(first, bottom, last, comp);
}

template <typename It, typename Compare>
inline void make_minmax_heap(It first, It last, Compare comp)
{
    using namespace minmax_heap_detail;
    return minmax_heap_detail::make_heap<min_call, max_call>(first, last, comp);
}

template <typename It>
inline void make_minmax_heap(It first, It last)
{
    using namespace minmax_heap_detail;
    return minmax_heap_detail::make_heap<min_call, max_call>(first, last, std::less<>());
}

template <typename It, typename Compare>
inline bool is_minmax_heap(It first, It last, Compare comp)
{
    using namespace minmax_heap_detail;
    return minmax_heap_detail::is_heap<min_call>(first, last, comp);
}

template <typename It>
inline bool is_minmax_heap(It first, It last)
{
    using namespace minmax_heap_detail;
    return minmax_heap_detail::is_heap<min_call>(first, last, std::less<>());
}

template <typename It, typename Compare>
inline decltype(auto) bottom_minmax_heap(It first, It last, Compare comp)
{
    using namespace minmax_heap_detail;
    return *minmax_heap_detail::bottom_heap<min_call>(first, last, comp);
}

template <typename It>
inline decltype(auto) bottom_minmax_heap(It first, It last)
{
    using namespace minmax_heap_detail;
    return *minmax_heap_detail::bottom_heap<min_call>(first, last, std::less<>());
}


}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_MINMAX_HEAP_HPP

/* minmax_heap.hpp
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
*/