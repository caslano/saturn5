/*
 [auto_generated]
 boost/numeric/odeint/util/split.hpp

 [begin_description]
 Split abstraction for parallel backends.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_SPLIT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_SPLIT_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

/*
 * No default implementation of the split operation
 */
template< class Container1, class Container2 , class Enabler = void >
struct split_impl
{
    static void split( const Container1 &from , Container2 &to );
};

template< class Container1 , class Container2 >
void split( const Container1 &from , Container2 &to )
{
    split_impl< Container1 , Container2 >::split( from , to );
}


/*
 * No default implementation of the unsplit operation
 */
template< class Container1, class Container2 , class Enabler = void >
struct unsplit_impl
{
    static void unsplit( const Container1 &from , Container2 &to );
};

template< class Container1 , class Container2 >
void unsplit( const Container1 &from , Container2 &to )
{
    unsplit_impl< Container1 , Container2 >::unsplit( from , to );
}


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_COPY_HPP_INCLUDED


/* split.hpp
ptIq28xrF1VNbYG/2ZpdvDEIjsFAszeF4bQJc6KY8uDjMHjnfwjgY28y6Y2Da/AvoDe+NsbeD8fn2HqGziTQdS6pQucS2DLPGI0rnz/uajWeMh5lRUyhqanCVjUbeyJMiWcYghHvpEu6jOm8WFjl1gFcYIAfGY/FCpNbEsazDTimx3OKTb0p55Jgt3jCFrZ2v7hgXSdY5gSmwflwHF4MR4Ox3wB4ijLG6R0xtBtPKcf52AdhDR9E7eTQeQA2mEwehO3kcFzDGozjmGJhnCglEg4+TEZu4x/E9fEuErF5iVS3+g0HZv67DfzJEsfch4tMzEkWMs60Y1TCy5H/tjcKe6ORC0/eWNgg9N+7YIwCJLlEj4mjNM6f9KB5z4oLCb54NJ7xptu1GEk1TjAEg2kQmhx+7/3mT8K3vXPz+NZEY4zAG7uFlKhNZalbBvrEyL8fwB7onvv9CKOMEl7kzv+OzJQ2VFQjG9iCebYi/lUQ4uaBKXf3u2p9fzwe9IPQH4+uPeg8pv7HYPLWnw4qzYYJUd2pDPJFIuTSwty6lU9Qqy4QzvuKWhrEeeZ4ZtHYAy5WsDCEDe+C4ApJJCqW1EwOcoYkK1jhy4ADb8uFbKShnCZJ/y4wVHhjxtNMpx2Rc38wNXlhrNOhP542qkPt
*/