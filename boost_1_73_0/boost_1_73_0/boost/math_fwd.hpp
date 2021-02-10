//  Boost math_fwd.hpp header file  ------------------------------------------//

//  (C) Copyright Hubert Holin and Daryle Walker 2001-2002.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/math for documentation.

#ifndef BOOST_MATH_FWD_HPP
#define BOOST_MATH_FWD_HPP

namespace boost
{
namespace math
{


//  From <boost/math/quaternion.hpp>  ----------------------------------------//

template < typename T >
    class quaternion;

// Also has many function templates (including operators)


//  From <boost/math/octonion.hpp>  ------------------------------------------//

template < typename T >
    class octonion;

template < >
    class octonion< float >;
template < >
    class octonion< double >;
template < >
    class octonion< long double >;

}  // namespace math
}  // namespace boost


#endif  // BOOST_MATH_FWD_HPP

/* math_fwd.hpp
UWids5Bk+TPbfGr+MRU3uhkOS0cmAW19wjDqEhj8dHxcIilLEgZlggpkEZ3SNEV3us++ToaRvLfgEJEQH/hTqXTL2aJNPmooK8JpQ11v4UxI2jziyias0LqWzJh8MxDuRSGgEED+A1BLAwQKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAHAAJAGN1cmwtbWFzdGVyL0NNYWtlL1BsYXRmb3Jtcy9VVAUAAbZIJGBQSwMECgAAAAgALWdKUnsSnMqoBAAAJhAAAC4ACQBjdXJsLW1hc3Rlci9DTWFrZS9QbGF0Zm9ybXMvV2luZG93c0NhY2hlLmNtYWtlVVQFAAG2SCRgrVdtT+M4EP7OrxjBl3LqUZYVe3Banc5NXMiRxlHiwhYhWaFxaU5pUiUpLxI//sZJWSiZ0kPatJB0nnnz4/E43vvt1107e7D1UvWfwgvvxsAv8n/1pKKVlXqG5oNGN3jfEqIHrxbPah+2WjxDp7ZQqxjfzbNSW8LcmMTMv54xvFHmESU7e2hn5YunIrmbVdCx9uHL6ekJ/A5Hh0eHXbCjLNEphJXObnVx14XvcS35exY9Ph6U+q8u6Aqi9KB2JGdJCWU+rR6iQgM+p8lEZ6WOISoh1uWkSG7xR5JBNdMwTVINlvDHjnfWhYdZMpmh
*/