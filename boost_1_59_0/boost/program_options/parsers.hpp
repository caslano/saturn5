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
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
*/