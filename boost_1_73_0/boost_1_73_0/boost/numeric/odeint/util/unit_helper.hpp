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
DN5nvtvze53Q7WGbTW43cNolEHfCDrryOG3nI1sf603YdXqcE3QADOR0QsfpoDAZkJ06ylAsVRIiFu52As9BlQsqXzdwOkEXVzPHCI4ThG63Q9BWMEyv63EchFvr7BzESm9nGFa6m9vrb1ienus6rhv4mCbuo+uEO55YcqhO7mPrxBWrrefgqh2GCcVa81AQbm3gchArI5dhWBk6bm3suK3BszN6WSaVyeTvVm7lYvbd9zWCN7IP2yKg3pChsmz9exrpsN+/SwNf8Rfx/UYWSRf6kgfHv38UrV//8vrNhvr7FGPPSVv9xl+/ydhkgViWOU+yzPlWjXaXbb66W2zuVuSznWPEo6376P7m/kFBuVE5tVLIsNZGhJ3jaLKlaLq9vZ0mHORP3tnNStIwPTh4+Wrfvf2WHWfh4tZRTv4te5Wwn6Zz+ef2b5PNCud4V9m9uiy33+SEWTwqVk76+7+lONL/CIm8yL7L5mvZ18PxOD+lyD/ZruY8s6Vz/pcXonspmzRlXsS4lOcVFJBs9DmQgJhF88Vskvf5zca/FfF6s2g9aSdaT+qbLzwufVze92Fh46touZ62qIMVpDzUkiJMAz3Touuk4hloKQOYJ3f0A4VZ6jvLIZZ7cmLYnp7tnuN2MQAOAzge0PU9OUUg
*/