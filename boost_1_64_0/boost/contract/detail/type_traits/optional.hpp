
#ifndef BOOST_CONTRACT_DETAIL_OPTIONAL_HPP_
#define BOOST_CONTRACT_DETAIL_OPTIONAL_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/optional.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace boost { namespace contract { namespace detail {

template<typename T>
struct is_optional : boost::false_type {};
template<typename T>
struct is_optional<boost::optional<T> > : boost::true_type {};

template<typename T>
struct optional_value_type { typedef T type; };
template<typename T>
struct optional_value_type<boost::optional<T> > { typedef T type; };

template<typename T>
struct remove_value_reference_if_optional { typedef T type; };
template<typename T>
struct remove_value_reference_if_optional<boost::optional<T> >
        { typedef typename boost::remove_reference<T>::type type; };

template<typename T>
T& optional_get(T& x) { return x; }
template<typename T>
T& optional_get(boost::optional<T>& x) { return x.get(); }
template<typename T>
T& optional_get(boost::optional<T&>& x) { return x.get(); }

} } } // namespace

#endif // #include guard


/* optional.hpp
ON5UbtVQE5PhbKf1/FcF/XS9jrglzuu0wc903dpLYWc0Q/YbcPwU9Z3anO1vp9ihZ6oeHrWBHbxUe7XbQa7F1eCnquAcOuAcPfsyvm++JKzX5UzZLD1J9yjBJ7bOqt6D339g/IPFec9CHry7vh39VX8XTplhjP4cbw+h6ZNwi+6+ABPb76KDxoojzAjer5E9B11ylF/K7UwSPqwsdt3n+fkI/VBa92967zsapuqvxlbVmlcOeW5N/bWnK6zZAGsw6Bd6OZ8a6sbz8cY9rO++U2oLR+wvGkr6fbmf0K/Vd8Bfc6l3E9/RWGHrFaWntam19ekQldRH/x4fp9ysXs/A328DjYADM6iRdXoa8vVlcU/4S/4fpWvpzKkfq8O/9Lj8V7cYT5oi5DlpuRRSe03kR1xwzoRWl29DW/JjD/BIA/1btVgRn3xXkm5OzXfQ/GPuwD5xzTYOv/n/DTVoBOsxj5f+TG22fUIc5FN5Y7g4DR+rmRfkc4p/1FBp+E4fVLpo7XD0IposbP9tgPu3oT1azHWtOriURm2ehWa3d+oyoUvbaMWOQc9WPIP3F/I4DR7qXwfvFznC+/bBT62MKSdNTfsOsna5+c36eg5Do0P2C/h//NyajisDC47/hGfl9ytqJkKfTFgrJtvxLI090/ybrIPjuWnfKcYqV36YSifThc8GZ+LrwOFfYBXuGBdjXN7D0ug3ni+Z/JxPC4+hEw49ftbtWTH8L9A2yWnGnGqDt85YVj5VVxMJPNH7+oOzYG6XKBNX6747dGvI838wSKy6wYpEOmnEaLrO9erSse1CuNv1/9Zria+qT/u7GtoU9NpgUU/1jVcP1pDTi+RqNN1aHz+r1eXWJ21ymJlKDXTSF6J50sjtNWqnWgFrNJUGD+P2sDj341vpsDnuvXIw7QrXXjHnKUfkm8+8VZc3sIZNr+g/VbGvBO+f6UpnG/u1aHiaBn4W54kf6qfRH7HGWDv43eAf+NxMtXiPpuepFus5JcjXT61ns0FqcLfc5U0axuvjLpVT38KUPvzVk3qOXe2divU5+N7nR7o2Rozd/6rYJv7D7+oJ+N1z3lFiDAf4ITrwGtwZfgruwsP3J+CO1s439oDLKWm4fDTDTnkWvPdOLLsMCyV57j/h3fjrrlPP3iC91KmsmLQPeRYJtzW23jz9UjH+J54/M+/+n9F619WN3Htaby6X/DtjnTZas3ATuGeNFxnD7sy0bfBeYD2fq3TxqzRG9cY0KY267QR8g2PV++ONnnro1uadG7AvlfHTxYuy0axi3kq/tHaivlqcXDTvV3rR/+/xK/nV+xoeoqYe1GpagK89xo8tKwBr5VI2tTNdT+wQji17lG/xZ8dYPDhL/dN1Y6fpseP7FPziXrXRu0eEX4WjpX1nlmcbxKzSa/TpNtfz3aY0UwMY0OuW3LDOpRRpHlzzySfG3wc/HVFDNEgT+LSQXy5SyWes9w59qejg95EFYzDGknp4o5rL3RY4o7t/j4M9OKmOXFg/FTfpv1XEAwmjPYvYN6RHSkPk1zPOKU8ywnfjr3sXT3TlS8RnRRd1qzdcJJs4vKKuYXXWqvIZJo2/yBPfpi3rqt2Xnbu74Fm6FvoQ9qH2/ccb0p4T7R/lt08fZQ4HjsG6RnRsZdr6A3roOXs8tHoe9/7cfv+6WHwPH2c9sHYw9ug1ObdTvWSWT2kev9fnZ+P+7yo8O0nX3FR3NHZi8OwHHxX8zpHC1qqjvkq+P8T7Hl0Hw9rN8bmnXDsnj3JTTGHnQrzWChcPX4dnxaaQXJ2hpuZ/B2+m8VU7YHMtOqubP9sZwyP5/oHYG2Nv86qaGqcsVXs09aJN5rHB2k23tzfD/J4Jfh8=
*/