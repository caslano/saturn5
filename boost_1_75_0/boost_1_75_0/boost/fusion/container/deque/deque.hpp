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
k6f2MNp2ccX+gV2k2M+Hj1NKhJ3wPBK20YKE3fMeUuzny9bvSLHPeOS0PYJfyg9+HoH1EnJRpsQ8MPu0SwlWv8y1JE1nBB2FBM3oONrI5XQT0h64BJPFCXLUxzwK5FrtilHyvzumkrMuukP9loouz2hUGamUBiqgigAGlVK2A4sl2oDs1QXodQRKMemM6PKhdg04u5dzqwLOmPAJ+tpTqnEvkkOtlnpIbcD5txHhMBrp/RrRSAXRyEw9jTx+WlDGQ8qvYafpKw/kx7/4V7/ndLiSj1GnQ66iL/9Pf4W7UYhKTaZ0yWU+UM0NzsDQft5JDK2MM7RV9N2TSvG7d8AYUnOf3s0Uy6uctYsYGlkSZ1RzhoZtwz+N4BV4oDADYPLjPUQA2arxOTsL+NidwuX7LvjhpeYYWm47aPcxBYL7AgEUuMzj9/BpWyZEP5LA0Edeu6O6F+2/17jplCYx1Q4JYkNQ7ZCNvCpduRhLbOHMFc8odRraatlIZ7U71oswQ+n0ck6nSaJR2gUmz4cCFKjf3B1lQFMyrNAZjD9mLwxFxt2XQ0DiZhN1n7mbJ8W+mXdYxvkZl0vVrR+iLFKrgcnBSQ1PznGZ79qtFcwJX59zfOVo8bUR238iOx2nZsIX0A/h6yMjAbNAxRfPiWGfrJZ8aqst5dZZ7S8QxoVpfBBvtEjVqMjJNBLKGOATq8HZHNU/+wFjR14ijN0u2EcX
*/