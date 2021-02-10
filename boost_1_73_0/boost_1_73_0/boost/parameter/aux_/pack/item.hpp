// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_ITEM_HPP
#define BOOST_PARAMETER_AUX_PACK_ITEM_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A parameter spec item typelist.
    template <
        typename Spec
      , typename Arg
      , typename Tail = ::boost::parameter::void_
    >
    struct item
    {
        typedef Spec spec;
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
        typedef ::boost::is_const<
            typename ::boost::remove_reference<Arg>::type
        > is_arg_const;
#endif
        typedef Arg arg;
        typedef Tail tail;
    };

    template <typename Spec, typename Arg, typename Tail>
    struct make_item
    {
        typedef boost::parameter::aux
        ::item<Spec,Arg,typename Tail::type> type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* item.hpp
ZRFP1CbS7xY2bOH/bS2v0cy8QdLMpQ6LFxh3886pXGLc0B2qzUhodU3I79gRF21ezlM6g1ciylXZOIgNsT+bkDQQOno89ttVRQ1xR2BSw8JmpYkcRTIoKPmNbhmVdmb7ZWwcJRcC8YhY65c7r6goddWMY6KrLp9zYJbEaaj6Tn8HMVDdozmm9YfRyCmGg8pQNkLsOXBdqv1i1WPypWD4o9EQPejmtnPy/l1b6iQjJYTfgmoW5ZL0OC59lHyymlZhli99s+/JMmJUWBA0oqcyLxGFxu/zEkHj/16iKh+Pb34FL5HV5Zlekj+6ypTgygvpfsW7d1E7UxTZeZLfTgohM+s3a3B2AnSXYrSbrb0WiEq1Sr6yky7w9ER1Bwf/OsUdoUtX5dHCxS1mrySWyYIvlebzQT4CcJ2pm/ct9GcqltLo9OpJ3XjtH9upOsgVp4ue2NCULgXLbh580ki3/bRWP0+3mENrDofWCznMN4VuGGz0Mxd3wUrxEnUM1wXZ+IREPFg9gOa8tJ+owZMdDjwMbhJn6eJdacErbZkGOSYX16TDTnFwpH2tNotVDlHOL07TmGLxiwSlT5e4uiK2rh3TNMvwhab+Oghj3Zmf10k79EOFBO0qVXy4+7Or0H6tSOdcrrpM1LcWVZFfstYk
*/