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
bZ7dQpv7EYd/tK4ckXxd3eDXfPQiAX90OTqQWqCBZNMcLDm72yhHNl+O4+1bKkdSC/2jIzm/n9NXkaI+aGsdTM/TOOPXEo1RLdDwJ+tfhA+waxe4WWiE26CxwJ7rg5IO3PcRkfHC0TjSAo1OZO0bhCmPK6K6srX+18jTiOVpnG1GI7cFGp2J8i1Ob98nj7YTD/I0ZvI0nEUVytFoyU7sQsKOcrbTAvJovXvGnhsD3HkjcnEzGi3p3QCy8ihXV7WPqasbfDkK/LnvZaJbnx9VV0HBXYn/O62zSwTkvk7cXwc3axoMRprLW1BwING8w+nES1Y0mo8g/jzSqzP3t7aVNAaHdCPSd7n+se8x47mkDdc/FnT5s+N5EFl8gmvLILtHj+cJPI0TLdKwPZ4PDgkm+vdaR6OAp3H/T9MIIRl4Gz708yOeFhpSGzSq23Byhf4pPjNFSo2j8bAFuepO1p5rnVwt45EO3fhv0QDw6DYPJbfwln8YP644WWgE2CjHTr4ci3kaJ5rQsCOLW6irHsTrC8JEFfMQaHjYoHGEp7Gbp+Eg6qgcjbQWaPQkt75sneye52kI2+aym9GwLbshrr1I5Feta487PLIgyJKvmIaQqim8R0gYmfOV5ftRdomzA5fHQZ7GwWblaC7zCO8eEs5oYF05i8ZBW75zEJ/B2aBHzwE01bvBwb3JtatQz204+8lSjuYjupDnpWDrb/G7
*/