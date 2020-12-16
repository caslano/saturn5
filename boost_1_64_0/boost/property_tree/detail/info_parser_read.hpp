// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_READ_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_READ_HPP_INCLUDED

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/detail/info_parser_error.hpp"
#include "boost/property_tree/detail/info_parser_utils.hpp"
#include <iterator>
#include <string>
#include <stack>
#include <fstream>
#include <cctype>

namespace boost { namespace property_tree { namespace info_parser
{

    // Expand known escape sequences
    template<class It>
    std::basic_string<typename std::iterator_traits<It>::value_type>
        expand_escapes(It b, It e)
    {
        typedef typename std::iterator_traits<It>::value_type Ch;
        std::basic_string<Ch> result;
        while (b != e)
        {
            if (*b == Ch('\\'))
            {
                ++b;
                if (b == e)
                {
                    BOOST_PROPERTY_TREE_THROW(info_parser_error(
                        "character expected after backslash", "", 0));
                }
                else if (*b == Ch('0')) result += Ch('\0');
                else if (*b == Ch('a')) result += Ch('\a');
                else if (*b == Ch('b')) result += Ch('\b');
                else if (*b == Ch('f')) result += Ch('\f');
                else if (*b == Ch('n')) result += Ch('\n');
                else if (*b == Ch('r')) result += Ch('\r');
                else if (*b == Ch('t')) result += Ch('\t');
                else if (*b == Ch('v')) result += Ch('\v');
                else if (*b == Ch('"')) result += Ch('"');
                else if (*b == Ch('\'')) result += Ch('\'');
                else if (*b == Ch('\\')) result += Ch('\\');
                else
                    BOOST_PROPERTY_TREE_THROW(info_parser_error(
                        "unknown escape sequence", "", 0));
            }
            else
                result += *b;
            ++b;
        }
        return result;
    }
    
    // Detect whitespace in a not very smart way.
    template <class Ch>
    bool is_ascii_space(Ch c)
    {
        // Everything outside ASCII is not space.
        unsigned n = c;
        if (n > 127)
            return false;
        return std::isspace(c) != 0;
    }

    // Advance pointer past whitespace
    template<class Ch>
    void skip_whitespace(const Ch *&text)
    {
        using namespace std;
        while (is_ascii_space(*text))
            ++text;
    }

    // Extract word (whitespace delimited) and advance pointer accordingly
    template<class Ch>
    std::basic_string<Ch> read_word(const Ch *&text)
    {
        using namespace std;
        skip_whitespace(text);
        const Ch *start = text;
        while (!is_ascii_space(*text) && *text != Ch(';') && *text != Ch('\0'))
            ++text;
        return expand_escapes(start, text);
    }

    // Extract line (eol delimited) and advance pointer accordingly
    template<class Ch>
    std::basic_string<Ch> read_line(const Ch *&text)
    {
        using namespace std;
        skip_whitespace(text);
        const Ch *start = text;
        while (*text != Ch('\0') && *text != Ch(';'))
            ++text;
        while (text > start && is_ascii_space(*(text - 1)))
            --text;
        return expand_escapes(start, text);
    }

    // Extract string (inside ""), and advance pointer accordingly
    // Set need_more_lines to true if \ continuator found
    template<class Ch>
    std::basic_string<Ch> read_string(const Ch *&text, bool *need_more_lines)
    {
        skip_whitespace(text);
        if (*text == Ch('\"'))
        {

            // Skip "
            ++text;

            // Find end of string, but skip escaped "
            bool escaped = false;
            const Ch *start = text;
            while ((escaped || *text != Ch('\"')) && *text != Ch('\0'))
            {
                escaped = (!escaped && *text == Ch('\\'));
                ++text;
            }

            // If end of string found
            if (*text == Ch('\"'))
            {
                std::basic_string<Ch> result = expand_escapes(start, text++);
                skip_whitespace(text);
                if (*text == Ch('\\'))
                {
                    if (!need_more_lines)
                        BOOST_PROPERTY_TREE_THROW(info_parser_error(
                            "unexpected \\", "", 0));
                    ++text;
                    skip_whitespace(text);
                    if (*text == Ch('\0') || *text == Ch(';'))
                        *need_more_lines = true;
                    else
                        BOOST_PROPERTY_TREE_THROW(info_parser_error(
                            "expected end of line after \\", "", 0));
                }
                else
                    if (need_more_lines)
                        *need_more_lines = false;
                return result;
            }
            else
                BOOST_PROPERTY_TREE_THROW(info_parser_error(
                    "unexpected end of line", "", 0));

        }
        else
            BOOST_PROPERTY_TREE_THROW(info_parser_error("expected \"", "", 0));
    }

