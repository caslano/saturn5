/*
  [auto_generated]
  boost/numeric/odeint/util/unit_helper.hpp

  [begin_description]
  Get and set the value of a unit.
  [end_description]

  Copyright 2012-2013 Karsten Ahnert
  Copyright 2012-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_UTIL_UNIT_HELPER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_UNIT_HELPER_HPP_INCLUDED


#ifndef __CUDACC__
#include <boost/units/quantity.hpp>
#include <boost/units/get_dimension.hpp>
#include <boost/units/get_system.hpp>
#endif



namespace boost {
namespace numeric {
namespace odeint {


namespace detail {

    template<class T , class Enabler = void >
    struct get_unit_value_impl
    {
        static T value(const T &t)
        {
            return t;
        }
        typedef T result_type;
    };
    
#ifndef __CUDACC__
    template<class Unit , class T>
    struct get_unit_value_impl< boost::units::quantity< Unit , T> >
    {
        static T value( const boost::units::quantity< Unit , T> &t )
        {
            return t.value();
        }
        typedef T result_type;
    };
#endif





    template<class T , class V , class Enabler = void >
    struct set_unit_value_impl
    {
        static void set_value(T &t , const V &v)
        {
            t = v;
        }
    };

#ifndef __CUDACC__
    template<class Unit , class T , class V>
    struct set_unit_value_impl<boost::units::quantity<Unit , T> , V>
    {
        static void set_value(boost::units::quantity<Unit , T> &t , const V &v)
        {
            t = boost::units::quantity<Unit , T>::from_value(v);
        }
    };
#endif



} // namespace detail


    template<class T>
    typename detail::get_unit_value_impl<T>::result_type get_unit_value(const T &t)
    {
        return detail::get_unit_value_impl<T>::value(t);
    }


    template<class T , class V>
    void set_unit_value(T &t , const V &v)
    {
        return detail::set_unit_value_impl<T , V>::set_value(t , v);
    }



    template< class T >
    struct unit_value_type
    {
        typedef T type;
    };

#ifndef __CUDACC__
    template< class Unit , class Y >
    struct unit_value_type< boost::units::quantity< Unit , Y > >
    {
        typedef Y type;
    };
#endif










    template< typename Time >
    struct inverse_time
    {
        typedef Time type;
    };

#ifndef __CUDACC__
    template< typename Unit , typename Value >
    struct inverse_time< boost::units::quantity< Unit , Value > >
    {
        typedef boost::units::quantity< Unit , Value > time_type;
        typedef typename boost::units::get_dimension< time_type >::type dimension;
        typedef typename boost::units::get_system< time_type >::type system;
        typedef typename boost::mpl::divides< boost::units::dimensionless_type , dimension >::type inv_dimension;
        typedef boost::units::unit< inv_dimension , system > inv_unit;
        typedef boost::units::quantity< inv_unit , Value > type;
    };
#endif


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_UNIT_HELPER_HPP_INCLUDED

/* unit_helper.hpp
s0a7yw1dmlqZa3W/OLPdBaLdI87a290cn9ZIFrNm77Y1e4Kt2cYZbYs9qu6sWFNbAdgJ6fBZNrcK/6HbMfeZhbEltBfLDWQtmir8E9g8cdvmyY2zVvv/Z6Bjfybk/8/s82S3dByFcL7Jq/8E/G8Z8L+FrfkffPoj6s81EoA1kP7yGbNBCJ+6qw5UEJebXyOhpincX8w8x1cv5kxu02UHVfCpAtnA7FgNiQQjn7/OrJYDT18ah+Z16H0CSwuIMkENeUq1Wu9B3zb/Q9jr0w54hiprvGMw/AFhpiseKzP9WdO8Xh8/M1aKs6JttIa8eA+ek35O8Jy+APwE0sRznLb9dalO24afY7TtP84ZM3AYtrKb2US5SoJSA14Nk5DvwcYZezbz4av0pfC4AynTcxmw9v43fbRbBo/O9PEAfQyij5H0MZk+fkcfy+hjPX1sp4/36OMMfVyhD/QneLSnjx700Z8+iunjEfqYDg+8ypXJfPar46HtMkouM3z2m9gZsg2xbaV5n4s+GQLABEjVn9M+EbrQmhQshjm/DvpdnvS5aX2g3bEjLnAIDyebpVp5PGa22anU7UXKltuyvW/53DJv34DMkc/5vN3/uX3e3pB6UQaS38p+Z+6J3tZxuZpApoSU0WTasNky534mKU121OMl30kMJBtPkgZSr8SZ1J5M7RNU165MBF3Eg9qv4JSU+X80CXpF7YSPQ+b3TdxO
*/