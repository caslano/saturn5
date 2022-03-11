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