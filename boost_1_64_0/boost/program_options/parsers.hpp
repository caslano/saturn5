// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PARSERS_VP_2003_05_19
#define BOOST_PARSERS_VP_2003_05_19

#include <boost/program_options/config.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/detail/cmdline.hpp>

#include <boost/function/function1.hpp>

#include <iosfwd>
#include <vector>
#include <utility>

#if defined(BOOST_MSVC)
#   pragma warning (push)
#   pragma warning (disable:4251) // class 'std::vector<_Ty>' needs to have dll-interface to be used by clients of class 'boost::program_options::basic_parsed_options<wchar_t>'
#endif

namespace boost { namespace program_options {

    class options_description;
    class positional_options_description;


    /** Results of parsing an input source.
        The primary use of this class is passing information from parsers
        component to value storage component. This class does not makes
        much sense itself.
    */
    template<class charT>
    class basic_parsed_options {
    public:
        explicit basic_parsed_options(const options_description* xdescription, int options_prefix = 0)
        : description(xdescription), m_options_prefix(options_prefix) {}
        /** Options found in the source. */
        std::vector< basic_option<charT> > options;
        /** Options description that was used for parsing.
            Parsers should return pointer to the instance of
            option_description passed to them, and issues of lifetime are
            up to the caller. Can be NULL.
         */
        const options_description* description;

        /** Mainly used for the diagnostic messages in exceptions.
         *  The canonical option prefix  for the parser which generated these results,
         *  depending on the settings for basic_command_line_parser::style() or
         *  cmdline::style(). In order of precedence of command_line_style enums:
         *      allow_long
         *      allow_long_disguise
         *      allow_dash_for_short
         *      allow_slash_for_short
        */
        int m_options_prefix;
    };

    /** Specialization of basic_parsed_options which:
        - provides convenient conversion from basic_parsed_options<char>
        - stores the passed char-based options for later use.
    */
    template<>
    class BOOST_PROGRAM_OPTIONS_DECL basic_parsed_options<wchar_t> {
    public:
        /** Constructs wrapped options from options in UTF8 encoding. */
        explicit basic_parsed_options(const basic_parsed_options<char>& po);

        std::vector< basic_option<wchar_t> > options;
        const options_description* description;

        /** Stores UTF8 encoded options that were passed to constructor,
            to avoid reverse conversion in some cases. */
        basic_parsed_options<char> utf8_encoded_options;

        /** Mainly used for the diagnostic messages in exceptions.
         *  The canonical option prefix  for the parser which generated these results,
         *  depending on the settings for basic_command_line_parser::style() or
         *  cmdline::style(). In order of precedence of command_line_style enums:
         *      allow_long
         *      allow_long_disguise
         *      allow_dash_for_short
         *      allow_slash_for_short
        */
        int m_options_prefix;
    };

    typedef basic_parsed_options<char> parsed_options;
    typedef basic_parsed_options<wchar_t> wparsed_options;

    /** Augments basic_parsed_options<wchar_t> with conversion from
        'parsed_options' */


    typedef function1<std::pair<std::string, std::string>, const std::string&> ext_parser;

    /** Command line parser.

        The class allows one to specify all the information needed for parsing
        and to parse the command line. It is primarily needed to
        emulate named function parameters \-- a regular function with 5
        parameters will be hard to use and creating overloads with a smaller
        number of parameters will be confusing.

        For the most common case, the function parse_command_line is a better
        alternative.

        There are two typedefs \-- command_line_parser and wcommand_line_parser,
        for charT == char and charT == wchar_t cases.
    */
    template<class charT>
    class basic_command_line_parser : private detail::cmdline {
    public:
        /** Creates a command line parser for the specified arguments
            list. The 'args' parameter should not include program name.
        */
        basic_command_line_parser(const std::vector<
                                  std::basic_string<charT> >& args);
        /** Creates a command line parser for the specified arguments
            list. The parameters should be the same as passed to 'main'.
        */
        basic_command_line_parser(int argc, const charT* const argv[]);

        /** Sets options descriptions to use. */
        basic_command_line_parser& options(const options_description& desc);
        /** Sets positional options description to use. */
        basic_command_line_parser& positional(
            const positional_options_description& desc);

        /** Sets the command line style. */
        basic_command_line_parser& style(int);
        /** Sets the extra parsers. */
        basic_command_line_parser& extra_parser(ext_parser);

        /** Parses the options and returns the result of parsing.
            Throws on error.
        */
        basic_parsed_options<charT> run();

        /** Specifies that unregistered options are allowed and should
            be passed though. For each command like token that looks
            like an option but does not contain a recognized name, an
            instance of basic_option<charT> will be added to result,
            with 'unrecognized' field set to 'true'. It's possible to
            collect all unrecognized options with the 'collect_unrecognized'
            funciton.
        */
        basic_command_line_parser& allow_unregistered();

