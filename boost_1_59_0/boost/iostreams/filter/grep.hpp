/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/filter/grep.hpp
 * Date:        Mon May 26 17:48:45 MDT 2008
 * Copyright:   2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the class template basic_grep_filter and its specializations
 * grep_filter and wgrep_filter.
 */

#ifndef BOOST_IOSTREAMS_GREP_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_GREP_FILTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <iostream>

#include <memory>  // allocator.
#include <boost/iostreams/char_traits.hpp>   
#include <boost/iostreams/filter/line.hpp>              
#include <boost/iostreams/pipeline.hpp>
#include <boost/regex.hpp>

namespace boost { namespace iostreams {

namespace grep {

const int invert      = 1;
const int whole_line  = invert << 1;

} // End namespace grep.

template< typename Ch,
          typename Tr = regex_traits<Ch>,
          typename Alloc = std::allocator<Ch> >
class basic_grep_filter : public basic_line_filter<Ch, Alloc> {
private:
    typedef basic_line_filter<Ch, Alloc>               base_type;
public:
    typedef typename base_type::char_type              char_type;
    typedef typename base_type::category               category;
    typedef char_traits<char_type>                     traits_type;
    typedef typename base_type::string_type            string_type;
    typedef basic_regex<Ch, Tr>                        regex_type;
    typedef regex_constants::match_flag_type           match_flag_type;
    basic_grep_filter( const regex_type& re,
                       match_flag_type match_flags = 
                           regex_constants::match_default,
                       int options = 0 );
    int count() const { return count_; }

    template<typename Sink>
    void close(Sink& snk, BOOST_IOS::openmode which)
    {
        base_type::close(snk, which);
        options_ &= ~f_initialized;
    }
private:
    virtual string_type do_filter(const string_type& line)
    {
        if ((options_ & f_initialized) == 0) {
            options_ |= f_initialized;
            count_ = 0;
        }
        bool matches = (options_ & grep::whole_line) ?
            regex_match(line, re_, match_flags_) :
            regex_search(line, re_, match_flags_);
        if (options_ & grep::invert)
            matches = !matches;
        if (matches)
            ++count_;
        return matches ? line + traits_type::newline() : string_type();
    }

    // Private flags bitwise OR'd with constants from namespace grep
    enum flags_ {
        f_initialized = 65536
    };

    regex_type       re_;
    match_flag_type  match_flags_;
    int              options_;
    int              count_;
};
BOOST_IOSTREAMS_PIPABLE(basic_grep_filter, 3)

typedef basic_grep_filter<char>     grep_filter;
typedef basic_grep_filter<wchar_t>  wgrep_filter;
                    
//------------------Implementation of basic_grep_filter-----------------------//

template<typename Ch, typename Tr, typename Alloc>
basic_grep_filter<Ch, Tr, Alloc>::basic_grep_filter
    (const regex_type& re, match_flag_type match_flags, int options)
    : base_type(true), re_(re), match_flags_(match_flags), 
      options_(options), count_(0)
    { }

} } // End namespaces iostreams, boost.

#endif      // #ifndef BOOST_IOSTREAMS_REGEX_FILTER_HPP_INCLUDED

/* grep.hpp
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
*/