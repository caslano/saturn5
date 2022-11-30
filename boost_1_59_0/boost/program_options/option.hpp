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
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
*/