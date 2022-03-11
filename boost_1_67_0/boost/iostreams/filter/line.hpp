// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_LINE_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_LINE_FILTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <algorithm>                               // min.
#include <boost/assert.hpp>
#include <memory>                                  // allocator.
#include <string>
#include <boost/config.hpp>                        // BOOST_STATIC_CONSTANT.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/checked_operations.hpp>
#include <boost/iostreams/detail/ios.hpp>          // openmode, streamsize.
#include <boost/iostreams/read.hpp>                // check_eof 
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/write.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> // VC7.1 C4244.

namespace boost { namespace iostreams {

//
// Template name: line_filter.
// Template parameters:
//      Ch - The character type.
//      Alloc - The allocator type.
// Description: Filter which processes data one line at a time.
//
template< typename Ch,
          typename Alloc = std::allocator<Ch> >
class basic_line_filter {
private:
    typedef typename std::basic_string<Ch>::traits_type  string_traits;
public:
    typedef Ch                                           char_type;
    typedef char_traits<char_type>                       traits_type;
    typedef std::basic_string<
                Ch,
                string_traits,
                Alloc
            >                                            string_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
protected:
    basic_line_filter(bool suppress_newlines = false) 
        : pos_(string_type::npos), 
          flags_(suppress_newlines ? f_suppress : 0) 
        { }
public:
    virtual ~basic_line_filter() { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        BOOST_ASSERT(!(flags_ & f_write));
        flags_ |= f_read;

        // Handle unfinished business.
        std::streamsize result = 0;
        if (!cur_line_.empty() && (result = read_line(s, n)) == n)
            return n;

        typename traits_type::int_type status = traits_type::good();
        while (result < n && !traits_type::is_eof(status)) {

            // Call next_line() to retrieve a line of filtered text, and
            // read_line() to copy it into buffer s.
            if (traits_type::would_block(status = next_line(src)))
                return result;
            result += read_line(s + result, n - result);
        }

        return detail::check_eof(result);
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        using namespace std;
        BOOST_ASSERT(!(flags_ & f_read));
        flags_ |= f_write;

        // Handle unfinished business.
        if (pos_ != string_type::npos && !write_line(snk))
            return 0;

        const char_type *cur = s, *next;
        while (true) {

            // Search for the next full line in [cur, s + n), filter it
            // and write it to snk.
            typename string_type::size_type rest = n - (cur - s);
            if ((next = traits_type::find(cur, rest, traits_type::newline()))) {
                cur_line_.append(cur, next - cur);
                cur = next + 1;
                if (!write_line(snk))
                    return static_cast<std::streamsize>(cur - s);
            } else {
                cur_line_.append(cur, rest);
                return n;
            }
        }
    }

    template<typename Sink>
    void close(Sink& snk, BOOST_IOS::openmode which)
    {
        if ((flags_ & f_read) && which == BOOST_IOS::in)
            close_impl();

        if ((flags_ & f_write) && which == BOOST_IOS::out) {
            try {
                if (!cur_line_.empty())
                    write_line(snk);
            } catch (...) {
                try {
                    close_impl();
                } catch (...) { }
                throw;
            }
            close_impl();
        }
    }
private:
    virtual string_type do_filter(const string_type& line) = 0;

    // Copies filtered characters fron the current line into
    // the given buffer.
    std::streamsize read_line(char_type* s, std::streamsize n)
    {
        using namespace std;
        std::streamsize result =
            (std::min) (n, static_cast<std::streamsize>(cur_line_.size()));
        traits_type::copy(s, cur_line_.data(), result);
        cur_line_.erase(0, result);
        return result;
    }

    // Attempts to retrieve a line of text from the given source; returns
    // an int_type as a good/eof/would_block status code.
    template<typename Source>
    typename traits_type::int_type next_line(Source& src)
    {
        using namespace std;
        typename traits_type::int_type c;
        while ( traits_type::is_good(c = iostreams::get(src)) &&
                c != traits_type::newline() )
        {
            cur_line_ += traits_type::to_int_type(c);
        }
        if (!traits_type::would_block(c)) {
            if (!cur_line_.empty() || c == traits_type::newline())
                cur_line_ = do_filter(cur_line_);
            if (c == traits_type::newline() && (flags_ & f_suppress) == 0)
                cur_line_ += c;
        }
        return c; // status indicator.
    }

    // Filters the current line and attemps to write it to the given sink.
    // Returns true for success.
    template<typename Sink>
    bool write_line(Sink& snk)
    {
        string_type line = do_filter(cur_line_);
        if ((flags_ & f_suppress) == 0)
            line += traits_type::newline();
        std::streamsize amt = static_cast<std::streamsize>(line.size());
        bool result = iostreams::write_if(snk, line.data(), amt) == amt;
        if (result)
            clear();
        return result;
    }

    void close_impl()
    {
        clear();
        flags_ &= f_suppress;
    }

    void clear()
    {
        cur_line_.erase();
        pos_ = string_type::npos;
    }

    enum flag_type {
        f_read      = 1,
        f_write     = f_read << 1,
        f_suppress  = f_write << 1
    };

    string_type                      cur_line_;
    typename string_type::size_type  pos_;
    int                              flags_;
};
BOOST_IOSTREAMS_PIPABLE(basic_line_filter, 2)

typedef basic_line_filter<char>     line_filter;
typedef basic_line_filter<wchar_t>  wline_filter;

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_LINE_FILTER_HPP_INCLUDED

/* line.hpp
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
*/