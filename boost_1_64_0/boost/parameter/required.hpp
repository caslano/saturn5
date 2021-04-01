// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_REQUIRED_HPP
#define BOOST_PARAMETER_REQUIRED_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.  In order for
    // a treated function to participate in overload resolution:
    //
    //   - all keyword tags wrapped in required<...> must have a matching
    //     actual argument
    //
    //   - The actual argument type matched by every keyword tag
    //     associated with a predicate must satisfy that predicate
    template <
        typename Tag
      , typename Predicate = ::boost::parameter::aux::use_default
    >
    struct required
    {
        typedef Tag key_type;
        typedef Predicate predicate;
    };
}}

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_required
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag, typename Predicate>
    struct is_required< ::boost::parameter::required<Tag,Predicate> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* required.hpp
PQLOpIpeDhwh5kC1lvvzOKZC9h/NgcFc9Xrp5ODAOHPKkMl+298UHDIwX+N/B+O/tTW40527ncpTHx5ZMC6chYbkx6iR2S1jvzC8Z0deqWa+JjsWxo2NLYK8J0y1ZY5T3gdxj/blnHOxkb53qtsb9OodN/pXKSqzwYUehWrMN4SpjlbVjdp6PZFz/CAL6+51+HXv3L/P0GKZQ9QOsnLaN8nL1IxRWl2aHly5swJzZIx+/m6u31gzz0J2NuADnO8iiHB/Ow3mNAqtHQTr4CUlpO+7ZIiija2zzEmIqyAtkkiFgnDKmhN/iDbbG0mKrVOGfzWuZ1jeU64ADAB1Pwgdh/bz+zSc1iqv5xtTvqouxjbDPrVBIW0xzUqk743oLdYRu7y5QFcLQ80AeDufP+54oKobbX71tDVCoq4kh7QXwT6hzlr6TADsN1mn6QfvhXrgFxbmggyarrNkzFhPGmnTPVlnixaQhNqUoCcnPdWdtkZam2xXf630r3nWAXYlEpag6o6VvgifMdPLfdjsdpfsJUiu0nDnOpHSX30rOOKDKL7pdikCNQMeLwtwVA==
*/