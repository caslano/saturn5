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
0bpVz0d7FJ6HowzRfSOz/0dmF8ckrkzJ90D8nkbM/uUC1Jf04sL4Rk/p8OG3v8LC21QhLTfyX/fwZX+HR9Bxzyy0//HwC7jyYy8ifH0Ns3/CPMzOnQfhdsSs/BeinSnH5oYCOHcCdNDsiN5jl5Uf8zCdz0MNLTrJBqzIEGtreTh91y/CdSi52ZOjpu7UQ8wS7keI5mMt5qMjdz7Yo5CRD9oeUhfjOiQuH55Xkdu5Vs7YfB3mYU1zzjxI0ctQfmo2zkvkrgP84on1583Kj/xyno++DjU1bH9wtaSEuQpW/ktQT5Obr2oS+euQ/zX//G0pFN8E9FkSswTPp7L5v0vR12QOvgxbCzb/h+xpTP9ZXBuRNEfE5v8uwzXKPPMfmB9ajtxf6NzF6BPL4JNn25cLf7cp85g52LbSHHNM6RiZ9lhdyPzJy4R1OqL9lTP/N5ejbZKHKaPtMv83yBw0hTKrFMtQimurhilgu1N6bGmNUC4t63ZXONwBrYxL3hgZYzYqk3Qg88n2HqaZbtIbLLH7MNEyrkfeW6keXiqtZcAvmxkVvMcCLWPTlehnpoUxpdhpU95K5C2bwXho+iB2nEHrtLITxxlc+ZKZhBTbknyqA0PmqhRjCre/ovW571XoO5hrozDLA3ZIYtdxUF4n8l7lyqanlWmaaQjlMf8PV+M4qc3Fgyaa0ETbfNIytiLz5nYX01AF65goby3yGqweXpOWFb4+no59mq7BsR9Xp8yWDWtWtBzI3n9kr0kxtpRxPuWVz0WdKVdWGNgKr1v67nch7wGu7cQSct7Fva5F3TfXbuqThU2ybBDnIG+HVhdP1QTbZTD/t9fhGD3l4tXrgp8d5VnIe4H7NgFMeFth/k+QN5F7fqASkjKmYfbP1zvMvtz38NjSqpLRMJoS/c1n6z+QuT7rYUrYy4fZP8xzmJt7y+nsoWPKsg9bgtxfvGWVYBtA2+2BN6Av/XbGlOLLlpZxHvIW9fCk+bBl9s83oj9C1hdUjFWmmrroOS/m/xB541s5ngVaIbIkXexYlfn/Q+asdo6ZNmKTbT989brwPe1o3cZvQnv6GV6uWJuSobTfQ9633nIq6SYjE1dBP2CZgucTWf93Mz5Xb1kl7IvJ+j9kXtrem9lgyGGGb8G1WimemSSiXYPgdkSZi5E5ycXUnFdGsE8ttv/RrfjOZD3MGBiM1kdjkyX09fR9XYDsc/zZ0tZK7Hob+ut0tScQa+NxKbxZyFvgeq62KbCc8m1A3qVZF69Bj4udH6LtNjUf19rNcPHADUZSi0nqE1Yjc1KrixmNxTThulhar5Hb0X8j/xxhjkO0rz3KW4a8q3leKmOJnl+nvKI7ULZMu3hp0Xs4sPX/yFtvcDzSw4r13UJ5292J3+lWnmdI8yU/C3nntPO8KGjulSYDHNZqZrMUbt8FuJ/z6RwXlHb1mkmGfJYmx79CK3K39uHCayJNJluH3Ov4eobBu4wxGC1r0124brPVzSQLPOozDaLLyvQ/yG1OebgNYnUkTP+7EPv2Xjw9LnqOhDKXIrPN+zzVRjMq+JtJn+fIu9Hfgaec+BUTbltDn+d85LZyXBnzbMz/3yJcT8F/q+OGMTkjtv0w+3fkqS6enhbdBzH7d+R9yrcdZybcjEuq0/g96Iedf4aNmvDvNJP/kLe23c1z5D6yU4vwdRuUrd6L+0252HLlBfpsVyL7Vq6eidJEicZlPdvy+9CvA8eUOT+8FHnT2nkeUV8olgQbP1rOgi6cq826uAnRY1v6LG9GXvXpPA9d6ktiDrofv2WtLiZ8rRukMWchs8ByM6NpbUSRYCYb/z2A35RmjqlmEinoCFVNvL8ppv9H7poz3VzR/po=
*/