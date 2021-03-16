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
l5ejzzUaHf0g0bLpBr3aoNFjv2t0wDiNZt0BvUEfZ39N9Ohwndo36vTPXKI/QDt2o04X3090+jiiEat0OjZM9MYFRIMQKXYNw/M5Gi0ZZ9A+zxn07hkYx1Kit9YTrZsPua3D/f0Gvf1vg26EHoc8rtMXT4J3yP969PkXdNF7mU5PrTDoiQWQx4cGjbxFo2tgfzpsp/ZBg357TaPD/ySaHIFsTjRo7hSNbh1PlLtTp1NO12j0YTq9WYSx3o515yk=
*/