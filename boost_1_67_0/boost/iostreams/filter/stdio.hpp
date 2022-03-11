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