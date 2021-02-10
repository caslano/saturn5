/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_31122005_1642)
#define BOOST_FUSION_AT_IMPL_31122005_1642

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template <>
        struct at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<Sequence, N>::type type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
lgW6zSu7XgRuay5Qe3Zo+YbWhgo8b6+YB/w0bowmmURNpPaM5VLcUiyL2aEspIXXvXsg0JNkYznti6R/Bn8JuRXUBpp9ZmselTXbEj+0rYRcy2JHa1DbLWh4aYcIejyetmO1s2x2nXRNIzK7pP1GoSZubBZt6ICpR3kGvVDOw+U09Q7d3rIkF+58vojTeBxPE2+v4MmX8NN8OvECUXqdJB0pv34lWC64GZICeTm0hwfwjwf/17M9eNQx3XwYlKahpYx3zHIaELUj21i7sAYU78UgT4fhaOp8FKnsa3Q9GR20p0HzGplom/2rf72g5K7o8HMYTcOP0TRKV17opszpak/KYpIuFzP4HE6XE2+BhpaydqgmWXwJvHTzY3ds2zRS0VbtNn1nsZxdzuKrWRa7ObXWJK6uLYNkMoFwmsS0hD4uHuocL6bnMBgeHxBl3n9QSwMECgAAAAgALWdKUnZGsjN8BAAA1QkAADkACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1RSQU5TRkVSX0VOQ09ESU5HLjNVVAUAAbZIJGCtVW1vo0YQ/s6vGLlfnBPByV3VNL30VM4hDY1jLIMvtWQJrWEJ2+Jdl12SWE3/e2cWfL68KflwWGbZZV6f
*/