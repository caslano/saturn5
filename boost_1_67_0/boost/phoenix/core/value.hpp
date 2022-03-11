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