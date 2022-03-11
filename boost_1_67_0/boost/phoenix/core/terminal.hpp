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
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
*/