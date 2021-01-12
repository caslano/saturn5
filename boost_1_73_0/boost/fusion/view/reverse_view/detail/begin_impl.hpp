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
gSBp1o2wrWnyeukWgz/rS2589PmadhlTtgPqzEsPUSa4vobk79D0+kQbjgHPscNerYzLUh7qS0DqMoPepn85TQe7zhrRLk+0OokxJvcKRKOzsEzuFYlO5zw17UqM1pzeJb4rMxo0Jmg7GQ3nMKEKys9VGC2YsUPEWcy1Z+5uRXaiSq9UDZnN9230ncqvaZcgGpVf0y5JNFl+Td9OdCq/pl2KaFR+Tbs0o6H8gnYZkeZcxGk7
*/