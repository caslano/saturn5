/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_AS_ACTOR_HPP
#define BOOST_PHOENIX_CORE_AS_ACTOR_HPP

#include <boost/phoenix/core/actor.hpp>
#include <boost/fusion/support/void.hpp>

namespace boost { namespace phoenix
{
    template <typename T, typename U = typename is_actor<T>::type >
    struct as_actor
    {
        typedef T type;

        static type const &
        convert(T const & t)
        {
            return t;
        }
    };
}}

#endif

/* as_actor.hpp
qbxJuqnS8sKHuYPYpsXilMdgFUeE7UgTnqhm2NOYmyOJJZpft2GCjkWGyQz1puq1nDvkcKVQ92HFQIUrmg9U2EwWTECe1cdfoStbI0Pw3m0ojh0vsNLsFeyVtqoOWJYOCrW3/Ej7E8quKijb3BgUGlFxxxGSTW3gWCbSvi14z1lJC2uo6lwzxX7Ykv14nz2hjiNNdAxS10xRmABqBwKicd+OxtaeCCO2pHFQETmb3+nqxpehp1lw/BS+qVLDiz4c7+8afl7q8kg+BQ6xgT4oqZxKx9w1vbDLFJF6mkgQr8dx9n0VHemgKqMhi2T0ZYWh/fNnjmWTh/86tsv0QOPiRJWZlqqwYp45i7j8Cs1mLXtMO8lJKIqv+oST1Vgc4ak1uiQ8NkcqTCfjBqw6CxwZOazA9Btgc0OTszNd/FPLVMD1ZJtOBFscQSoSEpZ39Z0J5s3uofZZ01D4e7eFuizhR0RLinB3bRTRUFc2OvNpHGk1cW6fBGiYNoEX3YcI3Oq/vPboQwkJNOWacYGEZrNOftIoM8pgcjyu9OzglGmlRNeTOmXQqgi6hzlzUw==
*/