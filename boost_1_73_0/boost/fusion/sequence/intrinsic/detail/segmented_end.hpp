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
kIFRmIe85xK/cAQGYBpWoVh+n9oDY7AA+fLb08MwBPNQ+HxshBGYh4M3EFdcPfJb0HlYh4okumAa8o/gHxiCJShvwPcwAeehXH5bOQHnwdOILpiHkiZ8CkOwDHtS1AemIO8YdYZBWITy4+iBSVgHTzN6YB5KWtADZ+AcHHghfoZZKLqZOsIorEJlmliCs1DQSt+AYViGwhv4rg1d16ELzsGBZ6ILZuFINd/DefDsp3yYh5Jn
*/