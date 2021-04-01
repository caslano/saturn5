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
jLNl2Tg6ftAOThudzTjncNnvpMlISeOECW6z8F1UgREuCzs6FTcuBdIDJ9nOOVDXZo8AkAOqI8gtLVK5Svr+IkBUsD3LLPdwpp4R1Q5RKaQBNENxINeG4cDPTADUmfkZMh20kv0H7Mjqx95izXIDFUWYVV6mhGuoyhF8GDsm+12IKSdRTj3dJYeDRWiWZSuFAVtORBh945rb9SHt1M8i6LiZ25rZbPvD/HAXPCwXVqPqfTOq/8cttwcmedL/pTcLKd4i71ygt/4TCpEhtMfoy8fZ8bIZw/8ilTXPSG4PD7RlN4zRcLVam5zAkwmyvPXfVT0vSzUmJ9vROD3xCyI/aYkg/w4Zf5vOPJpek9tz+RvQQU8nN4vpwwqqJgmkbn5nwvGYw9US4Dbj44cGWD4ny2i0IxfIoEMdwBPuA5oIaAVmA5JO4HroBvkhpcy+1yuYHRJQpHApgZNFzLz1EwJSKMvy5rl0sVnSjhaRrCcfO5yEn7UoNK+7MrDkE9jbiAANe+kjY6n0JvrY+uckF9oulKABQk3Nz025pVBcum0BnFuFgLdg+kCUZyn0DQ==
*/