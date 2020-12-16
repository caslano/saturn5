/*!
@file
Forward declares `boost::hana::insert`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INSERT_HPP
#define BOOST_HANA_FWD_INSERT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct insert_impl : insert_impl<T, when<true>> { };
    //! @endcond

    struct insert_t {
        template <typename Set, typename ...Args>
        constexpr decltype(auto) operator()(Set&& set, Args&& ...args) const;
    };

    constexpr insert_t insert{};


    //! Insert a value at a given index in a sequence.
    //! @ingroup group-Sequence
    //!
    //! Given a sequence, an index and an element to insert, `insert` inserts
    //! the element at the given index.
    //!
    //! @param xs
    //! The sequence in which a value should be inserted.
    //!
    //! @param n
    //! The index at which an element should be inserted. This must be a
    //! non-negative `Constant` of an integral type, and it must also be
    //! true that `n < length(xs)` if `xs` is a finite sequence.
    //!
    //! @param element
    //! The element to insert in the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/insert.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto insert = [](auto&& xs, auto&& n, auto&& element) {
        return tag-dispatched;
    };
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INSERT_HPP

/* insert.hpp
9vGCzw3EU597zD/9ZAWnC+nXtdCFpzNLfl1IF8KVqr/3I2kJN/l3FKidaem/WpEo/+y67OV/xCz/sXVDlj/LKv+Xy9PLX5ha/gKqT5ViyvyiwTN9sSe6dM2RaJ7YKvpEf21Y//IMDp5b0373GyilD7eK+ZZnTXtz3uKGYPstnYshihQcxhFiDbd01nKkWliPVxoJo49QEkeGJK+WeWkNnsUNtgLLmF4spsFRcETu4ukNnqhbdIkXxKnesX+k/NccaQ6Jucr0eQqJjXfePGX+Av1Nsw1GorPCtfqfK0223lEbXqAvsih94+KGrpsS3NzSSdn/KnjEZH55ZTrzoN3kKly7QH+JldXjnJXFtS320g8Z/7dIYK4QFjcptWUzlU/miU7xmNDxU5wS71QmnaaqgOwUVoRqaSqkz7jZYK55LMfrxSmmrwqTpllKvNkhJoobEfH3Cw1BnXtjD6p44m/zrOEowQuuw2vOR18l8ttuUVzdwXbNG+tS1mz3bmi/dm/sWWfzU6IKRb1icYMzpNzaVfFimSN5VPC2/u1mjjBVwzK48WbMiHCaBQYRooho0bsnNt4dWQ/JbVzaeEejS/c0Eoe+YPvihnd3cu2EFunvqLHYvpXuC1QJWI1HcbrVES9F48xfm2C6MJXpaxEiWIW5mbftHkV0gP9JW7SbBoLtSdw/gbfURdpMpWsmc663R7k/yhqgMkdaC0n14aaMP4+MqeULEXG6zFsAvbDmyD3jIG7gr5PagHgutLqu2tc5AAUbbabpJ8+v3cH9rnc6CvbLOXjBGSzdM13UKK53KrhHppfi2H6HNlcJnsek0/VOd8F5F5szYwcdwbg2242IS9c7PQVxmApme2KPOGJb1Fivwvak87F2NfZXo8jmL/cqeK8QOuONk/RJeymF8BQjAhcE1AwkCNBanQPiBbzc62w+Krogl8TLi68vwgusAQXEaHSQxgvN1++7bSAR5MzIURuMo/7GLqb+ihfgNDH6lFFvS8N9tzlcTnEG7Lu6ODS5CJd9tymureIi2HdWKnzvEdxzu7ooIe65rXQeK53HSIfaQiXFOsx6+lYDqujqScf7Am9ou1lxVQ6g/lFU5QBJIq7xOmrmb7eiakbclxL9ad7HID/EoZ97VKEYBwYFm0S1MfSDVEcPOpjrdOyAg5jfKp/G9jkQDjdDEbPc9EY/Uef6F+grOywqlInP9D3mOlFGhqCiidv7Dve9T2l7txNZUSoy/BQRJw5K4r3pcN/tbjNbii6lrI9rCIHP67vdg5yrFdfzlPHxtg86vTf18iZAeBH5vt/dd1iccvXhadvdTtcJyp5yvCAq3H3vV9oWO8U2LnI3FVfhkeU9TuX3vd7VIc7wqAlN+SyZsTRuk0Kk67tdMTh6HmXi3ekQGOSZqXRKZlIAzmURF/re7zFZMthhTcJ0eUCX8d455gsl0hJAoMzVU9YzMQ7R6XucX4+aFV3tM0mDCHVimNU2y8mV7b2pa7FrCwZb6CeXQKuM/JDyFP/I/5I8lbFEjUieTFlS+14vmZFlPou3BherDBYktyVIbrPMtruoyS0Z6yNJanAauV9IqgBY3UHQMlV0QwOlS6Cjb5lP9DM19NuqhaPI2KRHHYoeTzo9Hoset0lM21z5SJWPdoPFDO1V4TMb7PUZ2ssnqv1cedW+rO2lpLcXKDTqHdRkJ9STTqjbIlQ1qUSOeJTcpX1pAuBIbv/b/WkC4Deq+/bCNAFQBvPhH6rCfWIbl2fqN7ADJsAOiM1e4Z50PnzZJcpvVYySJlEVhcki9TpXV5JOY505o5ASI13fsnSdiWEasmbZGkJj+rILlmqQlYFPj8WnL53PRMX50zusktJghRk=
*/