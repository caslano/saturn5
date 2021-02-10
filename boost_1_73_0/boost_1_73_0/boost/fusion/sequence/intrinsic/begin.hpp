/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_04052005_1132)
#define FUSION_BEGIN_04052005_1132

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_begin.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag; // iterator facade tag
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct begin_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_begin<Sequence>
                  , mpl::empty_base
                >::type
            {};
        };

        template <>
        struct begin_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template begin<Sequence> {};
        };

        template <>
        struct begin_impl<boost_tuple_tag>;

        template <>
        struct begin_impl<boost_array_tag>;

        template <>
        struct begin_impl<mpl_sequence_tag>;

        template <>
        struct begin_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct begin
            : extension::begin_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence>
        >::type const
    begin(Sequence& seq)
    {
        return result_of::begin<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence const>
        >::type const
    begin(Sequence const& seq)
    {
        return result_of::begin<Sequence const>::call(seq);
    }
}}

#endif

/* begin.hpp
GCmOUBGPIcG8qeTNCt7DDYPIRhVwHzNms8hGFbiDGycBjby5xqxRjEejmDJzqCq4ntO2ZJFBDKJb7XJThjG3QiVOLHOEJsH4kK1APwhCbXJWcHSOMVMh91sI1sfYe998EgqlZ41UYn0c43xCk3SjUD2dwE5Rzzs/dZycGmemfTa0HcZZh6SO41HjYBS1kXmww9Uf35dQbM2vVSxLviZxrPjNcSuj90w10MJYyzcHtZY3AA0ZYkP6tAfXrgl1ERq+aQyTLGA+o4Ge9RoyrBxp+Qxn+eAs9Fl13JhC1EqUeIHCFIBTm1u/emHIMBvKGwFTx8udohd6I6q8AdZiTpbWrXu7s3nT3HfJXL/fpDKsbzw1DNiQDBLlrcEaQeJ0F0aB72VB+WajxFJwjGt5+aP3xQ/spY9zX/go9ZCXgD7nwQ/5YRHJkOsZkmuNaqmFLnJU5D4Rw+4tH1BPvUNQBVjfiKdR1HEi2ARBd81gb3AtVMjVa1Jsl+XXoMpPX72+uvjjB/HVo6dl8UTKN/kHU2jji6vq21/yl4j446p4/M/LV+LjSguyLB5O777cbTefyNNp+1h+uOi4WhzJvjie9tsD2e62X/6v2O+EnXX9Xa76E03l573WQuUoPo50+LR9JB/Xx1X5iSrz40ni+0jV
*/