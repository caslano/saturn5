/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_07212005_1230)
#define FUSION_REVERSE_07212005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/reverse_view/reverse_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct reverse
        {
            typedef reverse_view<Sequence> type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , reverse_view<Sequence const>
        >::type
    reverse(Sequence const& view)
    {
        return reverse_view<Sequence const>(view);
    }
}}

#endif


/* reverse.hpp
/OvD/93G7xXRaC96NpDsKmii8BG7XEES8L6EFvCnfg/usqqLHTY4OyroctMs0TBN6ymF4lzQE0MSMaj8ePZ0vuiRcZLPDUuAsOOLs5pv+n7kLN8r7y/4cxdtM+9HnpOoyftRy3x/4nx/YcZ36novYYiumrvyntM8mSK77vdqfm9c79ud1lh9/9Y5vw7vKq+PcwHH6QTqzhXsXJoR1p1LiAZ6C5xrOOgPjjUE5yKigYbgXMXRZTpI5zKigYbgXEfOkaAaOBdyOL40DZwriQaqHHLDuZJo4KsGzpVkCOqeda4kGqhZNJwryRBG0sC5kh/6yLkmDUpW8tych5KVPNcHouFcycs/jzXGNZwrKWNQo3QuJQR0gPhPscNLLVMwzisJgtE6C3YGRS7a6xCJTYmEnJ0weTMWzUzR8Fm4DCUVlo6m8cK5KFzR/LjhCKeRElr9njHo55kx3aZ/DgvtoN9h5wquOedsp7MJSctGabv+xcUkLQ5zXNruvNs/T8d2wu2wNnuj8ZBYYOkm4hpzgfGZtAebGg/ieM78RPhzDSeSXH1NTYaNIVyK0xnG+UV+eDuLoLauLTa7xIx5f/LW3v8m9sXcAeB6eUCh1HQSzT+x9avNghV7xKPD8R8lEvV+vxJW75WxjoiXgRqgcl00
*/