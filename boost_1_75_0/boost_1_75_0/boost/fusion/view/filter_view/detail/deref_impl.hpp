/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05062005_0905)
#define FUSION_DEREF_IMPL_05062005_0905

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<filter_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
cf8UdW5rQRAtwJSuzBh/ht2A6Jd+F2Zifpys2T7S7r6y9sNzN7IoUbzPom/P6k4e0mHaAB5aepbBcFzL3Gc/f+WzGqkBD7UZC8XvTBMNp4K491/uWk3OTfJ/O6Av+uWLqrmUo4G2UJOaE3dD5k8buFQA1+XGpJFzrm4cOZIT7uvZ5jgFj1F0uW5WrSGj25c3wUQ5C6GWZdqac/BguaJNziVLZZ2e6rXBFb08cOoZ55MXrwvz5/RqZa/lBANyX3aVaw5v7NgIGNyCvH4EDpeRaGnlIB38AyvzI3X3z3HOBy25t9sgvOaC2jfOdiHPVOJQF4iO5HwETSsiYFoYG/2OG13xGD8RPfO7MBlp8FWJEzcwF8bxcdOmDjIJo+2fkboGQLWQytDc7V39DwaTev1Se9J/9NzvIe9ybYV6+KQ4vegeQydDpzguXpYYnkDrgQX3EKII2S8Na4KK5xqDfurjon6zbq64WqwAe17E60Tp7L2CGzXBhpQsevqEOQdficYUAhhKWht5i44wxJXg8cb1269XOgHB1MO96g6jNxy7vkBUx1qxbzAgLUAI80VjFBQ9jN2mzs7fI2INOKz9K/kIyCNcQo54MSCc2mFP65ioEM8netZG5M01RvzUf6VlkY5gcJ6oDnvUBi2coC2TzRLYr4pVnXdZPj0I9tpxmAEha/MSp4f0mCHovN1UGMnetkVe+b6Tu50hi0CbECsS
*/