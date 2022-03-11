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