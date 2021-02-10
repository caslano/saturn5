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
vN1pkq7MLj8Kz3eC+453d/nrl6cJdevUOvrPC3Jh2z34PAjHg5NwHM6vvEGpsCwCDTzMYzaaL2YT+DwYL0bejBv8JqFtSaMkuiBiI01CvW4qBye/PV5MLibRl0kS2VuGVBFBPq1aa76YJ9FZcjm6jGZXdExfBLDFyNHIy02ei1QQ4RWcVXhhsJQ7FPXi0QgG4zjCa/dkBs8ZCXq4s9jkJ0ed+DtW4zCePxz/D1BLAwQKAAAACAAtZ0pS1oQQjBYIAACgEgAAMgAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfQ09PS0lFTElTVC4zVVQFAAG2SCRgrVdrTxvJEv0+v6LkfAggM8AmV9m8VtdLzOKNsS2PSRYJyWrPtJle5qXpHoyv8uP3VHePbQK54cOCwNDT9T51qia87tDBv/YVhKyOfvo1tz9zfOGzFZrU5d8yNk8LzOffyH1D8BqfzzB1RFupb/N9epbUN9qzUnNv6wP/PZ8/w9w1O8m/jlj4es5/4sRJevnTslrX6iY1tHe6Tydv3/5Kh/TL8S/HXfokCiUziowsFrK+6dKHxJ78NxX396GWv3VJGhJZ+EDhLFWadLk0K1FLwt+ZimWhZUJCUyJ1XKsF/lEFmVTSUmWS
*/