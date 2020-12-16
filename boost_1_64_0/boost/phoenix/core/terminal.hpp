/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_TERMINAL_HPP
#define BOOST_PHOENIX_CORE_TERMINAL_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/is_placeholder.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/transform/lazy.hpp>
#include <boost/proto/functional/fusion/at.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#define BOOST_PHOENIX_DEFINE_CUSTOM_TERMINAL(Template, Terminal, IsNullary, EvalFun)\
    namespace boost { namespace phoenix                                         \
    {                                                                           \
        namespace result_of                                                     \
        {                                                                       \
            Template                                                            \
            struct is_nullary<                                                  \
                custom_terminal<                                                \
                    Terminal                                                    \
                >                                                               \
            >                                                                   \
                : IsNullary                                                     \
            {};                                                                 \
        }                                                                       \
        Template                                                                \
        struct is_custom_terminal<Terminal >: mpl::true_ {};                    \
                                                                                \
        Template                                                                \
        struct custom_terminal<Terminal > : proto::call<EvalFun > {};           \
    }}                                                                          \
/**/

namespace boost { namespace phoenix
{
    template <typename T, typename Dummy>
    struct is_custom_terminal
        : mpl::false_ {};

    template <typename T, typename Dummy>
    struct custom_terminal;

    namespace tag {
      struct terminal /*: public proto::tag::terminal */ {};
    }
 
    namespace expression
    {
        template <typename T, template <typename> class Actor = actor>
        struct terminal
            : proto::terminal<T>
        {
            typedef
                proto::basic_expr<
                proto::tag::terminal
            // tag::terminal //cannot change to use phoenix tag - breaks code.
                  , proto::term<T>
                  , 0
                >
                base_type;
            typedef Actor<base_type> type;
            
            static const type make(T const& t)
            {
            // ?? Should the next line be Actor not actor which is the default?
                actor<base_type> const e = {base_type::make(t)};
                //Actor<base_type> const e = {base_type::make(t)};
                return e;
            }
        };
    }

    namespace rule
    {
        struct argument
            : proto::if_<boost::is_placeholder<proto::_value>()>
        {};

        struct custom_terminal
            : proto::if_<boost::phoenix::is_custom_terminal<proto::_value>()>
        {};
        
        struct terminal
            : proto::terminal<proto::_>
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<proto::tag::terminal, Dummy>
        : proto::or_<
            enable_rule<rule::argument       , Dummy>
          , enable_rule<rule::custom_terminal, Dummy>
          , enable_rule<rule::terminal       , Dummy>
        >
    {};

    template <typename Dummy>
    struct default_actions::when<rule::custom_terminal, Dummy>
        : proto::lazy<
            custom_terminal<proto::_value>(
                proto::_value
              , _context
            )
        >
    {};

    namespace detail
    {
        template <typename N>
        struct placeholder_idx
            : mpl::int_<N::value>
        {};
    }
    
    template <typename Grammar>
    struct default_actions::when<rule::argument, Grammar>
        : proto::call<
            proto::functional::at(
                _env
              , proto::make<
                    detail::placeholder_idx<
                        proto::make<
                            boost::is_placeholder<proto::_value>()
                        >
                    >()
                >
            )
        >
    {};
}}

#endif

/* terminal.hpp
V65Z1OmfvkSROao56qzTZb8zir2mYsVkFu/M4Pk/VkLmWnZNB8VcuxjvZ6eYJ7NmivmSOZn/0xcvxUq7UV/K2nVRTNe97JrUrrNiBs0MvpQSU3MWzIOsYdn9uikW1N3YFz/Fgpn1Y2ZBptNhbc3ooZiFYFaC6QUzCOYgmKNgToI5C+YqmLtgHoJ5CuYlmLdgPoL5CuZXrul0/jrj3OypQVm7KNaul3LNaMFiBIsVLE6wtYLFl2t0zmDx+ZvE11mXzdp9rBs5jluOYLmC5QmWL9hVwQoEKxTsvmBFghULViJYqWC6CuUZ/a+CMUeBuu4juXmzdn11ZgZuPoL5lmsjuvqx+32k6xFsNLcK4axdH/pvfs0I1i5AV8HAazCRtftQqcEk1q63MsdyWLsmSl3nCpYnWL5gVwUrEKxQsPuCFQlWLFiJYKWC6czKNwvBrATTC2YQzEEwR8GcBHMWzFUwd8E8BPMUzEswb8F8BPMVzE8wf8ECBAsULEiwYMFCBAsVbLRgYYKNFyxcsAjBIgWbLViUYNGCxQgWK1icYGsFixcsQbBEwZIESxYsRbBUwfYJliZYumAZgmUKliVYtmA5guUKlidYvmBXBSsQrFCw+4IVCVYsWIlgpYLpzMs3C8GsBNMLZhDMQTBHwZwEcxbMVTB3wTwE8xTMSzBvwXwE8xXMTzB/wQIECxQsSLBgwUIECxVstGBhgo0XLFywCMEiBZstWJRg0YLFCBYrWJxgawWLFyxBsETBkgRLFixFsFTB9gmWJli6YBmCZQqWJVi2YDmC5QqWJ1i+YFcFKxCsULD7ghUJVixYiWClgtH/lWsWglkJphfMIJiDYI6COQnmLJirYO6CeQjmKZiXYN6C+QjmK5ifYP6CBQgWKFiQYMGChQgWKthowcIEGy9YuGARgkUKNluwKMGiBYsRLFawOMHWChYvWIJgiYIlCZYsWIpgqYLtEyxNsHTBMgTLFCxLsGzBcgTLFSxPsHzBrgpWIFihYPcFKxKsWLASwUoF01mWbxaCWQmmF8wgmINgjoI5CeYsmKtg7oJ5COYpmJdg3oL5COYrmJ9g/oIFCBYoWJBgwYKFCBYq2GjBwgQbL1i4YBGCRQo2W7AowaIFixEsVrA4wdYKFi9YgmCJgiUJlixYimCpgu0TLE2wdMEyBMsULEuwbMFyBMsVLE+wfMGuClYgWKFg9wUrEqxYsBLBSgXTVSzfLASzEkwvmEEwB8EcBXMSzFkwV8HcBfMQzFMwL8G8BfMRzFcwP8H8BQsQLFCwIMGCBQsRLFSw0YKFCTZesHDBIgSLFGy2YFGCRQsWI1isYHGCrRUsXrAEwRIFSxIsWbAUwVIF2ydYmmDpgmUIlilYlmDZguUIlitYnmD5gl0VrECwQsHuC1YkWLFgJYKVCqarVL5ZCGYlmF4wg2AOgjkK5iSYs2CugrkL5iGYp2BegnkL5iOYr2B+gvkLFiBYoGBBggULFiJYqGCjBQsTbLxg4YJFCBYp2GzBogSLFixGsFjB4gRbK1i8YAmCJQqWJFiyYCmCpQq2T7A0wdIFyxAsU7AswbIFyxEsV7A8wfIFuypYgWCFgt0XrEiwYsFKBCsVTGdVvlkIZiWYXjCDYA6COQrmJJizYK6CuQvmIZinYF6CeQvmI5ivYH6C+QsWIFigYEGCBQsWIlioYKMFCyvXdLrxmuk8M5pqUGaF1jqdQzlWyqynYgYbo/kr5gpTfw5+RFdvGH62Hu0CmPVWrhnKTP0OQARMjYH2TTKLcr73EitYnGBrBYsXLEGwRMGSBEsWLEWwVMH2CZYmWLpgGYJlCpYlWHa5ptPllBlql7Wzqmxsp35XSC+YQTAHwRw=
*/