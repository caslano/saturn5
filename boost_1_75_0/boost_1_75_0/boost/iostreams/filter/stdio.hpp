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
IgIhP7UHKW5UxsbyfpzunjB8Cr61Q+7JIN7Y+kRKj0mgzbHNzfvCoKmKKkiQmIvxGkDnKdNpXAzmJ/nXrp9kzlFjlB/A/gBIHTXuZstHYhC7+GarNPbyCIYSWWEZtebOCERmRZ8PW3MHZN3eMu3sFS6eag4Gu272y7Kvgj83cRDC7/tDRIVWIRPbgb04YZ/g4CDnLoo3oCkKWOTkHz+xdm+saW05/aMKQZtL2JC39iA2M+GoanLFlkal4nNniNV1wEMQJcj5FpIYpCc5n2DLx32ILtrPwPN6qLxOqTh6TncM+Xq/C0l6/2C5+lWQCtFLpFf/YzWKqkqoPWuUr+CPgltEaZ5rs1dbP48cgDD40wICgn89dAZDg9bagfePidWQzIy+fo7ntiZsa2/rCPXe9uDtV20an8OwZ24SM2GnNO7vGvkDZ56/TTxuTjr+LHULr7XEgza4C5EV0JBcIznWf9r17RuCZE5zlBf93PQB/sVOjRE5q19Upzzl9nLltFDQZncUqn9IxEQw1BxNoXH+kXfDasRWbgzdpkqJXQdqM4g42+w/MzLe1xG7pbmVvcpzexBPYOHACmIG1qYCBFmAGzCw3UYB4bxnYSGueUNXh60zJSb3E0xbBLuF6OP5bbqDWPcs1BfQkWxs6W6hjZ2iWttcw2ewu9NfDeYXw1GzO9CVV8pZU+MJ9zxK4RF7XqJw3+rlKQO+BK9IJOnd
*/