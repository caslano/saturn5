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