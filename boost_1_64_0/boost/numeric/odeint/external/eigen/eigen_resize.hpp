/*
  [auto_generated]
  boost/numeric/odeint/external/eigen/eigen_resize.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2013 Ankur Sinha
  Copyright 2013 Karsten Ahnert

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_RESIZE_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_RESIZE_HPP_DEFINED


#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <Eigen/Dense>

namespace boost {
namespace numeric {
namespace odeint {



template< class Derived >
struct is_resizeable_sfinae< Derived ,
                      typename boost::enable_if< typename boost::is_base_of< Eigen::MatrixBase< Derived > , Derived >::type >::type >
{ 
    typedef boost::true_type type;
    const static bool value = type::value;
};


template < class Derived  >
struct is_resizeable_sfinae< Derived ,
                      typename boost::enable_if< typename boost::is_base_of< Eigen::ArrayBase< Derived > , Derived >::type >::type >
{ 
    typedef boost::true_type type;
    const static bool value = type::value;
};



template< class Derived >
struct same_size_impl_sfinae< Derived , Derived ,
                       typename boost::enable_if< typename boost::is_base_of< Eigen::MatrixBase< Derived > , Derived >::type >::type >
{
    static bool same_size( const Eigen::MatrixBase< Derived > &m1 , const Eigen::MatrixBase< Derived > &m2 )

    {
        return ( ( m1.innerSize () == m2.innerSize () ) && ( m1.outerSize() == m2.outerSize() ) );
    }
};

template< class Derived  >
struct same_size_impl_sfinae< Derived , Derived ,
                       typename boost::enable_if< typename boost::is_base_of< Eigen::ArrayBase< Derived > , Derived >::type >::type >
{
    static bool same_size( const Eigen::ArrayBase< Derived > &v1 , const Eigen::ArrayBase< Derived >  &v2 )
    {
        return  ( ( v1.innerSize () == v2.innerSize () ) && ( v1.outerSize() == v2.outerSize() ) );
    }
};




template< class Derived >
struct resize_impl_sfinae< Derived , Derived ,
                    typename boost::enable_if< typename boost::is_base_of< Eigen::MatrixBase< Derived > , Derived >::type >::type >
{
    static void resize( Eigen::MatrixBase< Derived > &m1 , const Eigen::MatrixBase< Derived > &m2 )
    {
        m1.derived().resizeLike(m2);
    }
};

template< class Derived >
struct resize_impl_sfinae< Derived , Derived ,
                    typename boost::enable_if< typename boost::is_base_of< Eigen::ArrayBase< Derived > , Derived >::type >::type >
{
    static void resize( Eigen::ArrayBase< Derived > &v1 , const Eigen::ArrayBase< Derived > &v2 )
    {
        v1.derived().resizeLike(v2);
    }
};



} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_RESIZE_HPP_DEFINED

/* eigen_resize.hpp
Czbc/2C4e7DWEXrYnJUNYmQ4PxJm36q9DorUgwyYK67f4dRDHcg1krDDJB073yUtGBF7mJYdN0iFlCcnpUyrkxYnWQ7m78/quhJ7KpnAKcqEwPn+3npglMk71PFkwxIuDzqEGKMUz253A5KAeQ3CWXvHLtYt4NWyMWrAyf+5radCoceJQ9q5UsJJ1eFEZinslJS0VxwgkxQlK8hEajmwRIp6q6d6pfeJlgroHJVVtyZvIv04FNcueUoKv0RQdtGBcUcJyDpTC3HBnYL05+2lPre+XIjvThJiym3zababVoi17lLHy9WFmG7VDNvqoOz4zWWFeH5fIX5oCbHR/EK8dFeGPXCxEFcsLsRS8wlx1ZJCXLKDENctm+H3XJAd/74cXjjP2UcJcepN2e9HbaU+nzhbiD0ddfzubEJ8uLMQJ64uxAwbCrE8OHcsIMQ2JYX/MpMQfxwgxOld9f2ri7Pz7TFldnzs3EKU0RYLXirEl+eiHdaatA2ac2bH31vqc9trhThsoez3TWcU4sjz1LG/pvrc9WAh2qE6/mzpfNs+Nu/oa/PznkK4G6IOZwlx8jZCzLWBEN/eKMQ3Zwjx1vSTpt39pOz4j+vU54rLC7FXG3W+BG3pC/EQzlFZF+e6JEu7iqs+X14cZV5PiGcm0naaO02wQ5b23YFrvfSs2fFx16rPj+bCdd1YHU8ZZfha+6Syg7L/mf52zN0ZfgXaajW093QNIW5H+z2KdJ9vies8z0BbnCbEB/Oj3htBxjbPfl9yoP1eviE7/gHcU/9i78rD5CqKeOcgCbCGvTdCDEsIMYSQhCWEgBCyV5JNNrvLHjm4JrMzs9khuzPDHLlAziD3YZQbOQW55JBDREUF7wsQQfHGA8EDiCii4PF73fVe1es3Mzsb/PzDz/A9dl51dXV1dXV1dXd1v1al9oEsdtxlYNEHlTqoQan1A6S7qOMjFyv1h4eCsv/rXKXenMfvd6Psx64DH5DPxAf9uBetVWrRGqXu6PPDj19r/o49imFfPJN0KJ6/zbs/kh8+DW23x4nQ9SVKLQcPD7b502+pVOqVW/j9yQb0B7THvbehze9V6tEepX57fX7aK/v5950PQM57FtbJmn7/+7XrRR+26N+21f/+E9iNjquhW5uV+i7yPf0ByBT0noAs9t6iVB/qNCDsVm19cds1dmYQ9prg7xrYkI8OCF3xZGa105ngYR7yJpW6Ma3U5P1gR+JBvOch48uA9zngrT0DPK/wp0+agzIS5vdu0Ifbz1bq5omwTfXQn1MA26bUXtDRzy6C3k0weB+cxvnPEPydsx1tlkI/+TjZJ7KPv7hNFf33xSro/DV+WOJsVdK/c2An2w4snP7XTqXqYE9/9lHwVgdZRGBj9i+gxzcLuuBn81T08wvM+3k3CTuS5d/zNyp1Kmx3JfTm/E0M/wzs1XbYvNZKpB+u1NcPBi+wM4vCSs2g8eFR6NSNUdgRZww438/LPlc7/0f67WTzoDe3NsO03QLd38J4N6F/feMy2MBMcTkdMWj+3tcL2zeOaE7n9OfAfwPs8yCNpTvPhC5Pgxxgv1MzlNqA8ufCviyAXfhRH+z7EGxdAmMaxqirPqjUM+Bj3Q6l3nc96plRI/67d5b5exLqvX+K4bfPMH8vtezbd3fzv/8GMv02+QF7k2297jTYAfSdMTHICLp38d7Febj+PIwxDaADfd33ZrTVZKUeWol+dX7xfP88WqkpN1CZkNddyBebHsQbgJ4tzMD2wz703gSeoINR8PZGvvFzImhOgG6eCnuzAja/GrIph6zbTXLZAWLMPlyN+O/PWUu3NwsbpI2iUj3Xgn/4IkuugO9yHp4jUP/teeR0jPk=
*/