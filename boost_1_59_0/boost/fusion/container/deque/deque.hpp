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
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
*/