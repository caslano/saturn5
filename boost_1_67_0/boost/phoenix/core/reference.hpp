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