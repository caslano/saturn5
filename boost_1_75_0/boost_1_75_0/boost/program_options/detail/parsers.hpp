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
ZY5OYkQXzRj8V1PKRiVT5OSSWDAfcQ2Ea4r+b82G5cAylz5+t5sOpA/to2cdnXOEJ1IvA1w4jA9t7B/ddvvDUT3wluhNuxFgnRzmFw03pM2ozZhe/Qzdz8CUbbRvn0+5CT5sWncy789Z0pcLdFBHZh5SS2KtHhk9Th3rKPrXSSNU54sVv+vqKH/i0ZiHWpjbwXwqCkrZh8AIItSvBqIvIp1ntZgd4prHkwasXvS6HAbSaIQCcdqd8pl05G+NUtMR9+hx0hvPALDDd9BxF9jx5yx5x6T+6mDvmKIJoyI6wyLX0sTRN4WrfOSdw45NgADXMsfctI1lYaZNydu3KDZqTF2mi40S3oGv6cT1l8Crm5p3g7r3+j9L2fbq3s91H8EVr5O5Hzc+NzOQyNIsSTz5JhK/C09GI8PwYAZFTfiJKULn9EZnqRucrbPpqbC7ZyyQIRHpquIyUrhgGYgC4d0wT8RPFfMX4M3nyLQSLfWt7YoVE8t3t21zvOgEtPEwcqC7zRIAbXGxbjHUThgONYZblFLgfYMbnepOomXJHfeglaZyI3+ROzpVieBWw+esX2n/9Du9nLoyj4MySibsqnbR1bTIJWaKcLAYxKtHsEqjZMjA2bBzhZfvnaL+lBLWR9vpLwix6b2GH74OiMlEQ7/E8dX9KYW9OUex1Igdz1wjnKpYn0qIeJlExNAaD8dCjFoEQc3cIO4cVzORvE3L
*/