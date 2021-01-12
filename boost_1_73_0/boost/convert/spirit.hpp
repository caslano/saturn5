// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_SPIRIT_BASED_CONVERTER_HPP
#define BOOST_CONVERT_SPIRIT_BASED_CONVERTER_HPP

#include <boost/convert/base.hpp>
#include <boost/convert/detail/config.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace boost { namespace cnv
{
    struct spirit;
}}

struct boost::cnv::spirit : public boost::cnv::cnvbase<boost::cnv::spirit>
{
    typedef boost::cnv::spirit             this_type;
    typedef boost::cnv::cnvbase<this_type> base_type;

    using base_type::operator();

    template<typename string_type, typename out_type>
    void
    str_to(cnv::range<string_type> range, optional<out_type>& result_out) const
    {
        typedef typename cnv::range<string_type>::iterator                  iterator;
        typedef typename boost::spirit::traits::create_parser<out_type>::type parser;

        iterator    beg = range.begin();
        iterator    end = range.end();
        out_type result;

        if (boost::spirit::qi::parse(beg, end, parser(), result))
            if (beg == end) // ensure the whole string has been parsed
                result_out = result;
    }
    template<typename in_type, typename char_type>
    cnv::range<char_type*>
    to_str(in_type value_in, char_type* beg) const
    {
        typedef typename boost::spirit::traits::create_generator<in_type>::type generator;

        char_type* end = beg;
        bool      good = boost::spirit::karma::generate(end, generator(), value_in);
        
        return cnv::range<char_type*>(beg, good ? end : beg);
    }
};

#endif // BOOST_CONVERT_SPIRIT_BASED_CONVERTER_HPP


/* spirit.hpp
8k/i29gYWmv9oagaGM8WaYvr6p5p2+JWkO39vmcfNB7b41++CyEhfPcaqv9m6j/ZqnKuzD00nLrSvZbiZ561N1eoxThueXq9B8VtjjWEXM7AZEo4W8Id8yluXBWZ7H8LGZntuyfRm5Z7MkzavXva8eOGx+76VR1aMb9dG/nF7vnuRUMB5qqeLOe3XPwezW61NJFnaf5WinwS91+a6tXy5i0RGX7j8paALHadsin1s8qq+DNO
*/