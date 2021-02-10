/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_END_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_END_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end_impl.hpp>
#include <boost/fusion/iterator/segmented_iterator.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_end( seq )
    //{
    //    return make_segmented_iterator( segmented_end_impl( seq ) );
    //}

    template <typename Sequence, typename Nil_ = fusion::nil_>
    struct segmented_end
    {
        typedef
            segmented_iterator<
                typename segmented_end_impl<Sequence, Nil_>::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence & seq)
        {
            return type(
                segmented_end_impl<Sequence, Nil_>::call(seq, Nil_()));
        }
    };

}}}

#endif

/* segmented_end.hpp
feECLCnSJPxBKqJJtJb/PRiP3OHV+fnjJC7koeLatMa7CTv7xkFWw68WZ8yR3DxZz6fTwDmWCReOGSnmt98i75tp0aTfSAxAFA6zuEy9kRR28EDRds4TxWLiXqdh9tT4yePbpSNekR88tqmsvjxYilQri6nlcjyajujY2sXCOHaOSfRJZIEXh9G9IiKCy6k7HAH2ez8av4N6Lh8Djv91NRhfE1Xk3RB++AJJ6H83C9YwazXuROg7+L1bo2V5USTmAIUIAKn8uOTzMAA1NSdaMfJpvUn5P9vLtk6CcyJtQJ0pw9+4CIzeyISM4TgoIwwazzapHVpLCgtPE7LGwIVSxR2duheDi9H4Gmy1+fhdt/bFpPHSOekwDHbSBkqhIIXyq6+wk3JzYSJUXqjzGupB+IycoBAz81p23R65QWLJqWlbWRjzNmPvOePxKkJzeao01I8XPGkZ8JkHGMLIup5TR+m2bIbCi9PB83shADl1vvAAPcImhFV72QKtvukLtq+9tukKclGSscDvGmhXhn7IDPzrZizsWllgopWVpqGZnWcVcSOekCvt8qAwWEUZqEFrwrKC43hDrUvphibhbSgPkUUTs8ELy/GrNsGLkgJNNh7856A/dTErmYhUepTCUA11azutAJvlLNAuTAEs
*/