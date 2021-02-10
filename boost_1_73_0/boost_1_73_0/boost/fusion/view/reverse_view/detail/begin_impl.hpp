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
XUgHzkz9jFsB+KxkJrQTOXAHuXCZlRN8kRp8IWAqlYDRxaebs/M/UpgVMisIZG5qcIWpVQ4FvxdgRSbk/QKj4taDmaI6gufSeQSsvTS6j7YFeGFLRxhknitngN9zqfgEDXEPhfeV+3UwyGqr0PtBbjI3yNrw+4Uvl5HcoBMln4OpPHgDtRMpkGQKpcnllEYkBCereqKkK9KVN2hK5wNjwQmlCAv1pHALtwVcNfSkJAYVeiw9Dc5oR6ZmhSmfCCKPhDKtrUZDyAMK5QZpTqHGbWSDcIi8NdFwGgh+NjUrf3MwGp2BveEVnF3twYQ76VL4cnY9vvh8DV+Gl5fD8+sbuPgdhuc3BPbn2fkppl6iMQviobLCoXELsqyUFHlj8+ddg05nX+pM1bmAPcoec8LXVb/YW1s4dj7H7tEvTtalFWbHB8FBAmPuCiRSZ1QyUFnjjZ9XAtAAjdSTnPwhGG6FpEBZ1sr2oHtvZA7JdzFPOy+3DbwaEBRmSug7X7xexynjHdN12Tsil0lvZEqse+6R4G3f+80yFpifGTLp+p1YPBmKReM5eFNABxTRKzSW8Idvgj8keAq99T/gdJMRJT2kJEceeo33JIhVXGNLXgrAP2hvfTJUACSeugDKY9/dLATcUBNBezyHqbGL5hKg
*/