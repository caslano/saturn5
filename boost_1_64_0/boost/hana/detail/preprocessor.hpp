/*!
@file
Defines generally useful preprocessor macros.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_PREPROCESSOR_HPP
#define BOOST_HANA_DETAIL_PREPROCESSOR_HPP

//! @ingroup group-details
//! Expands to the concatenation of its two arguments.
#define BOOST_HANA_PP_CONCAT(x, y) BOOST_HANA_PP_CONCAT_PRIMITIVE(x, y)
#define BOOST_HANA_PP_CONCAT_PRIMITIVE(x, y) x ## y

//! @ingroup group-details
//! Expands to the stringized version of its argument.
#define BOOST_HANA_PP_STRINGIZE(...) BOOST_HANA_PP_STRINGIZE_PRIMITIVE(__VA_ARGS__)
#define BOOST_HANA_PP_STRINGIZE_PRIMITIVE(...) #__VA_ARGS__

//! @ingroup group-details
//! Expands to its first argument.
#ifdef BOOST_HANA_WORKAROUND_MSVC_PREPROCESSOR_616033
#define BOOST_HANA_PP_FRONT(...) BOOST_HANA_PP_FRONT_IMPL_I(__VA_ARGS__)
#define BOOST_HANA_PP_FRONT_IMPL_I(...) BOOST_HANA_PP_CONCAT(BOOST_HANA_PP_FRONT_IMPL(__VA_ARGS__, ),)
#else
#define BOOST_HANA_PP_FRONT(...) BOOST_HANA_PP_FRONT_IMPL(__VA_ARGS__, )
#endif
#define BOOST_HANA_PP_FRONT_IMPL(e0, ...) e0

//! @ingroup group-details
//! Expands to all of its arguments, except for the first one.
//!
//! This macro may not be called with less than 2 arguments.
#define BOOST_HANA_PP_DROP_FRONT(e0, ...) __VA_ARGS__

#endif // !BOOST_HANA_DETAIL_PREPROCESSOR_HPP

/* preprocessor.hpp
9sZXi73xNRF8xN7419T2vzF2v+QeSp0BO8POiM175t/62l8HU1ua6mjQEaBYGnVo3uDvVvnNfyCm2Pu0Eayj3XNlOwdxO5Za0oMFqb8vptzHwF4/TOmFqRrnVPeb/HP6ou68otCy21TRtehgvstUFF9L2yqEG88M2OWRTcl3LuoO1aohYIbsXbF6Wvfd4lv3lbaXW/ripS11zHdE50Bd9Li/jfMrsq4mO2b75h2ib94ZwUf0zbuob96taYvorvjceo+weycR/3vJ7t1H/O8XdMD7fCYPEt1DEd97Q9ABq3zq5X7/+CNE/ygbo/ewMfq4qPsTxIfX/Uni8VQAbU748J8h2mcD5NssQL7nif4For+xyJh/IKLveKd1X9fvEcnng5eNNo13Zep6XXad49HUGhiL4/AY4NNxptLVm+rOZDXsacBmqXPJnE4/h/RcJ5NXEaO704OOgc1zCtlUxtvfvwjYApcX4qqRn/gl7ice4Roy2H5APJEVEF/O+kD7DlxXYc5umV3r3Uxe0i2rxO9j0E/M8EupAXBwmVnCpyt8udZ3ehzre2+wMfim6Ft/jKiPiNFJfeUtoj1E7I9dz0t7Np+h2Bd8/9MwVChkB7SptHNIwP6e7/1d74gOswt96feJ7/B5ZSP9YvU+m+hO7OzNLnyNPZ7vsUKlV3tr+Hd95QKXNxqm78XPGPJ9bItk/YRF5zxQZAfTfOssoCXeXY78PMS9r8DWhX8R7f8B0ovJDo0N6/b/kNr/75ENxgwfTK/iNRAw80ZM2Np/UH9bTTb5Eyrvn4LuQrHf+TfRORO9+rwh8owGTuU5nniPmajzlFGevUr+Rimvi4ChLtOKnW/ag02zPind5gHtbXV1NBur4yf622qTifrDx+qmVL8JE9mbTToXLjj6M6bc/859c9AafR0ldBwifpWibMwT+PjLriJZhtgZsOE71Rd/AXIR30nEdxvQKZTKW8fOvVeVy/Pvcmcy5d1SyLRDWH+4TFsR7daGFjjw98Ue2FbjSFbBA/ApxKPO8gBOxInczuMRqgyxmIiS90Q/7+la96HD2Xu7GSLPTiLPzkjbOk/09LN7pa7zTIZHXuCZ7oGfNdGe72Mt4W/LHMVLqDc8DA2PNQQeuzEewNkPX2PMIb3N1GOS+AffYUA3fE/yAx+fTHuTHkaFbH8zOgItx+GOCZMPMNv/uXzzAuowVdA0UB0amY3Z098+4OFvn2bePkD+LeLX/wLiGSc+PG9/SOMWMhzWcHY8cXlzst6QtxX5zJi3NJIOym4HXRGfeNG3AAkx3pLUt3ibdJi6s7sjtg7ALxZ9eY+waWPTbnQ2KXQ8ROWgTJfuq0R3INNTzo5J0jdbuxs+T4h1/cEBY6FO9IFuVqcC6ZW3Zy/jMVXjxZjDuc9EJhOr5wphp00/PJM+3E4fIuQwZUTJ1vUxOeoIXyfkGKBys1TulqAfC4zC/yzCP7zssc4qyjco2uVXYr4oEN0Qs4dXsrXnGtGH1k4UZaEe64jHoaKsnL3XRD55qw/Tzzke77DE+C4EjJcjA2jkXaejSJ6jjey2H6LtCfctIWtS9PNjie44PuZFX/iOxll5HghreUYJu3rCRG07a5ntVHp+hen5ZFbO+ol2XFj5APPZy+8JezkmwF6eJmhOw0fSnMHszyjCh9maI0x9+UxhJ+x4oT7wg2L2qcgaXNX5bNG3foR0rtzft87x5INMRcYr5DuP1XUV8IMBdb1gojOiu+X41RXc0jARlorgqA4/ZuMG3217/kT0r4tF//op0ydwVtZzaA1/CcNfhO/nVfn1fRn1wcNFrJvLAc+G/LS/YPPuIOHAU89RJNe+IfsWyerx74A9EqDHq4w=
*/