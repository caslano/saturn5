/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07202005_0851)
#define FUSION_END_IMPL_07202005_0851

namespace boost { namespace fusion
{
    struct reverse_view_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<reverse_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef reverse_view_iterator<typename Sequence::first_type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
WB+5qC15oT3iaXCrDIfM4hCZssJemyTpjuULgYF9tE+IwiYNw1x8a8Kolr/aazVMmAfuIltcGCxht0RbAz/3uPuSQkec9v29hqYZifY0Jnuxf2jjCG9DH2ZtYLXfX6wNje2l/IG1oSNr6/Uua4Ha5/3K7zuY/tBbeeiyUtjs0sP6aB9a1tY4d2VjeQh9GKz1h03YA6sCSWV4yZ8l9sDqIrZkSdbFnXRn+qiFOV0FKofULrH/
*/