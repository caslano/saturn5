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
LdgkE2L7lCYZZAqwFAw8VquNczokKR5MkkBDjYsbVLJgi+RCspyBk0m5PD+4XIIttTJ+ULlIVvMAe+lgx3617f4ECScNPmGgBeckDCFxsB3nQuLCwSaWcvx8KDkG2/SCxCHkKFn2Ekg0kz5rfxj+pKfEI3D3buEx31aiby3EhdgMxOx0Xc5mf5u+zYHnmIQYjUj8EFKY4ArnEkN/0pDrDrkZx34bgX5YaaC9uOIj3YvjYnt/iJdL6+cD4X3oqkr+79OVK+ISQ38kePiqXNy/aroxeLzBnRFSw2Duf6OahVy46jPz/evsC6ksTfhv1LCEC1O+jz8cFSzkYoI/Sz18m+UELi7Ed7WHr76lPFf+H/Xw8aHOYTA/bhXXLXl2fPeqC67wYTz63EnYz8WGG/EdNG5k6NPfbOn4tyJ0SZb+m86CaHlGDXgWhVwG6TdQabHwSC582DaKU4Z5o/hCbhRU+zy5UWQPfGj9e2kh0bR8SB+mjSSKKoivfw7jlrILUhykimKP+73UvegdKv+rdsVzbfoSPL4hrEUr66i+2sVup58jWm14cogUlAW1TAuKnO21edqcdh+mxni89OjT9Y22NqHdhg1d939Q1j6l9rYTUnS/Qpr+MuudDHMNH4a9Cv/mDXPXG89JrolqXxj0lLH8AA6bjtPfWqMjtIf9kMCM/3XB/3XBYd4FyTDvgq2cenbAzeyrC8rPZbZ6be3s
*/