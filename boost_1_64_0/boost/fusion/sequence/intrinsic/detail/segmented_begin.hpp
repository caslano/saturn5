/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_BEGIN_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_BEGIN_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_begin_impl.hpp>
#include <boost/fusion/iterator/segmented_iterator.hpp>
#include <boost/fusion/view/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_begin( seq )
    //{
    //    return make_segmented_iterator( segmented_begin_impl( seq, nil_ ) );
    //}

    template <typename Sequence, typename Nil_ = fusion::nil_>
    struct segmented_begin
    {
        typedef
            segmented_iterator<
                typename segmented_begin_impl<Sequence, Nil_>::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq)
        {
            return type(
                segmented_begin_impl<Sequence, Nil_>::call(seq, Nil_()));
        }
    };

}}}

#endif

/* segmented_begin.hpp
sJ2pwAUHlExNgxHlXi7QUcQVec+vPTakke7uw4+E+Q1OZdmAaFPBDTMAOepvwQTgx4C/yesS5meXvWKhuganXVvQCPhF/kiaAjEtn2dMk3tFxC3ZlNUbqJodblXlKNaeSp8tadFSypEwupdrFyhQpC8Q1kIakr4Zcl2roUGx0Q9wg6CSAKOF2GqxmIeYajgOqDPYtM3P6QV3+jfK8lpQLRY/xKRhvSHy+vzlOhjYmkozRQJmfYFsvTH3JnxpusTuvy7+zLrYzhmH/js33qS51OqqJ+wviyGtuVC43UYy9MOV4oAyCMsHuukDvbhtdGghbBIXrcW/KbMpMU99sGCclLbsjpSgJwt2KW5r7NKRAt2raBHL3+blzpEki3k9s1SSMxbaTp/bp/LjnCLY/79cnGgW33meMNMQCVOS6dnySTCO13/OECRYwjUQeTrDomr/Qj7eMIKbq06fZpTpBcqqZeXggSP9UB0NLHCbQnHI8l0nt+HBCpnEWWAeDFloSBcQJjNoSo4YBxdjYuiv94sqwQJA06rFRgT/DLz5zx0nIY1r1QKrrQNcquvHfg==
*/