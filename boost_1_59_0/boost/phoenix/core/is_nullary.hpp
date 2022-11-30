/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_IS_NULLARY_HPP
#define BOOST_PHOENIX_CORE_IS_NULLARY_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/phoenix/core/is_actor.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/support/vector.hpp>
#include <boost/proto/transform/fold.hpp>
#include <boost/proto/transform/lazy.hpp>

namespace boost { namespace phoenix
{
    namespace result_of
    {
        template <typename Expr, typename Enable = void>
        struct is_nullary;
    }

    struct is_nullary
    {
        template <typename Rule, typename Dummy = void>
        struct when
            : proto::fold<
                proto::_
              , mpl::true_()
              , mpl::and_<
                    proto::_state
                  , proto::call<evaluator(proto::_, _context)>
                >()
            >
        {};
    };
    
    template <typename Dummy>
    struct is_nullary::when<rule::argument, Dummy>
    {
        BOOST_PROTO_TRANSFORM(is_nullary::when<rule::argument>)
        template <typename Expr, typename State, typename Data>
        struct impl
        {
            typedef mpl::false_ result_type;
        };
    };
    
    template <
        typename Trait
      , typename Expr
      , typename State
      , typename Data
      , bool IsTransform = proto::is_transform<Trait>::value
    >
    struct is_nullary_custom_terminal_impl
    {
        typedef typename Trait::type result_type;
    };
    
    template <typename Transform, typename Expr, typename State, typename Data>
    struct is_nullary_custom_terminal_impl<Transform, Expr, State, Data, true>
    {
        typedef
            typename Transform::template impl<
                Expr
              , State
              , Data
            >::result_type
            result_type;
    };

    template <typename Dummy>
    struct is_nullary::when<rule::custom_terminal, Dummy>
    {
        BOOST_PROTO_TRANSFORM(is_nullary::when<rule::custom_terminal>)
        
        template <typename Expr, typename State, typename Data>
        struct impl
            : is_nullary_custom_terminal_impl<
                result_of::is_nullary<
                    custom_terminal<
                        typename proto::detail::uncvref<
                            typename proto::result_of::value<Expr>::type
                        >::type
                    >
                >
              , typename proto::result_of::value<Expr>::type
              , State
              , Data
            >
        {};
    };
    
    template <typename Dummy>
    struct is_nullary::when<rule::terminal, Dummy>
    {
        BOOST_PROTO_TRANSFORM(is_nullary::when<rule::terminal>)
        template <typename Expr, typename State, typename Data>
        struct impl
        {
            typedef mpl::true_ result_type;
        };
    };

    namespace result_of
    {
        template <typename Expr, typename Enable>
        struct is_nullary
            : boost::phoenix::evaluator::impl<
                Expr const &
              , vector2<
                    mpl::true_
                  , boost::phoenix::is_nullary
                >
              , proto::empty_env
            >::result_type
        {};
        
        template <typename T>
        struct is_nullary<T & >
            : is_nullary<T>
        {};

        template <typename T>
        struct is_nullary<T const & >
            : is_nullary<T>
        {};

        template <typename T>
        struct is_nullary<T const >
            : is_nullary<T>
        {};

        template <typename T>
        struct is_nullary<custom_terminal<T> >
            : mpl::true_
        {};

        template <typename T>
        struct is_nullary<custom_terminal<actor<T> > >
            : evaluator
        {};
        
        template <typename T>
        struct is_nullary<custom_terminal<boost::reference_wrapper<actor<T> > > >
        {
            BOOST_PROTO_TRANSFORM(is_nullary<custom_terminal<boost::reference_wrapper<actor<T> > > >)
            template <typename Expr, typename State, typename Data>
            struct impl
            {
                typedef typename evaluator::template impl<actor<T>, State, Data>::result_type result_type;
            };
        };
        
        template <typename T>
        struct is_nullary<custom_terminal<boost::reference_wrapper<actor<T> const> > >
        {
            BOOST_PROTO_TRANSFORM(is_nullary<custom_terminal<boost::reference_wrapper<actor<T> const> > >)
            template <typename Expr, typename State, typename Data>
            struct impl
            {
                typedef typename evaluator::template impl<actor<T> const, State, Data>::result_type result_type;
            };
        };
    }

}}

#endif


/* is_nullary.hpp
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
*/