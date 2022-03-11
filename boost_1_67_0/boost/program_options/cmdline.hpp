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