        using detail::cmdline::style_parser;

        basic_command_line_parser& extra_style_parser(style_parser s);

    private:
        const options_description* m_desc;
    };

    typedef basic_command_line_parser<char> command_line_parser;
    typedef basic_command_line_parser<wchar_t> wcommand_line_parser;

    /** Creates instance of 'command_line_parser', passes parameters to it,
        and returns the result of calling the 'run' method.
     */
    template<class charT>
    basic_parsed_options<charT>
    parse_command_line(int argc, const charT* const argv[],
                       const options_description&,
                       int style = 0,
                       function1<std::pair<std::string, std::string>,
                                 const std::string&> ext
                       = ext_parser());

    /** Parse a config file.

        Read from given stream.
    */
    template<class charT>
#if ! BOOST_WORKAROUND(__ICL, BOOST_TESTED_AT(700))
    BOOST_PROGRAM_OPTIONS_DECL
#endif
    basic_parsed_options<charT>
    parse_config_file(std::basic_istream<charT>&, const options_description&,
                      bool allow_unregistered = false);

    /** Parse a config file.

        Read from file with the given name. The character type is
        passed to the file stream.
    */
#ifdef BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
    template<class charT>
#else
    template<class charT = char>
#endif
#if ! BOOST_WORKAROUND(__ICL, BOOST_TESTED_AT(700))
    BOOST_PROGRAM_OPTIONS_DECL
#endif
    basic_parsed_options<charT>
    parse_config_file(const char* filename, const options_description&,
                      bool allow_unregistered = false);

    /** Controls if the 'collect_unregistered' function should
        include positional options, or not. */
    enum collect_unrecognized_mode
    { include_positional, exclude_positional };

    /** Collects the original tokens for all named options with
        'unregistered' flag set. If 'mode' is 'include_positional'
        also collects all positional options.
        Returns the vector of origianl tokens for all collected
        options.
    */
    template<class charT>
    std::vector< std::basic_string<charT> >
    collect_unrecognized(const std::vector< basic_option<charT> >& options,
                         enum collect_unrecognized_mode mode);

    /** Parse environment.

        For each environment variable, the 'name_mapper' function is called to
        obtain the option name. If it returns empty string, the variable is
        ignored.

        This is done since naming of environment variables is typically
        different from the naming of command line options.
    */
    BOOST_PROGRAM_OPTIONS_DECL parsed_options
    parse_environment(const options_description&,
                      const function1<std::string, std::string>& name_mapper);

    /** Parse environment.

        Takes all environment variables which start with 'prefix'. The option
        name is obtained from variable name by removing the prefix and
        converting the remaining string into lower case.
    */
    BOOST_PROGRAM_OPTIONS_DECL parsed_options
    parse_environment(const options_description&, const std::string& prefix);

    /** @overload
        This function exists to resolve ambiguity between the two above
        functions when second argument is of 'char*' type. There's implicit
        conversion to both function1 and string.
    */
    BOOST_PROGRAM_OPTIONS_DECL parsed_options
    parse_environment(const options_description&, const char* prefix);

    /** Splits a given string to a collection of single strings which
        can be passed to command_line_parser. The second parameter is
        used to specify a collection of possible seperator chars used
        for splitting. The seperator is defaulted to space " ".
        Splitting is done in a unix style way, with respect to quotes '"'
        and escape characters '\'
    */
    BOOST_PROGRAM_OPTIONS_DECL std::vector<std::string>
    split_unix(const std::string& cmdline, const std::string& seperator = " \t",
         const std::string& quote = "'\"", const std::string& escape = "\\");

#ifndef BOOST_NO_STD_WSTRING
    /** @overload */
    BOOST_PROGRAM_OPTIONS_DECL std::vector<std::wstring>
    split_unix(const std::wstring& cmdline, const std::wstring& seperator = L" \t",
         const std::wstring& quote = L"'\"", const std::wstring& escape = L"\\");
#endif

    #ifdef _WIN32
    /** Parses the char* string which is passed to WinMain function on
        windows. This function is provided for convenience, and because it's
        not clear how to portably access split command line string from
        runtime library and if it always exists.
        This function is available only on Windows.
    */
    BOOST_PROGRAM_OPTIONS_DECL std::vector<std::string>
    split_winmain(const std::string& cmdline);

#ifndef BOOST_NO_STD_WSTRING
    /** @overload */
    BOOST_PROGRAM_OPTIONS_DECL std::vector<std::wstring>
    split_winmain(const std::wstring& cmdline);
    #endif
#endif


}}

