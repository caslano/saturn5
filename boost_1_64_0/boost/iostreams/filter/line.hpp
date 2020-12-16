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
r91fkqQRMOtB1+lOdWyS8d3clfWmT7W71fGTtK/sBbSLcwiuDsbl+NPDS1oPHt8sKs8ef5xjIu+xHnH7aFq7HpaX1a0uD91eVddUl1eq/GpbFbcr2PVAGrp9F4bvm2zXBI9svfYZZB/TRFa3mwH5Xff7TNMORvIcHtcKw/c+5twrwoeQPP8rEh9Cku9rCY+TZrqhr/JVleWXiKo8fq9sepK4AUOny+scu56QtfhLLlXzQf2NztFKpsEZxv8nEk4Vedqikg9Zr7f3+41KPsmUIU1EjHa5XsmMMM9LOurE2l/RtLTQeJXKv36EY7CIz6G/LxlDuz+R8ZV6CiYsDyYmOcYcUfq8yO1FbpArl3p+hIykpV4CL1Bp5QYzjbTyPHIjkBus5OKDfRMj5PQ4c3dGKGz34YtX2pHhc0vakW5b1J2nzQwcF0rgDEKAMIvwa2RbzTZTU3tZqMn461utaf59drZGbzPaN9XLSiaX/hVnbwci976SS1bXgy3o9+qx9B9Xx/1PMO6lRb8ic+vYcJ0O8daplmkdK3WVE4iopwKfflbb+3bXvj33nhRK4Hq1n/wQnkC2KGjUybq1c2bKBd7z7WQ9ns9U8sda64i09HUgU41/1TreSolnqy+J573W6Lib1fEiu91o0HLtkXFhvDq2VaX7lJqblevrfy48VR3f4oxE/6lsH0N9jKQOTiDUkFYtwbweDfHx/Xb3enS3SteJ9m1e/Y1rdMS+ahmDo1+zUk6OvGbtpTxtRt1R4w2VdfXmVcvXWNwW9H/Nagv6v2a1Bbt/zWpvw7Fds8LPnS48RdYGOHFv4fMjHTba9UVNlNZdWs4Nt2rwagwYQeyA/o6+VV+ShviGzJf+UYdMuH+o4634hyqw6ZD40dvrGxwz/cu+qbYHsD1d+efMVtsfqnNfruxyyipMf6z91fH38d0xODIN4uxTfaCOMrd/A7tQHX/bed2JN+Zoq8tOlnSzYK6S+YB0j5G8htMdpMbFIMI7JjDHVPPkkoh5co7IPIzMMFcm0PiTYFrfiHlw+Lvax6LXmcgNJ6wjPEQI98v+hFGEocgMs/gUtX1X+1Bv47va0sbcus7WdW34m8yXflrX0Zdi/STxGyPneJLwKPpc1ke1KfWKnLfvNeeF1m/r66xtibjWvqevUY+p44VsJ9raEvGt/VFfu6rV8VzVfoJafphOQ/ZF/d5/nruljt9Li0pWMgUZ7rm59VUyM9R9k5oL9HXl0lU+22irmVImNFdVGyqWzscmleZtTgH1ncT28PyQf/Hj4CM5aq1ffzsGdDr357wRY62r92yld//jB/tUvikf+yifXi+RuLoccs8v7eKgtItEQpi7OX+tyldj3SWl02bMmLVwYenMWQtnnDOnZNGcs+e7I05pdcNaEjP6SmfjYyHPX2WtWc67f3LkeZ/nvI2dnbe2oW6VXNtvRM8B7r/t45ykwz8Za/irtn6d/bqgZXV/9lGWcF25+cgmH2Yf5Hzs43zh66CUueTUyDJn9ee5bHuZF84f6y7gzZqxSCs5dh2Hzzd7SuT5fpzLWGc9X21NrXxFSdY3OtUvaeg56unquuPGXdFQXW7Xscgb6wtdlyWs496iY9Mfv3vObH1OuX5KucdPjSz3APTcbC83jcpfmZuNNjU+o/M21XwEbaq3pU1xvg5t6m3YGhe7T067D9XoPkjtPlSj+RqN3YdnNN+bV8a7+7957oMJva96/4dDdj4zZMTX554W3efn15wA+w9trFv+93tfeW70ve/Ev3Lja1VHz0drrD5j7b5bo/uqtfu8jeaLNXbfqnafsbH7SrX7ko3uK9XuY7ZzH6obCPzUumULzCXtScbfzRn6bzVna+I=
*/