/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_05052005_0214)
#define FUSION_SIZE_05052005_0214

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_size.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct size_impl
        {
            template<typename Sequence>
            struct unsegmented_size : Sequence::size {};

            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_size<Sequence>
                  , unsegmented_size<Sequence>
                >::type
            {};
        };

        template <>
        struct size_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template size<Sequence> {};
        };

        template <>
        struct size_impl<boost_tuple_tag>;

        template <>
        struct size_impl<boost_array_tag>;

        template <>
        struct size_impl<mpl_sequence_tag>;

        template <>
        struct size_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct size
            : mpl::int_<
                  extension::size_impl<typename detail::tag_of<Sequence>::type>
                      ::template apply<Sequence>::type::value
              > {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::size<Sequence>::type
    size(Sequence const&)
    {
        typedef typename result_of::size<Sequence>::type result;
        return result();
    }
}}

#endif

/* size.hpp
d3KI+yPEvjgD4vvjOMTbs2v8SaXO/FM+K8by/bS8VmTVCPc2FQaNtPnsxxTPAjOeYBgy84AOcgfwzhU3VeKWKUDrpc69UQO1zjcWQR0rj9hUGmjuPrNTKcjfyEWlIojgJIQfFXYAXh5lvK/m71V8X6dU0vtmYX01lAbEiBTPl9eyLReCUQfxBw7ghIUwXyGsh2FwKnIxjB0FBjAIgQRkCGF9QikMrLDU0XbnhdY3O+7/XF++sB5Pg0ayZdHom1B65OIK7OnS/JppNmUN8WhNaVCQAtXQkFAK39Z32NAFwl3e6ULhBt1KWL879IMt8INZWNQb+o8u0I+ALg7qF8vooodvSOBknFB+HRTc2K8Pwh0qzd688SSedS/fLJT3ghcV/fsQakI5bseEE81YbLe8cFaDCouBBGFxd3giL5yi3ybSbbF+ewoVi097G3V/oNeNh1gqktNNpshrFRjsG5tYtBMfpuh3m/BuuX73Id49qd+twbsf9Tv07I5M2/hPi9FOC28ncnhjWpz+ECh22UzPxqLxRVZhzeZpkyIFFYgT1OCbIBfOMAr1nZkqoYSbn8lXOJun5VYc0wpeDaWuOoE92xw3o8/Z2eAl6qcaKK2txQ3aoLfbJJ00PfSLH3TSvMEvfI8FfrgM5siTZqH8Jr3P5+u9OoQ6eap+249uS/TbS5Gef+0dg3bqzC4bzTaYktZsFhai6a7iF3gdPoRX
*/