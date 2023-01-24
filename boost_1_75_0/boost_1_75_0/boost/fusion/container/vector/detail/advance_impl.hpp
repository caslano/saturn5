/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_09172005_1156)
#define FUSION_ADVANCE_IMPL_09172005_1156

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct advance_impl;

        template <>
        struct advance_impl<vector_iterator_tag>
        {
            template <typename Iterator, typename N>
            struct apply
            {
                typedef typename Iterator::index index;
                typedef typename Iterator::vector vector;
                typedef vector_iterator<vector, index::value+N::value> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
6u7NuD0pakIMTRZgS0pVAI54MDIyYhmv1VAN68dyvkyCPbDGKykKZWbatq/ZXwvT5D8YX1mFOUriThqK5vj6n5QmfyJt/z5KilwO9kdlSUs28J3pzwHggupMH9ZA3azZ1HQ3Jf9zaJFkEpxedTaoy8sVEWj5IEZ2LZnA3pmiQrqb7duGb+Tl9fo44FI5+1CPySm3JUSZtN2Akv8Xi0jyX0WSf4Gg9AzT3/4mCrPuvfJNlOmc9gfA+3ev04JmZMs/MGkIL0F79mXKi6G9bP+rK9mEZaYvhgmw+/uYoSsehf1X5wQ2txjm80Y5rkrbGvku+aJuuDeOPUKRiQLY52dXIf/t8A+sXFt95XzjFeOPfSKWBkOZrI2AMh5EmXY6koat/LL68JV/lmbMU2fcG6nObTR57Hf5AU//zLT1MELPVU55b6Z8P9Aftj8WdsuWc/Oz5cegCraR0i7a7o5xRtY602sW1Aetmb6tF+HCHbCX3RIhGuE4H5BwhNR9RoDvr2SYwqqGZlyTq6TtdQy/7q/CrKqfZqcV2+7pKPmz9qG+kiXXoEb1GOCQksjocDCObcN9YCjphJHQx++jAcCMwgUS1n/oir0c4jHhmvjX47iZyqVXJflz8xQXpq28V2HKUJeQfN1MpmoZIlINCPYIe+XtbsqR94ZV+PVfjETDKVVI8u9s/1uILDRHgW5mPj9+iJTCxqhcE0/sbAdu43vr
*/