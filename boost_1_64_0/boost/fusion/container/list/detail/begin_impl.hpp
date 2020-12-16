/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07172005_0824)
#define FUSION_BEGIN_IMPL_07172005_0824

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    struct cons_tag;

    template <typename Car, typename Cdr>
    struct cons;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef cons_iterator<Sequence> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& t)
                {
                    return type(t);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
g3vxevwY0wiJko9iyUcnTJZ8rJM25UIciUWYjCV4JdrRhuuxAEtluSkWOYfAZbLcSzFB1yYYjDYpXx7Ow9W4ANdgOuZrbS7yW49bZHn6Npc50uYyV+otFSPwCpyE83ElLsByTMPNuMjV1meR33A8JsvvhTWy/FiphwlSDxMxGifhFIzHuXgZLsfJks4UvAoT8Dqcig/h5XgQp+OjmIxP4Ux8BmdJvuot8vssv9vkSx1beZfkq1bamLbiGNyGabgDV+PNWIR1sh3cgnW4E3firbgPb8N78A7Jz514Dvfgedzryg/+He/Fr/CAxGdb5DcXa6X+umC65LNB1veDGIoPYTgexKn4I7wSf4z5+BPchI1Sbw+jc7+R30/cZ7LfDJbtYKjUxzCciFacjCE4C4djOo7AbAyV9TQSr8Fw3IoReCtG4Z0YLfmwW+Q3FDdJPrqhTTfO7wBcglZcKvnJkHwsw2m4XPLxPczETMnPCnRgFlZiNp7r4Fvb4Bnabw6X0AaYQPscwdVWmGl3txdaaQ+02/keIXGqu/2ww3ra4QiudsTE9c62xFqP9kTb+uZtiuGYQNjO3xoIJwlxxGcSZyllXoLS5hiK3todU0rdbY9VpSwDz/I54HL+zufDhFOEfxESysg3IZ2/OaSNcjfWllFefiTOE5Q2ywbiwrGxzNh22UQIcjjbMBPRRrAkOtszrVjlYHkOd9tmCnFNeJC4L/EEerZzniOuwaS9M7icPCWSR8KZdztYAq9tr7WB2sopE1bhLsK/xpIGhjNP0HTS4f/xavsoYQNl5v92QsIG6pbgajOt4f97CK6206Mb3O2nlqvIl7IswgE+n0fP9tQE5kknnONzDaaSfjXx9YQ9fD6KZwidk5ztrTb+/irx3WNZHoYT37kC+RyNZu2w6cQfw5Qkd3tsJv+vJujbZXfzOVSR+U8RzhMS+NxI/DFCUKWzzTYNHXiGOFuls/12F0bjHvJXo8yT3HpbbsBMvkM4Vuls002e6W7X3Y6NhJOEQD6frTS283ae1bytN+5qd3tvGv+3NlCn2EBIIe4omrUBnyG+lvgGwgnCWYJZu3Awn7tf42wfjsZDlDWeuPRrCFiBdYQq/r+HcIj/H8FTqG9DPklccJWzLTlOkc8ZWEUITOG7qG9jPsTnRHwbY/i7ZaO7zTl0I98lLgUrsE7aoCv43JhCeZQ4PjfyucN22psJiYRMQhVhD+EIoYlgucnfBu2f/JN/8k/+yT/5J//kn/yTf/JP/5P2/5yL1/7/WYhFa5+Kk/b/FdJGlkGYrbSRjXG3jdN4pPYjb0ubrve2qJIyi0ffxibJwzyClTCLMFdpI9PlQVmSvl00qJU8WD3zYOiDWiLj8+vfXZdTuiZWa2ekXVTixnm0g0t7/Uxpz0skhJFXy1iPvNrLVxUW0OxZZG+1znpKnYX0VdNUP6don1cZnhc4Iel3I3QkdCXEM19ArJa+9Dn1vQ8+6Ug9GdfLdmnz3yhtuxWEKcyb7SxrSaHN2XRpy8stseW1vm0obe0nxmpt7ebbipR9jTPOxiZr6W/oT02U+oRH69tVvLS3vyLr6mXCNGVdxRjzn1fsW/77GNaTMb9rdfntY+z/XJwr3w03yeunaL+AtteAjmpbXtremWcfKoyriz75qw//fdOoi9cm29Y20+9a2+j/axvor9R+uPPfTLIfPrNryL33bVv70mNLF19YG2iaRY7zcvwP92h7DJa2nCEYgkMxAofhBLTifAzBDByhb3uU5c6T5erbHsOkTWYUjsUInIyROB1H4ywcq/UTk+OrHHfDPfqJjZO2nvGYiHHa9+S4iN1MvjdA+qsGYVccKN/LJ2RLehvle10xU74=
*/