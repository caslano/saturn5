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
2jefaZTMGvYzU7IKSzjluyLwMkoMeA+i4h4rrdkKlqao7NWxatV1aWWSb9gdy/gOEADAmuecFei6sP8bNHvj82mYOlxaY1p4kEXMpLRHm99e4U9h5/Uy+dJanOuLYefB7lviN+dBUMQ/ZW66/ySQz+Em6YrHGmtDjI5uYHHiXajVkET9XWNZdDlz7zLDNLRJlXhUc1D/C6wChDmmkCA245LvwOzrs7N/PonHYYqAJVUigPBR22id3niq0KWHqbMO4jZ07He6xpUorglQLZdaYOFpq1bDknTqxdzn3Ub2QifigvPorPiNwKl3gRLKcM6jWVzO2FyuR95RXQSoHgf5UU2iZl5Tgj/sYKFSAsO+83OxJGqILOjOYQ+zI2/KfG1h1a7LXiOrwHJqR3y2NFqt7rXwWf7ZnwCK7/gOip54UtEif65NJVSikbN60gucdXC4dKLpcqV9oD4byZhIktrWRUFRCI2BnEr0viQVzQEKpL6uplXfSFGwW91SYVigt7SqUtYM/fxURJQEUfW1esWDB6vjbykDoQ/wgLP7jJ8/AHe31uoOhLQ3j63R0g==
*/