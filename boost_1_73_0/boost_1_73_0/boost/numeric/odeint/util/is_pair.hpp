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
T9Fh61LAysbGiR0vydZhGxJuCbhAvpRvvaUapJHRRWh0mpHBt8l3v+6ZEQ+/wLlcpepIMJrR9K97+jU9Xa99v08JarDx4+mvhx/81RTnmfgn99XDqz3vC5h/SHWFv5uY1GFJ8sWrwmaSL1DRJJ7l8paePW8ToyuSjf7UifLKo0ecQTKiPBXpbRZdTxRUTquwf3z8BnagsdfYc+CMJRGPYaR4MubZtQNvAz3z1wmbz3cl/9UBroDFuxbKnUQSpAjVjGUc8DmOfJ5IHgCTEHDpZ9EYB1ECasIhjGIOp4Pzy27/vQOzSeRPCORW5CAnIo8DmLAbDhn3eXRjMFKWKRAhkiN4EEmFgLmKRLKLvDkonk0lYRB7FksB7IZFMRsjI6ZgolQqf6nX/TyLUfp6IHxZ94vt707UdLGTSxRiym5BpAqUgFxyB2ilA1MRRCH9okJwMs3HcSQnzlIaZJUEdZGB5HFMWEgXcWnE5jCy6nFoGaQocaToR4pEEqvZREzXFqIeCSXMswQZoR5wUSBQzQ7kScAzvVjvvGBhdaoV/KhplvIGIBIUBsqtEXRHZRgzGUkHPnXdD4MLFz61hsNW372EQQda/UsC+63bP0PTR8gsAz5PMy6ReQbRNI0jHlie3+9TL/0UJX6cBxzKiks0
*/