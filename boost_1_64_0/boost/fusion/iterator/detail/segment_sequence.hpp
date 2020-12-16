/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_SEQUENCE_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_SEQUENCE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct segment_sequence_tag {};

    // Here, Sequence is a sequence of ranges (which may or may not be
    // segmented).
    template<typename Sequence>
    struct segment_sequence
        : sequence_base<segment_sequence<Sequence> >
    {
        typedef fusion_sequence_tag tag;
        typedef segment_sequence_tag fusion_tag;
        typedef typename Sequence::is_view is_view;
        typedef typename Sequence::category category;
        typedef Sequence sequence_type;
        sequence_type sequence;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED explicit segment_sequence(Sequence const & seq)
            : sequence(seq)
        {}
    };
}

namespace extension
{
    template<typename Tag>
    struct is_segmented_impl;

    template<>
    struct is_segmented_impl<detail::segment_sequence_tag>
    {
        template<typename Sequence>
        struct apply
            : mpl::true_
        {};
    };

    template<typename Tag>
    struct segments_impl;

    template<>
    struct segments_impl<detail::segment_sequence_tag>
    {
        template<typename Sequence>
        struct apply
        {
            typedef typename Sequence::sequence_type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence & seq)
            {
                return seq.sequence;
            }
        };
    };
}}}

#endif

/* segment_sequence.hpp
0Xp3f0F4ZWC1iDi0JDvEqawPGbQk8miBWIPP3jkF4F5R6ayTyeOhbS01ayoXlM8RrOPw2v9qHl4eryc5+/ufuJXVrbXaDj0P5OJHgpVLKubOQDbOPuJ5+4isCQXEXGeOZEF4u2CaHJy4ttWK6ZNNtdPrpArhYNHKngvBWUUYc3iu1DizFi6cVzZzAVOIVcMcODmZAy+fb/uCM4TSrbfdsNplgdrlfKNb2U0OvK6xngxYw+PvuOBye3rtdA4cugIOLJMDY1uKLivtgkmN1vMm3HAkrnmWyYdVtkaYoEE0OfqV2OHCQQMw5pZAuLqp8cxAXaSxOSCqnbViuzTuyX54hOdSdMJ7DVP7Dzv3xne778VjaH/yl865sErb5oK1kUBEEqx8xVO5uG48Z70qNz2uOJXOoSVUXbsc5qxoC7TUQrSaI7XHjQf/tL68nwcj0xcrlN0+3dkN/5E9ZfJwC+OFPnCv2dbiolzhxfTelywoP7Fs0eKZ80yrU76uYzzUU+g42TEebBXC8T+eOzt1hIdayc3wo2xK7QevM1uZZLmy+Y/dcG2W2l97PsnDQS0rbcWtjIDnrCWu6uLGkyqq/HU+HB5oWn35cPaufan1qZsObao6Jvj/lYeDqPVeYgXhinERFccMWvDWhmh13I0XxGFLQuMkCuKwLXCUrWicE8sXl5P2mMtpmjxXd4DHks5cVkc4LCmMuVJrlT2QrlUGG+sqm4N1bU2st0rNtd7EgUfVNU0BB425lB/opNasacmKRMu0q4a11St5BVVOV+askdU7DLi+saUxEqgMtNSxhmPrMQMv2NIaKYCt8+dZSsZ1pY2VNY1BHQes2S4Y+YYRI+ZpWGNDoDUCbLCjuws1jGSvVfn/kQ5d0qdDSwsU1iNflS+OysdZOUXDU2pvWVdbc0agNsL9yq9Xq7UbS+va91Or9lPrgrEfDUv1ULyHRc32hpVcBDVjDsyeWMETBeBMruW6wAVXDFM64XfDYZq6N9nTTRd5H9Mb+fupuXC3H4nPzIOzd31/VX0eHO3XcM9pbjiTu+ovT7kbzuTq3gz8zoG5+OYL5MHhm/ZhVTlzt5A6ti9gyjuHfojXe9vY2QWzoxOX6xTvIq57pcFpeOYuN32tjQ0tArhDn9icD6+sjawWWp95X5aLBhkjxWrl57u54SsD4cb6NWK1s0bsXLVGc03W87ZXYKbfFL/Kx8GuQNJ0iHJnnazN4MZJqHiNn0PnCQ4cNoVbkbFoVPqdA0NBybT0vRk9d6iN0iRYK5qVDI4zYNpeQ4Md+L0O7Vn2qjm1H2BHpXaxoH1WLyW3SHVDaU2jYUsW718zYNyrYb5eDsxhs9BzXjy2HbaouqUhkNVyPedKE8Zqxn0J131on5mnvJWl8+QFsytPmlleUUkTwinD64zegO+dfDxJQr3j073pfBw8IA2NpiZm4/RW5z1iR2Fc4oBNZZ2Dr2ridwvjg6drs/cK4LBdwY/KMQvh2BnDqupGJmPLotXRi9CzGremKUh4ClW3oXYq5mq47H+QRC0LB6rrRKPS++cUTnZ7beFwgJz2jGCNULzNwYEUELFRfpSOGjh2hJQLaR/4jAFvraytDtnBXd/vTWk4u8BAoEDPz/seNJzEIJylUGgatyk4/sHkhuZtjHfqgrOk4tiFi8orTq4sXzB3YeXM2bPLFi/Oqgq8Vfn78I5x0d6A0s8fmRPR6j7FiWNdeMeXnVw+J6dPkyiIw2qGnicL4rASOCqP2gSOmDVzcfnsytkLF5CQzSxfUKH2qGiK3VEYz96fih+F53LFiBj/3gI4cytra2pJjGrDa0JmjkyN6cDra6ZPVRiVyk91K2qH09Zw7l2j5P6pvDc=
*/