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
ymf4kR5YF6WmC41jALxSK29ikSsLEwSvzysAI65nq/A5zRsj8/Kbsh7WizsBlaj+5b9hAX0nO9pUbto99u4AV50yAXM9aFZqacLN9iEdrDvEISArkAuEYu4jyErsz+wb49fgr//ljn79m96D/ObYZ/T6VZG5gUwX+RDKDLYYhqNnzTo5BfVuxyfE2pl4P1eM0qGH8JIo8HZ53ltjeMIKk5fhBmsvQ5O3Z6VI7m7GuZg/q/T08BfF+Oq/UWyXJL+XX2MtE2rXPmAwBHKO95rsfTSpEdcdsR005H8rFR/mXrJAHJN0p41Ef7KyV/CZQ7kNan02O9sQ3Ee3wOyw58ceIJ7LQdyxd/f69/lnrbXvQlV2DvhkMdWiyxcj0x2uqmrVUCB8xpFApSlGivwzWz9Ao3kUkRbT5YtAvoLaBeMsX6yP7GPDwlW4Emomhyyi01wCIjueG4WPqwfzgPRTPGOmhkBQnL/ZJEyQg1ryDnXfUkU4g1iOosfTlEypvfv9CLgYxnqUnOs9tboZeMLy8frHEzq0uu+LZFavuDwYdVn7HZllZIxGr/qSXGUGbQ==
*/