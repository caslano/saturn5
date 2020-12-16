/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_PMF_HPP
#define BOOST_CLBL_TRTS_DETAIL_PMF_HPP

#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/set_function_qualifiers.hpp>
#include <boost/callable_traits/detail/qualifier_flags.hpp>
#include <boost/callable_traits/detail/default_callable_traits.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

template<qualifier_flags Applied, bool IsTransactionSafe, bool IsNoExcept,
    typename CallingConvention, typename T, typename Return,
    typename... Args>
struct set_member_function_qualifiers_t;

template<qualifier_flags Applied, bool IsTransactionSafe, bool IsNoexcept,
    typename CallingConvention, typename T, typename Return,
    typename... Args>
struct set_varargs_member_function_qualifiers_t;

template<qualifier_flags Flags, bool IsTransactionSafe, bool IsNoexcept,
    typename... Ts>
using set_member_function_qualifiers =
    typename set_member_function_qualifiers_t<Flags, IsTransactionSafe,
        IsNoexcept, Ts...>::type;

template<qualifier_flags Flags, bool IsTransactionSafe, bool IsNoexcept,
    typename... Ts>
using set_varargs_member_function_qualifiers =
    typename set_varargs_member_function_qualifiers_t<Flags,
        IsTransactionSafe, IsNoexcept, Ts...>::type;

template<typename T>
struct pmf : default_callable_traits<T> {};

#define BOOST_CLBL_TRTS_CC_TAG dummy
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC
#include <boost/callable_traits/detail/unguarded/pmf.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC

#define BOOST_CLBL_TRTS_CC_TAG dummy
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC
#include <boost/callable_traits/detail/unguarded/pmf_varargs.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC

#ifdef BOOST_CLBL_TRTS_ENABLE_CDECL
#define BOOST_CLBL_TRTS_CC_TAG cdecl_tag
#define BOOST_CLBL_TRTS_VARARGS_CC __cdecl
#define BOOST_CLBL_TRTS_CC __cdecl
#include <boost/callable_traits/detail/unguarded/pmf.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_CDECL

// Defining this macro enables undocumented features, likely broken.
// Too much work to maintain, but knock yourself out
#ifdef BOOST_CLBL_TRTS_ENABLE_STDCALL
#define BOOST_CLBL_TRTS_CC_TAG stdcall_tag
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC __stdcall
#include <boost/callable_traits/detail/unguarded/pmf.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_STDCALL

// Defining this macro enables undocumented features, likely broken.
// Too much work to officially maintain, but knock yourself out
#ifdef BOOST_CLBL_TRTS_ENABLE_FASTCALL
#define BOOST_CLBL_TRTS_CC_TAG fastcall_tag
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC __fastcall
#include <boost/callable_traits/detail/unguarded/pmf.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_FASTCALL

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_PMF_HPP

/* pmf.hpp
kETx845FpGAwF7fm2z/ZOw/4Koo0gO97LwkhgJAACQkQElrohAQQqaF3DL1YUkioIYQASpOuYI8nInoWzoooioqKihIVFTsqeniW4xTUOxuiZ7/z/u/Lt5N9L/sg0au/y+M3/PPNfDM7O3V3dopLuTR1Joww5B1MPazDbGvCvZWn27yioHYtQdJDdfDZnPwegMmympj9M94Xt6nYNqElSnPO0RD/I138T6F9jxU3d/9alk07FzVY52eKzCxnkRvzPBYdvM+HeU9sKToNiAOyuc4UalZTrt6YeDQI3uvDlN0U8RuNX+TgOGI72Io+6XtJiOd3lXMD5oHOaqjrZslwr/J8//vnYJM38wsXLmJwJj9r4bmy/w1pIXHHHbe82Ytmzy80bdzF4i/SZ95N9X6C68JI45Yo8njky0SO8Kmuc66N6rb0xZS3Rf63oIV22s02Ols93UX2WPWGIjOrIYY070H6TcOswNyAKcW8jwnzNLFaY4ZhosrzxJS/KyRMn6+zFU6+bfce9/qscRr/URJ+G08NcrYRvtvCnnAkPBPOgyvh5XArvBc+CV+HR+BfYYQnyorz+HQfGfoICbOx5eNfJy2neWIXj2YjqwNmDKYI8xvMLsybmO8wEoa57x7IjZ1l2rSpz8s9DfHEiKz6tKm1rOaVKFu1Ad/fh+EHxjDHcVHZ3y1HjUnvZqnduHK7NNsu1dilnWbbnVJu1922+3SosUu37Z4vt0u17bYZuy6n2nYXlNt1te0GlNuZuOSV23XByry3t5B231mueW8P6h+SjJwr/tqY/sKUyYD2b32cJb/Xdb7VfswLtH8lw00dY7vSgP7CzBu8Q3R28dZu5lqpv/gKc9JGqptzn9LbRN5jdeT/KNNf9jd9/NvivrFCOZmL2yFxu1jctjeRIiBu43B7T9zOd7RjOQF7HX09XPttbauPidzFCsPO4Sdgn6MfRacFfpCNn4WUyxZOP+nO9vJn0WmGH2SHn7rYybMi7VtGnL5f1m1lOd4vHc+6km2mfjwgYdQ154jsE/lG61TiUZXnTGeZ6RHY/pqysbqRJb8F+jw5F3OQtN46wi4beYuL3J/5VSfGzKW7T+Szrdr8n4lxzG02+3K9gg4uxCHclLG3xC6N/iVC0mwjadO1kT4ThDWTe7bX08Q3kHEB5r5XbT1NB5fngk3xZYpLpF5AfZ5KHan3Lk9S7vViuOicbQ3hPjQ91F+8eZa6XWSPvIes5356xOvzUtMTPy99jW7XePt5KcU8L8VqOBNsN1/92t4I556sv/xZKc0eA0wQPWzKx8+PUB4O2GkiI+YzCnJmLqxQ/0kD1YtwfWZXtyqO/+We8Jn4oMZXGmV9H5qKv8MB8S3KKc6ZR7sYUOdmzZ4+S98ZbP3Uk/Y/OuaqcZEwAtJvSuMyZSlaOg/+gqY8445yxEcGUF3rlOrFnzQewc9YzjTp0aRM8TSMyJqHGSYOjOHyEiaD+u51W3V9pp0bKHJ3t3xFN/S72ARxi6zy/Zwoz0v1/mpqAJGYnvgrcd5fYf7MnEWzz8l3vz/VrVnleAXUlaZlinHqIVbjsdUZj/l5eSHSWPXiflUcDmscEtVDU41DaUAcCvPd46B6+JaxUDzfhTkifZVVpfdXt7htSwyqm/o94ZiJ2wm/Jahequu3BHWTeB8hzLxEjXeTXxbv0N8Y0GnmXt5SRzvuY1l+8Xz3+0DvpGVtxMnS8mBz9+8cGSYOBfn6pcPtO4fqNTffOXJFnirfOS4O/Z1D/XU142IvIzu/c+wRmX03sZtCysxzfOd4StyO8fwUxpVrcp1JIb9zZIluksiZJr7N9DnSvs7frdTA7xwmXmPGyLoA0z+fKfozrdE=
*/