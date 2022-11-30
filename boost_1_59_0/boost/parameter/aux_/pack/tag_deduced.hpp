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
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
*/