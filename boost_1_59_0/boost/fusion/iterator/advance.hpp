/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_09172005_1146)
#define FUSION_ADVANCE_09172005_1146

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/advance.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct advance_impl
        {
            // default implementation
            template <typename Iterator, typename N>
            struct apply :
                mpl::if_c<
                    (N::value > 0)
                  , advance_detail::forward<Iterator, N::value>
                  , advance_detail::backward<Iterator, N::value>
                >::type
            {
                BOOST_MPL_ASSERT_NOT((traits::is_random_access<Iterator>));
            };
        };

        template <>
        struct advance_impl<iterator_facade_tag>
        {
            template <typename Iterator, typename N>
            struct apply : Iterator::template advance<Iterator, N> {};
        };

        template <>
        struct advance_impl<boost_array_iterator_tag>;

        template <>
        struct advance_impl<mpl_iterator_tag>;

        template <>
        struct advance_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator, int N>
        struct advance_c
            : extension::advance_impl<typename detail::tag_of<Iterator>::type>::template apply<Iterator, mpl::int_<N> >
        {};

        template <typename Iterator, typename N>
        struct advance
            : extension::advance_impl<typename detail::tag_of<Iterator>::type>::template apply<Iterator, N>
        {};
    }

    template <int N, typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::advance_c<Iterator, N>::type const
    advance_c(Iterator const& i)
    {
        return result_of::advance_c<Iterator, N>::call(i);
    }

    template<typename N, typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::advance<Iterator, N>::type const
    advance(Iterator const& i)
    {
        return result_of::advance<Iterator, N>::call(i);
    }

}} // namespace boost::fusion

#endif

/* advance.hpp
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
*/