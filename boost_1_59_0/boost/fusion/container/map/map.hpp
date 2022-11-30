/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_MAIN_07212005_1106)
#define FUSION_MAP_MAIN_07212005_1106

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_fwd.hpp>
#include <boost/fusion/support/pair.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/map/detail/cpp03/map.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/map/detail/map_impl.hpp>
#include <boost/fusion/container/map/detail/begin_impl.hpp>
#include <boost/fusion/container/map/detail/end_impl.hpp>
#include <boost/fusion/container/map/detail/at_impl.hpp>
#include <boost/fusion/container/map/detail/at_key_impl.hpp>
#include <boost/fusion/container/map/detail/value_at_impl.hpp>
#include <boost/fusion/container/map/detail/value_at_key_impl.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>

#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    template <typename ...T>
    struct map : detail::map_impl<0, T...>, sequence_base<map<T...>>
    {
        typedef map_tag fusion_tag;
        typedef detail::map_impl<0, T...> base_type;

        struct category : random_access_traversal_tag, associative_tag {};
        typedef mpl::int_<base_type::size> size;
        typedef mpl::false_ is_view;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map() {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map(map const& seq)
          : base_type(seq.base())
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map(map&& seq)
          : base_type(std::forward<map>(seq))
        {}

        template <typename Sequence, typename = typename enable_if<traits::is_sequence<Sequence>>::type>
        BOOST_FUSION_GPU_ENABLED
        map(Sequence const& seq)
          : base_type(begin(seq), detail::map_impl_from_iterator())
        {}

        template <typename Sequence, typename = typename enable_if<traits::is_sequence<Sequence>>::type>
        BOOST_FUSION_GPU_ENABLED
        map(Sequence& seq)
          : base_type(begin(seq), detail::map_impl_from_iterator())
        {}

        template <typename Sequence, typename = typename enable_if<traits::is_sequence<Sequence>>::type>
        BOOST_FUSION_GPU_ENABLED
        map(Sequence&& seq)
          : base_type(begin(seq), detail::map_impl_from_iterator())
        {}

        template <typename First, typename ...T_>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map(First const& first, T_ const&... rest)
          : base_type(first, rest...)
        {}

        template <typename First, typename ...T_>
        BOOST_FUSION_GPU_ENABLED
        map(First&& first, T_&&... rest)
          : base_type(BOOST_FUSION_FWD_ELEM(First, first), BOOST_FUSION_FWD_ELEM(T_, rest)...)
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(map const& rhs)
        {
            base_type::operator=(rhs.base());
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(map&& rhs)
        {
            base_type::operator=(std::forward<base_type>(rhs.base()));
            return *this;
        }

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename enable_if<traits::is_sequence<Sequence>, map&>::type
        operator=(Sequence const& seq)
        {
            base().assign(begin(seq), detail::map_impl_from_iterator());
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        base_type& base() BOOST_NOEXCEPT { return *this; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        base_type const& base() const BOOST_NOEXCEPT { return *this; }
    };
}}

#endif
#endif

/* map.hpp
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
*/