    // Extract key
    template<class Ch>
    std::basic_string<Ch> read_key(const Ch *&text)
    {
        skip_whitespace(text);
        if (*text == Ch('\"'))
            return read_string(text, NULL);
        else
            return read_word(text);
    }

    // Extract data
    template<class Ch>
    std::basic_string<Ch> read_data(const Ch *&text, bool *need_more_lines)
    {
        skip_whitespace(text);
        if (*text == Ch('\"'))
            return read_string(text, need_more_lines);
        else
        {
            *need_more_lines = false;
            return read_word(text);
        }
    }

    // Build ptree from info stream
    template<class Ptree, class Ch>
    void read_info_internal(std::basic_istream<Ch> &stream,
                            Ptree &pt,
                            const std::string &filename,
                            int include_depth)
    {
        typedef std::basic_string<Ch> str_t;
        // Possible parser states
        enum state_t {
            s_key,              // Parser expects key
            s_data,             // Parser expects data
            s_data_cont         // Parser expects data continuation
        };

        unsigned long line_no = 0;
        state_t state = s_key;          // Parser state
        Ptree *last = NULL;             // Pointer to last created ptree
        // Define line here to minimize reallocations
        str_t line;

        // Initialize ptree stack (used to handle nesting)
        std::stack<Ptree *> stack;
        stack.push(&pt);                // Push root ptree on stack initially

        try {
            // While there are characters in the stream
            while (stream.good()) {
                // Read one line from stream
                ++line_no;
                std::getline(stream, line);
                if (!stream.good() && !stream.eof())
                    BOOST_PROPERTY_TREE_THROW(info_parser_error(
                        "read error", filename, line_no));
                const Ch *text = line.c_str();

                // If directive found
                skip_whitespace(text);
                if (*text == Ch('#')) {
                    // Determine directive type
                    ++text;     // skip #
                    std::basic_string<Ch> directive = read_word(text);
                    if (directive == convert_chtype<Ch, char>("include")) {
                        // #include
                        if (include_depth > 100) {
                            BOOST_PROPERTY_TREE_THROW(info_parser_error(
                                "include depth too large, "
                                "probably recursive include",
                                filename, line_no));
                        }
                        str_t s = read_string(text, NULL);
                        std::string inc_name =
                            convert_chtype<char, Ch>(s.c_str());
                        std::basic_ifstream<Ch> inc_stream(inc_name.c_str());
                        if (!inc_stream.good())
                            BOOST_PROPERTY_TREE_THROW(info_parser_error(
                                "cannot open include file " + inc_name,
                                filename, line_no));
                        read_info_internal(inc_stream, *stack.top(),
                                           inc_name, include_depth + 1);
                    } else {   // Unknown directive
                        BOOST_PROPERTY_TREE_THROW(info_parser_error(
                            "unknown directive", filename, line_no));
                    }

                    // Directive must be followed by end of line
                    skip_whitespace(text);
                    if (*text != Ch('\0')) {
                        BOOST_PROPERTY_TREE_THROW(info_parser_error(
                            "expected end of line", filename, line_no));
                    }

                    // Go to next line
                    continue;
                }

                // While there are characters left in line
                while (1) {

                    // Stop parsing on end of line or comment
                    skip_whitespace(text);
                    if (*text == Ch('\0') || *text == Ch(';')) {
                        if (state == s_data)    // If there was no data set state to s_key
                            state = s_key;
                        break;
                    }

                    // Process according to current parser state
                    switch (state)
                    {

                        // Parser expects key
                        case s_key:
                        {

                            if (*text == Ch('{'))   // Brace opening found
                            {
                                if (!last)
                                    BOOST_PROPERTY_TREE_THROW(info_parser_error("unexpected {", "", 0));
                                stack.push(last);
                                last = NULL;
                                ++text;
                            }
                            else if (*text == Ch('}'))  // Brace closing found
                            {
                                if (stack.size() <= 1)
                                    BOOST_PROPERTY_TREE_THROW(info_parser_error("unmatched }", "", 0));
                                stack.pop();
                                last = NULL;
                                ++text;
                            }
                            else    // Key text found
                            {
                                std::basic_string<Ch> key = read_key(text);
                                last = &stack.top()->push_back(
                                    std::make_pair(key, Ptree()))->second;
                                state = s_data;
                            }

                        }; break;

                        // Parser expects data
                        case s_data:
                        {
                            
                            // Last ptree must be defined because we are going to add data to it
                            BOOST_ASSERT(last);
                            
                            if (*text == Ch('{'))   // Brace opening found
                            {
                                stack.push(last);
                                last = NULL;
                                ++text;
                                state = s_key;
                            }
                            else if (*text == Ch('}'))  // Brace closing found
                            {
                                if (stack.size() <= 1)
                                    BOOST_PROPERTY_TREE_THROW(info_parser_error("unmatched }", "", 0));
                                stack.pop();
                                last = NULL;
                                ++text;
                                state = s_key;
                            }
                            else    // Data text found
                            {
                                bool need_more_lines;
                                std::basic_string<Ch> data = read_data(text, &need_more_lines);
                                last->data() = data;
                                state = need_more_lines ? s_data_cont : s_key;
                            }


                        }; break;

                        // Parser expects continuation of data after \ on previous line
                        case s_data_cont:
                        {
                            
                            // Last ptree must be defined because we are going to update its data
                            BOOST_ASSERT(last);
                            
                            if (*text == Ch('\"'))  // Continuation must start with "
                            {
                                bool need_more_lines;
                                std::basic_string<Ch> data = read_string(text, &need_more_lines);
                                last->put_value(last->template get_value<std::basic_string<Ch> >() + data);
                                state = need_more_lines ? s_data_cont : s_key;
                            }
                            else
                                BOOST_PROPERTY_TREE_THROW(info_parser_error("expected \" after \\ in previous line", "", 0));

                        }; break;

                        // Should never happen
                        default:
                            BOOST_ASSERT(0);

                    }
                }
            }

            // Check if stack has initial size, otherwise some {'s have not been closed
            if (stack.size() != 1)
                BOOST_PROPERTY_TREE_THROW(info_parser_error("unmatched {", "", 0));

        }
        catch (info_parser_error &e)
        {
            // If line undefined rethrow error with correct filename and line
            if (e.line() == 0)
            {
                BOOST_PROPERTY_TREE_THROW(info_parser_error(e.message(), filename, line_no));
            }
            else
                BOOST_PROPERTY_TREE_THROW(e);

        }

    }

} } }

