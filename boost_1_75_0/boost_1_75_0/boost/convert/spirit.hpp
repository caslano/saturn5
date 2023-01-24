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
wPOO5Wwt//oJw2g+8I+yjUE5oAPr/7MyxoCOuwS8HAV+HVme2G/1UWG0sVZP3znwPIyhJ1lf/+MPavP5AxA4BkwdGczXv0h+oD4Wq9KpMS4CymbH2thSvj/Pf+nQAFo6rCsXoF9NAT06dWQI3bd6AX16cjzLtxjgZSO60SfSR7H2/vjtN2zw/G/68MED0LPcPcxv79/JtR/yJ+JfOcCPjbVMF9joT63nfyjjH+tIM6q7KIRAmbpQJeRniOnDyqIZ3Z3FU0I7TQIZSutIWH//5LilHH/8+w/6++8P6O/8PdLLdVOY/n+8rvrP+ce42rE9mWw0DVqQbQ7XiwWUdRYAppZ2ZXoJy7F31TxzGX6H+keR+hF0l2pQJ6hj9z/B+3/Afy8XaoiNoMb4/hD6NguI08O4WT6mB/DcjRYP7gyhEy0b3o1WwHing3KldiB097NPMf5RfvA5tGM9TfMnnM79r/LvSisTJbQqeQitmjDIEsYPopXjBzIZmQ7hqaxosNXBlllTx+T68icf0l/BTlttVFANyBXS/ey9Y+Z2QL2JOurPyc5/Vv/I48yJI2hNqtQSkofSGaDD0f76HHytfz/8vVl//fbKRdY+mB7lapWxgMHx7ibVwI4wNriCzvVk/bf15fjz8o+812ZFMr0pDugDYN0jbkddDfMFHvz2K7135zYnI9ufo9OiwiHeKBivRlDTuP6g+6/R00cOgq0W
*/