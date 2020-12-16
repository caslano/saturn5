// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_OPTION_HPP_VP_2004_02_25
#define BOOST_OPTION_HPP_VP_2004_02_25

#include <boost/program_options/config.hpp>

#include <string>
#include <vector>

namespace boost { namespace program_options {

    /** Option found in input source.
        Contains a key and a value. The key, in turn, can be a string (name of
        an option), or an integer (position in input source) \-- in case no name
        is specified. The latter is only possible for command line.
        The template parameter specifies the type of char used for storing the
        option's value.
    */
    template<class charT>
    class basic_option {
    public:
        basic_option() 
        : position_key(-1)
        , unregistered(false) 
        , case_insensitive(false)
        {}
        basic_option(const std::string& xstring_key, 
               const std::vector< std::string> &xvalue)
        : string_key(xstring_key)
        , position_key(-1)
        , value(xvalue)
        , unregistered(false)
        , case_insensitive(false)
        {}

        /** String key of this option. Intentionally independent of the template
            parameter. */
        std::string string_key;
        /** Position key of this option. All options without an explicit name are
            sequentially numbered starting from 0. If an option has explicit name,
            'position_key' is equal to -1. It is possible that both
            position_key and string_key is specified, in case name is implicitly
            added.
         */
        int position_key;
        /** Option's value */
        std::vector< std::basic_string<charT> > value;
        /** The original unchanged tokens this option was
            created from. */
        std::vector< std::basic_string<charT> > original_tokens;
        /** True if option was not recognized. In that case,
            'string_key' and 'value' are results of purely
            syntactic parsing of source. The original tokens can be
            recovered from the "original_tokens" member.
        */
        bool unregistered;
        /** True if string_key has to be handled
            case insensitive.
        */
        bool case_insensitive;
    };
    typedef basic_option<char> option;
    typedef basic_option<wchar_t> woption;

}}

#endif

/* option.hpp
2vIn/7yZSL6ZEGifGbXl38N7C9Fsa/EsxMtp7TRY/ZmGx6PK3z7/o8tukfnQyTz7HVH26PRVmVLfXibzrOtqmOb5F/vui/LZZFlztZ3Cu861OjuxD9n1D7nnRXDRybCd6bLt/d9envu7LpqNxq3KlbJ+jNxXItoXvPY7a9/2/J/47a/LN7sZ6mP7MVLm5F9Un9/mrX5TSRyuxSMhuumw61/608/Olw5UAu1ysOc/yf/pski+el8jba7Z/ASdpqK5cPHurOyfIHvjaDYmVMbqgB1EbtArn+2RdLT18RzoTP105CoTsUqOFdFRfrzMdFxzaf10pKYK1dNVGHDzCHVtqjLmd57Os+7X1U+HOe1uzAC6Z3Pt/hfT8Nzk/GnQPgcuZdEt/vjnKQs8gIa35t30j3b9x3ScdU3ddLTD/BvPKJ8flnzoG+Daq34+tNkjgA7mBvb9U6ZjbGa+dMRNeeDwtmoa7Pufg7SDRPfRTuZGMg9dRXY6WA+WnWI0d8M8/Awv9m3XhpgO9ialnF8m86vAXtJQz1kDp/V0Oz7DLXW+a4jvvNZNQzE1ySl4d7ysXuYHSV4wHbmodDg4eyp9zlHD9NEyGcE1ewLmYE+mQ/kMqPX/R/7ikN5nOL5zdMAI+7rpENfRnRDpVx4j994w1+E9DTv/P5N3FsN5vUB3NR4hf2WY7/DOhJT3TmfRD0U43x3dIZB+9VZyN50McR3cIxBm09mcR4Tz2WE/Mk3mM2Gm4zO35IPH9UUxio8uLJWrtiz1vTSp21eR/3pYf4fnqKS8vyd7eZjtYOyW/C6cS9+aYabjsyAdojP5j4bbszdmxcvlYnUtWZ5SXkda/c+jn6T5+f3LunX59v1H8nfxzxFxHHRocGC4h68Cuqrr6fN5d2Immu3i/LHk+9dkb1dPb2NBcNfPpJez3OvpjvOiLvem1pB/b10+OlnlcxMyhi6/gLGj8t7B2kR0/oTcW4sB7kDfsqXnxvoHunscjKXCHrmQe2L+dSB9v3nZXf0DXb3t+S+yv4lio2vXvtNg9z9jvIfor2PG0YOdLMXGHNnmV8UYu1iPrbvet/5PL2JeX1rDzedS2UxOuT+x/k/JXV3D1T9nYPc/4l7sU6fCTDf3/0XX+8jtruHq3/uX/nqnUS/2bpMhJgfJXDI1xWsrTvj3kb/Dn/AxUVDlS1veLkFfg9H8FMzc6msu6/+V7Pdr6rb+GQZ7/y3pxV5Uq6/RtTo10b43bP0fJdmuKjXspPZepvV/QOYBNfrag+9Q280cvJzieYHpENtsozK/zSRcd2zuEN3J365Yn++ybRXGvNitk1F8N23Lrn/IPryW3dM/MnQuWrfTM8R/8HaW0c0VQRjGXT7cofiHl+BQpBKgUEppix4OIU1u20CahEgpUEop7u5W3N2huLu7u7s7m3vfGa5s+muGf+05Oee5szo7M/tuoQ9vg0/GTyfLSWH7+fwDfk/Fztf0j/r7kccOrGtt22679fYd3g6azkjnqmjvfhfsXhu7N5OVtpm4O2WQM7dxU+WidC3oCuQDg/uhn+uqe8rvITS22/bAHcTAuhLfqTveXn153ZtaCjlqrn8F/+G9rHyV3BPrX+6JXw+BTXrISvF4fv8d3HcrYW4pXxRuZ9b/yiIHPxpiKucALgP30bCt/0MOYOoA3tkPs5X1g4h/Gfiv2/hrJnImUrt9wewbWvypOe/XL9r52WRJh0/j/GzwO8LzSyGGQcwpeejLhG1WyAfQ3DoczFP3CjGVNFbY/y/gXmSkfVkPQvweNbFHwd4hzFbUg+D8x17Ys8Ls/+kO+yj4q1r5+vN6miLu/lr5+vO6DP7b4fGukIPh9z/AnD9ss9I9a7I=
*/