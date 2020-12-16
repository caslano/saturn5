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
bOg/7WBOjYcv02wuWRVmGS/zmmFNVmxRt9uopS1kfsye37kdg3Eha8Osb+ibt5q1fmOuq8Ss+KYfrD1ZW2b1hlZ8pdkssmbM5iXf7apZKpkts25THjTU7ChZfWbVXWeO0ew2GY/vh4+WzNTsbzIew+PMafc0++At1RKzut125KB2yfg1K5vV367ZJLL2zHZnGP9eQRrZDmaxMV0naBars9AtY7Ygr4eVZt4VLExy+++DTp6ahZC5M2s56qvZyC1ZR2ZJ3wZiPC+StWK2M6BioGYOZha66swGRn53TLMWZBXLrL1Su15kdSr8Y35kZp5zKmv2tbkFjbXR3M0ndtAsl8ycGf97YBfJ/JgFZq8YoZmHhYVOz4zPzY5kXZkds7tRiLEms2JmVSmkm2bryJqVmQfZzcLWezU7I5jO0jguHyi/h9xANqxsnW+urPPzybQ6a0E2rfrDdKzlZBZl1pFMV9dtPuaDpTH2DmSeNt2nYS0nq1Bm7dS/e0xmx2zlL9/+ifMEYnAO7aGeJwS7LlihYA8FKxbspWC6iuVbRcH0gtkJ5ihYPcFcBWsqmKdgHwjmI1g3Zr0U8xfsI8GCBBsqWKhgY8s1twrjmfWh/zaaTjeZWV+dmYFfM5LZhybX7Kyby+xj3chx/JrRyjW5LVOMXzNOuSa3dYIlCPatYMmC7RJsn2A/C5Yh2EnBsgX7TbC8co3eJ1c07ivd3/0uxBD3y5pdE6xAsNuC3RXsATe2x5mR0b/er/O+Ok/frqjBf8yiQvlmZVa+6c3LN4NF+eZgWb45VizfnCqVb85WOp17mbmTWRa0HKdZoFVZO8M/lvN66i3NgshcmK02N2ulWRTZ2nem8/VtTLbP/+fnmnlZ63SGsnbv7OEGu9ea+Sv2i33jXM1CyBoy++uv4Ws0i2bWiOzL6bE9NEshq1lmbmSl3ZqEa5al2De/9v5IswKyGswGd8k6g5qwMbXe4+7+jLEmc2GWPv1ZHcRHFmDzz7i4kuUvLKmkWVINYwwuZF/Mu9tFs2yylmXWgOxO6c4TqEEKwJxZctOaaGdFZses2esvPkfeyVoz2zq1/8cYazIHZjNcbJ5pFkGmLzPndzH4941FHshsmMV1ztqtWZxiB+3DftcsgcyKWWDXFXs0SyYzZ3a+S/xg5FaxIRen79QsVbEr4c1fabaPrCWzonmjD2l2n6xFmdUnGzMg+65mro46XWjZXKlHtqJBm7OaxTui3XubX7d1oWY5ZJbM4le6p2mWR1aR2YMTSY81u6rY5ZHbMS6FyjW/Xv24g2ZFaruFu65oVqL00y7+9A7NPGvpdLWYOZy3wHgGKrbWsGOiZuEEzZhdm2d2GXVN1pyZvvfjmZrl1zLWfF2yIzWvNkbt1tbpfN+b73trt7paANYeMm/Wrvv1NRaaJZIZ3lvge3s72my2ZhmKea44dFqzXDKzsms6kfnN/fQOckRmzqxJRL/diIHMgllsXhNn5I+sIbN/1frQC/HVoTnGLFRX/yXmJplf2fpZh2zNZ5NyMP/IrMvavbPfZjedinVXscJa25ZoFktWmdnN0g5nMf/I7Jk9NHMfirmi2LGh91DX2WRVmfVO77IEsSv3K0lyTEd9Ktd8OtSmGcbFydSumJ3agHEh4/cbXFDXuK+Q6Zllvjj/hWZ+ZLbMtt7Y44xaUqxPj4+wr4wmq8EsZffIgRhrxbJ7t3fAeCrWs+Zm7JtpijW6f2I7apDMjplPt0WTsS4pdqFgxlHsAXVN7dmCs8OwHynmn3dqMMaMrDazx3PvHcK4KBbg+mg3alCxDXtvYm6uVcz1zjVf1BIZj72dU5c/sEYqtqxnx98ROxmvpfWVj3fSrFSxZQM=
*/