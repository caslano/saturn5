/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07162005_0137)
#define FUSION_DEREF_IMPL_07162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<joint_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
3jJ9H8U/HK8d3njEIix0IQ4HW5ZBqYrGflTbqbe5QOiVed5O1F8y4ujwnhBvm3QaLuv9Yo5RVLnylv/xJdyDGxheUM5NJmc3jotljSlHa96M/IgLLsP/rquF/60c+Phut1Z2jOsNqHWfGK/Zmz8OtUQLRH7h74SfCLUkdAJgaYbaj9iFpKyzvhDpl7mE8RTUs+pCnh/V7MHWdOXhT1m/YO3ZwOZvxa/wt2A0TgBfwriJdhrbwyAP9bcas9Vdgo46WLXxviOsbQ3VJ6BVG+/UX2X/Z5fHkPWjeg6NX5+y23WwdQmc/cF0wPato61n510zp/P/ZF4qBQDnG5D9VWiNVlz8Alw7G+GfKlKCOErWRyDbt1fEejDuy/6KyFD++9bEin56213+sYCypqK6VmLkdjvtymrvJOpWL1x+rOIw3p4FpTcPLCtvDu/eGtZeWQzfK2f9/AF1O/e0A7la8t5PU7ZjlFn9VON7KYeF+CY6lUSrh3iKs/aouFZc1584XtYoJ7nSaK1im8hnBt051nxYM49lRTW+qPAF87VyHKm/B2tU2BJkiS+6qFfYT6WI8DAMdwoQtKjsIOMQtr8IRicxXj3WcjiAvpHDAI69o25H8Y/lveTzJVTjG8O3C+kctqYnNCZ3b3RaDVWeTNXnk5ne8FZWqrUXa/iXyvA9q9e8bPKGv+QMGTq+aID0J7/ey9Ib9de3LIuNme/SjTd+
*/