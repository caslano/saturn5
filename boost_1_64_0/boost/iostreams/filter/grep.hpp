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
+1e7vWl0u1u7nWh0e1C7vWzsds+x2tfGav96tHy92u2qY/eh+o7Ya/JT16gmeAEhXf7+KIG5kPq7kZAt+7cSMuXvZ0n7kDouz2Hk+RLHTP9+yp7R5bdgCrwN9oLfhgXwu3AYvBlOgbfAs+EP4Ar4Q7ha4q2BP4K1sBleKvsPwdnh5yNwnORDf4dd7HGVbSxMhRfADLgUFsIL4Vh4kaRXpJ9ZyHsnnu9LL5NylcFkuNywX22WeFMlnmm/+nkp/1Y4Cn5Z7Gy3wSL4FTgBXif62CbpLguvaYMFkm4qYZGkWyXl+yhMh+vg8bBOzrMejob1cCa8FM4Vu9cSOX4ILomT9VxZc24S3c5jv8pCIJR+NsyDOfAEmAdPgoXwDDgUXgafgBvgU7ARlsOvwAp4O7wE3g+r4KOwAe6Bl8Pn4AZ4EG6Eh+An4NtwEwyQyatgKnS3c+Bn4WC4BQ6D2+Cp8Ho4E34NLoHfghfDm+FKeAusgrfCDbAZboS3wc3wdtgEfwy/AnfCm+GdsBneA++AP4N3wp/DFtgCH4QPwGfhg3A/fAT+Cf4SvgGfgm2wGiah60YYhE/ADOgez4SVcIAcHyLHj5PjI+BQOBUeBxfBE+AFcAyshifCejgOboLj4dfgBPhNOBXeBE+Ht8CZ8BdwNnwSzoXPwI/AfXAefAn2h+9IPt6Fp8Ag7Wci7Aefkvpbpdc46WvSjnsRLpR2vEHs02krqn1dAQfBK+EYuAnOFjvsefAzcCG8RuzvN8Olsn0I7tDreNS5nE+9J+b53vt0mAVnwoHwDDgEnin9aDacDOfAaXAunAM/AufDs+T882WcOhvWw4XwY3ARVDb68BtwAbxR9ov9PGtg7fbzTR77+a+K/f4NcBz8OjxJthfJtuhX1mi4Xlj0+2IgpN+X4Wj4B+m3b8Fi+Co8D74Gq2T7O/B1+Dh8Az4v8pJvuZemT1vy/QxyQfgsPB8+D5fK9nLZlvcX5D6LOpR0zPcX7pB62gX7wZ/KdeMeeS/hXjhDtufI9lJ4H7wYPgRL4QPwKvgg/Kzsl/Fe7hEY0yzjfaWM9ytgdrvfVtq3zM1l/t8kcUbJewW/lnzvgcfCZ+AJ8FnJ7154JuwTCLXrffJewQvwIrgfLocvwQr4Ilwt+6tl/0fhK3ATPAA3wz9J+3oVflfS/x58U94zeQs+Dt+Fv4eH4QH4V/gGdNx+GwCwCMbDiTABlsBEuBgmwUqYCi+BfeBamAI/Jfuvlv1bYBBeK9sv/5Ps/v9fbf7/0+z9u2vr79fO/z/Nxt+w7/dl2x+rH9qjbc/fHVv+aHb8rX9I9G3L/++04z8SG/4DlDH9j4lOEWEJYT1hG2EXYR/hb4TCA7zrQFhGaCTceqDHxr/n1/Pr+fX8en49v//W37/M/x8GcUfL/1//fEc/m1sWWr8jfju/PJL9ie3P5qZPWzhnhvpennoLgJwo015k1feso/kCJA3vd9rwLWez8/HIxid0Yt9vTbd83ep66zNaZK3fQ7f61xFZbQOSm+3fbyF6cP0Wer4TR3kNW1/Kpd8TyDSfm0r+xe+L95vM2k7rarHFHywZKCBcx3lro9WVW1VO1/VUa+jozxmuXOV6u601shG6X1tTbrUJQtajzy08jPX73VyvPskX2+RL61N0J+c3nzfXuwkYvjz6Ea4nvR1WPVXQ8eorlap86GqHvfz2b+N6yn995pG2p8iy7pfbiIGSyADCV4nbYi0rb2iE+i9Wrl2XtSWG/ttBNkH3SUu7sMnyPcVoNhYeHY7NOFIdduyTnL9D/0vX+8iTx07y4SR7u2qLpmuf/a8thjbV5tHHtiPoU942dQblNA2D8iSRXMLXiJue1Ek5S5c=
*/