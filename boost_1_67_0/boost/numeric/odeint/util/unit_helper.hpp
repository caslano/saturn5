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