/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_REFERENCE_HPP
#define BOOST_PHOENIX_CORE_REFERENCE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/ref.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    //
    // reference
    //
    //      function for evaluating references, e.g. ref(123)
    //
    /////////////////////////////////////////////////////////////////////////////
    namespace expression
    {
        template <typename T>
        struct reference
            : expression::terminal<reference_wrapper<T> >
        {
            typedef
                typename expression::terminal<reference_wrapper<T> >::type
                type;

            static const type make(T & t)
            {
                typename reference<T>::type const e = {{boost::ref(t)}};
                return e;
            }
        };
        
        template <typename T>
        struct reference<T const>
            : expression::terminal<reference_wrapper<T const> >
        {
            typedef
                typename expression::terminal<reference_wrapper<T const> >::type
                type;

            static const type make(T const & t)
            {
                typename reference<T const>::type const e = {{boost::cref(t)}};
                return e;
            }
        };
    }

    namespace rule
    {
        struct reference
            : expression::reference<proto::_>
        {};
    }

    template <typename T>
    inline
    typename expression::reference<T>::type const
    ref(T & t)
    {
        return expression::reference<T>::make(t);
    }

    template <typename T>
    inline
    typename expression::reference<T const>::type const
    cref(T const & t)
    {
        return expression::reference<T const>::make(t);
    }

    // Call out boost::reference_wrapper for special handling
    template<typename T>
    struct is_custom_terminal<boost::reference_wrapper<T> >
      : mpl::true_
    {};

    // Special handling for boost::reference_wrapper
    template<typename T>
    struct custom_terminal<boost::reference_wrapper<T> >
    {
        typedef T &result_type;

        template <typename Context>
        T &operator()(boost::reference_wrapper<T> r, Context &) const
        {
            return r;
        }
    };
    
    template<typename Expr>
    struct custom_terminal<boost::reference_wrapper<actor<Expr> > >
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Context>
        struct result<This(boost::reference_wrapper<actor<Expr> > const &, Context)>
            : boost::result_of<evaluator(actor<Expr> &, Context)>
        {};

        template <typename This, typename Context>
        struct result<This(boost::reference_wrapper<actor<Expr> > &, Context)>
            : boost::result_of<evaluator(actor<Expr> &, Context)>
        {};

        template <typename Context>
        typename boost::result_of<evaluator(actor<Expr> &, Context const &)>::type
        operator()(boost::reference_wrapper<actor<Expr> > & r, Context const & ctx) const
        {
            return boost::phoenix::eval(r, ctx);
        }
    };
    
    template<typename Expr>
    struct custom_terminal<boost::reference_wrapper<actor<Expr> const> >
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Context>
        struct result<This(boost::reference_wrapper<actor<Expr> const> const &, Context)>
            : boost::result_of<evaluator(actor<Expr> const&, Context)>
        {};

        template <typename This, typename Context>
        struct result<This(boost::reference_wrapper<actor<Expr> const> &, Context)>
            : boost::result_of<evaluator(actor<Expr> const&, Context)>
        {};

        template <typename Context>
        typename boost::result_of<evaluator(actor<Expr> const&, Context const &)>::type
        operator()(boost::reference_wrapper<actor<Expr> const> const & r, Context & ctx) const
        {
            return boost::phoenix::eval(unwrap_ref(r), ctx);
        }
    };
}}

#endif

/* reference.hpp
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
*/