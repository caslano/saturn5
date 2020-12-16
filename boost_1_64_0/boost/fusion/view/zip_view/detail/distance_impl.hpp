/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_20060124_2033)
#define FUSION_DISTANCE_IMPL_20060124_2033

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    struct random_access_iterator_tag;

    namespace detail
    {
        template<typename FoundIt, typename SearchIt>
        struct best_distance
        {
            typedef typename result_of::find_if<
                typename SearchIt::iterators, is_same<traits::category_of<mpl::_>, random_access_iterator_tag> > finder;

            BOOST_MPL_ASSERT_NOT((is_same<typename finder::type, result_of::end<typename SearchIt::iterators> >));

            typedef typename result_of::distance<FoundIt, typename finder::type>::type type;
        };

        template<typename It1, typename It2>
        struct default_distance
            : result_of::distance<
            typename result_of::value_at_c<typename It1::iterators, 0>::type,
            typename result_of::value_at_c<typename It2::iterators, 0>::type>
        {};

        template<typename It1, typename It2>
        struct zip_view_iterator_distance
        {
            typedef typename result_of::find_if<
                typename It1::iterators, is_same<traits::category_of<mpl::_>, random_access_iterator_tag> > finder;
                
            typedef typename mpl::eval_if<
                is_same<typename finder::type, typename result_of::end<typename It1::iterators>::type>,
                detail::default_distance<It1, It2> ,
                detail::best_distance<typename finder::type, It2> >::type type;               
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<zip_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : detail::zip_view_iterator_distance<It1, It2>::type
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static typename detail::zip_view_iterator_distance<It1, It2>::type
                call(It1 const& /*it1*/, It2 const& /*it2*/)
                {
                    return typename detail::zip_view_iterator_distance<It1, It2>::type();
                }                
            };
        };
    }
}}

#endif

/* distance_impl.hpp
pHloUaLudtUrDdASwHjvs0p79kczgtkw+/L3aGc0k1izweGnJdDSRH+VRq2nzLLAvJm9Ln1nPloBWHFm2VkVnNDcpph/Jgo8XIJmpAHjd6Lkw3OJaFowPvfriZcXounB7Jntj+kTgxYLxl97vpY5cxstTqw5xS/FG80g6qZmraqKlij2e5xXLBctSdR1KDnqX8oajH9GCYvr25WyFnW7WzewR0sX52z7q30gzUHU9Tlym573bHHOCqqC02i5ok754VVztDyxnzo28DiaYqp53X1Li8loNmB8v/HTl4ehqcH43MfUPFiR5g7GczkxO4LuWZCoM32wHooWMlV8Xsp6/QRNB2bLbOaJb/loUeKc2xo190CLE9Z6ZIsPaAax37IWcwehGUUuzRdEnENLEmv+SPZfhpYs6l7vaOWElipysX/Y5CRahljT9mrDHJo7mB2vu9NgD81d1M0Mq1UfrQDMkp3l8teqJdAU08zrFm9a1xRNBaZk1tk+dgLNVtR51N+yBi0QjO/3FyRNcxd1bjO856NpwWyYvY1IKIemF3VLXYu3RosFs2V2pGfES7QEMDdmvdp+7kOzBbNi51znONKLZivqRtu/XkXzA3NmZvx2qy3NT9TlWEy0RsuZJr4XbzWNQFNMN69bo4/fiqYG82O2sMa8LLQQsOLM3C80vosWBWbHrPGe7qFocWD8+Tui/NeNMhN1qzu0OoiWKOr6ZnZsTXmKumb/ph1GM4Hxz27T0mfRmslg/J5VcPFrhZY2XXyHDWwwgbIW1mlr7XVo2WLNPa3OKtFyRd3FWD8ntAJRd79r7gk0m0TzOu0Ht+s0IzBe59lmeB20ADAHZsW33aiFFiTqXp3WPkHTiroVjkP3oelFXZXrN2h+sWAezCKOLTtK8xN1HcauTkZLEnX/2Z4+juYg6pYMLNKT5iDqBqlMPyhrYcOXzj1Dec4wt4uWXxtQZmC2zKa/mreUMhN1d146daFcwPiMYs6lnqBcRN3f3zovoVzEfrfmj+hEuYDZMfOdOqs5WrKo+3ogfBRlBsYzm1D3fRhlBubErGenJ43QckQPxtr2GrQ8MBUzH+vKgZTnTPP3sZG1WzZBU4Pxup1jTTXRAoW10A9Xo2nBeA+LBrUm04u6fP+v3mhx4iyP8lJ2oRlEnX9oRCZlDebMzN1qshVaqqhbEnQrg/IEs2HWtuObKmjZou64bugNylPUfT35wB1NMcu8zqHSryzKE4zX/aOLdEULEHW3FNGJaCGirsPZIQFoOlHXZ1zubLRYUXft0i+ae4Ko08w7UPiaLOr6RFyxQzOJugUfg1uipYm6/kPLj6GsRZ2x3eI9aDmi7v4zz8aUtagrVVl9AM1qtvn7Srlt0b5oKjD+/G0o+4bqNGDOzF6+O21ECxJ1HZc+aIOmFXXV1lZUoEWBlWJWP+T2fbREMC9ms1Q389GSwfyZ7R62dwXaDdHfs/iqoykzUTfi1Q8lmv0c8/fNixtTaA5qMF735NOz+tQfGO99QosdR9D0oq67am4K9Qfmy2x1940GtFSwcswOuc7UUg9ivx/5u5/T3MHKMxuY7WSFFjDXfL+dN+tuQ9OB8bptIS0W0znB7Jl9dTswEy1J1NWPjFyPlgXmwKyqo/dt6kHUTTpcqwZlPc/87k6Z1SsTLRCM9775kXM7tBAwF2Zu/T9MpjmINVemOmxFiwPj5zTsiKS7awBTMxt0bA2dxQTmyGxc8NQmND9RN7XMuFTKBUzJbFXvZB3lIuou57wZjqYwmj8rXjUODqLZgvG6smMdbdC0YHy/6e3d31Euoi66f5nC1zqx39Rr129Q76Juzvuz4WjpYr9h/j37U+9gfA5RFRd3Rcs=
*/