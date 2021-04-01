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
hEHc3+w4T45DcyvvIC5A+31iU4edbe+boGP8W7CdbTI5MksSMhy62d4XPSbBtZ7jUkRJnJcRruUIazkpHFzKyDDuJvYvWceRUuB+Z08CwNJE4MFaomphwWfqValn8KTe05vMTVAKmuEkeaMHQiHV8CSFAeiYtxu1ANxExaycM/39S9kJHQ90xcSkGnJo4yelnFryA8RoUgBcsaQjMVMsRRqKewuivzn6s/oXvS1r1a0U5vEU/LoK3nbMiZpZpNbcsdEYyumcsGuZM2AaD0szyu7HbzQ2jlh55kOsVGRk7R7n2iq2ChmZdnWN5M7WEkXAuD7+aJNlyRhyZMpFKDh5y+3kL31/pN+YgG92AFtdSh933imJw77zaSGiuGNr56jMsQQ56A8vzQuAH9ifQzK8lsudcrd63wve69+2PDinuXkCT2gBoB09Tm2IwSMpgVN/jRgXwkWFZZoImh4ggk4U9CCz0VQNkxEFZHhpXInQEy9O9AAEjDMr7vwsCQu1FIh8aT/wAwfYGYW77IhGJwX1zZXhnW1ppM+beDdIbP223oQvHKeYlV3IpkNK8Q==
*/