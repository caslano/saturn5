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
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
*/