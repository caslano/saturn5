/*!
@file
Forward declares `boost::hana::union_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNION_HPP
#define BOOST_HANA_FWD_UNION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct union_impl : union_impl<T, when<true>> { };
    //! @endcond

    struct union_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr union_t union_{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNION_HPP

/* union.hpp
xpJh1SNdQ3daT8Yrv5TIrNIDet1XKywAbgjscqsd2+VWutqv37/pH/7v3kZC72+YTdZEOpA2SXQZ0Bsn1qVX3lXlaR0R6yYXy8mEDIToPh8WjjGoc8Wn1c7mj7uddi+W1tYDcqaJjX/MzjCrPUmMf+ydn3eWvfgyLEtH2uIWPV9XKWvIVzBEsIkKVsl/mvmhP+CStiwFU8qenjAX1wuguVgdsT0T0S527ALc1NG5B9ZMQNJB6BqSbRBVYWkGJoxgCvUM8CcW+NBtGQX6nDyTCMwqqAAFpBMUmIB5BCtalo2jkceEEBzj1aYMVPgZAPb4gQl+y3yBbtxKQJ/KcRkCzQOA0WG8TVcVD0bZ9JZZNi7881jWt7ZBAz7rcvANIr2whRsb24le4oI63eb4aE6zJyiM4wMGx28qns7AzS9qsZIzVPMZFBWjMRKGCM44WPDLmFn7xpCMs866OiIea6iS595lgZQ7DlOQGOzUtwvzdW9d2V7rqQno0HurMe9w19Ih/B5jddagQyVlyjhjpHfnh9191emKPibkOtq9vU+BCtVbEZPABxcxiUqdPf9Jm7MEVUJvW1BlKxZrlK1YPCNhK1YxgwVVlW9EBlWiGXRQVeuKD6rqqpCgSgiD92ZpyviCqmrotqCKFgfFUzo2
*/