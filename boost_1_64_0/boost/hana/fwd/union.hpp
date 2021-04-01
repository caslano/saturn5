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
kRn5bYFwbN1WVNMzHhITzU1T9/Pg3QiKAUbNp+Tr66RSzn4RUyqDIX2QwzNeuvNKBn9J0QaIMmApKhCFKO5ARE6EMgH3vD3sxenfdadfdD90O6N3d68iZAO6eCAPeDk60ICqxPzAbsR3zjzsV54VhA0a5SvrW0G0ybF+IUmZ0wc/H8N9TKHylm9FRbcwMMzjv8B2el8T4mwWSUWKoel7LqUiFVvCmuqc+YRt6kbTQdFU51eQggTW8ZxHQlRsBx2cng4vGi0sOCFCc85CqcO/u/pdeubcL4f/N4HhuIqD4fKJcG4SlSrFpjy2roS6SaoQ/S51e5O+PrD6d9N22M7WqkUUpn0OxPxeL70oIg29MiwOBzj3h75Yyf3K0UHQy3ElMoWvzZUtue0rcMI4yetunSvPbidNlAP1pqOZ57DQmB7R7Nn7ACWG05qNh1pwI9eVWkC+7lu9xTGFwEC+9ORpfJxUU2+VXT7VTam5d3Ldcv3qSRaPJeEMvrrN3UMfK0X+vEopNC9rHrLTEt4eH30BM8qLJfOBjYeNDANlVMHjLsDZMN6wlGI/YvyT+A==
*/