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
6zc2hhryCsNNEXe0HFBHf6ws0ob1SCLcn1cSirqjrmJ9V8G2wqS+t2h7/GTCV5woSZYWldWVuysqyt2VQ1Vl5U1YLy8qW1kaL/HGN+h51c3LqmqGllfWRJatqQ3VXaj1LgtW67ruCGpFapEclJyouNbn1PxaxFfgK9LKNexBmuSUCxVyLsPwe3yaEYDme8JaXiCkueBuIaR4uNxTGijRqrVlWg2lG67uvBpd3ehFV0evQlfbXBbbyPK/VxE5Zx28HTL/BskpM9xbkJFwHjZ7Zs8YH78B865/C9/+iI1af6T4USGjK/AmkYFH5Xy1X96jNTi2Opv1JHxWJY6iUpniNCqPbUPu6N3IbWu6TB57DppzDTmLcxEyud0qurGb2G7SpRg2eWllk3/APvk6acUkczJj52e36WMYS3IEXsa2/sI9QBg0Ae9cB1PhVrt0Ui6VFmDtOcfNdn2ZY4P6LPRyKw4wGxugNwhuWgx8kflMNOcbBru5D8kHIXMg3baxiFnpksH83IQvLEmSux1XCYWiXzoB1EGhrEtxIITKUEJxSJzW+7IxQ/fyeG/ZkCm/N2XPuvnyMbO6I1ucGrPMYNlSbvGcXXyoPtRG9H2ZQaK8cyPxs6SlbSn77+W2lN+DzJZ7UzS7+VvZ1w/rzTgqLBdDsMfCNo5KaRwt1p/RRak+zfB/93I+bAoyQo+KHKZjacnLLCEO054cwXHhuPgq
*/