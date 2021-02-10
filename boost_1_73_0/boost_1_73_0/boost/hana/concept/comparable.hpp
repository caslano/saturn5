/*!
@file
Defines `boost::hana::Comparable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMPARABLE_HPP
#define BOOST_HANA_CONCEPT_COMPARABLE_HPP

#include <boost/hana/fwd/concept/comparable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Comparable
        : hana::integral_constant<bool,
            !is_default<equal_impl<typename tag_of<T>::type,
                                   typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_COMPARABLE_HPP

/* comparable.hpp
iCfXjmyntBIfv+s00CEx9QVXqR373nOOj517pAojqcD1sH81nGaDu+lNNpvd3M2G2XXniFeUofcX09OPax2c4mDLmifjxn2TcevsH8rD+9FZ9ozdj7MeuD9EkmKf8pyd4HDKM46blKxluYzjLDtE9BC1xb80Zj5kccgznBYzB7baOvVYBhwPTvD54uILPuH87PwswZUwijRmgcyS3GOCS9nM/CjFZtPz9D0BBQjda6HmpfLwtghPwhF4rFVOxpOE8JDkc6eW/KIMQkkolCYMJreL0fhXgqdS5WUE2doavrS1lijFmuAoJ7XeYVTCBdiC0xlcKh8YsA7Kmh5zEwK5lY8YkV5obyHWQmmxZCIRUIZQ+a9pmtdOs/pU2tyn+cv2e2VYve5kwSJWYgtbBQSL2lOCGJlgZaUqYs+G8GRVL7XyZbJXw1RGptbBk9YRi/MU+Z1swqy1J4lhqFixCrHz1vhI9VTa1ZtA9jGiFLUzTMQ+cJC0bHOCmj8l1wQ3O3+haD1tDP7v0ez1SljDYtDtzzCadbEUXvkE96P59eRujvv+dNofzxeY/ER/vIhgv0fjKz56xWQOtKkceSZ3UKtKK5It58e1tNM5UibXtSR04+llnkJd9cpuXChiPYk1YnI7HHO54ErxuuOSRLSo
*/