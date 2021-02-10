// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_DEDUCED_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_DEDUCED_HPP

#include <boost/parameter/aux_/set.hpp>
#include <boost/parameter/aux_/pack/tag_type.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/pair.hpp>
#include <boost/mpl/apply_wrap.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // Tags a deduced argument Arg with the keyword tag of Spec using TagFn.
    // Returns the tagged argument and the mpl::set<> UsedArgs with the
    // tag of Spec inserted.
    template <typename UsedArgs, typename Spec, typename Arg, typename TagFn>
    struct tag_deduced
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_list<
            ::boost::mp11::mp_apply_q<
                TagFn
              , ::boost::mp11::mp_list<
                    typename ::boost::parameter::aux::tag_type<Spec>::type
                  , Arg
                >
            >
#else
        typedef ::boost::mpl::pair<
            typename ::boost::mpl::apply_wrap2<
                TagFn
              , typename ::boost::parameter::aux::tag_type<Spec>::type
              , Arg
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , typename ::boost::parameter::aux::insert_<
                UsedArgs
              , typename ::boost::parameter::aux::tag_type<Spec>::type
            >::type
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >;
#else
        > type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_deduced.hpp
hcXruVPCg2h6B+3i8vUm0hFu147bm9oupchsclpZ8Jalg4TRW415XkLElukoWhfR3pyXDWT9e8tCb2NO0zUZp5TLRSylKxFNlZJvNUL3mC3Nkfg7Qdpzt6u2VXXkG46wpENtQU5BqRGeZoLcc6avYYD4oa42NZyGAiRnRCg0Tm2hgRvJfBWngi+wNl3RNMbrDhLP2coUitIECX3rvGGOh+GqXPfaegp3Qi/sIS0EhC3m8nDRh+i47ecO1P12OstQhDv9xW0CGjifRlFALYBXPz3Fs0ZIQ1QfCrTqUomU4ekHm9IsUa1vz199u7/iUusla+nNgzlLlq26PjwHn0r0YSVM3Bbme3ivWDoRku1gXxB2gpzvl8LwtsRwg26ZqcOM7anHNuMjPPQtGX0ogmkMC7q73vVhVpD8/0esgNJhVjINozjdoU1DUR8rAQCsBSJdHyYVR3vJ2KPeY/OOl6s3mzQClWZl5zpq097d6g2ZJnRWr54AW576D3KV6OQ1syCrbBnYuxn7rjFAmGVLd4HDnrnh3rNYLDDwITsyl6IqiKkQStPW8bZ9AcQoBDUhVQR+CEA3FIp3I7s59VIV3Bs35tVfeFSCsmBlleSFl7AVS/Q6e3rpX0pS36up4ql/+i2OQP1/fAYCrv6UT8F0
*/