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
#include <boost/detail/iterator.hpp>             // boost::iterator_traits.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/mpl/if.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

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
    typedef boost::detail::iterator_traits<iterator>  iter_traits;
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