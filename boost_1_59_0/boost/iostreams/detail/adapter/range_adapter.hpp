// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_RANGE_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_RANGE_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <algorithm>                             // min.
#include <boost/assert.hpp>
#include <cstddef>                               // ptrdiff_t.
#include <iosfwd>                                // streamsize, streamoff.
#include <iterator>                              // iterator_traits.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/mpl/if.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/core/enable_if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams { namespace detail {

// Used for simulated tag dispatch.
template<typename Traversal> struct range_adapter_impl;

//
// Template name: range_adapter
// Description: Device based on an instance of boost::iterator_range.
// Template parameters:
//     Mode - A mode tag.
//     Range - An instance of iterator_range.
//
template<typename Mode, typename Range>
class range_adapter {
private:
    typedef typename Range::iterator                  iterator;
    typedef std::iterator_traits<iterator>            iter_traits;
    typedef typename iter_traits::iterator_category   iter_cat;
public:
    typedef typename Range::value_type                char_type;
    struct category : Mode, device_tag { };
    typedef typename
            mpl::if_<
                is_convertible<
                    iter_cat,
                    std::random_access_iterator_tag
                >,
                std::random_access_iterator_tag,
                std::forward_iterator_tag
            >::type                                   tag;
    typedef range_adapter_impl<tag>                   impl;

    explicit range_adapter(const Range& rng);
    range_adapter(iterator first, iterator last);
    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    std::streampos seek(stream_offset off, BOOST_IOS::seekdir way);
private:
    iterator first_, cur_, last_;
};

//------------------Implementation of range_adapter---------------------------//

template<typename Mode, typename Range>
range_adapter<Mode, Range>::range_adapter(const Range& rng)
    : first_(rng.begin()), cur_(rng.begin()), last_(rng.end()) { }

template<typename Mode, typename Range>
range_adapter<Mode, Range>::range_adapter(iterator first, iterator last)
    : first_(first), cur_(first), last_(last) { }

template<typename Mode, typename Range>
inline std::streamsize range_adapter<Mode, Range>::read
    (char_type* s, std::streamsize n)
{ return impl::read(cur_, last_, s, n); }

template<typename Mode, typename Range>
inline std::streamsize range_adapter<Mode, Range>::write
    (const char_type* s, std::streamsize n)
{ return impl::write(cur_, last_, s, n); }


template<typename Mode, typename Range>
std::streampos range_adapter<Mode, Range>::seek
    (stream_offset off, BOOST_IOS::seekdir way)
{ 
    impl::seek(first_, cur_, last_, off, way); 
    return offset_to_position(cur_ - first_);
}

//------------------Implementation of range_adapter_impl----------------------//

template<>
struct range_adapter_impl<std::forward_iterator_tag> {
    template<typename Iter, typename Ch>
    static std::streamsize read
        (Iter& cur, Iter& last, Ch* s,std::streamsize n)
    {
        std::streamsize rem = n; // No. of chars remaining.
        while (cur != last && rem-- > 0) *s++ = *cur++;
        return n - rem != 0 ? n - rem : -1;
    }

    template<typename Iter, typename Ch>
    static std::streamsize write
        (Iter& cur, Iter& last, const Ch* s, std::streamsize n)
    {
        while (cur != last && n-- > 0) *cur++ = *s++;
        if (cur == last && n > 0)
            boost::throw_exception(write_area_exhausted());
        return n;
    }
};

template<>
struct range_adapter_impl<std::random_access_iterator_tag> {
    template<typename Iter, typename Ch>
    static std::streamsize read
        (Iter& cur, Iter& last, Ch* s,std::streamsize n)
    {
        std::streamsize result = 
            (std::min)(static_cast<std::streamsize>(last - cur), n);
        if (result)
            std::copy(cur, cur + result, s);
        cur += result;
        return result != 0 ? result : -1;
    }

    template<typename Iter, typename Ch>
    static std::streamsize write
        (Iter& cur, Iter& last, const Ch* s, std::streamsize n)
    {
        std::streamsize count =
            (std::min)(static_cast<std::streamsize>(last - cur), n);
        std::copy(s, s + count, cur);
        cur += count;
        if (count < n) 
            boost::throw_exception(write_area_exhausted());
        return n;
    }

    template<typename Iter>
    static void seek
        ( Iter& first, Iter& cur, Iter& last, stream_offset off,
          BOOST_IOS::seekdir way )
    {
        using namespace std;
        switch (way) {
        case BOOST_IOS::beg:
            if (off > last - first || off < 0)
                boost::throw_exception(bad_seek());
            cur = first + off;
            break;
        case BOOST_IOS::cur:
            {
                std::ptrdiff_t newoff = cur - first + off;
                if (newoff > last - first || newoff < 0)
                    boost::throw_exception(bad_seek());
                cur += off;
                break;
            }
        case BOOST_IOS::end:
            if (last - first + off < 0 || off > 0)
                boost::throw_exception(bad_seek());
            cur = last + off;
            break;
        default:
            BOOST_ASSERT(0);
        }
    }
};

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_RANGE_ADAPTER_HPP_INCLUDED //---------------//

/* range_adapter.hpp
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
*/