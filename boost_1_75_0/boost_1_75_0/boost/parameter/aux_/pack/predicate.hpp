// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_PREDICATE_HPP
#define BOOST_PARAMETER_AUX_PACK_PREDICATE_HPP

namespace boost { namespace parameter { namespace aux {

    // helper for get_predicate<...>, below
    template <typename T>
    struct get_predicate_or_default
    {
        typedef T type;
    };

    // helper for predicate<...>, below
    template <typename T>
    struct get_predicate
      : ::boost::parameter::aux
        ::get_predicate_or_default<typename T::predicate>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/use_default.hpp>
#include <boost/parameter/aux_/always_true_predicate.hpp>

namespace boost { namespace parameter { namespace aux {

    template <>
    struct get_predicate_or_default< ::boost::parameter::aux::use_default>
    {
        typedef ::boost::parameter::aux::always_true_predicate type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using predicate = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_optional<T>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_required<T>
        >
      , ::boost::parameter::aux::get_predicate<T>
      , ::boost::mp11::mp_identity<
            ::boost::parameter::aux::always_true_predicate
        >
    >;
#else
    struct predicate
      : ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux::is_optional<T>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_required<T>
            >::type
          , ::boost::parameter::aux::get_predicate<T>
          , ::boost::mpl::identity<
                ::boost::parameter::aux::always_true_predicate
            >
        >
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard


/* predicate.hpp
YyGr+V1nojnbNMp/56525UE/yqQ6yBuflZonno3SZ99C6AmNNhHqCjMUopshEJWbbPQEhgrMt64pOB7r9tC60XO6fKNeQwsm+mR1jn8qlSemeq/OebeIROeqHcL+pYzHi3aL0/PRd04EP3J2YvMvhJ1VUBtQFoYLFNhCgW0ppTgU9wLFrUBxL+7u7hqCFHco7u4FiksIFAnu7h48OARJtruzsw8rs6937sOde56++c75z7NJRgmS2PAleZF8xHC2F/SAEyC1P5eXxn99xSkRILbfbZREBJPn9NojvakclQQyuI1XmP4V4qT86uIxlJchQIvvomM6coMUAnPZbtrrO4RktyK+4y+IHvfdQAOUtu8UzNpIGkiyv/H2l6iMM+UdQMh9XHru8ggWhtEqG1OWx5ZtT6UcappV9ajHpwU48OoX8muxcerNmZd9JXOas5ptqGcZUov6Z3GtA05NaiSqxL+3GwnWrEmZcZ8By95Pk+f88qpc1vFNuwXGiobC8N7f197nXSvqDiywPj2j1xoYWj0BLxW8b9Uu7vC80GsxMILH/OTTxkLB4C38kcu3uxtiu7k/Pb9TvO5862+rudHFdymPQISKRl1G/AEr/KBYhCXwo0qmPwIRkgcgdyy9hKtR5wyMINWP2Tb++CqMCt/3G3l1kTg/n5Z+CmnsC1zC27Ir/EUrAFJDoh+I/yK05klbtwb0ST0Gqz/qjJJq
*/