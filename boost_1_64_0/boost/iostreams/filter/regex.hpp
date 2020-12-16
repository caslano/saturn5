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
uWd+JLr3+jr1XLs38L+8g0qp6FOEv5JmcZylbfDQtay+gXPZ20gunKXiLXJy7G2EdK1txNYetGym9mdtnJ/zZcLNSibd0iZs8UOPnh2bT2yP/NqckPyl3PrSiCzXIJu8vt+wXIds8nIfIvIDDfmBWt7apvU4s1zJDKVOUzu063w5viAu1K5TkcggDHT6q7a7ljHhZgp9snvtGpg2lMtVUNUVx1ax/yaCaqfBoRHt1JxXTiD+KT7m937ba47pP1zXt9yT6f1Sj7I/C6JP9kt9yf482e+9Dxyo94v+zfFSfADKe7P6WvA++W729Am1ihHZF/R4s1PJZ9j6AWl5xzp8Glr7gcjKtaKRhIszpW76prbXTdfXirld1QP5sH77Z1S/jnPhZEKAFwhbbfoolTkc5frQ0IlNB8T3taYTzvOH4Tx78jdPXsiaJZFmEhLI335r/lQ785W//UYd7R7gytba76E9snEnKFl1l2P1a30E5Q7XFflhH/kxxnj3vNlyXtM39NtZkfWXiGxxvE0/tetqKhrKKytKy+p96qk4vvvlMa9F27Lt+Syx5VPdKTE6rKv0lceSo5THxpyQ8Cp5J3AloQbZZWYexcG2+ipEyAOxyuPSLvyikoZuQ5ORZf1tuWOsEaxSx0udwfw/j5BP3ycPav49JSPEd/vz/mme//F4qfY76unzueL3PATyRJ6pizZLOWVa4KuMxO/gC2qqD3/4tryadXKgf7vv84D4Pv8A2fSE9ryGrpyhliPZ1dfVgOe6mguzVdzKaHNd0o46t9D3r1OVzGDreEF8+1xD8pAJRyuZMcoXsWUc8aThWZuWNJYpmSzrfMcb37s23Q9WKZk+1vkP8XV7ffN4dYdRZ/rbPUYdz6b9ss1fE9V2MXnP5S4gzrrOnAWHKrnF6vj7Kl10I3rpB4vU8RNoN8mST+6G1b5Mo111PYfOMf3p6zag7zutc41glLlGepS5RpZ9rqH9s+3Jj/TPdtC930wI+2czPpVq+GdLH9m5fzbiG2u6nfpnQ7b7/tnIR4R/Ns5n9fl35YDIshYRv1mX1fuYqLqhSq5BY7oob7OnDG0xlGFMuAye/NYPjMzvOGRbouZXfYPKV35bEvzP/0S2fa7XzbLZ5nmmX9R9lvLeSSZadXmXnFw0STtjjNkX4zg5T+OgyPPcw3n2e85D5Sv93JXduS73H0Hdk7bWj5nHigKLv0hk2zrkUXVIWb/sPI/E8zw/iN4f246gP5IPKY933Z7zeep73uDIMt6X7f5hllEateOvLpxE/+3aSex+u74ru+t2PVLKeXCwfiatOZN96aFyMoqH+ux09jG/WsS2rWwiH/CdR9IjPyo99UyQ+PqZoOm30m5nHrt/RLvdeOz224mBAPvXvlDfZ8NPJ8867fuZH2RcdcZ5R8//Yqz+Ju324UfPD6Xd7v3o+RO1+w2NZocfu7/PWO3t7X5AY39/wW6fb/qtDD3vXwZz40LPKHfBMrZfM/5+w/j7Tf136PlyYYByO2qNlb9Dc/vnjb/HItMEJxBOlr93EbSfRnkOj6o51tFf1iV0fpdrYRKsgocgEcQWQtmIqHiDCG9LvJORC8KJMB1OgDmy7cpNhmPgqXAynAqnwNPgHHg6LIfF8HI4DW6Es+EmOAduh3PhrfAjcDecBx+EC+CTcDF8EZ4LX4NL4OvwfJhEvi+AeXApLIIXwnGwDBbD5XAJrIAXwJWwFK4SPdRq2wDqWvSXRqggyPcyGwNwCAzCobAfHAYHwuFwPDwOToCj4OlwNJwOx8AZcCQ8Q7YPqfPI83JYKtt9CVca/gUDcDZMg3PkvHNhDvwIzIfzjHc+BsOz4HGwBE6CC+FcuAieJXI=
*/