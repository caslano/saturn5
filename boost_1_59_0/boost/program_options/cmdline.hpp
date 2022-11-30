// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CMDLINE_HPP_VP_2004_03_13
#define BOOST_CMDLINE_HPP_VP_2004_03_13

namespace boost { namespace program_options { namespace command_line_style {
    /** Various possible styles of options.
        
    There are "long" options, which start with "--" and "short",
    which start with either "-" or "/". Both kinds can be allowed or
    disallowed, see allow_long and allow_short. The allowed character
    for short options is also configurable.

    Option's value can be specified in the same token as name
    ("--foo=bar"), or in the next token.

    It's possible to introduce long options by the same character as
    short options, see allow_long_disguise.

    Finally, guessing (specifying only prefix of option) and case
    insensitive processing are supported.
    */
    enum style_t {
        /// Allow "--long_name" style
        allow_long = 1,
        /// Allow "-<single character" style
        allow_short = allow_long << 1,
        /// Allow "-" in short options
        allow_dash_for_short = allow_short << 1,
        /// Allow "/" in short options
        allow_slash_for_short = allow_dash_for_short << 1,
        /** Allow option parameter in the same token
            for long option, like in
            @verbatim
            --foo=10
            @endverbatim
        */
        long_allow_adjacent = allow_slash_for_short << 1,
        /** Allow option parameter in the next token for
            long options. */
        long_allow_next = long_allow_adjacent << 1,
        /** Allow option parameter in the same token for
            short options. */
        short_allow_adjacent = long_allow_next << 1,
        /** Allow option parameter in the next token for
            short options. */
        short_allow_next = short_allow_adjacent << 1,
        /** Allow to merge several short options together,
            so that "-s -k" become "-sk". All of the options
            but last should accept no parameter. For example, if
            "-s" accept a parameter, then "k" will be taken as
            parameter, not another short option. 
            Dos-style short options cannot be sticky.
        */
        allow_sticky = short_allow_next << 1,
        /** Allow abbreviated spellings for long options,
            if they unambiguously identify long option. 
            No long option name should be prefix of other 
            long option name if guessing is in effect.
        */
        allow_guessing = allow_sticky << 1,
        /** Ignore the difference in case for long options.
        */            
        long_case_insensitive = allow_guessing << 1,        
        /** Ignore the difference in case for short options.
        */            
        short_case_insensitive = long_case_insensitive << 1,
        /** Ignore the difference in case for all options.
        */        
        case_insensitive = (long_case_insensitive | short_case_insensitive),        
        /** Allow long options with single option starting character,
            e.g <tt>-foo=10</tt>
        */
        allow_long_disguise = short_case_insensitive << 1,
        /** The more-or-less traditional unix style. */
        unix_style = (allow_short | short_allow_adjacent | short_allow_next
                      | allow_long | long_allow_adjacent | long_allow_next
                      | allow_sticky | allow_guessing 
                      | allow_dash_for_short),
        /** The default style. */
        default_style = unix_style
    };
}}}


#endif


/* cmdline.hpp
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
*/