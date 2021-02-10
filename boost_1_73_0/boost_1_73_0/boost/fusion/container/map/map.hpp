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
/iam2r6lro6tnNgzsmc/CLwinHFAFIQoZpfQ56Icz/MimXmu2Kgu8VzUtUdzmp2lI7qV31exaiPWptw1si+lcsBEJ+CPdk3Tqg1XsiFah/jtxDQvFNCCcKSEZnGQu3peo2d+XlqzhJQK6WQTxG/JUdWQu87Tye5TglRYFgFow4PHdU/gWqU+gjXFvpWfOW7Iaprw1gblsmXPJETPPmA3HUCUEwDAHt4ADou3OqljxtXO4EXvkA1C1VtPVZSVap8NhqNh/+RjD5Rm56BDtQn81lZZrfCDOFo+i+kcrolrdneX3YFAzDqSXAkT+6mLMBE8h6uKbaq6YI2qKYsQlClEyJxIZ/cbdYI1t50GPXy+VXK98fnkP+3Z5PWfS/5Tnkle/GTvU0VurlcEI0B9WZbE8bRj4btHVjsElE8O25VI13IIYh3LYWqVpXc6uK+BcPBZr6V9xssiSm93WIB5rZdAAFtFvIW6uvab5lGr/x9QSwMECgAAAAgALWdKUicFr61HAwAAPAgAABkACQBjdXJsLW1hc3Rlci9saWIvYy1oeXBlci5oVVQFAAG2SCRgrVZtb9s2EP6uX3FLgMIWVGvtp3YJirlONhsrkiB2UBgIINDSqWIjkwJJ+WVN//seSkqcFU6MDaVh80jec8/x
*/