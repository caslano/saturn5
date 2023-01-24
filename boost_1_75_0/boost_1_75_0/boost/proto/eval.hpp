///////////////////////////////////////////////////////////////////////////////
/// \file eval.hpp
/// Contains the eval() expression evaluator.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EVAL_HPP_EAN_03_29_2007
#define BOOST_PROTO_EVAL_HPP_EAN_03_29_2007

#include <boost/proto/proto_fwd.hpp> // BOOST_PROTO_CALLABLE
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace proto
{

    namespace result_of
    {
        /// \brief A metafunction for calculating the return type
        /// of \c proto::eval() given a certain \c Expr and \c Context
        /// types.
        ///
        /// \note The types \c Expr and \c Context should not be
        /// reference types. They may be cv-qualified, but the
        /// cv-qualification on the \c Context parameter is ignored.
        template<typename Expr, typename Context>
        struct eval
        {
            typedef typename Context::template eval<Expr>::result_type type;
        };
    }

    namespace functional
    {
        /// \brief A PolymorphicFunctionObject type for
        /// evaluating a given Proto expression with a given
        /// context.
        struct eval
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename Context>
            struct result<This(Expr, Context)>
            {
                typedef
                    typename proto::result_of::eval<
                        typename remove_reference<Expr>::type
                      , typename remove_reference<Context>::type
                    >::type
                type;
            };

            /// \brief Evaluate a given Proto expression with a given
            /// context.
            /// \param expr The Proto expression to evaluate
            /// \param context The context in which the expression should be
            ///     evaluated.
            /// \return <tt>typename Context::template eval<Expr>()(expr, context)</tt>
            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr, Context>::type
            operator ()(Expr &e, Context &ctx) const
            {
                return typename Context::template eval<Expr>()(e, ctx);
            }

            /// \overload
            ///
            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr, Context>::type
            operator ()(Expr &e, Context const &ctx) const
            {
                return typename Context::template eval<Expr>()(e, ctx);
            }

            /// \overload
            ///
            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr const, Context>::type
            operator ()(Expr const &e, Context &ctx) const
            {
                return typename Context::template eval<Expr const>()(e, ctx);
            }

            /// \overload
            ///
            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr const, Context>::type
            operator ()(Expr const &e, Context const &ctx) const
            {
                return typename Context::template eval<Expr const>()(e, ctx);
            }
        };
    }

    /// \brief Evaluate a given Proto expression with a given
    /// context.
    /// \param expr The Proto expression to evaluate
    /// \param context The context in which the expression should be
    ///     evaluated.
    /// \return <tt>typename Context::template eval<Expr>()(expr, context)</tt>
    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr, Context>::type
    eval(Expr &e, Context &ctx)
    {
        return typename Context::template eval<Expr>()(e, ctx);
    }

    /// \overload
    ///
    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr, Context>::type
    eval(Expr &e, Context const &ctx)
    {
        return typename Context::template eval<Expr>()(e, ctx);
    }

    /// \overload
    ///
    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr const, Context>::type
    eval(Expr const &e, Context &ctx)
    {
        return typename Context::template eval<Expr const>()(e, ctx);
    }

    /// \overload
    ///
    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr const, Context>::type
    eval(Expr const &e, Context const &ctx)
    {
        return typename Context::template eval<Expr const>()(e, ctx);
    }
}}

#endif

/* eval.hpp
yO8EU2YCq1/Y5R5JL3+dwgPsnFzkBdr5bUiUrT6dBjPictBlwuitUOI+UhXC3T5p3SWcY7bCe5c13Sz6VlqJX8N0H06ngl8HrmXZPkzjlK/D95DE7A8KYU2CqsylXRKaZniDpXzI7jO8/QMqrB0j1UKIE+V3nbRM65ERg0J/AEjq0eC+3Xt980KTRZTf7C+NncgGFaav7pDDaxMG3/eKPAJA+iofaFXiCsW0phskucMBNMGpc1jE5q2xwqYpKINl4XXasR6HSScfAPR1mMJVtCoJ5j+1ijtgCvQ7YlUZeoAIK99RwzZZSbLD2yNi4TnzT/GObZ9YazFvP0Syu8Mqei5Y3QZRPhxIFH1eRKiWDxH/9iGCYaT4ejdu15ttvYrnIqKw3Nv6dVzhXRmNNrs83+LbqJf/0fqRXjlyIaQIfLs8PwMEOSm7FWQjaJtd14G0TdlM+/7zQUK7y8Kg896WUXhXWqPRV6rxlqR55pv0JT59Eu0HA1GTT3mbalDLoZisM5q3v6XybFLsDTtKdZJ3sykwgek07gntI59SRvDkj6vJd5bUyj/JtIgTvu7rso3uEz2ffifCZIK6ZhSUmhptku9eDeplwWijwKecpM0bN9skZuwqxLWMQ4oVO0mUv94h6nD/K/uQVyRzd1OQFt9WQwA0LwT6isfjotctOLyzMhUPKy6JuG2MUS5fRi73CsJ6eO1lTDbZvLvhB+QT
*/