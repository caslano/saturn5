/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_FUNCTION_EQUAL_HPP
#define BOOST_PHOENIX_CORE_FUNCTION_EQUAL_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/is_placeholder.hpp>
#include <boost/mpl/int.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/proto/matches.hpp>

#ifndef BOOST_PHOENIX_NO_VARIADIC_FUNCTION_EQUAL
#   include <boost/phoenix/core/detail/index_sequence.hpp>
#endif

namespace boost
{
    template <typename> class weak_ptr;
}

namespace boost { namespace phoenix
{
    template <typename>
    struct actor;

    namespace detail
    {
        struct compare
            : proto::callable
        {
            typedef bool result_type;

            template <typename A0, typename A1>
            result_type operator()(A0 const & a0, A1 const & a1) const
            {
                return a0 == a1;
            }

            // hard wiring reference_wrapper and weak_ptr here ...
            // **TODO** find out why boost bind does this ...
            template <typename A0, typename A1>
            result_type
            operator()(
                reference_wrapper<A0> const & a0
              , reference_wrapper<A1> const & a1
            ) const
            {
                return a0.get_pointer() == a1.get_pointer();
            }

            template <typename A0, typename A1>
            result_type
            operator()(weak_ptr<A0> const & a0, weak_ptr<A1> const & a1) const
            {
                return !(a0 < a1) && !(a1 < a0);
            }
        };

        struct function_equal_otherwise;

        struct function_equal_
            : proto::when<
                proto::if_<
                    proto::matches<proto::_, proto::_state>()
                  , proto::or_<
                        proto::when<
                            proto::terminal<proto::_>
                          , compare(
                                proto::_value
                              , proto::call<
                                    proto::_value(proto::_state)
                                >
                            )
                        >
                      , proto::otherwise<function_equal_otherwise(proto::_, proto::_state)>
                    >
                  , proto::call<function_equal_otherwise()>
                >
            >
        {};

        struct function_equal_otherwise
            : proto::callable
        {
            typedef bool result_type;

            result_type operator()() const
            {
                return false;
            }

#ifdef BOOST_PHOENIX_NO_VARIADIC_FUNCTION_EQUAL
            template <typename Expr1>
            result_type operator()(Expr1 const& e1, Expr1 const& e2) const
            {
                return
                    this->evaluate(
                        e1
                      , e2
                      , mpl::int_<proto::arity_of<Expr1>::value - 1>()
                    );
            }

        private:
            template <typename Expr1>
            static BOOST_FORCEINLINE result_type
            evaluate(Expr1 const& e1, Expr1 const& e2, mpl::int_<0>)
            {
                return
                    function_equal_()(
                        proto::child_c<0>(e1)
                      , proto::child_c<0>(e2)
                    );
            }

            template <typename Expr1, int N>
            static BOOST_FORCEINLINE result_type
            evaluate(Expr1 const& e1, Expr1 const& e2, mpl::int_<N>)
            {
                return
                    evaluate(
                        e1
                      , e2
                      , mpl::int_<N - 1>()
                    ) && function_equal_()(
                        proto::child_c<N>(e1)
                      , proto::child_c<N>(e2)
                    );
            }
#else
            template <typename Expr1>
            result_type operator()(Expr1 const& e1, Expr1 const& e2) const
            {
                return
                    this->evaluate(
                        e1
                      , e2
                      , typename make_index_sequence<proto::arity_of<Expr1>::value>::type()
                    );
            }

        private:
            template <typename Expr1, std::size_t... I>
            static BOOST_FORCEINLINE result_type
            evaluate(Expr1 const& e1, Expr1 const& e2, index_sequence<I...>)
            {
                bool result = true;
                int dummy[] = { (result && (
                        result = function_equal_()(proto::child_c<I>(e1), proto::child_c<I>(e2))
                    ))... };
                (void)dummy;
                return result;
            }
#endif
        };
    }

    template <typename Expr1, typename Expr2>
    inline bool function_equal_impl(actor<Expr1> const& a1, actor<Expr2> const& a2)
    {
        return detail::function_equal_()(a1, a2);
    }

    template <typename Expr1, typename Expr2>
    inline bool function_equal(actor<Expr1> const& a1, actor<Expr2> const& a2)
    {
        return function_equal_impl(a1, a2);
    }

}}

#endif


/* function_equal.hpp
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
*/