//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_SIMPLE_TRACE_APR_21_2010_0155PM)
#define BOOST_SPIRIT_KARMA_SIMPLE_TRACE_APR_21_2010_0155PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/karma/nonterminal/debug_handler_state.hpp>
#include <boost/fusion/include/out.hpp>
#include <iostream>

//  The stream to use for debug output
#if !defined(BOOST_SPIRIT_DEBUG_OUT)
#define BOOST_SPIRIT_DEBUG_OUT std::cerr
#endif

//  number of tokens to print while debugging
#if !defined(BOOST_SPIRIT_DEBUG_PRINT_SOME)
#define BOOST_SPIRIT_DEBUG_PRINT_SOME 20
#endif

//  number of spaces to indent
#if !defined(BOOST_SPIRIT_DEBUG_INDENT)
#define BOOST_SPIRIT_DEBUG_INDENT 2
#endif

namespace boost { namespace spirit { namespace karma
{
    struct simple_trace
    {
        int& get_indent() const
        {
            static int indent = 0;
            return indent;
        }

        void print_indent() const
        {
            int n = get_indent();
            n *= BOOST_SPIRIT_DEBUG_INDENT;
            for (int i = 0; i != n; ++i)
                BOOST_SPIRIT_DEBUG_OUT << ' ';
        }

        template <typename Buffer>
        void print_some(char const* tag, Buffer const& buffer) const
        {
            print_indent();
            BOOST_SPIRIT_DEBUG_OUT << '<' << tag << '>' << std::flush;
            {
                std::ostreambuf_iterator<char> out(BOOST_SPIRIT_DEBUG_OUT);
                buffer.buffer_copy_to(out, BOOST_SPIRIT_DEBUG_PRINT_SOME);
            }
            BOOST_SPIRIT_DEBUG_OUT << "</" << tag << '>' << std::endl;
        }

        template <typename OutputIterator, typename Context, typename State
          , typename Buffer>
        void operator()(
            OutputIterator&, Context const& context
          , State state, std::string const& rule_name
          , Buffer const& buffer) const
        {
            switch (state)
            {
                case pre_generate:
                    print_indent();
                    ++get_indent();
                    BOOST_SPIRIT_DEBUG_OUT
                        << '<' << rule_name << '>' << std::endl;
                    print_indent();
                    ++get_indent();
                    BOOST_SPIRIT_DEBUG_OUT << "<try>" << std::endl;;
                    print_indent();
                    BOOST_SPIRIT_DEBUG_OUT << "<attributes>";
                    traits::print_attribute(
                        BOOST_SPIRIT_DEBUG_OUT,
                        context.attributes
                    );
                    BOOST_SPIRIT_DEBUG_OUT << "</attributes>" << std::endl;
                    if (!fusion::empty(context.locals))
                    {
                        print_indent();
                        BOOST_SPIRIT_DEBUG_OUT
                            << "<locals>" << context.locals << "</locals>"
                            << std::endl;
                    }
                    --get_indent();
                    print_indent();
                    BOOST_SPIRIT_DEBUG_OUT << "</try>" << std::endl;;
                    break;

                case successful_generate:
                    print_indent();
                    ++get_indent();
                    BOOST_SPIRIT_DEBUG_OUT << "<success>" << std::endl;
                    print_some("result", buffer);
                    if (!fusion::empty(context.locals))
                    {
                        print_indent();
                        BOOST_SPIRIT_DEBUG_OUT
                            << "<locals>" << context.locals << "</locals>"
                            << std::endl;
                    }
                    --get_indent();
                    print_indent();
                    BOOST_SPIRIT_DEBUG_OUT << "</success>" << std::endl;
                    --get_indent();
                    print_indent();
                    BOOST_SPIRIT_DEBUG_OUT 
                        << "</" << rule_name << '>' << std::endl;
                    break;

                case failed_generate:
                    print_indent();
                    BOOST_SPIRIT_DEBUG_OUT << "<fail/>" << std::endl;
                    --get_indent();
                    print_indent();
                    BOOST_SPIRIT_DEBUG_OUT 
                        << "</" << rule_name << '>' << std::endl;
                    break;
            }
        }
    };
}}}

#endif

/* simple_trace.hpp
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
*/