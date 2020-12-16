/*==============================================================================
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2010 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_ARITY_HPP
#define BOOST_PHOENIX_CORE_ARITY_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/is_placeholder.hpp>
#include <boost/mpl/max.hpp>
#include <boost/mpl/int.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/support/vector.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/transform/fold.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    //
    //  Calculate the arity of an expression using proto transforms
    //
    /////////////////////////////////////////////////////////////////////////////
    
    struct arity;

    namespace result_of
    {
        template <typename Expr>
        struct arity
            : mpl::int_<
                evaluator::impl<
                    Expr const&
                  , vector2<
                        mpl::int_<0>
                      , boost::phoenix::arity
                    >&
                  , proto::empty_env
                >::result_type::value
            >
        {};
    }

    struct arity
    {
        template <typename Rule, typename Dummy = void>
        struct when
            : proto::fold<
                proto::_
              , mpl::int_<0>
              , proto::make<mpl::max<
                    proto::_state
                  , proto::call<
                        evaluator(
                            proto::_
                          , proto::call<
                                functional::context(_env, _actions)
                            >
                        )
                    >
                >()>
            >
        {};
    };

    template <typename Dummy>
    struct arity::when<rule::argument, Dummy>
        : proto::make<is_placeholder<proto::_value>()>
    {};
    
    template <typename Dummy>
    struct arity::when<rule::custom_terminal, Dummy>
        : proto::make<mpl::int_<0>()>
    {};
    
    template <typename Dummy>
    struct arity::when<rule::terminal, Dummy>
        : proto::make<mpl::int_<0>()>
    {};
}}

#endif

/* arity.hpp
+GW0w3yCVSdWMttUB/MC1pOc74cqF9rj+fy18TVpsngCXsfAIolZ3Fp+iO26ukG4StNcV8yMWRizMhYNVp7YSM/hM7G9MOmSGEtmLI2xdMYyGctmTNTI27wZMzFmZszCmJWxaMZsjCWAmUl/mFm1wVjMS22D+JKkiy46pT3GB4sMLY3SRp3qm43pYCI8naTLjDs2HcsarBaxv3YVScZyCYJrALGVM47+jvUOto2cr3GbH7pg7A3t1yppgS9O+mM7a2QQScQOXB4ai+XSGK5VxMp3ii+BdRsC1ypi3kVfjscYwDoRWziuS0fMSxMDrP1K21l19Rz5Lod2nDh6bagZ2y5YDLFT4cdxTmSFiX5dYsc9UntiH9PZN8MWJ+ExwaBpo31f9dtWeMxQg/Ai9d47dNgw7CsWA+wIKE25dakq1nsL7fmGvvejvH9vwbRBxhLAShBrsMAEF52896PFGMIMcA8rzbO1XzCeD8xMbH/dF3JuA1ae2Hyvva0wdrAgYq4nzWsx9rbaY+6t4JuNsYN5EHv9wY0emBddusRXf0zCvIAVIzbBUFE+PwLzJ3b1z6IDc80+KS9MrOSzV/CvqvkE62aQdnSOfP8lvR3Jp+65fSZYaWJnh750yTX7p+7cpWmehXi319bDHJ+CeH9rBvMm1iHpGK7PW8HKkHwqF1+swXLpYJ9DS7N8EfUuxgD2IbGdc2a/xLbUEeYMxDbt8pHzF7BBxOJvVxks32cwiLbEKhxy+wXrT2dTJ5wbiXkBq0As5E5h+T6KFdq8NO21gzETY2bGLIxZGYtmzMZYAmOJjCUxlsxYGmPpYEVp/cWs6oTjNVhrYkHx6/dguXSGeydF2oG+sUMx9giDWEDSDR816SLWA3SwZSTdm8Q+feT7BXCfSvvtvDUeGAPYCpLu/owaOGZ5R9rnfNJWDvq5MNYtWLyLtCouQytg7P0MIoD0o0JBu3BMtg6w79svrevfaW9h/YHV9pD2UUaafNdopP0+QNr5B6flPFlng+6k/oFtF14cGWiUtvRxxFJsZ3H2cV6aoYXtBeYFrDKxKU3Ou3H7sWMfi9dazZ8GV8PYdTar2dwsbINg7xEr2uLC31jW8EJwc2L9lxfdie0arAaxdgcOyXs1sDBiNV6Ph39VbS9jtTbt02Pf4DHB6hMr0uvaMRyTdTa6cfb7eMxxBrGVWNcrJvlscDzMUYgdsaXuxbIG8yf26Z5J3bGswfoRM0Q898TzTdDa09Sk4ZhOZ10yW6bK56JaS/IqfQXTgfkRC7xUZRfGzpj3RPguK7GYsdXkNRysCLGdtfadkM9TDeIksbjEedflM0yYg9E2EVflBpYZWAliS/9qL+eYYPHEvps4YCvGPhnuRYl9uW4TrrtZwIYT8/Vtfgrbks5mjB73BfajKXBNNUgrU+n3ythvpxrEOJJuQvXZ8zEdbJIUSOzlgwKzMAawBsRSJkTiMbPBhtA2nyrXZhLeh7GV2GbD3pNYD2BRxJrWaGHGvEyTY3lJ/TUnT4PzgQUR8z7xq1xLB9tO7GiTL8tifNMNYgmxiLeWBWFe4CWBGcQuT/p2M7azmQbRi5h/sb/lXAPsPrEPq3oO5b+dkfc3RbANzoF2Rizx5uFHOLaClSV2xf9jE7YlMDdi62ot+j7XrGAFiRUK+6ozxg62zSCt4pj3/8D45pF0+rkUWF1i2W0qneG+FZNr9o9Llif2bpvv5bobWG1iG0e9K9dfwIYRK+Z+YwEe8wOYKxJ7VqcVjnUmMG9iT88Pls+EwX5SpG2J7Psjtt2PYG5K0l0o7joZz5cIc3Zi63eZNuL5wAoRu9Nr+huMD4zms/60onhvaAWDhUuZl89298Y2+LE=
*/