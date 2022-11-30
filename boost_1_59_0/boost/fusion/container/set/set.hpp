/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_SET_11062014_1726
#define FUSION_SET_11062014_1726

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/set/detail/cpp03/set.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/detail/is_same_size.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/container/set/detail/begin_impl.hpp>
#include <boost/fusion/container/set/detail/end_impl.hpp>
#include <boost/fusion/container/set/detail/value_of_impl.hpp>
#include <boost/fusion/container/set/detail/deref_data_impl.hpp>
#include <boost/fusion/container/set/detail/deref_impl.hpp>
#include <boost/fusion/container/set/detail/key_of_impl.hpp>
#include <boost/fusion/container/set/detail/value_of_data_impl.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    template <>
    struct set<> : sequence_base<set<> >
    {
        struct category : forward_traversal_tag, associative_tag {};

        typedef set_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;

        typedef vector<> storage_type;

        typedef storage_type::size size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set()
            : data() {}

        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        set(Sequence const& rhs,
            typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler,
            typename enable_if<detail::is_same_size<Sequence, storage_type>, detail::enabler_>::type = detail::enabler)
            : data(rhs) {}

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type& get_data() { return data; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type const& get_data() const { return data; }

    private:
        storage_type data;
    };

    template <typename ...T>
    struct set : sequence_base<set<T...> >
    {
        struct category : forward_traversal_tag, associative_tag {};

        typedef set_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;

        typedef vector<T...> storage_type;

        typedef typename storage_type::size size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set()
            : data() {}

        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        set(Sequence&& rhs,
            typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler,
            typename enable_if<detail::is_same_size<Sequence, storage_type>, detail::enabler_>::type = detail::enabler)
            : data(std::forward<Sequence>(rhs)) {}

        template <typename ...U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit
        set(U&& ...args)
            : data(std::forward<U>(args)...) {}

        template <typename U>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set&
        operator=(U&& rhs)
        {
            data = std::forward<U>(rhs);
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type& get_data() { return data; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type const& get_data() const { return data; }

    private:
        storage_type data;
    };

}}

#endif
#endif



/* set.hpp
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
*/