#endif

/* info_parser_read.hpp
OTY59NngD0PBYVetfyqPH5sLnruG65T5kkiMne/pe6ifH/nMyLYeI8dEv2a7dsNxq5eSMxtkiDG9pbFfxj1wM+vW2PWh8lXHc8T+D3wOdj51Oo9aMGTlvNYcrqMuIWKc/NM1/Zd8SXz29PM4+UzU5FfOJZZZMv2lefhz64j2rm0ZcZO8/SPs02LbflPxjJiiSJv+z+VzA3PkenIQtzlDb+Pcvu4wPs/PtYtiijXyv3IOrvNr85PZxayta45jn/6q4+9iPb69Y9jh+N7WqM/p99PGo92+l/NzNmZeXELt7q7/85mXF9DHrbxOEaesprtR57uj8zH8ldqTMncuS+x+5iVZ50nsyd98a2iP6Hi8YKm/K97HOVuu7/3sc1853ttcZv8++tR/lm2uSOPixnt1x1/ZmNbN4St6fCXr0ufV67s+D76k631GXcT1T7jGP5SPbYuBa/09dTZnznZci++q/0+0f+a62T/xBcd/Sc3M16z2TtecEhdfcU7H7Tr+iIx2duSzUtYcPxYjrDrfNl3bY191zZ3niL5jjuUQoj90/U8jCXmc0GRFDuXvGv/P7UtybBuDc5i/51FDcbniPnQdKtdQj8vJl2tc3n1NTbv8Tbl8w/30bfOr5zza5cu4vnSZkz6du9vqdTvXT9w+n7XcdT/8tHv03ObOn42B0JZ14tbWBtf44Db2I7plvnAdxy0dX7YtQ+3W6rzl2tzGmiHOadO9rdztN7iNc2ifpW3/E483bq1/aqfH3NY+2kd07R/2eF9ciJHLeh/wA+Nhv29+WldyYpM1NW/9VNs1DtzzB9oR6j9RT3FCTb2zbP/EtaR+Aeczv0qfNA+W/MP1EGfn8vydjZ9r3EVbnTfVuXdNY6TM8hq2iVPr7GUvK8/LcQVjMgd3zcX61Zz3itpXMib3xJhDmiRj7hvCN1d7hkxupi5ik4JrsPtp10G8jti2LXpzdaV4Vq083rUtJGaYhs3986nfudWN9Tvo+wryu7Lt9h8x+JS6fNo8Prd8mWi3WG2ZX3cwtpsa483kbb+KdvOs84aMU/4nnzKHN//3xwFrN5Qv4RuZPx5vin1r3ln7LMWE2AiZk2HEuLgnBu7Vzk08vrHHNzRG7ab2gRiIHec6Fkvi1k30zXVuLJ8byJ+NGxqPMa/Kra7P7Olj+zbCxntB495xXmb62b22WlOiy9Fl5XgdOWuviyun1/NyrsPf3WPXPbf3544hTWTDuamSYI3p9Z33eva7rvmsrle8ohpeVf9XUx+xy7H2zhWdg/Ur6fuqznk1dW1aL64vntO5vW4E5zLu2zvfHe3ntTNgm30S59TvGfWlfh79hPUTUqM7uf+MrcvBXdTi7uq3p2bWouDn1piPu48v5BjaF3PMRd2bVFblw/wi8mF2YWPnLHnadC4iD6Kr5hALdjzet23iHC3WLqZWFzcPONQucvxZ99Qn3WMXt8+afal6bvVT1g55bF/UvheR55pzX0y8qO0RfdNb0deFnJMI0wvK0bUZX11e69qnvqwmPfP/69bcr6mNmKejXbOWBbZt0v26eSxuWRPq37fOsure3CN2TbW4ljFe1vhvoR4r6rinP69lwXecq23dGIvaC2v0Xse99jP9kCR1Vde3LYfzmzscssvodJ1kYf7E5FwRs/+SF53AvfZv9xlpKoQD9eQsS/uM/ylXVrULgfkuFi+ozheQm/MvAnPr33I5re9nxX/I77zOeznXU3/jz5hTn3Re27bEiDFMv2Ms/5Q3Z9m4ujo7Jn8utRfjYv6c7gO5HtO5gn6a9juX2tzdveZxjPrljY9djpmevq5exVxhRootiuTv6NoyvoO8rmRurntM+sriVdVMDpf1mrk=
*/