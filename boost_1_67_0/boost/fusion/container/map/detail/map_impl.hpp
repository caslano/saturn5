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