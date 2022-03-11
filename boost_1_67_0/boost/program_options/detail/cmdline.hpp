// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_CMDLINE_VP_2003_05_19
#define BOOST_CMDLINE_VP_2003_05_19

#include <boost/program_options/config.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>


#include <boost/detail/workaround.hpp>

#include <boost/function.hpp>

#include <string>
#include <vector>

#if defined(BOOST_MSVC)
#   pragma warning (push)
#   pragma warning (disable:4251) // class 'std::vector<_Ty>' needs to have dll-interface to be used by clients of class 'boost::program_options::positional_options_description'
#endif

namespace boost { namespace program_options { namespace detail {

    /** Command line parser class. Main requirements were:
        - Powerful enough to support all common uses.
        - Simple and easy to learn/use.
        - Minimal code size and external dependencies.
        - Extensible for custom syntaxes.

        First all options are registered. After that, elements of command line
        are extracted using operator++. 

        For each element, user can find
        - if it's an option or an argument
        - name of the option
        - index of the option
        - option value(s), if any
        
        Sometimes the registered option name is not equal to the encountered
        one, for example, because name abbreviation is supported.  Therefore
        two option names can be obtained: 
        - the registered one 
        - the one found at the command line

        There are lot of style options, which can be used to tune the command
        line parsing. In addition, it's possible to install additional parser
        which will process custom option styles.

        @todo mininal match length for guessing?
    */
    class BOOST_PROGRAM_OPTIONS_DECL cmdline {
    public:

        typedef ::boost::program_options::command_line_style::style_t style_t;

        typedef function1<std::pair<std::string, std::string>, 
                          const std::string&> 
            additional_parser;

        typedef function1<std::vector<option>, std::vector<std::string>&>
            style_parser;
        
        /** Constructs a command line parser for (argc, argv) pair. Uses
            style options passed in 'style', which should be binary or'ed values
            of style_t enum. It can also be zero, in which case a "default"
            style will be used. If 'allow_unregistered' is true, then allows 
            unregistered options. They will be assigned index 1 and are
            assumed to have optional parameter.
        */
        cmdline(const std::vector<std::string>& args);

        /** @overload */
        cmdline(int argc, const char*const * argv);

        void style(int style);

        /** returns the canonical option prefix associated with the command_line_style
         *  In order of precedence:
         *      allow_long           : allow_long
         *      allow_long_disguise  : allow_long_disguise
         *      allow_dash_for_short : allow_short | allow_dash_for_short
         *      allow_slash_for_short: allow_short | allow_slash_for_short
         *  
         *      This is mainly used for the diagnostic messages in exceptions
        */ 
        int         get_canonical_option_prefix();

        void allow_unregistered();

        void set_options_description(const options_description& desc);
        void set_positional_options(
            const positional_options_description& m_positional);

        std::vector<option> run();

        std::vector<option> parse_long_option(std::vector<std::string>& args);
        std::vector<option> parse_short_option(std::vector<std::string>& args);
        std::vector<option> parse_dos_option(std::vector<std::string>& args);
        std::vector<option> parse_disguised_long_option(
            std::vector<std::string>& args);
        std::vector<option> parse_terminator(
            std::vector<std::string>& args);
        std::vector<option> handle_additional_parser(
            std::vector<std::string>& args);


        /** Set additional parser. This will be called for each token
            of command line. If first string in pair is not empty,
            then the token is considered matched by this parser,
            and the first string will be considered an option name
            (which can be long or short), while the second will be
            option's parameter (if not empty). 
            Note that additional parser can match only one token.
        */
        void set_additional_parser(additional_parser p);

        void extra_style_parser(style_parser s);

        void check_style(int style) const;
        
        bool is_style_active(style_t style) const;

        void init(const std::vector<std::string>& args);

        void
        finish_option(option& opt,
                      std::vector<std::string>& other_tokens,
                      const std::vector<style_parser>& style_parsers);

        // Copies of input.
        std::vector<std::string> m_args;
        style_t m_style;
        bool m_allow_unregistered;

        const options_description* m_desc;
        const positional_options_description* m_positional;

        additional_parser m_additional_parser;
        style_parser m_style_parser;
    };
    
    void test_cmdline_detail();
    
}}}

#if defined(BOOST_MSVC)
#   pragma warning (pop)
#endif

#endif


/* cmdline.hpp
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
*/