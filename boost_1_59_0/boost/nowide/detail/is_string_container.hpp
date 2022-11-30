//
//  Copyright (c) 2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_DETAIL_IS_STRING_CONTAINER_HPP_INCLUDED
#define BOOST_NOWIDE_DETAIL_IS_STRING_CONTAINER_HPP_INCLUDED

#include <cstddef>
#include <type_traits>

namespace boost {
namespace nowide {
    namespace detail {
        template<class...>
        struct make_void
        {
            typedef void type;
        };

        template<class... Ts>
        using void_t = typename make_void<Ts...>::type;

        template<typename T>
        struct is_char_type : std::false_type
        {};
        template<>
        struct is_char_type<char> : std::true_type
        {};
        template<>
        struct is_char_type<wchar_t> : std::true_type
        {};
        template<>
        struct is_char_type<char16_t> : std::true_type
        {};
        template<>
        struct is_char_type<char32_t> : std::true_type
        {};
#ifdef __cpp_char8_t
        template<>
        struct is_char_type<char8_t> : std::true_type
        {};
#endif

        template<typename T>
        struct is_c_string : std::false_type
        {};
        template<typename T>
        struct is_c_string<const T*> : is_char_type<T>
        {};

        template<typename T>
        using const_data_result = decltype(std::declval<const T>().data());
        /// Return the size of the char type returned by the data() member function
        template<typename T>
        using get_data_width =
          std::integral_constant<std::size_t, sizeof(typename std::remove_pointer<const_data_result<T>>::type)>;
        template<typename T>
        using size_result = decltype(std::declval<T>().size());
        /// Return true if the data() member function returns a pointer to a type of size 1
        template<typename T>
        using has_narrow_data = std::integral_constant<bool, (get_data_width<T>::value == 1)>;

        /// Return true if T is a string container, e.g. std::basic_string, std::basic_string_view
        /// Requires a static value `npos`, a member function `size()` returning an integral,
        /// and a member function `data()` returning a C string
        template<typename T, bool isNarrow, typename = void>
        struct is_string_container : std::false_type
        {};
        // clang-format off
        template<typename T, bool isNarrow>
        struct is_string_container<T, isNarrow, void_t<decltype(T::npos), size_result<T>, const_data_result<T>>>
            : std::integral_constant<bool,
                                     std::is_integral<decltype(T::npos)>::value
                                       && std::is_integral<size_result<T>>::value
                                       && is_c_string<const_data_result<T>>::value
                                       && isNarrow == has_narrow_data<T>::value>
        {};
        // clang-format on
        template<typename T>
        using requires_narrow_string_container = typename std::enable_if<is_string_container<T, true>::value>::type;
        template<typename T>
        using requires_wide_string_container = typename std::enable_if<is_string_container<T, false>::value>::type;

        template<typename T>
        using requires_narrow_char = typename std::enable_if<sizeof(T) == 1 && is_char_type<T>::value>::type;
        template<typename T>
        using requires_wide_char = typename std::enable_if<(sizeof(T) > 1) && is_char_type<T>::value>::type;

    } // namespace detail
} // namespace nowide
} // namespace boost

#endif

/* is_string_container.hpp
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
*/