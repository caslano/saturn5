/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_13122005_2139)
#define FUSION_DISTANCE_IMPL_13122005_2139

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion {
    
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        // Unary Version
        template<>
        struct distance_impl<transform_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
                : result_of::distance<typename First::first_type, typename Last::first_type>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static 
                typename result_of::distance<typename First::first_type, typename Last::first_type>::type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(first.first, last.first);
                }
            };
        };

        // Binary Version
        template<>
        struct distance_impl<transform_view_iterator2_tag>
        {
            template<typename First, typename Last>
            struct apply
                : result_of::distance<typename First::first1_type, typename Last::first1_type>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static 
                typename result_of::distance<typename First::first1_type, typename Last::first1_type>::type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(first.first1, last.first1);
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
Y9BMYBWZVbfXoRysYAZmwTm/zad1gnkwE/ALLUOyOo+69UNzSPbrzaActEzJbGeurUHLlqxmWsxMtFzJalltfdDEcrwWmD9ZytQnc9GCwPCsdISzOXfp+pFoZrBgZg8mdA6muiynvn+yRw97/Iz3v1Qw7EMnuP89rd5I+x5rMPxaQWd4Lb/7wUA03Qptv4CJ6DePy6AFgeGYYGLC0x+Ho5nBcMxEeP3Ts8+/NB8Y7hcwsaril/3RHGBVmLVt4VYa7znie23MLnDP2THg7QI0y/f0mc4n294/tzPaLLAqzIalTOuA9xUHG7Mr3FfW/31jIZp+JV1bP9mS12/35tmoAVFgeB/rBtfBMjkHS6CZwIoyOzK/8Rk0M1gws9p7sjzRrGB+zNqf6lsBbRZYKWa3Gse6o6WD+TNbmD6/K5oDzIfZjq3DC6FlgumYvetU8T9oOZJN6ff5MzSxSojizLp+t2ACWhBYCWbegSKIaibFHU189BAtXrJBU30/R7PINs96FC0VLJTZodH1quVZ37FpYNiHJDFquOvxNU/RMsB8mHmeCItDc0hx7Zuc90XLBCvGrGnx/b+hZUtjpk4zb0DLBSvB7GXFJQfRPNKE8GbWv2q32WhBYJ7Maj69FYkWJpm+aOQbtFgwHbOfQ48WQTOD8bXEp0wahpYMxnNYtPDZIbRUMF6Xs5+7P0GbJVmNse2+QFsGxms27IdjO9DSwTx4rUd8KIq2R1rL4W0ltqCdkvJraroXTH0A82J2899zsdQHXCdakZKUn1hd0IZ9bBqKpgPjPVpfrd9rND2YHzP3Lv8MpT6A8R5FBj4fhxYv2a2XjVqjJUpr6V9u4nDqERjPfWU5Yy00Gxivtcvs6H5odsnWF+5yDC0NjNfsacNaHdEypNzdXjV3RXNIcZcHn/oXLVPKoVXYXCP1SMphwuhjlMNrsOLMNhdZMoT6sKbgfKvmXw1H00s2enGTeLQoMD6fMf7je+qDFFe12KsY6gOYB7NTzy5TfslgPsxq1PglhM4KWFlmPlP++o5qDVaKmS2xfwDVE8yXWXrhNR3QssB4H6YN7EC554Dx3lZZff8R1RMslFnpnEVUF/3agteCllMefkZ7F6wcswrX/tyPZgHjPTq6dWsPyl2ybUGX+qDZwXh+9SP/boq2bi09a3yy7m3PfkTLkOI2V7qXQdcCsCBmrjlltlFdwHitB8a8GYzmsa7guV07u8bvVBcwI7M1B54sRDODhTA78UdjiktdJ+2zjg83Ue5gPsxSKnzVHy0NjOfXolUw3Vf2gAUwa/jHAUF7AoznHtH8yVrqO5g/M//awx+i6X4oGBe3wysTLQqsBLMq//y6is4KGB9zeMnMV2gWsAA+pseSZWg2sGLMWq9o9JTqIs2XOqiqF90fpDE/XExIpL6D8f4N1dddh5YNVobZvg7G1tT39UIE8jE/rAlECwMryqz3AEMmPl/HguFzZHd4Zl9yd9opNCtYeL59Ac/eQ+sk/YjP3hlg+IzZA569Dy7OqY6m20B1+WQ9n1RZiaYHC2e2rvvCcLREMC9mfYf9JwQtWbITNd21n9EKhmuxCBj/+fP/omWD4f0ITCwaUK49Wi5YFWYZ/ylXAi0qXfsZrWDC2+Xr3mjLwPxZ3Njr4dXQMsD0zLrvHNIGLQusHLMea6auRRMbhQhjFlKiR2daC1gJZs3qjgtAi5fi5v68sxXVBaw1y6FpL+M2qgtYPRY3ZuYSHc23SYgyzA5fr1MPLRFMx+zhyJQHaFYwnt+NP6ZEUM3AjMz2xM6dhHYKrDqz35K7lELz2CxEXWa2/3F133E5720cwH+V0e5uukslMoqQ3TFzOGSHkJ2dlTuJ0CE=
*/