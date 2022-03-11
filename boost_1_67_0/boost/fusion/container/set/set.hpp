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