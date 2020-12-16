/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_26112006_1649)
#define BOOST_FUSION_DEQUE_26112006_1649

# include <boost/fusion/container/deque/deque_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/deque/detail/cpp03/deque.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>
#include <boost/fusion/container/deque/detail/deque_keyed_values.hpp>
#include <boost/fusion/container/deque/deque_fwd.hpp>
#include <boost/fusion/container/deque/detail/value_at_impl.hpp>
#include <boost/fusion/container/deque/detail/at_impl.hpp>
#include <boost/fusion/container/deque/detail/begin_impl.hpp>
#include <boost/fusion/container/deque/detail/end_impl.hpp>
#include <boost/fusion/container/deque/detail/is_sequence_impl.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>

#include <boost/mpl/int.hpp>
#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    template <typename ...Elements>
    struct deque : detail::nil_keyed_element
    {
        typedef deque_tag fusion_tag;
        typedef bidirectional_traversal_tag category;
        typedef mpl::int_<0> size;
        typedef mpl::int_<0> next_up;
        typedef mpl::int_<-1> next_down;
        typedef mpl::false_ is_view;

        template <typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque(Sequence const&,
            typename enable_if<
                mpl::and_<
                    traits::is_sequence<Sequence>
                  , result_of::empty<Sequence>>, detail::enabler_>::type = detail::enabler) BOOST_NOEXCEPT
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque() BOOST_NOEXCEPT {}
    };

    template <typename Head, typename ...Tail>
    struct deque<Head, Tail...>
      : detail::deque_keyed_values<Head, Tail...>::type
      , sequence_base<deque<Head, Tail...>>
    {
        typedef deque_tag fusion_tag;
        typedef bidirectional_traversal_tag category;
        typedef typename detail::deque_keyed_values<Head, Tail...>::type base;
        typedef mpl::int_<(sizeof ...(Tail) + 1)> size;
        typedef mpl::int_<size::value> next_up;
        typedef mpl::int_<-1> next_down;
        typedef mpl::false_ is_view;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque()
        {}

        template <typename Head_, typename ...Tail_, typename =
            typename enable_if<is_convertible<Head_, Head> >::type
        >
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque(deque<Head_, Tail_...> const& seq)
          : base(seq)
        {}

        template <typename Head_, typename ...Tail_, typename =
            typename enable_if<is_convertible<Head_, Head> >::type
        >
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque(deque<Head_, Tail_...>& seq)
          : base(seq)
        {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Head_, typename ...Tail_, typename =
            typename enable_if<is_convertible<Head_, Head> >::type
        >
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque(deque<Head_, Tail_...>&& seq)
          : base(std::forward<deque<Head_, Tail_...>>(seq))
        {}
#endif

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque(deque const& seq)
          : base(seq)
        {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque(deque&& seq)
          : base(std::forward<deque>(seq))
        {}
#endif

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit deque(typename detail::call_param<Head>::type head
                     , typename detail::call_param<Tail>::type... tail)
          : base(detail::deque_keyed_values<Head, Tail...>::construct(head, tail...))
        {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Head_, typename ...Tail_, typename =
            typename enable_if<is_convertible<Head_, Head> >::type
        >
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit deque(Head_&& head, Tail_&&... tail)
          : base(detail::deque_keyed_values<Head, Tail...>
                ::forward_(BOOST_FUSION_FWD_ELEM(Head_, head), BOOST_FUSION_FWD_ELEM(Tail_, tail)...))
        {}
#else
        template <typename Head_, typename ...Tail_, typename =
            typename enable_if<is_convertible<Head_, Head> >::type
        >
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit deque(Head_ const& head, Tail_ const&... tail)
          : base(detail::deque_keyed_values<Head_, Tail_...>::construct(head, tail...))
        {}
#endif

        template <typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit deque(Sequence const& seq
          , typename disable_if<is_convertible<Sequence, Head>, detail::enabler_>::type = detail::enabler
          , typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
          : base(base::from_iterator(fusion::begin(seq)))
        {}

        template <typename ...Elements>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque& operator=(deque<Elements...> const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque& operator=(T const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque& operator=(T&& rhs)
        {
            base::operator=(BOOST_FUSION_FWD_ELEM(T, rhs));
            return *this;
        }
#endif

    };
}}

#endif
#endif

/* deque.hpp
2D/52BRnYSsswDZYhN2wGCNxDurvM5BrmxlS/o3vM2jOcp2wtezfc3EIhmMKnocTsQ3q49pLO/o5Judf5VnwMLwNW+BKlHTI9QzbbpKOw3KcvIfReBSTZHz3NPwYM/ATTOa7CQlhIemEYkIZYYMSOInvwErCMULIKMYbIkQREghZhJrGLy5lfjjjqnq3oRvHI/6eoIw7HEHoT5DxhT3GFq4waW83jh9cSthMkLGCPcYJ7kZIIci4wD7jAZewDcoYwJEE1zi/NkIVJ8Bqgnc7/iE8TjgVJeP2ErIIKb7j9cpYvZ5j9HYh3E2cxr4AcXNIGy4lrCW4xtk9RAjpZxxD12TcXOk/UInlrNc4Xm47QizBNSZumUkfg5NIPwOP8W7jCDK+LYWH7xEOs+7vCS2vZnxaQiIhl1BCuJuwnXCIUE1oek2wv0JwCk7BKTgFp+AUnIJTcPrV+//brFPr3/avvPv/2mj6Katt/1nZORm0E1hoGp+Z7cyVNvW93d1jBKTIff4UQlupi8/h+3GJrjZ15fX4aguNVEEH/oyAdx10rt7335ld7AzxGNv/qJ90VHikw5qXk+9KxplJxzHpC+CUtol8Qq6SH9d6psNeyHvCGRsxOyPvF6WjjaTD+7mA9p7va890WvPzLFnZjswQ7+cn8mdYMilSDr7j8b7vzIy8zGyb/E2Nu1Rvd8ixZUxzqMuXSXuWq63KojaNeObFIWnbz5e8mK4E8qLKNy/qVTZM80KWtZukvdg07d7Pkcy05iltejK/1KStzzjWvlNuAQdL+Ysh2KKJZ7RxWwsd2QUW5SXo6na2q2U7I0y2sxs2VNOur0udH6LPz7dlqbM990WxtKM7ZF/kKUE5PjzSpz1HIjvjN7UvlPllhuPSIWsy5kGltC1/wgb3xNdxotK3I8mVB/TsYNsLM50WSbnkQc3thwmG9kO7V37INkq6OD1ns3I5HuW48/yb8up+fV9L3uj5KO/sYF/uZv6UUNTSrr8PpFG4e/l+Mr8/TjLsj74yPxbzo93z++jlzvAcErrahx+TuOzRnmU/tYmWIQ+r32f7CbNYpnyMnq+0yTqz1d+Q/Cw1TxNqKVfJer6oGaJv34OXankr69LaWiUdA6VjVzcijcDO6CAdZWP1dDgLbCEBx+993k/V8yVzZha6xoptbXhfSK5+HNr1sWeXkhjKvLrv0sir/qRzKvNDx7n3Xay+bvrbZVuUA0TZNo/yWy7bl+KKk1DI9rVMke2jYFF88+dI5gTS16yGfNXjTZb29ufl3LZbfltL3PEW2j1+42t/b47PsSLzir1+W9u4+07IPA5S+xyP9FX7S994Y/qMv/2/bvqWyvvssxpo514L5irpm2BIn8k1QXGN/QEatVqQqvd/kXcJ+Z6LS/1cI5TVcI1wt59rhLU1XCNsNjm3l/s5t7fX80xPl+Qa+0WOM/7mmTZZoL3+/KgxfdofL9SfI/VOo+8+WS7v2H9bfg8r5dqkZKLPPqlXmfbzzKrsL988K63h97DMz+/h3d6/h7XksTEftso79Y9KPrwr1wVlkwz54Hld8JvKB2X+Wp/rgtrzx/WbEi7v2J8t59xZhNnKb9v1rvzJKcjOrv08K31B/T53vFziiZF4+hCKiCc5zRXPtGxnlEUOCP00FvB1pN53xyvesHPc/ZMaEVpIvGs946WDtvtICGScNxnj3CfeGNc5UeJdS2hDuI8wh3grPOOVfmq/rJ+k51jwVo/tPiXxx0p+D5DtLptsEv9pyG/X8WZvab6fqzzjpaC6Yq1/nJ+29N3Hc4kzaopHnPoNRV32r7/ynNBKW7i39Nu9jDBPKc/GOC1Sv1CH6xVjGdovcURJGepBmK8=
*/