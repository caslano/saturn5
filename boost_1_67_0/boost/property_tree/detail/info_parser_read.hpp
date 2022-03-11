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
Mt/uJ0TjQTGDEq5TvhpzQTYKs2h9x24V2wHsTLD7IDlJ+CdQxNlTyuUb/V9mq55i5OAquXKKoVKHc5AnGk1W0pBLlG9BMTUhSvkLd7gS+g9QSgRvBD6w2tsBcieQ978gE/ywTLD+M6zN/XUpH9Ifg3SJf47xvdowkJ9AGIuBsVm6saJnVWPDahhLtVdvDvXdUH+CE75bxKsUVOW1yUbCK8iVUwLy3aUgp4tefE0qU/j3V5TwIvqwVWk/lFybov5ZqVw0zrabsFJA6Q3K20xJE60GwO5asaafXT+IsNqdBqVIKM1lpVwxsb/spuNVJTSi7laljlBKh1JfVioU2re3ONuP9rvARporysYS78okQ/9PcuWUQv/2Euhniebf2v2j4V9YyQdBdmlG5K+XyLLN4UjyRHZfmdLd/CwTDV9VSgT3rpdB1R+qKUtkre5Yrv7a9tXReq3y7+9WGRLfYXrekPjXtk4D1F/buq1Xji2wxmmOiDIQ0ROcxmxRXaQsrtBwr0201v9EtHJ31P9ikEtFbhWOnAvFMVUJE/9hUMNBPalT1+vUrfbUzaAWgZqpU2foVLM9dTaovZsTdQluisil8bDR1g9D7XS7dzHci5OPxfCT0E6H9oDFslAH7NFXnrzJeHWUXnB8MrjKkPhk8HlD4pPBOYbEJ4PTRtmaDHeq/AmYDBDRd8/LiL77UI1oh73CRih0aEEKO3SFG8/a/aonBpQAUJY9j3GL/7WnjFD8ZqlCfNhYzbccvwZAIREKz7ICD3RxrGARCapCiVSoD4VcKHhAgcxOVFjcUf8KJIoFlDuLZDrvZKkZKxypluAPz96REv/T1vVgzNpIqxsZ+0FIFxspESG3yxCR60No/4uQlsuiTg7aRIk42kgunA/xs1TsU1XRRoZCNQGqE1jVIr5tLC+8rFGpWOa0BDUb1M5MLRfhbDVLJDwtf8EQqKrsJhXxHKlUQuXWQlkCtz5QS+DuCLUE/grQSyATUqq1dNBqig1mMqSH/Iz2hW663JD4cGmeIfF1iDGGlSCcJ/9uWCmGtLOhXqolkLYY0m1ISQ3tyrgVsuLWkrLiuVDmflZDubOYrlKxM748nqhZoNbSc12rRq6n1Mj1aGvOIA00JO45vwxXe06RIfGZejMw1RQuRrTFiHbdAhntuvfVaM+/oJ/dueOIt8yQErHI+8kotNuQThhSDJZ8nxpSOaR0IxGB+ATQV8v08bJTY5ICNb0IPSENN6TukPoakhekxfYz66fjKPGeD1Piv5kvE//Ne2riu9RIfJsaiW9VI/FajcQ71kj878PUxDeskfgtDdTEJxkSJ/4FQ+LEfzpQt+ILCevBGlm5EoB+gqzUno+hJBO/ZxtWB6vFDDi7NrC1l9Xp8pP6eWj6PGvsg7Z/K9IumCcLomC3XhD8D4+1nqhHng3pfWNo5c8ePK9srzkpETCWAmPPz0NS+EcdIb3wjboM8W59tN908VZ9JT36Nwo9relpDxNFMNFbT0/vGunZMEFNT6sa6fnLV5d4B9bQkDQ0305KrJzWg2MpoiuI6Ot42cGSLiqjOgbU10FZ/ghRduuUWfaU+aCUg7JKpwy1pwSA4uNBlBnxMkenuupfC1osNtWzS1Z7sBeA3Vtnr95ht5F2AiUDlCYcZ4WIXqdYwRa3bAxKEZRLZrkH+LUbxsxk0f1dhbqWqHvHGEW/C0rOj5LSQVZKF826KxWM1WailbwUZE+Qk5lcKr7JUtKJcWkSKJNBmWOWWTnhbPdxqN6gJIIynK2kiM/Vf30G6WtijbIuyNkgP2yWJ9PPLeStSaVllOEYvFDdo/D+91nMCdA6GydnnGh1OYyZZg8oLVsTJR8Uebb7UDcby5iEVz1rpOUFqPhCZb1u9Xjdc1wXR/iZISbMsn7KdPpA+er/8Mx7P2XaE4aSYciXDZWLZbqhRfwsEWtmyk+ZurBB/pRpw4H3fsr0nD8Z8mhDhqpjZWk326/f2MzHzPTJIn1M4R9nvGdI/E50qyH1xVw0up/ecfwgLb2gj33hkGIMaTmk7x/U9RIhTRyq6/GMJsYZMwvel9Zx0dPSln/w8bly/osa8ETiFyPxg/TET9ynJv7uQjXxlYbEif/NkDjxG/oknGVQlF0bx59HEHbJXUCQZukG6cZdmqUEBERCpFO6JBSW7m6WpUUpCREQZFG6pESklm6W7uXlfd+Z+8M1c58z8z+/68w1v0+nKkbRpd179UeojXr+BbU4xV0PSPywwIk9xJ9R/PDN2l9Gi96E8h95s/rLHpKIztQnOo5WUrFYZlexfAhL7UNp95ohx8TwDr8ly8mTzdhf46yJ8ta/1Xeg9f/EJg1lMNaIC/0gVo7jtf3R9WhyURV8KlFp/Nomb/vmnYvB3uULftPDBkOx4H/yblnhtwFzobH8TSS9e/7zHn/cbxyldOgTU/2bGqwCaBKz5WefDcVJ2c1qfc1fUd5ft+/oc3/Ww+wy8jZeJHYdyG2v9NUynj9XsedDLQGb2QmRM9AxFRLwlO5DrkrZjUhq/PMuE9vGOThZqCbPM/YzSr3ZZq6BGAday6CEC7fJZyvXg8lSHcj/vsEz6ex7/Z4l+yxia8aB5PmfzHm7pk91j/Zkx/v8jesmvp9hGo2iOawzGpdJvv3L/bBIbiBd5ImsUscDoq0qPXiM6X7ULOGpKZWqqILbgRj1zr+4rDYmW67Oh85VytbtjbMYe3ZnYpLTkHiSbzQcgxX19RSYL6qSFtOD74y19kLqXpJoRbbSbj9TJ0zYSys05JaK8p+l+23w34czkvsvX2vTfCUOdWzTb/Cn33d53iodlh6LWh2QXrv2+S3Tb3mtHfin3P4m82QQHLldoeez9bRqcQgalFHs5srB5NIx8XSLbODay+ZscbGmRlmO+ZuBaHcDCkQWwaGPKesWUPEVaIuUfvyJqq5wJVv054nVQMCjfccvzZwTjKtyybIiXw0RVWdEMZ4+LVBcnJn0I5bFmHRgyPTL2/6dln8D9w51LZg/6864Vfr550+Sb23L72blfnwK/Mc2TsfRphGgUFVj/nd/QYWFigIlzDde03jlMZZGJSajP/2ddnQ7N526qMUboskl31qILEx7uCPI+WimrPP14/rrsGCacw4CYwZBLwvR8Yd3T7dzPTKfZGJsH00JrbUxvBCdsU2oHcRMjDj3fP1Eu7rr7T/cR5SaTwY3pX+bO9GnSSR1k9cwUW//m0Tw/IvUYxI2309HxaC3kNe62QlCftMOmqOswnV8DyPdWW6rU2pBRlKekT9SJx41z5lBMoz0XhA/0jWCppH5yfRqy/Zp9MsI5lieiM9+f2Ep9rhyPrusl/1u/3zvoR/XdWgnO+X2I727lvKr4FM4w/NgswBAVMdbyfg73yuNw7ViPIERvV9biUfmL6pwWr6GR90Hoa/sRIa8RYfm6Ds/ApRvNA5tl3ceCptBIqsihakzSTiUPgif2CPMA5NDMxJ3D/DlmU90dzcj1Ct+QjHWhhaAEI4L5/21trEhQUsuuw+B3OXvx5z/Fpz00AU64Mecta8vXYaf/7gdp9xkqfgnVG7FS6Ur6AWJRWvoG/kQ3ZDMGLIbfhomf8F+qm+d+J3KDruW/GYzOu/VX8m6FQ+UlhIaTFdB0gtFSu3hF/JbKMZSjWl7pkK4b1xqGFGiELFnEGqzqEKoICCDNQNJnTI0qp9SqUiZjeSqWn9vyfna+849pDWaRdxcKvmbVPZ4UxFh2WC/Os1paNk3Q/e3W6+W3yQYxqqdROdtjRJcNSQ6PY6rMXw8EoXxs589j3q7R2NorH6NNDJ2h50fT7AqVBoFSu4GdtXAdT/Lqn6B3wJr+43eASviTGykzFUaMZPK3PmHgkKMPpSKP3Z0yA+ft+tssreT1lRsDv+aAKB1BzpzSRpr8RTS4/HZVy7i3243PDWcj7BAVU4iqUOo44plYxm1+r2C4w/tOfnXu5fRudS/amR+DF5pdfLFcWQgM1hzkIKsKUjDuyuv9/vMJYOYe2jUQDVIRazO9WrHgCX5+RpX010bdxjFr+uaVJ12p+vxPH2ayTj9c4Ps4JA1miXnRwPs8yh+TtIaKr6ODM5RnhcWe5x+4aPdpgSfOP68VAqBq7xpEMv0UaPrX61QKd3xrBLk2hlVvs35rktT/0+K/reflWsJBU14r88OtJ9ISrxWlevwswmyuCm98PljEOq7ZJ+DXbKvd9/gOg0NySSmkQ+hXKY3W32TM5n/JuSPuE/21WXz7c9e6XBu7fIKHm0hhH5uaqqMlXhzlr/GUchUr+L3/vNdxdsUVpP3fKUDnYQEh4IWR0M/FVsc8F8qfiY4TMSRl6vcFVmoTB04PScRo8O8WR04VNKvQTx+1H3Z6SrZz/SPx7/RvdXKJbhKhiq3/qOqdo7BXvSo5rOeUdZn6FHYM+/BGkX8bjfIbg+tr5VQ2qUYbstX36etP1Aupopx0strxuMg/PBu4eTXRe3fw9+nwZcveNtP/AN3MIWBcowXjmCm1s62kQlsvBBFjFfGRX1z0HDc8ijspq18kQuXmjeu80vbseIf3e0NCy/bIOlAf2pFnrsrUfONr6MZmP5dS36KyxesFBcat0ikGO64wQyxaDgelbCf8G96B9aeO9jnQBupsooLKjyVqw5c8wz2eBzoOCZL61KN9KzPvMxAl25UbEdSMJ8YQWvxA1+SyL8MskXr/h5tg5x67Z5GQRerhbZ0W42R63f0n+UoDOW1aEhRG8TfJJpPTJVZ/NPdQjd/ZkWHOdDWZrlVnJO+cCu8agjHnYwh953kZuIOdnUPV1kKdcP2DQpTyjzbBT6mnurr225mDZzR/XvLNxaKY7p9lLH5NfQVr0yfUreyVuvbAGZT0oqbZyEDH4isub6AfvX9zYC7dkAkFt3zDtTzDh7nvRHKe2OZd1AisXgmsdgqYTm8/va0dercrn7q3Djvzdfhc3jegbHEYpJLh7TEoqRLx5s/QZbNlzVNlyP3X/iBBW73UtdrabD3PU5rafj2lZSjQ+ARXeHD4nmey6Dshh937k+d7Y7t3XPr00I19gd0bnbm0ZjWSXA+Pu5QP3h+yO/ngFg2W6+5l2V8m3+E7EehTMrbD1c0uk1I0OXbp1y2y6m1ms4xP49yvo+6pPgP1xUKWLpJcoULrUnDd2rqLAA71X2B/hd/tZvwGMvFfvNX9BZ+JCOXGTdpyC+2nUKwMVj6k6Ffst4Io61BHb+pFQa9iyQfEHuNGkdx6S3RNLFUBI8ZNnxq+PUpFBPAnPqNz0WooVhGjvYMnX4xALaIwboCRpUuXnG0UzDNVzNl2uPkjG+NDp/77UXb9tYRT2HIg9eLXsyBcEbSQd0FxxpdMY/Q9N+D56PmBZZw8Na/Xbcfva+nPCeq8rwvauqbv1VZeO0B1sYMkakrG0rSDMBlBc4RT6m6f3DzmDuGm8V03BQhL2aRAteFteS5PWACvHmKG8EiSe+4aTET7rr25+/1hQN1WXoMsKdp8Q+b2edVU9EGLkzrV9howrYMm85//Ni23NoWCsbXQjro/kT/6rtYstv4aOn0JTu/PGuWYwncwcs8Fann5yfpKfBmxszZ3FHkhY6/F1qbkKK/Vz9L3IDusx0vE4bnU8zY/qec6cqv09S59C+On+bQb90+Samy5aNoQgR337a2OBJ65uqNob58iPXzxNnqFTt8YuxTGfPF31Mb06Ol+qdaDp+DddML3ycVigEMqI0x4Bco6ynRNjJAHwLowosmAK0S0eGpYMPoIgtA67sipNTmU3AQs0ax9+L7gw19lIvoo/UGQyI1dLAFxwbIV/DdMa2v3VmTUVycbNXamVTsa0lpgZ+y3LEyyLT6h+MzqyIDjtRhZCyVwLDyvqJ4t9KMhCJJ8CQBNNxGjy7ME3RCEdbKsvmEg5vmPg3dOxZj2lU5JpWoohQAXUxRHJ503yPoJWA7tkgDcKVD8DXhy3r5O6+0zoeXb2LzPR9xKio7fRFR3/tVUtr8vOqha2kRFX4GZJMHXyALSixhKlCugB/nKJEkdtbXEFDaoJYzzBYur8VjlKR1tmlzPDPM9F4iif/MxOW4zy5pXiKJgTZumC1L3kzyhfzR0pOdLrzLPv2jDwPb2EvuUvJvNsRRBydbz6cwQmi/uJO9+dQgNWS7GWMHQQdf6ZuL7tVrsSDJLknTK0EHlQ7XpbZHHZSlb5bZVl+Sd8hidgSCDeT7zq++rF6Dg5DpHTlJqQeOF0yIN6JbeRO5QUnd58QXMuqLYRKrbTQdi9/Pa/81exL6/faj9+K761Lv30prwV37eArqt1///P7YHbp8A+8Jk/ygfeJVImH11eAgqOnufeZetMRKcNUlWM9CwNH1i8mgl6cslbBkkYu7YkhcC+X3At6vaV+KEtgc+MLsWPteEtQbCYZlsnEzQRltxjwdzKF6+GEWMD35nCPeCybAV0PGDqaO39cNbyzeHs2fkmb8oL4ozOxQSUo54LzYf3fgsfVy+n2Q5bsDQuw8XzAfs5oLVv77nuVVbiHLYj1W/sHi83HjHeWO26W3Dzo8xn/faRydxhWlB5Mv8uzSWzQOT79DKlvZlhtAssRgvbKkFuT9bUTnK+PzwbK2i9WiOXlNCZ8PcA8fTmWltHSfT8FiS2mDPl7Vh/19aeMl/fdk4HPPl3ctk+pF9fYkwzDdpyuVk4C75OI6lkqy4s33ReYilfJzL8vydrgxPCd33sUBbA5fSQb6i6TEExsoRkx3veehI3mkmCDq1Y1sl4BOwVwDQl2RSRdJWiKlGdFxvZ9/S49UlHbU04mmzZRpCI0o+49uc8PGQWJMUCHWTTtLMiIVPZmwQugYH+DqOYGAmh5BmBzohCDsyPa+EgEbEkPbQI0GBLYQB8kw3JwmlBDUqEOwBuEmhlqybRLj/+wvosC3ZeOmh1aAqLjD3di4CaG1kE0//NM0qKDK5kOAaWxRHMBJIHwOZBhRBMJ/zlaZWFjrVzkk4WRCJOf/fS6CWy3WQfij8dP0I/tsfQJNEm4MdNH0r7ImjXMU6YGmE/n3I0q9t7pVtrin0BSAzB3nQ/mEIlKRSto5vrK2TcKP/dk1wjkXorGUgddFklRzMal5hw2uevb7Uvhnae9HDvRFOl2+a58/yAHsqnIuv2IFfLJLfRRb1A8gUtajCnM7T7lsj81hht6CGimgFdL/HQznSeXlnY87esse2He4+hF5RsCIwj7b6GlliJcxRi+NLfxaVXdnlaJ0AjtRboPMAOQgJvZJjhaKbfA2JR1IDKYEY4NZh9GjgCgeFG1XwVj+WBgWhOLAWMH40Gz45OgSxDRCAtGM8EWcIXoBjIAkShmKQhZvVjmNTS3/2CWNTdim5qbqps4mdFNjU2VT2z93LApLghJCMaMUrf7pihNOFo5e0sZCSDhJICQcFxSR4EhKVdANgA1YAigB4hD2QGuANfBfhAfiELEBeI8AImIQGoh+BA/iA8IRwQITtpKBIECaALYhliF2BCUroAHQAExBSCO4YWKQSOEsEDyaLRt4iAhAXCIeIiIQKogNYBwQDoADhUAW7AxA3S/i0Trzv7wHXZkKdzEe3du/CuRfuzB9+8OWJEd2ovIW/jZ89u9LhzcWn795JNNChVi5iaF7Nnprgts0zNMbT3wkpRftKqI+AEnZ9bBRaAi3WUDuI7ltiSfLpLvv/YNdmNL+sPWsg38wbUkk6Z1x1wcgGqLiPk6xpcoTgVdEEj20Ty/E5Yc4Epo27EhrcG6Zo7lV2wdGp4OQ2ca9PyeLH9TQlAsl6caTSgNvJT+bDljD50gL3uobGZU+Mxrpxq6I8JWfa7gKfXRML8areaWNtyNhopP6fG7G6VdFxdTrBy3z311POTw6D4bNhExI3qvA82SyYzPDm88Yi30eCMDHpZqV8c3nYNBgUKMGgTzgnHdLMCjb4bKIEW+YBvpMZJOItXUrNlqhJiH6dSC4mpSVjnxWT76YPNqXohGr405d1/BgJHyXf8tpOJ8eZxvuvuFmRO53tul87NDPhJIgJz9T/xLQuOcqUPRwtVEM1mqdUhT8TQr66C33NpTBZ1ltdfenjlFlYC6VTqcO0UdUHYzX7N+PkIaF9Rv4wdp18l2r0dqAvbo03sDDV5ea1ITa+3DoR9AJY1jhJOkuFx7hq6WnRoqsQeccAg2C75d4gYLSyuprj926r510z2qC4+dgrTThFKPpaLzV/Idc2ukXMklrpytiz5r/uabsL8zXaaJVSA5z64zMIYZutULwVVg3xcJ6IA4RJEQXjy+/2Iq5g+oV/nVWMJlg58Pfrx//9mAfNX5LNDeqfr7P4Cx+eqYqHrCeuhVMjvZGQzW/Pzhqwu868a2Uhjc1AUzji7oAV8nHi0rNNeF9ivR9CC9q2WNUHQORm94FFZG0PgofGgNoTdGEcoFOIkl4lcZM8W/DipCgRi0CD0nAKaqIDUAByOUJH4rinh0kL6IPWkW46YlkOwjUR7WT5WaVTsno7O+Pz/+zTzY+T7CfuauwJIkQEyIt0WiXDnKGE2QF5Ao9JFWZswafGPu9EEYazB2D/fyF2+PKvvws4amei0xRpXQYUh37lzY9MF2MoEFVIj945gX+hsHup3cNArLmHSz2Xr6q1MkNCrKWkU1/xmfD9rUTrsSS6nzb5lcbXQIyXluQ7/+zzuR+7lwTo8vcaaBNtCgxjf7C1Esb7/jaq3q5qXzW196ToXoNdif+YltjRxa1x9JkzvN9+WVtq4xc3vFiQnDwEj3xohJW/meHcxVyJ/PcUerh3mwTX3v2A98XCtC+RjZCzSL3j//y3DyIIDECdOL7VXm/XLLgm/+C0Unel4lYlYD7sbV021JQcKb9LKi7EA7qVe+xdie3+iKnuFqi6TG8kx8iOKCWthyvvU/69bzmuLWdVC1BaO0552Vrh/en1s9dmMhu46BrdLiz2bTYiaVo39fWvv0gz5droQl3KtVY231TSGL1Eii4ovAjrthobXDf9GKqZzZFyOnrp88y8kY7I3iFdBwibRsRTgpYysHIQi6OUeM58d9OIvhR/tgG+FQQlltmVMZyWC2hWMBMyoxKYAntUTy2dBT17Xch5G2Iuzb74NFT3SRaLm8Ru/y+GDEzqdooypYsMmOiJ5/DSs3Mr2LK5MxluvQ7BIMH9N8LBvfpowRduWJGh5XjHpv0fqC5+S3MB8/KrEuvhv/iX9s=
*/