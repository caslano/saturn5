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
+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
*/