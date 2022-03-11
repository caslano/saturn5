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