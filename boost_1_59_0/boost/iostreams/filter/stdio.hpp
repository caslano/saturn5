// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Based on the work of Christopher Diggins.

#ifndef BOOST_IOSTREAMS_STDIO_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_STDIO_FILTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <iostream>
#include <memory>    // allocator.
#include <vector>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/aggregate.hpp>
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/stream_buffer.hpp>

namespace boost { namespace iostreams {

namespace detail {

} // End namespace detail.

template<typename Ch, typename Alloc = std::allocator<Ch> >
class basic_stdio_filter : public aggregate_filter<Ch, Alloc> {
private:
    typedef aggregate_filter<Ch, Alloc>       base_type;
public:
    typedef typename base_type::char_type    char_type;
    typedef typename base_type::category     category;
    typedef typename base_type::vector_type  vector_type;
private:
    static std::istream& standard_input(char*) { return std::cin; }
    static std::ostream& standard_output(char*) { return std::cout; }
#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
    static std::wistream& standard_input(wchar_t*) { return std::wcin; }
    static std::wostream& standard_output(wchar_t*) { return std::wcout; }
#endif // BOOST_IOSTREAMS_NO_WIDE_STREAMS

    struct scoped_redirector { // Thanks to Maxim Egorushkin.
        typedef BOOST_IOSTREAMS_CHAR_TRAITS(Ch)                  traits_type;
        typedef BOOST_IOSTREAMS_BASIC_IOS(Ch, traits_type)       ios_type;
        typedef BOOST_IOSTREAMS_BASIC_STREAMBUF(Ch, traits_type) streambuf_type;
        scoped_redirector( ios_type& ios,
                           streambuf_type* newbuf )
            : ios_(ios), old_(ios.rdbuf(newbuf))
            { }
        ~scoped_redirector() { ios_.rdbuf(old_); }
        scoped_redirector& operator=(const scoped_redirector&);
        ios_type&        ios_;
        streambuf_type*  old_;
    };

    virtual void do_filter() = 0;
    virtual void do_filter(const vector_type& src, vector_type& dest)
    {
        stream_buffer< basic_array_source<Ch> >
                          srcbuf(&src[0], &src[0] + src.size());
        stream_buffer< back_insert_device<vector_type> >
                          destbuf(iostreams::back_inserter(dest));
        scoped_redirector redirect_input(standard_input((Ch*)0), &srcbuf);
        scoped_redirector redirect_output(standard_output((Ch*)0), &destbuf);
        do_filter();
    }
};
BOOST_IOSTREAMS_PIPABLE(basic_stdio_filter, 2)

typedef basic_stdio_filter<char>     stdio_filter;
typedef basic_stdio_filter<wchar_t>  wstdio_wfilter;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_STDIO_FILTER_HPP_INCLUDED

/* stdio.hpp
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
*/