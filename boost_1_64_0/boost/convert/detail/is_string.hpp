// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_DETAIL_IS_STRING_HPP
#define BOOST_CONVERT_DETAIL_IS_STRING_HPP

#include <boost/convert/detail/range.hpp>

namespace boost { namespace cnv
{
    namespace detail
    {
        template<typename T, bool is_range_class> struct is_string : std::false_type {};

        template<typename T> struct is_string<T*, false>
        {
            static bool const value = cnv::is_char<T>::value;
        };
        template <typename T, std::size_t N> struct is_string<T [N], false>
        {
            static bool const value = cnv::is_char<T>::value;
        };
        template<typename T> struct is_string<T, /*is_range_class=*/true>
        {
            static bool const value = cnv::is_char<typename T::value_type>::value;
        };
    }
    template<typename T> struct is_string : detail::is_string<
        typename boost::remove_const<T>::type,
        boost::is_class<T>::value && boost::cnv::is_range<T>::value> {};
}}

#endif // BOOST_CONVERT_DETAIL_IS_STRING_HPP

/* is_string.hpp
h7MtWRARouqNhRe9M12eSwZtA1UVa05wS1ld0GLfGPk1LXBDiJ6rGgGM8qGF4jNt0P9X/z1Ofkf0sJDXEkZqnYJw92eFl7xyDpc271Rgb/vzsHE1J8uKH3DD48vic+KIydrMKq7PdKRKJUuXS7VFyU/0535wRZZ5O8LiOvz0tgkhglyC3oPUuH1XBfWkfdv9gaqDpBr6a5x3xirJhChgbK5op1BsW3GMw92gJH3QhY8Z5k+LiEAyPfPvzgU+7jY81FxrFkeWo57K8peqcu6rz6SSk17o6S6gyKxn2paaur1VolSpL9sbTv6EKCuZzjGx5ShFQs0pMibn7N1ojJe7lqLgX38LedwH4vHpi9G4nsqxLPKLzRQiL51jtZZUxysbP1oxhwFn8sHDlQY+y3pBnNxl85KSQQAAwrCrkcxENMAyOZg0zF5rlvneOVmCQ354OzgzZKXxuv6c6S0IUye4XBxhnh5Z966Bz8I7Opfab/taJAPZlXe/TlASEzGlOSxhfeOVts8fql1JO28T/ajWWGVI87UTx95YaRkw4LP8Mpj+2dbbCSbJd4qzAQ==
*/