/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_BEGIN_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_BEGIN_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/view/repetitive_view/repetitive_view_fwd.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<repetitive_view_tag>
        {
            template<typename View>
            struct apply
            {
                typedef typename View::sequence_type sequence_type;

                typedef repetitive_view_iterator<sequence_type,
                    typename result_of::begin<sequence_type>::type > type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(View const& v)
                {
                    return type(v.seq);
                }
            };
        };

    }

}}

#endif


/* begin_impl.hpp
JKm0GTxeb+nYNuOgTx9+IH+pH9QS9o0+aP7cLnV5F8IkIz8YE0zatKud5ieeHXv/dq9JC8WTCrnUadFgFFt2XO8UeqKNiQGBv9mozK0xTaoe6f640niom7fDe38nJdd77EfQJTX+juqtbfEqt5fsGf9JfIcDqfqABILHLsYKtLfSL8aiTZdb+uAhzhJht7aPhSTnt1yOtjPLa7tuL2nr+CgKrFZq12r18BZ+bl4+aBJp6ebcJO2e0UK22Zo+/KcevVPfi+FRcKxuRvUca/iuxYGSAQ8pk8KR43f5wNed8xsR3p/cNrjFX09jXi8Zlgb18BHn62LZyA419DVy6jOFBmG2R01xXaPj1mzcF8PYVpzcLE0PbfmXk6dyq9RT9+DH+r3bp3le4Lrm8uE+d80buog17+c0J6Yryb9JaFrwSKWvyYgS3JxvRtDDNHFmdkXlXkC5BIwWNUbCUyPaQvsjuT9el+QSL+fUnlEvg29IEDKHqySMC3R2Lh9bJ91M2uFOird71NasidOxBxyAfneaJlQRAnV0sU9etLflXfF6f+42cUe4mrl0o4TI5EJxpM+USboIkVxYtu/ySEGuHeBJYgvsvWtkzD7FA/nRCndwL3/wFH888Ff/uZtx5MB4+AKjGalCgbqBhSIvDXLy+mxObMyEOKQ0uHuMjDkwxSVMSyyYfbkX5HmPsDsO9mHeI47KVMbpN7JAgMY8fBBj
*/