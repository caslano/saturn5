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
XXAP3A/fhR/DffCQ8k/XI/Gqv2BRjxxX68RfwlD4FXT1MwuVu34W/cyPVX/7ExgCP4Xh8DDsBI/BLvALFf8jsLcy7yvm7vDJu4gw2iJ8X6vneQJGwW+gy93Iv3D3knK3Vbn7G9TjCOUu22IcsUPtb9gJa8BXYFO4C3aA/4Dd4BuwL9wNB8N9cAh8F06Sa3c6yrtkYIxFOu5X9/tA3e9Ddb9P1P0Oqfsdhr3gcdgbfgFHy7V7P7i8owXtFvvBg9S+nlowuCTpx0MZhOQhu5HzSCw36oEUIPEMPAYhWUg4dpfeIh9hbqNSDRnMdTZ5jAJ0FvHrRboj7ZCRyCwkD3frkGX83oXEHPaxnYDXkVgisI7GPQFmIfnIBmQ3UohcQoITCSMSe5y0gpOR1cgupBC5joRT8TZDhiG5SAHyCvfcDs8gh5BrSHRf9JBhSB4yGdmAvIIcQC4h4WTyg7htBYchWUg+sg7ZjZxA/Pqjh7RChiHzkeeRPUgh4nc/6YB0RkYiZ/EvFxYgub7kCXgUuY7EDiD9kXhkFrIM2Y4cRc4g15GYgdybdOoMU5E8JJ50LIB7kEPINSR8EM8faYUkIulILlKA7EZOIJeQZYShwWDSEzmLv5nQj4WVPLga2Y7sQU4gfkO4P1ID+3g4CElHcpECJJVw7IMnkMtI+FDSGBmEvmOwWoMFyix+Z2G2zCHHcQf3IMeR60g4ejHDsEOvGfpxw3CPpCOzkBXIBmQfchS5jDRwuCEPBgznN5KAZCLLkAJkN9IZnQJfngm/bSNIayQBGYnMR9Yhzb7k+cN9yAnkOhKTRPoiqUge8jyyCzmKXEICRuI/Ya0DeyAjkXxkH/IKcgI5jwQnk25IKyQBGYbMQvKR7cgB5DhyFrGNIn8irZBBSBayGnkFOYCcRUJSIPdtAOORYcQvEU5G8pHtyCHkMjIdu5BU4ockItOR1cgu5AByHLmEBKcRRiQBGYTkIgXI5Za+tlfgcWQFfgWPJp2RzBz8g+lIPrLBIdgfhGeR68grvsRlDOUWSUDSkXxkA3IA3T3wDBKQjh7SAIlHEpHpyLocwgp3IyfQPw6vIQE9yR9ITAZ1DNKD34lw5L/ZO+/QyIo4jsfe9exdY4vtjEnUs0WNXqI5jUlMYj9dN7ub7Opmd90SY48tHiJiR2yIiIiIqNjQQw4RFTlEbIgEFTlERERE5BDbd+d9f5P33r6N7TfRP/bBzzF3c/nMb/r8ZuY3kGnI7ZDHIG9AvoA0XYzfDemCvIzfuRzhNOQxyPp3IM0I10A2vgTtBtILyUKmIc34+8cQvgFdViF8D7IWsnkW+QXphHSjrl6E8CrII5BVkFnIj5D1J1CvIftC+iAFyH2QLNK8EmF1s3A1wu8hi3LgQ7ogF0EKkBshb0BWIP4XCNdCNs6jLuLnNqStD5KFrIA8BlkJmYX8AmmGEawLshwyBbkP8jLkE8hayHZ3rd/UBhmEFCC3Qp6HzEJ+gex2N/o/yAikALkV8gTkDcgaSNM9aNeQXkgasgLyDOQTyFrIIhjdDocMQgqQFZAnIKsgs5AfIYtgkFsM6YVcBJmGPAh5GfIh5EfIdvfh90AGIQXI7ZCnIG9DvoZsDCPeAZBuyEWQqyD3QZ6HfAj5HrLofnAgvZA05EbIU5DVkDWQXyDbPYA4kMbX+Bpf41vob33IWNM6WyNo6j5medURSilfKSZS3v+WsoeMVjLZ5CHtre2tbWOHTJY62tqPtH83ddSSQ0rpeDGVPISvB0iMeKFQqv4nVn0BpDU/iqEObwd1bo3DmrAxbIv1zqvxJhuenkkU86X8WLn5gKEDmwcK8LqZuQLP0jUvxXuA8BNUNL7EyvgdT8A=
*/