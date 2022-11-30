// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARSERS_HPP_VP_2004_05_06
#define BOOST_PARSERS_HPP_VP_2004_05_06

#include <boost/program_options/detail/convert.hpp>

#include <iterator>

namespace boost { namespace program_options {

    template<class charT>
    basic_command_line_parser<charT>::
    basic_command_line_parser(const std::vector<
                              std::basic_string<charT> >& xargs)
       : detail::cmdline(to_internal(xargs))
    {}


    template<class charT>
    basic_command_line_parser<charT>::
    basic_command_line_parser(int argc, const charT* const argv[])
    : detail::cmdline(
        to_internal(std::vector<std::basic_string<charT> >(argv+1, argv+argc))),
        m_desc()
    {}

    
    template<class charT>
    basic_command_line_parser<charT>& 
    basic_command_line_parser<charT>::options(const options_description& desc)
    {
        detail::cmdline::set_options_description(desc);
        m_desc = &desc;
        return *this;
    }

    template<class charT>
    basic_command_line_parser<charT>& 
    basic_command_line_parser<charT>::positional(
        const positional_options_description& desc)
    {
        detail::cmdline::set_positional_options(desc);
        return *this;
    }

    template<class charT>
    basic_command_line_parser<charT>& 
    basic_command_line_parser<charT>::style(int xstyle)
    {
        detail::cmdline::style(xstyle);
        return *this;
    }

    template<class charT>
    basic_command_line_parser<charT>& 
    basic_command_line_parser<charT>::extra_parser(ext_parser ext)
    {
        detail::cmdline::set_additional_parser(ext);
        return *this;
    }

    template<class charT>
    basic_command_line_parser<charT>& 
    basic_command_line_parser<charT>::allow_unregistered()
    {
        detail::cmdline::allow_unregistered();
        return *this;
    }

    template<class charT>
    basic_command_line_parser<charT>& 
    basic_command_line_parser<charT>::extra_style_parser(style_parser s)
    {
        detail::cmdline::extra_style_parser(s);
        return *this;
    }



    template<class charT>    
    basic_parsed_options<charT>
    basic_command_line_parser<charT>::run()
    {
        // save the canonical prefixes which were used by this cmdline parser
        //    eventually inside the parsed results
        //    This will be handy to format recognisable options
        //    for diagnostic messages if everything blows up much later on
        parsed_options result(m_desc, detail::cmdline::get_canonical_option_prefix());
        result.options = detail::cmdline::run();

        // Presense of parsed_options -> wparsed_options conversion
        // does the trick.
        return basic_parsed_options<charT>(result);
    }


    template<class charT>
    basic_parsed_options<charT>
    parse_command_line(int argc, const charT* const argv[],
                       const options_description& desc,
                       int style,
                       function1<std::pair<std::string, std::string>, 
                                 const std::string&> ext)
    {
        return basic_command_line_parser<charT>(argc, argv).options(desc).
            style(style).extra_parser(ext).run();
    }

    template<class charT>
    std::vector< std::basic_string<charT> > 
    collect_unrecognized(const std::vector< basic_option<charT> >& options,
                         enum collect_unrecognized_mode mode)
    {
        std::vector< std::basic_string<charT> >  result;
        for(unsigned i = 0; i < options.size(); ++i)
        {
            if (options[i].unregistered ||
                (mode == include_positional && options[i].position_key != -1))
            {
                copy(options[i].original_tokens.begin(),
                     options[i].original_tokens.end(),
                     back_inserter(result));
            }
        }
        return result;
    }


}}

#endif

/* parsers.hpp
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
*/