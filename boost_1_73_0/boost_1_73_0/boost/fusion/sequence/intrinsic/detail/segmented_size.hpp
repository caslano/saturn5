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
Gx0rG8kUC2MyBRT080WaK0a5sGQ66+7yErnMgz4Qqwi3yL1Z98OrfnjNu1ZcUNGsd3uZhS1hTww1ATXZmkToCR6oDskaTlhboeSEqAqeXEWYAXgKTo9IQIJ58YI1cM4xax1aWwVeGAX6xKn3sRWDiQwXpM7m57JeeRRpC+UtAcVCmQpPCrc/ujo/GU7d8aB3ouHkae98MqiybTWBMjJThzusbTq+GuwEQ//OZgXhjCeBCoU0FTtyZiIybMT7KhDVYytga4ZyKYFF7bdy4JYjp+AbG29YgHRNWrHx8oxiQVtiHglpWfklJhRarUMb9V/vgP9z3ZcC8N94tNMvpkDQq96MechDBw6ZoBos2Sbi2XgyuKQsbTp+G086e7azV2lNtZF3WPIbolL1eRSIBUQDs4Acs2weOk2tnFOExupTDHp1q/GsjQsDkWerwOqg8giMQHlAM3AdIggALM/uM4DAqySj09Eux0USXR/Cp03VgdWrrjqiMSb22SRM5qp+O4I0yQmb+brgWAEIRHhYwEdU9tyFuN8RovFPULwoRp6U4U0SA+KTVKW0abhcAiqnuAgCcApoDvp0ayYLh2lFfbcj31GWDz8dAfpFNMV4mgKSINvaJIAcARP9YUxNB1sfyDYmL0YnA/dkcNq7Op/C
*/