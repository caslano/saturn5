/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_VALUE_HPP
#define BOOST_PHOENIX_CORE_VALUE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/as_actor.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/phoenix/core/is_value.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    ////////////////////////////////////////////////////////////////////////////
    //
    // values
    //
    //      function for evaluating values, e.g. val(123)
    //
    ////////////////////////////////////////////////////////////////////////////
 
    namespace expression
    {
        template <typename T>
        struct value
            : expression::terminal<T>
        {
            typedef
                typename expression::terminal<T>::type
                type;
           /*
            static const type make(T & t)
            {
                typename value<T>::type const e = {{t}};
                return e;
            }
           */
        };
    }

    template <typename T>
    inline
    typename expression::value<T>::type const
    val(T t)
    {
        return expression::value<T>::make(t);
    }

    // Identifies this Expr as a value.
    // I think this is wrong. It is identifying all actors as values.
    // Yes, it is giving false positives and needs a rethink.
    // And this gives no positives.
    //template <typename T>
    //struct is_value<expression::value<T> >
    //    : mpl::true_
    //{};

    // Call out actor for special handling
  // Is this correct? It applies to any actor.
  // In which case why is it here?
    template<typename Expr>
    struct is_custom_terminal<actor<Expr> >
      : mpl::true_
    {};
    
    // Special handling for actor
    template<typename Expr>
    struct custom_terminal<actor<Expr> >
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Actor, typename Context>
        struct result<This(Actor, Context)>
            : boost::remove_const<
                    typename boost::remove_reference<
                    typename evaluator::impl<Actor, Context, proto::empty_env>::result_type
                 >::type
             >
        {};

        template <typename Context>
        typename result<custom_terminal(actor<Expr> const &, Context &)>::type
        operator()(actor<Expr> const & expr, Context & ctx) const
        {
          typedef typename result<custom_terminal(actor<Expr> const &, Context &)>::type result_type;
          result_type r = boost::phoenix::eval(expr, ctx);
          // std::cout << "Evaluating val() = " << r << std::endl;
          return r;
        }
    };

    namespace meta
    {
        template<typename T>
        struct const_ref
            : add_reference<typename add_const<T>::type>
        {};

        template<typename T>
        struct argument_type
            : mpl::eval_if_c<
                is_function<typename remove_pointer<T>::type>::value
              , mpl::identity<T>
              , const_ref<T>
            >
        {
            typedef T type;
        };

        template <typename T>
        struct decay
        {
            typedef T type;
        };
        template <typename T, int N>
        struct decay<T[N]> : decay<T const *> {};
    }
    
    template <typename T>
    struct as_actor<T, mpl::false_>
    {
        typedef typename expression::value<typename meta::decay<T>::type >::type type;

        static type
        convert(typename meta::argument_type<typename meta::decay<T>::type>::type t)
        {
            return expression::value<typename meta::decay<T>::type >::make(t);
        }
    };
}}

#endif

/* value.hpp
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
*/