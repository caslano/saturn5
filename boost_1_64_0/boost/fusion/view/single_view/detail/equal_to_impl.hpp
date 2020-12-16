/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_ITERATOR_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_ITERATOR_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<single_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
              : mpl::equal_to<typename It1::position, typename It2::position>
            {
                BOOST_MPL_ASSERT((is_same<typename add_const<typename It1::single_view_type>::type, 
                    typename add_const<typename It2::single_view_type>::type>));
            };
        };
    }
}}

#endif

/* equal_to_impl.hpp
hQYl0rZk6Rttq4ZMmyLMrbMV92LlfSpaO2aTM9QfRP3sFx2X88TdZ5Qn2mxm14ZmaU9x/fE8zezZ5SXNaG3RJvGeufL/+t62xvgGaPT9h4/MW2M21CvVRFhEZx/OyJNVmGugBm5mX43t/F9hIbThJmm7s2rphQU8aGZpb0c260VxQzVwgDRoMv+xMMswvJdh5i0cbxfmRcvOjN4HQ/OjDWZ2Ol9VGtMxXIMUZnEPPJVoTLRszGKzp1hpTLSs0tg9LNaH1pXZNNv83jTfCLw2ZRbMfrG8MA/aXGYLWjRqQ3Ej8XzEjM5HaG60RGnsHId5oiUxo/M0WthgTMsotTnRVGN6DSyIpsoTRkfPtyz+dEaqHY2vX41PTH1oTLRNse+tEFq3yG/pqfbx8txYGK1mo9/OUc+8uH4maV0PjuhP6zdBA0yMLDy58lnqGVpBZuYif4ynnk3UoIA09vkf1oDWlNm449XLUp5onZndL+jdJUz7QgOPNPb5H+aJ1oLVMPrn4jmpvsnyszo0+VkdWgiN50Kfx6E5p+B1ljT2eRzOh7aaGX0eh+adqsF2Zmd7H8lIuUzD8zuz1d2gK9WOlsiMbxNhNDuZbvucjvstM/l7lTgfWl5p7JoW80RTjRlAU+USQdudtp0VQdv0ruJ1yvNLDd6AtFsfraKeaXPx/Mcs69q3cl9By86MnqOg+dFyMqPvh6MFdXbStTUP5aKzbAWvUw0wL2o+dg2GeaLxuCa/NhshzKmz2v3/OkC95mPqjrtetCrMFmc521NYKDpOXoegRaJNPtNBs8yPNnr+guaINvkcBc0VbfJaA82Dxuuj7+mj+XQGgbGpwgJoOZhtypnvY6pPZ6V7Z7xB9aGVZdZpXs1kqmFBdFzqiWm5qQY0VgN7foY1RBu77sEaoo0968Ia0Hh99WqXGEc16HLpvay9h2qIHlM+60KzLIwydp2F9aHNTSct5WTLRLLlGnRncf4aqQ0oT7SZJmk/1O4XI8y/UoP8LK7ErGUNhQXR4pg13f/kLdWAVpHZkTbz6ghzfo33FswKf5PvN+onGp+vUPpaEylPtDrM6m6cc4364o+OG7uyPVDtaDzPyYP/OCzMjdaQWb/bvjFUH1pJZvT5ERqsip6v5dvTc4RpOgtN+imJakeryvNcvX4S1Y6mmi+EVprZ0ho381Dt32iQzCw83N1FmAuNx81zHVpH86HxPOnZGlog2thzRcwF7SNm9P+GaLBaAx/bBoOdRz4g24DnYpO0mdkmf0q93qhBCZBG/+eNBps0KM8s+d9mLag+tEPMTtxeso5sM95vsvkGrvCNovm2apApC9sG63xVn+rbr8E3IG1chWlbhPkPaFCf2Zmdk/4UBkENMrL5MrdqbqJcDmowxCwtZCl+RJj7Zzy/x0jbPmLaEGFwRIPDLC7X3544Yd5jGowEaelH/9tPmHZcg1iWy7PSD+Xx7IQGm5l9u7ob7Zu+kAa/8HNqocy9yE5pMJnFTZm28i7lclqDdMz29MgeT/08o8F9kPaqcf6rwuBc9Pn9/KZS3YU5z0evuyN+W0vKBe1DNl+Hm7WKC4tc0MDP4mpUPnyN1v0i3j8w2/V8UAma75IG5dg6ZN8y43tav2saTGXrsGrCR62o9ht4TGa52H5Y80RY+KYGd/h5c1mLZ8LgtgZ/M3NPXEDr4LijwSI+X+tkMs89DRzMHtfe8wXFPdDAy3JpXuHhfmGWv/D4wmymtRv12vdIg2MgzVcpxwmyVA1uMdvvG03zBSJ4HRIrzTlqZDdh8BTvKVnc6D1xu6gGtK0sl8t/TlhO8z3X4DsW992OB/Uo7oUGa1hc/1w+ef35CvNkVrptzmRahzd4nGc=
*/