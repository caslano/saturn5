#ifndef BOOST_METAPARSE_V1_TOKEN_HPP
#define BOOST_METAPARSE_V1_TOKEN_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/space.hpp>
#include <boost/metaparse/v1/repeated.hpp>
#include <boost/metaparse/v1/first_of.hpp>

#include <boost/mpl/void.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct token : first_of<P, repeated<space> > {};
    }
  }
}

#endif


/* token.hpp
4mlr/vf0+PHtO3bnMBZH1LZzm4u5l033NEFvL9dmOKeG+45UvrN/qM9tteIM3Dix/4zxcYDuww1mu1M9bnwU+617CxvY4NuzdWEL/c9NqrLyx6Upsqw8i1kaBCYWhQu2I2NRuKvAvC8zn3mNu8e52ursWtCeZ3TWSukNuFsd7d+fIuL/tBH8fI774e3h++AtSl8Z0PE/f3hV77df4+i067LXhXX53Kg9bgqyPZl2O2cJ3/PdhmRdIGS9Q+q2pa1lfu5UXEw+yR0bI3gLafhvZ3L8M776n+PdT49/iwgf37nU3hXpX53bfneKg+q5OfmndRQpt921UuSflrIOqH06KbKhPEcr0nn9U+Ey0fi8vHn4/GR/WXeou5aVq7RlIyP37Yvo5OYOKwv4vVXN8WddVysfZvHjfdiB7MNQJsS3Puzg5sK8WB92KOYyy814/VnQJhpqvD6M8mXfLrNzNMQfOtzrdbDLtYIc41KUX1bEHC2yoY5mjm+U9fWtHfRXscgTdmXcGUKc/RftWFnSSaR6errVeWyTR3XE+7fiykJmioPCcz6X/mGYzg4GLPOaIueAs0EzDTuV8R4qRXygtQSvEnPCuVgbrpPrn5LQdJe0LV68L3tqm1lg/VN8eWc/R8B+3N9paUuwof+Sj+hp1vsFvcaWFmI/AGnn/F8ZD530e9mWe/kHmh0uRT5H2x8l5F5Y1rFGtpxPoc3iYxZb/OF+I0P07Vouq+p0apm3gLWEpPAZGeEzji7gM9bn8RkblM+w+PE+45gYn7E+xmccBx+QMe12Qh4f8LnmwrxbH/P5vOuIVDojlc9Jp7e8a7+TY9Z+p1De20X0sVtA8wuCBnwLlfeVp+WZgPfoe7/PAp6LRxW4+FsB30PbMKL7aEnnOEpjDkBpJzVVThkS5xTCaV+r804b4eYKqXCeIPzJ6SNCfzIH8XRPlXtAI5yxtdBcfJ/WJTzW6zyS+00jtwvpGKXfpnRXmu88vVxi9eC+q2g9HNdI5UooIKHQwyXQQzTX+o6TO+D0dSPcXKDdTVhzeXePcPLqMxSPAA+HMXL5j0e4Zt71pNH3Mzl9c/y004TO/pbTGUXKZJ3pPBMb4mURG2KTGdtyegswKom115dFva8Xae9sm6zbt3HuZC7ofoXpkj1GvB+4omU5C2Qy8Q0zvo6gxtWhx5j35FoSY8yZcfWy4+M09llOFn7v7Ob8ccXOIRj9KE/7jnPhm85D2QWG/zA2NdvxTKRTjc6OKbgs0l91+CMgj4gD/DW5J5ezi4NWrWQ16jy33viIPiTrdUc2avASJWS0Jm9UyeKcXZeWLBHzoOG+4qlGP/eJfJOPT7SwJKN8x/lC3uW59mu1voPz8s65C7e9a7MLmgvFhiqubkfnm2JucXKeucXFZm7xLUrH11ucv3R1XVoU/wV9SBifEnTi51nF913/zbsongrbr78zJHTaWcPfqtrxN+6gqe9P6wTekQLvknr+vhmmEatLvP17iXnP9Rq018QqXXaySY836WqTHsfp8DsM6ppozkPe2Kzhkw38ZgMfb+C3Grj9jni7gVeb8j8z8Kwpf6eBjzPlf97MNt+LM032e9498JW/EG1LjHIcqXH8933V/PefK4RfBn153nY0ftIv34+6fqP6I5d9oFm/C/Fb4P8O+DfEv8Xj60yIt+V+SfgU0339YDfHr7iX8uis5mAaMT3uo3RZ0DEwRN4+glcEHWvTSP+K0pVuTYbvSr+mdFXQSeVBE3nVLrZTdrA/2j96kPKmBLmbZ57AbPjRh9iPulh83f3t7r5df+75dZVDfU5+57yb1jV3qThDYk6DvITPo5jTKq4E8NozqaPTMoYKcDk/HCMCF38=
*/