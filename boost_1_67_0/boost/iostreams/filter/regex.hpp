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