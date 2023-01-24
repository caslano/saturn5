/*
 [auto_generated]
 boost/numeric/odeint/util/is_pair.hpp

 [begin_description]
 Metafunction to determine if a type is a std::pair<>.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_IS_PAIR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_IS_PAIR_HPP_INCLUDED


#include <boost/mpl/bool.hpp>
#include <utility>


namespace boost {
namespace numeric {
namespace odeint {

template< class T >
struct is_pair : public boost::mpl::false_
{
};

template< class T1 , class T2 >
struct is_pair< std::pair< T1 , T2 > > : public boost::mpl::true_
{
};

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_IS_PAIR_HPP_INCLUDED

/* is_pair.hpp
ydBSij/EPbenZxAwDx4L5U6tyROzm7B2/GFAXnM7QxF5T+SMYrMiJV3tTEfi7PfJmg9jqBgqjY4YognNW/2i12Texgq6E6hCReAkEkGXGUJv5hZZwms9tuCJ9MKVwv1xi9WWjUqxq1HO0TJAC2E6MQIuY4ngTmFUkKJNGsXu76ibo6fADYr8O1VzEvDVIpq1ggoyi2Y1iIf3ycPgMbeI0SH7I6ECxU4AipPBxmmIl5I7oKa81X5g3Xp5J7ZuleWKWupgloPDOP0U5NIS0zW7k5NrBILYSxBHCcszgDzPhjBWR1UJZUn8od1FVN4ZzFIsB4fOMjohHjEh0Qkw/oruSkIqRnAqQR+5vMy0BRDLKygcOqkMzB2apgDmSN342JGx9H4UMKbTK9mVjSSn6qfyQAA3oXMkklYEUbMUfUq3DGU06BNpHcPtg67jucCJIWVHaOhqI42iSKKrgH8Fw7CEGDgdI/kdxQiUGA6ZTZuCQ2/zU6nBf0clkdypDCBuf04TtgSNVYlcxddAAGWzKOTiJoXAmpUpWmeCgnkdKOGvaFvIwVRVTyEdNwfME+aNQoi0zXRbiCWcoawvWet0JYhWEejspnT+QhMKaCqMYbY3FaU2i0CAvIlI3jmvWKHOcA8Zr+EZNqpR8QG5yVlqAvBdSRwhHQAVPm/CEkniFDO+u9GmzxCOuf6nsBNjLmz38kdN11aNTvDimspxTVQT
*/