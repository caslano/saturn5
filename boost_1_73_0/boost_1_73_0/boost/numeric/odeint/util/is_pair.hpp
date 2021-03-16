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
q2HDCiRiO9Y4QTzUfq3Zfl9D7Ncu0eD7PFgyA96B6wZtkbvGpNQvKRajNWWsUwpOha+NnbmN1mxouoQ3+Gxo+3gVZgvv+t9sYb181yXpClsYjaqcNL1I+fx78LN456JtnrAPZSVTK4uLYIKw3xAuDpZkZf6bvXece0WV/W8F16W3N/NtR3gDoq23KyyYtpH7bgcv6Df4xqJHYMAHBccge+TBBwf7HoAPiQbp+98jD02BKz+4h9E/+TW0slSa4Eg=
*/