#if defined(BOOST_MSVC)
#   pragma warning (pop)
#endif

#undef DECL

#include "boost/program_options/detail/parsers.hpp"

#endif

/* parsers.hpp
brBxkykjfZpMSWtXcf0v2L8fEmK74ufGaOG2pjFXfxF+Hra5D/tqyVS0m/6Wnm9k92XgLzgGfldnB1523zuteGek7mLcPTzYx/U/Z9rXLsrl8x+49/u5iPe4YdyM/L0s6uvFL8GdwwP/Y0OmbM9cfu+csdl7VkCYz/lf8Bf39/UOTY1dChovxJzhUtQBRZlG5lvnzDkK5tQo05UuNnn2Skn4XU0a17+CfQOzt2ndJu6VTiQ6tm7uWk+2nYlbuAx+4t4WbvM2XdJjmrifgntbwF63bMMzV5hL42rXy7FX7x3lGnNFmUuSLwzmkQcRc8vGddaMqbDWvgJv//hYsXXWVWGNgzXiY62p1G/zXwmNSF5/49A3ltel5PsfYPYEmKmelJFGqQKk722RLz/lKtxx5/Xe6KWZCyeZtCvjjPC+Tr0cxaJG8Q0v+r9BoeaEeN+CtzuNpc6uRm9jlfXZibf71dBbPdDHK2X2lY5FEO9Z8HaBfeD1Seec+f7DNTiLBng+P8mtMpXVSaN58yDYc/nb1ijIZjM0c2T3b+I2XAtN0SjXmC3P5fp/cOcPcCEg6xqsV1O79nXer+ssbGO0CpvG9EVgvzr6H1tjjaA9YOHr4RMO+3jGA9UYy1z/DubiPqZGbpFs/BO8qT6eW+ivsM/RGBq6AfVAQaYJEUIBOSFfa0nt+ynYTXv9x9bIobL/dyM0/fxjFmcpR/hNQFqXXgSz3bcWu07umijHVrpbuOVN0BI5mLjNa7t7gIJOPTEnwFzVz8wXyhra5eSHTr0Z2iE+pjSL9W/A2uQ/VkyrTTn/ewt0R/1M44Zq7S3s/4I7Q4G4je0tOBoaqTbxnBHr/9+K2qkA1/V6xccQ3/8B8/iDAkxHWheDbPwQvL/zfp4bNDRNK1trTMydbkMe0N+uLk5ec5va9VEwd93PxzSRlLIjGxclGxtuR+36AeBV19n1vSfxCj2yNrL/B+ajIwFmwSwJ7tbtqukLx765/u0O1I8H7IXnJ+yHcf0bmBNBe00yeYfE1vGd1eqnyea6O1F7Nubjr+edFrV8pLPBXPwQPxNlT1Q0rsReeAJ1bkF7XZE/U/bl/iH9vhT7v2AfHmHL1lnx/Y+7UB9ygJ+H0ptUWc0PLYBbHvJz5ePbHP8EbzzQru5ygf6UXR/Jzp3uhh5RwE75+y2sfwreyWNBXiaXFL9bS8zN7kGdZJDp5BTWRGLeBOZVAabOOkzrQv29qLkOMpNpL/FoclLm3TelPNxlYOeC48g8uNeu8t4btfPi92E8+deHdapbu9njldr5dDDHI0zP9S8p9DG185T7sdfVYGcGdbiHg/to0cddM0ZXVgaSKVku6/88gLzyAUFuJVdIVusY1jOzuHr5UHrtoL4+GPwptfgKd8XJ9hkehI9hZycr5tn6ZK8jfgZi/X/wpwb57jgzHa7C/BLMF4PjzNUUk/Yf+f7bQ8ivjASZxsZqoUzJEa5pJu6b4L4Y4rqbvoFr9WvHw7A32MaqdZ9PgjlbaCxhQ0yUFOIlvP8/gvuVIbYp1xDfD8neCTA/DvVtV+Pm8abGLbx3uTOyMWpaNxoeRd34JOyeZJ8afwL872vz16x6JNL5Urb/MeiL2fnqGqMT4P86Gb+6cgvHANj+xxGnO6A230QjUqX1dfgT4P89Mhl//UxOWFuX7X8CeSG7/WoxGLYf/NdHJudLa2Fx/eOTuBNlt19lnSfbbwP74VFix7dBiNhclHEfl3PvlLTHdxTlc/7zKe/X907OV2FfB3ZhsDa7uVNWa4fYqz6NPMRhtdmN2+8kyub7j2Cna9styuX3n5/xfj3dgVaum1XbvslEIJXG+kXg/zlai9/hFhtsLXynhO8=
*/