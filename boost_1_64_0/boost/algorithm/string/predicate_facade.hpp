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
D9OwLKrU9Cqv/9FLkB4mt7AontqrUHrLDJsT5myOKl2CDZ+VtX4uRNMICzWhKy6r7hQxkaz6AQ2Ol80WdkAfA8KyFQENh+co4N4xqUNpJwWj68/0UXiH8U/jqc+KLaxdly7S5dNtRJpJmqx1iQuplTbG0hBQ9rbokqHvIIDy4J/Nzi0KcZdZ8a7uPmfO6TWgbflYI4Pv78A2C4wrRdoeGyPSIcfVLLAb8XIKQzghhT4E/5aOZHgexlnAVPQdsHqxew3vGAWIt+hmQp2aInabQIwPiUidxXIrXO013PrXv52KZaB7/DycVGsTjC2DJyojWS8CV0DNiOnQc2Z1JdIeCmXtIw0tGoKeLx3pic3UUZQ5PMAau6pH3tBscSSSy8Kd1uayQN/3zgQqwrWJNVq0WXLPp35fu3QRXI0XxZfM9fhd0nsEQ7wq/zoa9a70y8y9Vi9r6s/aGAYrj1Mpwlswd5p07pAQEQWIrF8utiqCFvxT/g9a5gXfrnhkYZBSDicQPtpFpJj+3At6/hFXbEzrCKsN27VRG8YoZBO6zTRih/T0wLWrGb/aqCozjA==
*/