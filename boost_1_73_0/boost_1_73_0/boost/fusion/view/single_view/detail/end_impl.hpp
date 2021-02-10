/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_END_IMPL_05052005_0332)
#define BOOST_FUSION_SINGLE_VIEW_END_IMPL_05052005_0332

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct single_view_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef single_view_iterator<Sequence, mpl::int_<1> > type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
i/e9Rfve+gYb37p346zfklYeAWFsNxtYEoVn6HQgfhlHMWA6TITGPXBkZrMSqLS4SZHVkrrHym8P5bRWyK/uWC2U4vDkQuAw0H0ACgsI0Bn6eLIiZlJxeOFKTHOHZuYwTdRumSiQsfeIN/GE/HRagwpgySGTOVODegS/A7hhA/CliyMQdNJRF1/siS53AWnyhyAgqHAH+xibg85PLIQ4e1bcAsUT2hh9C3aiGSV06/d5KFzbkyeELbDU4PL0+PT18LxLG3nyhBYyqXK2w7q0jz/0RGf70azToy0GxDsVFlmwTEEdlCEav4StYIBcC36jTCQcGL/C9vPiFgYxkoQUVC03kWtV6HJDzhvDoaDoVseIv8JB4olL4H53giSU5qBwquSLIvwgAwTU+dsoJ2WNlicKMEJnOWEDdk2l0RhZmpGEL/I+mUoTGeWo0U2KGwYqzdbTMmTTGj21WoKZ3kMjAOSKhROCAF5MpiGPrOQrAm7aUxQ0jhW2LAEy9RC7TKJLGwaCBt+xAxIxg4APGX7rMWLDgneBGMfEodW2u5tidResjz2zEUYrMJm7OE9/D04XUNRtIfZ2Bb/zMCJwpPAZnY9LnFJZLlFVgQzVJhYgFqADGoNRhqoV2ttoY4B1ls8TbwMg3h7R3QKg1i16
*/