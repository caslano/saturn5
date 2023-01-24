/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_09172005_0721)
#define FUSION_DISTANCE_09172005_0721

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/distance.hpp>
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
        struct distance_impl
        {
            // default implementation
            template <typename First, typename Last>
            struct apply : distance_detail::linear_distance<First, Last> 
            {};
        };

        template <>
        struct distance_impl<iterator_facade_tag>
        {
            template <typename First, typename Last>
            struct apply : First::template distance<First, Last> {};
        };

        template <>
        struct distance_impl<boost_array_iterator_tag>;

        template <>
        struct distance_impl<mpl_iterator_tag>;

        template <>
        struct distance_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename First, typename Last>
        struct distance
          : extension::distance_impl<typename detail::tag_of<First>::type>::
                template apply<First, Last>
        {
            typedef typename extension::distance_impl<typename detail::tag_of<First>::type>:: 
            template apply<First, Last>::type distance_application;
            BOOST_STATIC_CONSTANT(int, value = distance_application::value);
        };
    }
        
    template <typename First, typename Last>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::distance<First, Last>::type
    distance(First const& a, Last const& b)
    {
        return result_of::distance<First, Last>::call(a,b);
    }
}}

#endif

/* distance.hpp
YvMgo7yJ4nRw6VXIolXo4vEe6ViaXKF9SfjmhFZtysMXhPalJbbp0qXENqVRm85TmzJEm5ICGXDtIrXrAgwiDHWSti/6SHVby0KNoKA+u71Tvjx26EqcSWic/fQ1XX3Vygkl3OGfNcFs+v5rKztV3YnvzG/zKunZigtRIqrO0zLCA8LjX9HXtshqWNnzD7hgpHuWhS6MDI60ng91WKUnkAWHVrSbpKrtrDd9Xq929JVImfkHBPhDdAJDKhCOhpKUjVWllIX9KjRx+mjSUDW7e5zhxnlUYU9DTGNlFqqmmtW6K0kF1ky1l16BeonPO+jO0YECx6c7dkKzrYMVOh5Yh2l5HrYA2pe85hq3VfOGdlmwhNvxULv02Cj0GeqwBtPlha72stBKV8fIoAUz5UH11QOFJotw2Nd0mAzPsB+xdVEMtfDMWPxqJ8+MD0gjrNmmvCbszVlk4ll8o4WO+mOAm8RZtGOOE6kdhsPE7fXx+l+KWzVG2PSqMcIM5k688CqyloHsnEXutifgH0Ke35xGd8+ThfejArQim6VqjYymnhMIhY4JXt4qoNFaf46vNxHaPN/6rbj1MdpoPU2FnhPSE3+jsyt56c05gFrfbiTbJy/Lo4FtxFFAPfg0ee1Fk8lsWiq5pZp6DDJUxy7WNEyvDhvPH/KBHguRWV9DBrVG9YH+zJlWkMG3gQKJYQ3BnT3dMXuk54TD0wQTR3pC
*/