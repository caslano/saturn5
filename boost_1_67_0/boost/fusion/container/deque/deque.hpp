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