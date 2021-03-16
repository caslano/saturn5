// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_HAS_CONSTRAINTS_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_HAS_CONSTRAINTS_DWA2006429_HPP

namespace boost { namespace concept_checking { 

// Here we implement the "metafunction" that detects whether a
// constraints metafunction exists
typedef char yes;
typedef char (&no)[2];

template <class Model, void (Model::*)()>
struct wrap_constraints {};
    
template <class Model>
inline yes has_constraints_(Model*, wrap_constraints<Model,&Model::constraints>* = 0);
inline no has_constraints_(...);

template <class Model>
struct has_constraints
{
    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof( concept_checking::has_constraints_((Model*)0) ) == 1 );
};

}} // namespace boost::concept_checking

#endif // BOOST_CONCEPT_CHECK_HAS_CONSTRAINTS_DWA2006429_HPP

/* has_constraints.hpp
I6Xa6wV5jN/+FweKZCeOzWCfr9yrRkbajNSu7ir46V0pE0L3hyshhCMycm2+WYa8ho7tYujesq+h+74rjPS+r8LEaaTUvg+VM/jtwKfqsfS+b9bUsooK2salorK0sup8m3Ll8FA+Rx73M7CDWyPtt8qnV/LEXi8Ze0zUQHrdW9FfL0FKL0MWBr/omazIml1WUW4f6t8j2Xlsj3dMHt8BZ2AvZptuwwTYDk9LYhlEj5OZ4D4v+jIZLE1IfQ6egp8=
*/