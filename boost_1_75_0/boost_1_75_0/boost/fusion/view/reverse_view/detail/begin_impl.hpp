/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07202005_0849)
#define FUSION_BEGIN_IMPL_07202005_0849

namespace boost { namespace fusion
{
    struct reverse_view_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<reverse_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef reverse_view_iterator<typename Sequence::last_type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& s)
                {
                    return type(s.last());
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
Oxm+PFzIdW8dqLql+S1toTrx6uHFM4eiq0jz6YcAjAKPgJWt+sfcrRaXV6r3Jv9DnfsV4KGq0GJCLmZG/Y0mSK9m+UJqYqZvfsu5IoCXT9yGz6wD5RIbOqX10O0PmCHpYwXV9lNBNxEkOuZNBVLY89eIbqEpho4/ygyzXjqMfiJ90F/GQUasvn0gu25P5oO7324cfam0V7icOPttW9owq0PmAQNAah422OpiiL4/HvuO8xIz2s8VI01yv+uCcCKmHYi83iaSUDQ0oVsu58tqcj+3TZkCkY98llFAn1BDP366QfmZXzjJXFb7F5YpUpImDBd8U1F8Wjs//amsXWY5t1ZcatEY1cYgBXfwg42tgOPZKwM/4jGZofNs0zEy0WXy7OVA09ymKNiqgrHHVbQkJSN3SqF5hv6hzaLjC4qPJftyCGVTQbOK3M3p9wih3/sxj/7CXWDgugdnvD3XQkTuZsPN+euTZZbkrUno3xwnx8KtJoUT+n/nGcFSvfK/A21/Bt1O7z7Sfr6+eyhpdVSphLCBJZZyoDzB6crzu2X6VPaBz0rEfaFepXSkvJ1OnY2boZwiQ3cNdtJcXs1y4rJORNmJopWOpjrkShwlgFX8rZlucA1tqUN94KsFuLfa65yAzoCdNHvR+qJTEXz91/LmhdF8O+upY6zm4zuLLr6goCm1WtR9f4LCRYpov51wRIbcLxvOYgLhGPCok8Pt
*/