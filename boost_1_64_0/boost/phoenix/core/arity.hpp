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
7OaRMdoZ9C5vG1LRx7lfYjCXl/GZH0kdW9j1gfFuczSSiwjnbwF5BkW9ur8hKKWoWWk+FhjYi1jc8pBKXepiy0hyJb/X+I4ZfkB+WdRNht46lCNeuNgByWaeNBw0wkjPoMN2Zo433/fZs8x/9Fpzxw3S8KlhUad5HekVH93VMgxACzMhC5efhq8FzUgafYDs5g+t9JE6ybgLPHWFNuYs4ARLNg0nsZXLmfuCi7qK40fsjOUf3/AEZo5+FElz4s6N50S9ayPYHzpSxojE+8b+OeQ6jZLjkCYwCHvpbMi4TU603sp3u3+0FBeSZcFF06RF9Hl64kyoS0xNgiqyWrKkZFMd9x1tDzuzcODztxVVFSNXObO5P9ZTiA+zxdpTZuFUWvfHguSeV7StA1kio3fdEG2emuHpTsBERBO60Ra4kIEm1P0vScP/3M4JTZt87PdrCqHSXBQXv3t0j3JVo0rOLj6NHIeBWrrcVczX+HoefyBXdl2RAgEbjFv3K+OPCRf1VyvqEGQusIenNSnAb5s+24q4n2X/TUaKNIaPfOMtGFBxKSeM76c2QPgdUA==
*/