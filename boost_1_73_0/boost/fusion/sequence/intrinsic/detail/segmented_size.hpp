/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_SIZE_08112006_1141)
#define BOOST_FUSION_SEGMENTED_SIZE_08112006_1141

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/mpl/begin.hpp>
#include <boost/fusion/mpl/end.hpp>
#include <boost/fusion/support/is_segmented.hpp>

namespace boost { namespace fusion { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    // calculates the size of any segmented data structure.
    template<typename Sequence>
    struct segmented_size;

    ///////////////////////////////////////////////////////////////////////////
    template<typename Sequence, bool IsSegmented = traits::is_segmented<Sequence>::value>
    struct segmented_size_impl
      : mpl::fold<
            typename remove_reference<
                typename add_const<
                    typename result_of::segments<Sequence>::type
                >::type
            >::type
          , mpl::size_t<0>
          , mpl::plus<mpl::_1, segmented_size<remove_reference<mpl::_2> > >
        >::type
    {};

    template<typename Sequence>
    struct segmented_size_impl<Sequence, false>
      : result_of::size<Sequence>::type
    {};

    template<typename Sequence>
    struct segmented_size
      : segmented_size_impl<Sequence>
    {};

}}}

#endif

/* segmented_size.hpp
RzvZV2xhbaM9q0f62Ahnxti8wLMvfRM72ZNm3QTTz2UPspi18Vs5ix/CvjdzhfOwAAGtjhDg75Pw/z////P/P///8/8////z/z////P/P//7n9nboWLrtH/y5/KLnvG7Idb5ZWUOx6/PyvtGTsp7Jer060Xyfp7LxvTPn5P3qNwm74d5QN5re/vf9ete+Xf/n/8p/XrF3fLv5Mfl3/N/nEPeu65f/36nvH9N3k982Yv064P3
*/