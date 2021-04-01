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
cVsS78dCjX1F9d6tgxzksdZBC45FfJVtlIY2K+e7OGd5B2Cgaas6TnD3E4u4ia3ODRr+C8XhbLWonst9bb6SrEnS8Li3W16huxLuzPJg3WeeKX6vR969CXk0cT2lvGr0585ZDVNTzBABqJG7TcE/qOkC3RLLw8f4lciSQuf/VCJpC9qjFhRmRRW3lja/OSGp/DJ5zanPhhn1eWmooVhQ67SP8U6X1ImhAp55kC+Tz3Isu+4MeURMFfNDT9DM960+7gP8inmLwy65+hCAIsogilca6v1lpHRlaOGYljtXIXgAQpRu216TGGx2xolunYrGxuFIZrvYC1B4hAhVyKl5A9GSwfUwiqjvoduaWlBBkRvxD0sVWZVNr0m8cJ4pt18aTxsLPbCcld6b4MF1ekBacPGJzCiiFEt2jMMB1jQvpxfksAMH0+rRA8oAa8Q7fnr4/g0byi4LMM+5qW0NI5sEsCeTCHbr074PnQsi+UlyOuCf1e7Dciccy3jODRKkw/SK4a6EtBSbq5mL/G8mFjtbKJt95uI4qTOfzovTF89FMMHN2k5It6HPuC7XpQ==
*/