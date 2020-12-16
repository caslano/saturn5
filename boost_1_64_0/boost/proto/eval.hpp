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
m7I3szJG/08evkc7+Lfw75f231+C7z/rxwWhI8uPGps5eSm+/+4z9J3cStAi2j/4/gp8/1v/fby6wb6d+6z+Ns3gzLdT6tsrCe5z9A34NJ1X057ov+HKCPRPsu8v/Lz7Ps2+P/ML7vspPY/XpfvkD+O7ehtklZIv4JOd+1/1ZTrlhf7+6UvQx/473LjhVjilcb0GNG7ZxyyVMjnZ+1ktI5VU/6bNa1Gm4pP88CTq3+tQ9qce3/7hDo2Npv23/tv2Pm/PS3sclKyLcjMo2Nej/oP73ClwKdR7/I20lz/S4xyNcS4ZfvFmfH9qH6tDSa4ONgyPeSvxhI8bHqPr6LK3oezan9BrYFD2dpQJlGk+Y0up7J0o6z5p95UuUu14F9Hr27G/s6Y9yagvh3Rn2ve7z2ABWPXtm5/Ua4KOV51rDt/7VVa1TarzyGH9qG/kzAToEb1CPaXhP4Uycx+2fKDgP49v5GzSuzkuRlksH1DFOrcbrXE4zlBRnxfmy32utzquqjygj+aNn29SP5eyhTiQ9HoxXvGBO+hS3sSsvDoSQJV/ry9HYpoHLORLD+nz0uXhA5biRWqH7ic55OTNUt+Pl+o+rvayBvqhv61iQR0ssxKdz+YLKKPuLQVhFfev0Ks6X8N3ctIZ9p1o/ABl5Ayj+6nHW8OjIebbtwCnshbmC+bbT/GtbwD5mKyrPtD+C9AyoOt//04/ttP294/g90etrS+v7yj49+D3MFHUb69z0lVXpNw+xlUMyK33Ec2qg7vPlTy409PHwN31yhwO/o/HwN30KgYOLmgXoLt2VQ53PN13Xo3DHU/3T1cnuAm3Hg3l4MQ1CY67+vkIb63hZq5l4HaGMDbv322vTTDGHVWVmZyBn76OLtMuqbohFv9Tr0flQ3dgH8fU9TWMR2HKlr/zBrrcp2JpHNyIyp3LPbz2ZobteO+NJ2Ci6eHY3mQAs1BLuIBrKNcecVMfbtjeczfT5dqbz5TfwKydW1A5XeyqEvP9rbfEd3dO2O93vDV9hyuiArffu9vgO3aM7qydrxO37b8fOV9fvZ0u80bS4XzhHaicyPtr4EN31N+xNHUdW/a7O+kyyE/DsbjtXajMuijqYvAElKs4JCpfxxG7ZvNpvfZu9I27zk3Zshvdw5Rp2YOVvfAEK0Nb9Jzpuw8qc9qY8h52ffjoPVFOZ+3yGewBhNbuP8rN132obEzBMOenGL2Pqu/MDXnKxR23Ku54Gycyf6+uMH4ayZRnD8rTqA3b3tg4u0rvzM4gAEHf7SPxEhycNpECVJX1GjnLCyK8PF5NU+VxDVO83st+XGgGWH6nlXd5HLSxFLGGnoW0QKnJVLXV0PgnePVKEQZtncUdDIwjXU+TG635KLA9p02fOY5GwKhfp0FX9GngBpXuZ/Vqj24q0rxOS5w3Nu8kLfFJmoHN+XQbL+dT0iZFCbeSvUfd0z6FdKnp478A69kA4iKvkiCy+TEpcgDas7xnnwf0cNXluTww9G6U89w2cds0XZzglVnlDjJ4L4zDykAAuoyitrC5PMejlf3VDTXp6mXQkTZkoLfOZ+uZhRebF6YtrMcBiGJstJK/Uhg7UOG/9xTnjZSZbC1NxRbseLKMnhP5VZe8vkZxngZpLkFX49Dw97M+Thw+go2xyeMsKpsJ2upF8bHXcfY+2lNzvt7TKqrLIotBV20OP7+ZR7MTssjLGj4fhiZGc3XrcG10JFEW0/gzr691FYVV1tAYr40OkIjO3v/ey6w7Dh9KkTUprKB1rvLzQd589KGmadPJrpr+fQh1uQ9FnIZ5loPWysGBNhuN7Du9Xv9i0eayqfMgnuzfyg7bLYRp88yhW0P38dZQgruSIIY=
*/