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
casEen284vbLqmXVN688kccds+aURTdM9a1RaQlKXJbqsg04ppudI46Dz6HrUt9y6FU/h3EHTx5begqLnfeygxuj4WGnUk2xR6zhoGx4vdsY/ed5is9Uydwiv02lSCclBEuBk81sflPm2wSFHW1thKcarzO6GmJuZ5ARrqbkGb5i0CBQ1/k9ZV9XuaxysTKz337KpusLZSYu0adeeGp3wc5/JC7Ln5W4wNdz7b70bn1O5hulANSv9PS1pYnZzYE=
*/