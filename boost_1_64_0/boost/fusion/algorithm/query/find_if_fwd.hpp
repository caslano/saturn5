/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FIND_IF_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FIND_IF_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>

// Forward declaration of find_if algorithm
namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct find_if;
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find_if<Sequence, Pred>
        >::type
    find_if(Sequence& seq);

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find_if<Sequence const, Pred>::type const
    find_if(Sequence const& seq);
}}

#endif

/* find_if_fwd.hpp
cxnC9omsBpVxCiwxOyBa+bhGBs3XaDMOHTNbvJsiQaDgcsTYvzCB4y1XKHvcSdPD3d/VHKhFwiIPIm/pz1FHaFZu8IjkOiDhmDpTisT0jwLeCct2B32rKKUv9K4Zh7EEsunvI8ng8NiiJZY6PJ0EFHJOqWrDFsOsONxOO5cbiJd/NoCNsnxdnl+gXYkvlwV3glW1Bk3ki1CpBrYKiFs2F7MdMmeXFimCMWdQ7hhoP9lI9ojp4F9DHlnhz51gW72zJOtIwkTCADWIu+cujBIXVBMk/1yYoPBZow9l1BhzaGzOL7O0FU6Htdfm3xe3mXFAoZTdFjOLct/9BZ+8moOO7zEYHvmf2iIjzLbShxexNRjlky19XXPxp8FqZZBHG7QAZVGmOTb7NMEpVTfaog+hifWNht4bh2aIWGH2EhZ1ZVJNPL8UFFn+SDbQN7h9+cMSUWgV6FNFc5h19aq0yDYYCHrAt0hUIIcQgtVjgLuEoCfcTmSzIVEqugL9kEIYuvZ8JbYkKcobW2X03PBk9goSndpk02yiVVWwn+h6/PN6laS0t0kp8ku90tdEWA==
*/