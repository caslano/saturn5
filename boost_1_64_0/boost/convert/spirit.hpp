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
4J4lIfpFok5Z50+zxMnwzir/UQkWmmhYgIIXNwyLQLMsTLr/3JYY+2qqKFmPSoRO38YnMsP220GF/Dpcm2b64O77YbcXeJ+PWOPsujM2umnXqsZFyT9lABeRxBct8s7PMhYnGvnV6CN5ihGYmslY4Bl2MJnVsJOIN0kx+nKY/rZY2ec/uDUQUkhF70f6OuCYFfEWDE+77HSUykE7iNbKE7V7U1YqBQmVltvriLubNoqpoi7nO3EzJs2n+go0QpDi0RfmzUTpW4ERLTiGDnPldFpxyaVaERmdxoPWzfmXHuUxw7BzoMqwoy/2oGVPgrRv68mIXPBgcdJQdL0sfrd2cP/XgYcBg1+Jow98eIM0/p9F/TlGN6288n3dLPAe73FR9Rlc8fwzKHx1wdtZMkEHWanNAqP86rZyFIc309/XqMR4CUPo87ITkAbW4MDgQ5ry7mlPdt9s48rlqZ8ckJFb1uAVcmQQ/TGabgBqeDfo/ygRJZ0gcqe6co49/t09jCf/sTyKFuqcNp99Ey9o2DZmfZNPyl8TvawEC7XEUlcoUWg89To81/nKbQWz5g==
*/