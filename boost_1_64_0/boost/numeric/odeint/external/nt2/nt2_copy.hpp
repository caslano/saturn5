//==============================================================================
//         Copyright 2014          LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_COPY_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_COPY_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>

#include <boost/numeric/odeint/util/copy.hpp>

namespace boost { namespace numeric { namespace odeint {

template<typename T, typename S>
struct copy_impl< nt2::container::table<T,S>
                , nt2::container::table<T,S>
                >
{
  static void copy ( const nt2::container::table<T,S> &v1
                   , nt2::container::table<T,S> &v2
                   )
  {
    v2 = v1;
  }
};
} } }

#endif

/* nt2_copy.hpp
j6dreY31WfwW61tIY7k9Z/WR5y1Z/EDIwqGz0OojL1jph1l+449F+vMsS/Bv0n9KfSi4j9jlHNzr62lc1hrqau1u40+8BRKKxrfsAh09j7Pk8qI1J/glvQPuWz9/0Rqnf2P540jX49NLLBfQDvrbL1u+74sFfN/fAd7EPpPZE83F07HWLSm4RPEseUbsqyAWLt7vwleFUyncMsj3If6hNvjdqnyGLJhS5PuHu0BH3/FmtcFrVhu8Tu+vcRvwGVML9w16BzyAm7Nw36T3nNW2n7Ha9m9W2yJdt+3fyW7mLPx3LPwc4f+DdQF8B3XhXyIdeQLpY+r8uvKZAroyrk7zhTFcjgFmTXo3pGG/Do8/z4Q6MX8xSrHT1JXnN3Lt4ijYnxUF51kp55SG841/6xBIgTTSgz3r/HpQVudvr/dQvSZrPJbVsU6sk+VrlhNuBdMs7xLri1UWDX3+o85Po4Zo1Fq4wAvgTiHc99YVuztWVzslbkRhgLBJ+9QFx26UZ+In8Ve22/uo3Gl1Rc5e6O/nLwql0vFNIUg/8AX9YBLfT1nHMtsvIHfogiWH/YmfGRrX/K638s3MI7/3U75Zlg4wHt0JRXgH4S/3Oc0L+lxwfnAw4c8NtGGwf80n3EMC9QzyeyjhLqgL+iMH0V5esL12Uwsp3+FWPY+1zhYeQXhHWroAvAL3diJygvIcXVQHaeVDKCFDxF23mgb7P0vw/hrdezm3wqyNGZ7Z/2mk8puK5zX5rbwtlLeV8p4+Vs7Dtc2w7s3UMH0wBgm836Lh/C0h/tZRSgdfpRXDyhXHFFXW0fmvUDTm3KzrrcMDPkXDYwkJ3xvwqRoe8eL59wWsXsNSaTfu+ADAZijdvQxhwj0Q8FkGToSZxhwNN0S8b1ECPt/UTW8CuLAFJId4NuPBFhFeLJJLx7Mm0VvHQPpRKuXcnEYMmfo3AL7EwF2GvHJbCD4cz2TgROhyDgN8OcEjydRWKZd2A9eScevUZWBUKYO7CPBeHcfF8voAYGupDdMxU8/FgJ1gYJFseki59VivkthFC8hW1yWq04LybUbaoN5nC2GBPD7gnvtZCviQgYOhhLajU9HRl9UJK7rLY9sYjG1sR9vqeN60wrI1K+vwWLamnfrGKsLVNCz70Ul5MGZq+9FFeY4lvIECe5bmXv/EMPUY7kc6npj7Ecc8JuPRkD9/uUK/Iph7RqZHyK26hHGvu8jeBewF9XcZ7+f2deWd1SyzzmquoLjMPsFL+S6Oha78MNfEv0yC93N1/C3eZfyt/47fMiu29Fd6r9fEqfH5ASM/9/zDGsHzFC0/K25NgOQ+za95n8a3lrTF8o+Oq2PdMWk89pxAugQ40eLxDXt3iMllv7PCuhcthLwi5gWPtRfA6WjD4H5chNNxV2GQ75iVjseXvoHTwWOQfpzqhjr45srniDWGIatvDVs+SILL0LL4tbXfkeJ05GWfBHg6PU19E3m9PcG3KV7wizhPL9/vgJ/dPfK+AT6FjmUg+hK61o/CyZ6fubmOy0e76vIepXWF0637kLYB9x+VXBe8a//qVEs2O3lNFbjBNc7T6zi2jtdUJ6G84LuM6WiyYu/O0XLle8ynW+s+2725Eq/tZMebh8sfrz4k2moLfr9uteX5op8o0jXgad4utPK+YcXBXGzyQs6sW5da9v4yoR8oW+e7XNBFvQPrUjtIhkjzdFjiv2Tp/BV13I6GHuPgr27Hq7x24T0vE0MVnEd/wbIX11FewH3z6IylQzfU+efFSDdxrqY/IL8f/2YLH+ka/xarj+csG/BxkY4yAn7+7ZyOugTT70C62O8DTjBW4S6LxjZrveweKz1jlXGvJzPet5RxcfOsWMA=
*/