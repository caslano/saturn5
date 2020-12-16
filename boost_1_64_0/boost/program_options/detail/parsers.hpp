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
4SznnnHLUL33XMzKWpupr0hq2WjM4utiJlcXUHuMtQZZh4bwiKx5yMo4MHgO/fLecp1TMjpmnNezRNBBxJMhPOL9JpzP1YcSMxIJI0nyB/fd6gL+Gsm6z/lpmmkQFitTk1OmcHWhZUBGWFuZx54v1C1tK3itk10jl9j52ax+es4Ptm05nPMl48bAHkacLircF/1oUH8aWM6DPGWJacTvO6m/Uve1JnvrPnot4b0WM5Loj4O185XYzgtGFhTw70aKlilp6el0lOSU5rML8zkwhEfM5y4uXtRsVDTTNEwX71XnvvqwgkMPIftW4D37orprtxAe8Z5z+fdEqYpWYf5pulGYblAIj5juEfquuNOx8i118lGWKs3GUlbEXpDD7jkIO8BPQnjEez7kystUw5zs1POPPeczcMFo1syGuDGVXNtqFp8mk1S5a6Nd13T6gpFrp/hdU4aRNnwGu8batqtsWdYXaI2aCV0b1w80Ydm2CeERy9bmKoO7P5qbI80ULo3uSfNqjjTX0+fiw+m7qX+a2SwN47BnVYdpzgnhEdO8QdNwzyof6m6d63zSSNKceN6LFaydjiTdWDfEArutd9l626su+3n4rcU7D5uyZMhRK944B96HcnL+l2dnvHxxfsGK26dPeNNYm90J9iKx16NFwXYHYivEORAXQFwGcRXEDRC3qwcbH4iVEFWIbRA7IXZBXA5xNcQNEAfF+oUKIFZCjEPsgDgP4hKIKyF2Qxyg9gvtC/EYiOMhpiDOUgNdchCCEIQgBCEI/+ZgD71PFSr/x5qiSRXE+KLGNNECyPcB0M7Z+LehrLgn+gEcDPFX+OdOMofejtKOQvNI1v9/MTgE10rJFd1I1mgxw1SJHFKat71TR5i+D1nfD3PqJN3XTrq0BaN9Pd2kmWVmNKH1pOvvSQe2+WTt/qckXYkBVZy1kEbTbOlJMwBZG/e104TBr0LUigEKU7N0AzzptoO/qW+BGVA/uE7AL7QNIYwtSLmgLrw1AWm3IHmH8vYuLaa1bw7l8pTK5m5B8gL598l94E9AhD+B39g7E+AmqjCO79YGEBFp7SW2WCsqHmgRVDxR8R48UEDuJU3SEpomIYeCg05VHFFUqoKDgweOiMig01GOqqAdxaNYoSojoqAgUkELKlYBLYP/996XkISkJDQtCt9v5vXf3WT3vX3bdPJ/73vfPiW9Ql3Ge2tP+mp11sW7u9/2ac322bHXEaTqal1ArXX/nAEN2CfWAmg2+AhbeP6AQmw3l0PgarweWBvgwO+R6wMexb5G6EJo6DqBOptaJ9BgM8WVWyC12BS2ViAf2zljtZg5BgrxemSegQHF7GEYhmEYhmGYI4/WiP+3WMaWSuvfBt5/Grzt5eT9J9HcODaCuhue9MaHKP8fmub32H0TDXhQS6lhcblK7TaVdw+2C+8J7FG5/9K1wLFHB710RbNeeor00umYFxosj9OKzXaH3yPraCfrSA/Uwd43Kd63RnpfR5+FmxfMO7vyq2WOquphNTWxve9q7cDe91DnzOswSvrZuHPmVbCXZRiGYRiGYRgmDpLv/80Oh8ti7nWBHAE43NYAlNm9FqwACLlMWgQQiD+YTmMQZ2ukgZjTaSpOVB1moPOKbEavC+RYwVz1Gr3UNzguUIjyt/S39Vv7nvP6tWe8vrmb6a1ZHZdcFzs+dAeOqdSovpB2HI8yZ1+bymUsP6UrOBdqUvWVt4f2gnaEngftBO0N7QztA+0CPR+aJq4ZmgW9BJoNvRR6IvQyaB70cmg+tB/FGFwB7Q69Enoa9Cro6dD+UPF3+DX7WIZhGIZhGIZhmFYj+f4fk/9eH83/H8b+ny5Tuv+Q9bAzyf/31Eg=
*/