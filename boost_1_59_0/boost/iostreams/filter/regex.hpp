// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_REGEX_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_REGEX_FILTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <memory>                         // allocator.
#include <boost/function.hpp>        
#include <boost/iostreams/filter/aggregate.hpp>              
#include <boost/iostreams/pipeline.hpp>                
#include <boost/regex.hpp>

namespace boost { namespace iostreams {

template< typename Ch,
          typename Tr = regex_traits<Ch>,
          typename Alloc = std::allocator<Ch> >
class basic_regex_filter : public aggregate_filter<Ch, Alloc> {
private:
    typedef aggregate_filter<Ch, Alloc>                 base_type;
public:
    typedef typename base_type::char_type              char_type;
    typedef typename base_type::category               category;
    typedef std::basic_string<Ch>                      string_type;
    typedef basic_regex<Ch, Tr>                        regex_type;
    typedef regex_constants::match_flag_type           flag_type;
    typedef match_results<const Ch*>                   match_type;
    typedef function1<string_type, const match_type&>  formatter;

    basic_regex_filter( const regex_type& re,
                        const formatter& replace,
                        flag_type flags = regex_constants::match_default )
        : re_(re), replace_(replace), flags_(flags) { }
    basic_regex_filter( const regex_type& re,
                        const string_type& fmt,
                        flag_type flags = regex_constants::match_default,
                        flag_type fmt_flags = regex_constants::format_default )
        : re_(re), replace_(simple_formatter(fmt, fmt_flags)), flags_(flags) { }
    basic_regex_filter( const regex_type& re,
                        const char_type* fmt,
                        flag_type flags = regex_constants::match_default,
                        flag_type fmt_flags = regex_constants::format_default )
        : re_(re), replace_(simple_formatter(fmt, fmt_flags)), flags_(flags) { }
private:
    typedef typename base_type::vector_type       vector_type;
    void do_filter(const vector_type& src, vector_type& dest)
        {
            typedef regex_iterator<const Ch*, Ch, Tr> iterator;
            if (src.empty())
                return;
            iterator first(&src[0], &src[0] + src.size(), re_, flags_);
            iterator last;
            const Ch* suffix = 0;
            for (; first != last; ++first) {
                dest.insert( dest.end(), 
                             first->prefix().first,
                             first->prefix().second );
                string_type replacement = replace_(*first);
                dest.insert( dest.end(), 
                             replacement.begin(),
                             replacement.end() );
                suffix = first->suffix().first;
            }
            if (suffix) {
                dest.insert(dest.end(), suffix, &src[0] + src.size());
            } else {
                dest.insert(dest.end(), &src[0], &src[0] + src.size());
            }
        }
    struct simple_formatter {
        simple_formatter(const string_type& fmt, flag_type fmt_flags) 
            : fmt_(fmt), fmt_flags_(fmt_flags) { }
        string_type operator() (const match_type& match) const
        { return match.format(fmt_, fmt_flags_); }
        string_type  fmt_;
        flag_type    fmt_flags_;
    };
    regex_type  re_;
    formatter   replace_;
    flag_type   flags_;
};
BOOST_IOSTREAMS_PIPABLE(basic_regex_filter, 3)

typedef basic_regex_filter<char>     regex_filter;
typedef basic_regex_filter<wchar_t>  wregex_filter;


} } // End namespaces iostreams, boost.

#endif      // #ifndef BOOST_IOSTREAMS_REGEX_FILTER_HPP_INCLUDED

/* regex.hpp
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
*/