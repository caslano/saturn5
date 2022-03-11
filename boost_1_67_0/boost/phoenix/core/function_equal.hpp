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