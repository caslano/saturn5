/*!
@file
Forward declares `boost::hana::is_empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_EMPTY_HPP
#define BOOST_HANA_FWD_IS_EMPTY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether the iterable is empty.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` `xs`, `is_empty` returns whether `xs` contains
    //! no more elements. In other words, it returns whether trying to
    //! extract the tail of `xs` would be an error. In the current version
    //! of the library, `is_empty` must return an `IntegralConstant` holding
    //! a value convertible to `bool`. This is because only compile-time
    //! `Iterable`s are supported right now.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_empty.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_empty = [](auto const& xs) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct is_empty_impl : is_empty_impl<It, when<true>> { };

    struct is_empty_t {
        template <typename Xs>
        constexpr auto operator()(Xs const& xs) const;
    };

    constexpr is_empty_t is_empty{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_EMPTY_HPP

/* is_empty.hpp
WwMtHPTVUzM4qLMP79QAHJSdb+Kg35KMU753Yl8cdDbI+SkmDhpu4aAvDzJl2FcaaGj6IFOA/SXGRAPHEyY6rtvERG68saW2wkQwb3Bfd2qWmucnUQperWE551QLd2RzfQb37Ic7Xj9G4Y4d++EOUjrnsVThXKAOE8ByhdOAOdQnixaOPxTiyCPEUR2KhMOMMo7luvJSjCleJI8lcJOfVAJjQjX+FmiL5PjdJtYYS7FDdm6IwhhgsVbttjI6lzEGQupW0WqpsU+jKlF+Cme4VbsoqptwxjEk4bPu21S4Y/nAvqLQ3NqhoQgt1a9mSnnGwBxPWZhj5YGYIw+iUMIcBsooHXhUKCOPUcZodF0uo4zTGWUUcP0yHNhoqs4z7xvViU5meSiFCVDF9g8jwBzFiPEHK8an+2AORxd6hG36FOLYu28/xJEvg+9b7A3QxUMZdPFqEaGLO/+L0YW6T/fPkKmwJVcJM8XMHQpwgmIdvW16Wd4IIqYmSDYkHXQ7bii2z7Hoq743oSgqdi+91+TnfbvpME/DKHP8RJsP6oL4jHR3e+KNEYnOESPbu1+I7bB3vzDSe31Jzi5/su5FAZIvbPrYO+PabZSmzNHjR651D3aGaZFcivTT9vEKEX/Z9NqmPTqmbLw8PVLGL0gjR9HcvYE918sRI9vw8Xysyx7bbu8mf/iF8cp09wZE6hOYhcDYLgeHF6hwyTVri09M4xV+jjYiSuINvI1sJiuV7s0Ql3fY8YqDJ7Sqx0+hRtPtr4mXs8iCxbfRtwUbu0oskaWNLKq7Ou7qjmvX66RuGfUoEpWo/Y4t/k1NDBDvjkS+I5EV3cya0yZCvSPpbiTt5zntgBbGp1HLup9NvDUip1kg45F88Wj386jYJFSrTSDDnPZYkyZI/5PQqHAqhMrzb61bLlBX6lcH1gf61rtkAtXeT/W+YTobP/EIFwf0BZpcfkrGSmIOxveobz/+x/+oHWzjGmLNM+OcTa/6v625p38bp1yBKk4i/3akAw8nXs2Kj10mhgjv9ybowxzv+9fX7ZpbZZh0JQ+bv4YZ6oxPwAw15kGie3Py44QfLsy0n0SQBV3BNrLTC/rS41I70+Mp9Li54GI7q6Vpg6uDzCLgIvVaiNcvqVcX6DbHEES5OQkmgGu3zY4MLscXO6DHwqFpYSqC8HTSs/YMnNH4tRJZXA06XZVr0Ok5s1AuVQaYL3UqYT6qLLxmzpDjsCEnacFotTEXPdAGDAebOYR3dyXy7v6KeN7YjxYsJlp3yD29hey65BfHEL3+xtuKXo+WVcbbOBnCG6mzhNR/x7p2OQkQVIUU0CAIBTgmdTwyxGshXt39lNlcNp5EktIaE+qAJZA4XX55VEYgkVLqcy9h+IC87DOWTGKdRgoDi7rnM3Ufu3ifRd7zmbx/KrZvuvpk8j4E5H3f/sQ9f3HayiWXczljcZpzyV5haB7S0/GuNA9Inz5wV/FtF8tEar2gl0/vNFDswv6CtM959B/OT0PYVt/7oUWIB1CrXwrKILrK0onzGJzab3+d+DaHwuReXBE/gvE390ubQ50mi+2FJpvDQyHSIYbkwvHWRuF2RIpfeOCGZhLSQfly25uKN7nuIeYKED1KFoycVfqhh+hW8IAclcks7FB7mpUQCWjUKmozshpH7ee2r09ZbUdVZqLt+G+0/YFeq+3HOFTbI28d2PbTtf3b/nJWpu0jP7DavgZgEWWJydWXoQYFRvuDsn6cVV1wq4fYzPlpWs9bFpI/32lyZqy/X0gsJpcEzgz6+7GZjOZmqXY/TUWm2S0uKshnIfgrTXaOvjfZbHQ2MdZoyEJwu2yjKy/tsao9VG2UK2NNaZo27iUvIo8=
*/