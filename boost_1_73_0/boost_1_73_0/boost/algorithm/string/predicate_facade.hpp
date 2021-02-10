//  Boost string_algo library predicate_facade.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_PREDICATE_FACADE_HPP
#define BOOST_STRING_PREDICATE_FACADE_HPP

#include <boost/algorithm/string/config.hpp>

/*
 \file boost/algorith/string/predicate_facade.hpp
 This file contains predicate_facade definition. This template class is used
 to identify classification predicates, so they can be combined using
 composition operators.
*/

namespace boost {
    namespace algorithm {

//  predicate facade ------------------------------------------------------//

        //! Predicate facade
        /*!
            This class allows to recognize classification
            predicates, so that they can be combined using
            composition operators.
            Every classification predicate must be derived from this class.
        */
        template<typename Derived>
        struct predicate_facade {};

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_CLASSIFICATION_DETAIL_HPP

/* predicate_facade.hpp
1zUb1qA39G4FtJ/cq0OKObRkpcnCXJdq8CUiyBzvOCEIy9Q9tqKt6eFP0vm29C2PIW8i86E8HLifUWlgCNdR1+twHcaH2D9wR/vJJEUTaMfabTYQVtdAlC4lYi6VNhY4tg++tFB5DVN/X0VfQvjP0prttNvgKPaODjufuctA73+mu8Mq2oVHhIo/L+wdF2E+LSSYdRuNXP/LZylNhMSoRHZY3pVdu5fVBjmrc4E+OksIF29dWI56hgfDYo/lgE0Nf/2L/f3v7BIeOXn1oxQ6j3U/Rk9I8rNhTJEaKBtkJHFsdGUhxwS7ggJQRupQI1leOJQNsCzE4fxMqYmH0/CVePggK7OaZhCWP/6BnxY/qlJWXR4tU1KV8gkButR3Q5cyNBlNd4E+KxPlle2cZTzYlwYXhx0klt/vuJRiysMIXCmjbPQ8wNpvd+NyPhKARl3GUSeUsS9TyQBqGmbjQsexn8hjfGayU5EEA7+o7ldHVCGX69rgwMsJbO6kxL/DEQ1EJIWo7eK/FEi5yVbN4VIKzemlcynnsbmgAN2O8kXZqLSOjkcZhvy4pw06u1cf5TeW86nZRiwoC5MY5R+RuF6FLOzLcv2yxOjy3OhYXiToIGrEZ0dO3cyyUnIcOmZbOocGNQx8cwJUoysi2bcB
*/