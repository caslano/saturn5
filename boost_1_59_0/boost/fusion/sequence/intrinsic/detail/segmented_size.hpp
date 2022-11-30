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
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
*/