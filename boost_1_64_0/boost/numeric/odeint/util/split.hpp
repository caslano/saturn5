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
TtrG/puUgxWEUJGV9d5o7IPcJ+7XsTERDYz9RSn2ELJxOqsjeE/CS7lxHl+oAUE8Zjo5EdWLomACpdgl3KxKHWAjmCL2EvWI06wu5tYAHuyOaVhMg4LbKHLGGbPaFnWvILjfnls2piy12nwFWuCCZ38A9G6B8RwR0f7vLlNfLj5i1jGt6ewbpEafxrhVO2+KV56pWeUC3rMUS75r/R3YnRCxEvpcq6sX+9K+iYj5yi+GCCu+O8sI47HUPiT3kQGiYS9SAvLJGJkata9uit/nSmF3vNwd8UySaC817p49lwXkA/VbEDlTmg930r41K8lUIeyV7QWNDtE2hF4M3coLGMZLo0LEB1SJN+m+iM72+DJOoQWhF3QFdCPkbmVEcfOO1+/HUhjKYl3Lhzpg1oI1Md+bgn9qyE+3RXrv6OrGa2hBH7/6FKGeloSBDKZKzchGb6FuaGkHH2u3ptA2iSpm3tHgSK4FHTR5TrEqub/yu50HQKJe/aC262cE4Jkd3bJt6glF6/Q/SMJ+GU5IZLRR8Vp119QQ8pDErMVMUL5q8wUDwZpDwOfioZ9fAg==
*/