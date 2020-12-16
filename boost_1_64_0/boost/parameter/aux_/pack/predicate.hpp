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
1apGj3Xe83GvJvwDWhdvHsRzsVcvy750lYWNP5wPkQULNiP02nrftiLk0FivraaEn2GnIokLMUsxlh2nz/vh9E70ygu36PFH+yXtGzaL/1O0f/cM7GXi1pZrrOKrd7Q27PiVzL1452lMOU6U+ANteY8xcxyuPqLoOQwnyOcS5yT2LyZ73n/ys4vzXX1F4feYyXo/1Yfj9H18CuYS7e/npJVPn9a3X8bs3419g9hzjJ4nrge7XI/RLURZcXPKWj79MxXV9+KvryaW/pmK60Xx1ydTcX0psfTe1B3vuD81YtCtT8zp3/6SjJ7vDPtb7qpY+lUqri/FX/9MbD0z/vpwYut18dd7U3F9Qf76YWLrt/HXhxNLr07F9cb46/mJpUcotr6gn9z7S/rZRK7nLIysSYXy3UO/qSRimumcjvP7hA7Q4aewLtwB68FWgdDa1s+wN1F7JvwCe0u1t4LfYj9C7W3hbuwd1N4Rfo+9m9q7wz3Yj1X7cfAn7H3U3hfuxX6K2k+Fv2Lvr/YBcB/2v6n9HPg79vPVPhQ2htlqHw4z4Ui158NmcIzax8IW8CKx69rfgM7x6/cIR159QuH0DSC0x2gCbAknwdZwMuwOL4YD4FR4AbwcDoPTYRG8Ek6BM+CVcCa8Ec6BS+BceB+8Fj4Jr4MvwXnwFbgAboUL4XZ4I/wc3gR/govgr/BmmEHZv4Et4LewE/wO9oC7YT+4BA6CS+EF8A44HN4JR8O74AS4DM6AX8OF8H54O1wBl8OVcD18AL4GH4YfwNVwJ1wDv4SPwL1wLdwHH4U2sn0MJsAnYSrcADPh07AZfAYeCTfBDvA5eBJ8Hp4JX4SD4cuwAL4Ci+Hb8FL4DpwB34Pz4PtwAdwMH4b/hI/AD+FG+BF8E34KS+EOmBRknIQZ8AvYAu6GuhdJ519lXpd2E7kXqavNdcJusDnsDjvBHvB4eDTUPaQ6hyn3KOlE7iHN1nRGwHQ4Eh4F8zW9AngWHK33yRXwHDgW5sJxsAgWwevUfx4sgTfDifANOAl+q/7fwUvgT3AqjKMAl8I0OA02gITTPZs6rwZ7avm9ezZnaPlnwzQ4B7aHc+GZ8Bot/0p4NpwHz4PXwwvhDXAUnA8L4UI4Hd4IF8Ob4B0a/y54C1wDb4Xr4G3wabgYPq/hXoDLYIqzhwMeAe+B7eB9sCtcAY+BhNf61nko2NOnvodov3oulLlN2BFeqPV0gabTz8z9kKam490rNUDldRasDQfCTHg2PBIOgr3g3zS9veE5D533IT3Zf7BL0zuCKmsKu2p/1Q32gt3hSbAHPAceC7PhcXAa7AVnwt7wWngSvAGeDFfDfvBReDZcY1Me+Dg8B26BQ+DX8Fz4DTwP/gaPg39A6lZ06AyDrWA2bA9PgD1gH3gMPBqeDXPguTAXZsEReh8uDb+bwp3a/rx7XlYhp8Phk9ruNsCu8Gl4NHxG75tndVz5SNvbc1B0bcDLSfNdOAu+BxdB3KU/fAs+BrfAJ+D78Gm4Db4GSU/3HOq7FLxJ69275/BYrffjtP30hnXg8VruE7Qd9YNdYF+YB0+Co9U+AZ4IL1P36+DJ8EaNp7rEeEfRcqi8vLrEfqCo1eFvsAHcp+2nkz4H/I79dPgHHAUt3Meo/0UwCC+HcXAuTNR+pjq8FybBFTAZPqTxHoE14TMwBb4MU+HbME37pQ6wKmXsCAkr8WrDujAd1ocdYUN4HGwKT4PN4fmwBcyGLeFY2BpOg4fDa+CRcL6mmxG3/306S/Fb79mjk4+ZillUuV+nQvt1KrJX5/95n84izLSD3KcTe4/OX78/53+1N+dQ7Ms5lHtyho3gZQCzHLMZsw+TOZI9N5hczFw=
*/