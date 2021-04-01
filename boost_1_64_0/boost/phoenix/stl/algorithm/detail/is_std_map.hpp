// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_map.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_MAP_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_MAP_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <map>

namespace boost
{
    template<class T>
    struct is_std_map
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Ty
      , class Pr
      , class Alloc
    >
    struct is_std_map< ::std::map<Kty,Ty,Pr,Alloc> >
        : boost::mpl::true_
    {};

    template<class T>
    struct is_std_multimap
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Ty
      , class Pr
      , class Alloc
    >
    struct is_std_multimap< ::std::multimap<Kty,Ty,Pr,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_map.hpp
kBo+HYW/3ZGeGbKYoJaWFwZP5d/KNrrd9FCqLJeLxx9SeBsT7ipQvHF0apZtysOIUP+3NSjVTzIQNgIUhMSkxWAyimPI/vlGYJwGSTWG6VwgKUdB/mArxLeX/CewL55r974TOmG8MUcZm+5bRCKVI601DvLRw/TFfUHrkhjyaaCZ+1OopuNtxZccOVZIrTKOqcY4+DwinKUylx38x4XXDUQXI6w6kxya7Wlbnfdixncp/S7byfbamWZKD6d92qJoxYOqYrWsSJt0xeiLTKSb+Jpm+z0e3jtNJJHTm1JGCTck7dS0TOSm7KWGz/vUEs6o1H1bRTzjPHB/FWsVXtbJ7GkLsQd4fE8026h06UMv1A8A2Eq+vsBchRjGeBzJ+Re71VRxK+llmitGGVmwTdkjr4422+RlvVo1fxKYV+50dFZG61lh+UFXziFajVZkZSYW4sp+rJE6qRpEQUCnZYp7iorTybVmhS7omQnXBsdkFY2RoSDWa+tRHQUP1Ut/nu3JetGebkCtIE4TxSTlsIV+gQsZgx18jWykPpYTY0zo308tIKaufJQFPlczgA==
*/