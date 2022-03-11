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