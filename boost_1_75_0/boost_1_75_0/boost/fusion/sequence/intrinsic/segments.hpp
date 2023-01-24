/*=============================================================================
    Copyright (c) 2006 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTS_04052005_1141)
#define BOOST_FUSION_SEGMENTS_04052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct iterator_range_tag;

    // segments: returns a sequence of sequences
    namespace extension
    {
        template <typename Tag>
        struct segments_impl
        {
            template <typename Sequence>
            struct apply {};
        };

        template <>
        struct segments_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template segments<Sequence> {};
        }; 

        template <>
        struct segments_impl<iterator_range_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct segments
        {
            typedef typename traits::tag_of<Sequence>::type tag_type;

            typedef typename
                extension::segments_impl<tag_type>::template apply<Sequence>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::segments<Sequence>
        >::type
    segments(Sequence& seq)
    {
        typedef typename traits::tag_of<Sequence>::type tag_type;
        return extension::segments_impl<tag_type>::template apply<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::segments<Sequence const>::type
    segments(Sequence const& seq)
    {
        typedef typename traits::tag_of<Sequence const>::type tag_type;
        return extension::segments_impl<tag_type>::template apply<Sequence const>::call(seq);
    }
}}

#endif

/* segments.hpp
wTIE7iIfxRx0jOKOWwMtaJkFVUbEr33987r7+0KTS7FJFU/EkC8IGwuNzbmaQxa7l2+cu4VKbtfWfLfY+JFb3zWBPBN65qdcMQCJGA99GOkBlTuw8te0yhMlNgYq7301Lg1n942F/Im+ZpNuC0IL+0smU7vDgbzJ223cYYzQOej7HTY8tELagE7vI+JKg5YKqQKz2o9IrFAb6KKrFByXrNpz++Gw7UYE+IIaLcXu6gNQll0JUP52ikOZil1A5yq/VO3TrzK3UwDbjRfEoQVImuW21ChV6N8a+H0hiut/i0fUwO+L4XJsVuD3d5GXX3BUKp4Ox2Ne1i25OEBHpVcnIFdWj0ozoelY2HEEzTjXqfZhfdseuimvnX25apczSclKwfNqqMrbffBgq3UVoGFue7Qguj7HmFiwzstEjMbQPmmichVBO6nQFJhUDP/v0ojQcdcflSb9k1fyKVTiUPPvLp6XUn5wVme48PeT2NxUDGMFfJ1pdFp1234rS8SIwhIbuj+yh86XbVgOkkA5su2Ieq6ziOikIg/b+c84lEoSa5IEF+5ywZ+TUn4THz7C+ssleUacsP4atIPMi8v+0tenFFikj7B+u9IP5mph/U5h/X6lB11Wsi+y6/1WKODfWr5HZFuFVytxh20P7rCdy3nlbP5GGE5MHjKAg+hhGB7AY0B5zJN/gqC8S4T1BdDOKSK4ap2w/movAA0yHH6z
*/