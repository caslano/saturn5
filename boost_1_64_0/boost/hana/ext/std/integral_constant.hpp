/*!
@file
Adapts `std::integral_constant` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_INTEGRAL_CONSTANT_HPP
#define BOOST_HANA_EXT_STD_INTEGRAL_CONSTANT_HPP

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/integral_constant.hpp>

#include <type_traits>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace std {
    //! @ingroup group-ext-std
    //! Adapter for `std::integral_constant`s.
    //!
    //! Provided models
    //! ---------------
    //! 1. `Constant` and `IntegralConstant`\n
    //! A `std::integral_constant` is a model of the `IntegralConstant` and
    //! `Constant` concepts, just like `hana::integral_constant`s are. As a
    //! consequence, they are also implicitly a model of the concepts provided
    //! for all models of `Constant`.
    //! @include example/ext/std/integral_constant.cpp
    template <typename T, T v>
    struct integral_constant { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std {
        template <typename T>
        struct integral_constant_tag { using value_type = T; };
    }}

    namespace detail {
        template <typename T, T v>
        constexpr bool
        is_std_integral_constant(std::integral_constant<T, v>*)
        { return true; }

        constexpr bool is_std_integral_constant(...)
        { return false; }


        template <typename T, T v>
        constexpr bool
        is_hana_integral_constant(hana::integral_constant<T, v>*)
        { return true; }

        constexpr bool is_hana_integral_constant(...)
        { return false; }
    }

    template <typename T>
    struct tag_of<T, when<
        detail::is_std_integral_constant((T*)0) &&
        !detail::is_hana_integral_constant((T*)0)
    >> {
        using type = ext::std::integral_constant_tag<
            typename hana::tag_of<typename T::value_type>::type
        >;
    };

    //////////////////////////////////////////////////////////////////////////
    // Constant/IntegralConstant
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct IntegralConstant<ext::std::integral_constant_tag<T>> {
        static constexpr bool value = true;
    };

    template <typename T, typename C>
    struct to_impl<ext::std::integral_constant_tag<T>, C, when<
        hana::IntegralConstant<C>::value
    >> : embedding<is_embedded<typename C::value_type, T>::value> {
        template <typename N>
        static constexpr auto apply(N const&) {
            return std::integral_constant<T, N::value>{};
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
jcocbcq4IsSbY4BTS4F//9MJK+l9tIqKWiJZhN47WgR8Zb8cOYAnwX1cQjj/PN0yxsn5NtZ/DQ6PJ0iGUz3dW1PbAm8JrgCdIZIB0LqqkhnPu7y/lQma6fPVFgPr0cYADfIQFJmtZ22cF9OaGWPQIGTLnF6FhttaH/o27yzbeSEa7z3LZtDECSSbfmamzH1qCdKZHIaortZwXcZU43tbV4p/qVspjHFO1aYqdajRYLrz5+i3rC9z9RvcjPe9I0Qnx/C5vs1V2lVapIP0wb1Xij7AMRx/jd9i63DHgzk/58KVYiuCpqN1MJbPmAJOw9XFV7vTwNGJIpKPrZZOiY/jDfOws9q3dCCoRt/SDTogotcXoKYxB737MSSKkOBXz8rQOb8WVBO367eDDjkZWq/692oYDR3fb7nYyDY9Xer61AccndUSdBTPdXfZT4+5WNxA1E9wq5DTRkAShwBEpmJw0fcNrmS7HvErzeXoyi6sPxRf8PkU22wmfg/ZcUneszDicOgHeELv3+4GDv588B2nPa4cyoDN+QriGPSmn8UbGQCRu/eY+AmrqHW2WLC2wSjhAG9VnkjsPBSNU2oEyR9bd410e3rqwSEaT09lQOMR6H7K3XK2rrEEnThiJJO5YF2sp8Lfhm/X9sk44D+AfaKIVtRsY6ijiv4+zVMXV9sX47OAEa8LaJfefBMO0fkq4JFXHTy7VwSO97UMkRv/aeA1iE7hq28tA37iiVij1RpY87d2BL71OXN+a4d8q71zVeYVbA0dHeRx8e+MyY45WX04zcdWrQBdruwjV/r7gQFNSvrxkTSfPCpV2q7plwrvNimNYuZlxRjd9N5VkqZwgMbucYxXaMKNLWLbMv5OyxOsnkeZZhQmPfik8PeirOD5+0ReIl49leSlGqt4Tj2dZC/Eq6hPzwzWS/tgXI8iID48N/pWusuitYa8DDxklMkVEGmDY8Jy9HxaozkP9oWAt0PmF4JmVY0ynz8c2od94xwyj37xnkw4B0XO9cyVEyLP3xGfJPeEk/v1d70E35WW72qs6XyO6mWUUZ/Y06dvA877Nsqq122/HG1fhrbXqH3Hmnk6O5OMJ787yNPLUT98Y5QpxeKsV5A+gNhAJlxM9NVxnPWTg/h80eLXBvB00UnpAMX4mUb2rtx5QuAQXtPKluISyJ+pWi/l0VSltTSNRMN9mDNfR77TkITbET7O2RfQcD2+fGBkk3dRvH5l9ObMdJ73xt+Y5LONH7x5pbtfg/XRW5PjrjSkqVlyiN4OmvdDJk8BfVNtMllGUCowF66vPs9VCf2ljt/vUH0ecCk+hiZ/KHCXN7iozhXQ2mfKFiqulP6W9wD+Q3wLOlK3pqZvUW+ShXTWjVW/RZXQn1Jb/Xm1rZGMq3ypav2mhIsDXaVsj5OwRwv8aTXFkbHJldAXNwX11AdWmnyTrgExIQn3QeBQk2w7TuZZR3/IlBPPddY+LcKy95GVdDez7xPQN38UdIg0lCSHwZb/+MqqbzrOHKI7lD5ZrR2Q8fd8CnTqEFMuuleF+rAY8XTzndgjpDKf1vqUtAXpk88CF7twXSswh7/BlLVdUyRc/kbqty1PbX9R8BZHvtuXgZMTH1YHfHWl7JOgPtZHX+N2+L5gvuscNOY5SzMKcXmU1DS+d1XrKElXNZ2zuNVLJP86n98vOxD2m78rdk3UH/+84/ejvvp383MeH2jobn3UEn7P4cf03XwPMvDJu46RAwBNnuPyP1np362AfEEq/wW654W/ZR3h2Y4hURjo3gM9eEQ6x7efrQzltyJOGfoWfMbyEFzlilH/b14ZeK9TbL9fAtcGnYM/dafXpnMCZ9XvrK7jJHF0Ln777wk=
*/