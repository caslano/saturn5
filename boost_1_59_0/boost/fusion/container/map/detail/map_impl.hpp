/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_IMPL_02032013_2233)
#define BOOST_FUSION_MAP_IMPL_02032013_2233

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;
}}

namespace boost { namespace fusion { namespace detail
{
    struct map_impl_from_iterator {};

    template <int index, typename ...T>
    struct map_impl;

    template <int index_>
    struct map_impl<index_>
    {
        typedef fusion_sequence_tag tag;
        static int const index = index_;
        static int const size = 0;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl() BOOST_NOEXCEPT {}

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(Iterator const&, map_impl_from_iterator) BOOST_NOEXCEPT
        {}

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void assign(Iterator const&, map_impl_from_iterator) BOOST_NOEXCEPT
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void get();
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void get_val();
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void get_key();
    };

    template <int index_, typename Pair, typename ...T>
    struct map_impl<index_, Pair, T...> : map_impl<index_ + 1, T...>
    {
        typedef fusion_sequence_tag tag;
        typedef map_impl<index_+1, T...> rest_type;

        using rest_type::get;
        using rest_type::get_val;
        using rest_type::get_key;

        static int const index = index_;
        static int const size = rest_type::size + 1;

        typedef Pair pair_type;
        typedef typename Pair::first_type key_type;
        typedef typename Pair::second_type value_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl()
          : rest_type(), element()
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(map_impl const& rhs)
          : rest_type(rhs.get_base()), element(rhs.element)
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(map_impl&& rhs)
          : rest_type(BOOST_FUSION_FWD_ELEM(rest_type, *static_cast<rest_type*>(&rhs)))
          , element(BOOST_FUSION_FWD_ELEM(Pair, rhs.element))
        {}

        template <typename ...U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(map_impl<index, U...> const& rhs)
          : rest_type(rhs.get_base()), element(rhs.element)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(typename detail::call_param<Pair>::type element_
          , typename detail::call_param<T>::type... rest)
          : rest_type(rest...), element(element_)
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(Pair&& element_, T&&... rest)
          : rest_type(BOOST_FUSION_FWD_ELEM(T, rest)...)
          , element(BOOST_FUSION_FWD_ELEM(Pair, element_))
        {}

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(Iterator const& iter, map_impl_from_iterator fi)
          : rest_type(fusion::next(iter), fi)
          , element(*iter)
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        rest_type& get_base()
        {
            return *this;
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        rest_type const& get_base() const
        {
            return *this;
        }

        BOOST_FUSION_GPU_ENABLED
        mpl::identity<value_type> get_val(mpl::identity<key_type>) const;
        BOOST_FUSION_GPU_ENABLED
        pair_type get_val(mpl::int_<index>) const;

        BOOST_FUSION_GPU_ENABLED
        mpl::identity<key_type> get_key(mpl::int_<index>);
        BOOST_FUSION_GPU_ENABLED
        mpl::identity<key_type> get_key(mpl::int_<index>) const;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename cref_result<value_type>::type
        get(mpl::identity<key_type>) const
        {
            return element.second;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename ref_result<value_type>::type
        get(mpl::identity<key_type>)
        {
            return element.second;
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename cref_result<pair_type>::type
        get(mpl::int_<index>) const
        {
            return element;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename ref_result<pair_type>::type
        get(mpl::int_<index>)
        {
            return element;
        }

        template <typename ...U>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl& operator=(map_impl<index, U...> const& rhs)
        {
            rest_type::operator=(rhs);
            element = rhs.element;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl& operator=(map_impl const& rhs)
        {
            rest_type::operator=(rhs);
            element = rhs.element;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl& operator=(map_impl&& rhs)
        {
            rest_type::operator=(std::forward<map_impl>(rhs));
            element = BOOST_FUSION_FWD_ELEM(Pair, rhs.element);
            return *this;
        }

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void assign(Iterator const& iter, map_impl_from_iterator fi)
        {
            rest_type::assign(fusion::next(iter), fi);
            element = *iter;
        }

        Pair element;
    };
}}}

#endif

/* map_impl.hpp
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
*/