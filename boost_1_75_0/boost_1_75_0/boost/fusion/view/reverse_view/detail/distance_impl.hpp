/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_14122005_2104)
#define FUSION_DISTANCE_IMPL_14122005_2104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion {

    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<reverse_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
            {
                typedef typename First::first_type first_type;
                typedef typename Last::first_type last_type;
                typedef typename result_of::distance<last_type, first_type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(last.first, first.first);
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
+94nXzA2p14s3Tx+LBXabjpwP1I/bjfA5vlBj0ZRO/HBouD8hr+cAHYxSjliDtokDgn7+nzn7En4EV5qrNKfMJ0nw0etLMJHNif0u7e0bPsW+Jbml+6dnZGe3JPdluKCk+14AWByTAc6e3DdiOSm1FeB8x71R0gvWGciwt4XOiGRV6HV+VSFp/LvTytNtNRqGx03jD9+A+IPvGfsA/S66ENZaZbze26jDUjZ7d3HMq5xG3oZT/9pNOkZ3tivQTwW+TMiXMuzKvo/ZV4mOo7EiQNzyOEzByxkDuyNPTf9xdOu3UBSP7cIWds7futFZMfKnRTkq8F9uLSnGVvosH2FIr8ScB16ccIjGP8jgLmxDZwavpJmQFeBhfvsEvXQ1Dx5MsyjYQ5P4paelZrVq7JAkVGjDh/T7qeY2WkvqVinUL9dyJQAAobRFt/3UCeGrRWLvtbpbA9N/2LS8KHQw0Fy+Os5uZKyayUTckXKp6Z2eLm4V8XYLIQKTjAve0b8vNhxLM/+XsbFP7yZGYz0uBshxbtozvU/3+P3VTOjjd5uME8acCNa4tJtSytvqp6X/yA99mfm1hPVHJPjrzWHGUZnVSXuZN/aLLp3yqv/MtX/5FueT/T5K+2OzyPe7/e3teCZ5KRAz84E7C5IAD2sA4ZrPD7zYRsVk4BPfvnN61uAY9jsl11c4aT8Grdwfa+lgYEimwbssXBxZR6eL2Br
*/