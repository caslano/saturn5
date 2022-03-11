/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_1208)
#define FUSION_EQUAL_TO_05052005_1208

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/fusion/support/is_iterator.hpp>
#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl
        {
            // default implementation
            template <typename I1, typename I2>
            struct apply
                : is_same<typename add_const<I1>::type, typename add_const<I2>::type>
            {};
        };

        template <>
        struct equal_to_impl<iterator_facade_tag>
        {
            template <typename It1, typename It2, typename Tag1, typename Tag2>
            struct dispatch : mpl::false_ {};

            template <typename It1, typename It2, typename Tag>
            struct dispatch<It1, It2, Tag, Tag> // same tag
              : It1::template equal_to<It1, It2>
            {};

            template<typename It1, typename It2>
            struct apply : dispatch<It1, It2,
                typename It1::fusion_tag, typename It2::fusion_tag>
            {};
        };

        template <>
        struct equal_to_impl<boost_array_iterator_tag>;

        template <>
        struct equal_to_impl<mpl_iterator_tag>;

        template <>
        struct equal_to_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename I1, typename I2>
        struct equal_to
            : extension::equal_to_impl<typename detail::tag_of<I1>::type>::
                template apply<I1, I2>
        {};
    }

    namespace iterator_operators
    {
        template <typename Iter1, typename Iter2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
        boost::enable_if<
            mpl::and_<is_fusion_iterator<Iter1>, is_fusion_iterator<Iter2> >
            , bool
            >::type
        operator==(Iter1 const&, Iter2 const&)
        {
            return result_of::equal_to<Iter1, Iter2>::value;
        }

        template <typename Iter1, typename Iter2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
        boost::enable_if<
            mpl::and_<is_fusion_iterator<Iter1>, is_fusion_iterator<Iter2> >
            , bool
            >::type
        operator!=(Iter1 const&, Iter2 const&)
        {
            return !result_of::equal_to<Iter1, Iter2>::value;
        }
    }

    using iterator_operators::operator==;
    using iterator_operators::operator!=;
}}

#endif


/* equal_to.hpp
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
*/