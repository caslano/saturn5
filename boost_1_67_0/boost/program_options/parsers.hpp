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