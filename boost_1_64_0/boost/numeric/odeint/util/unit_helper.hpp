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
Ab+jFqXhof8MYDYp0U9lBgVes+9mJoc5cKUXO9wo3us94v2uhqatF+TJKsO93bFsO9xDt0P9Q8UTcKH4VAveFkVpEMpqSeSXILbKcaYHaobEsTOEWollu+RytdVL4ckIx7dKpwlir77MNHrrwkFF6dVXmqnXo3csTC46Q7U6aimFB9B6mQUaSkbbkhbE0cr9JPNn+agcpYveyIoc2qLFWBfG4s8nj/IPbbz4RI2yTyRR2kXGd91JH514aI1RSIPWa6OC8keiRuFBYxR+AxftiaKJU2qfpLYXSp1On6TSJKGS59lL+9fGBXpw8n9gBA6+Slraf473WRJFIhoYmsDSZxQfvtkuunGb7dS5dUio3Hhyt1ZaLVQ7KKAozicu7cUMQm16OZSa4jV6uSEKej1W7eZcT63mSyK3XB9mOv78zKxQvoujlDOMIp6MKqK7VafCTT8drRX/v7+D9+KrRfvVGH/vhLb+JTHxs61t/Z+Z2/pfi/Efi0n/Skz8X2L8f4zxPx9Tfygm/uYYvy/G/8MY/9gY/62WmP7F1NcrJv0RU1v/1TH5fxbX1v9cTPqGGP8fYvzhmPoejIlfEuOPi6nvBzHxk2L8d8eUP7xtvBKXGNGPfo88x+4ImzvUn8SyPTlQp0BkksM5Trt/JD/ZKuTKWl5ffJaypas+NS+hSdpXTs2isLkTtxySP8Iuq7Hj8ZJ4mfqM+obvLr1Jz2E6ZR7tfEQ3ulIJ1RGrdrKlIPoBXzYi39AiKYh+JG0IW7wVNsNZx5xNFEA/sROBJAtZWXfqa5eY9sTLU/YnJ6gEILQd565LZPznLIn/JNcESzV2vi+odevLKdZFxUjVmsRZQlUk+2q2UEpfCHiPOPI5GAqCgA6pLpMc0SoGEsRbx80R9QJpSlMU1ni7/Pp+pNCPMURQLdDqXo1wVaBY7Mcflkxe5dXCKyncY3fU5lnUYts1vuWT00bBQw9rjqo2wZdGZI7lQETwl8wokXQ4THpbsK33zHV/sXjjTP20RPXBA2SZXEZYJ0b79H8SvkJk5ySH97f//SKisRVmQzT2jWNmTTS2468ZLb+0th35JXuMaFDkvkPRGHx7na1zJZBg1a2EWWaPcwV+OBvc4VBWccIO1f1VkjrH+oz89tksvYK44mL2xWm+ueyzSd9uSLqDSSUwQGnuGlHGNF57/4x75lIbv8EtBo2nPOB4JJirddQ6QXzX/F59WHvuuMZWqk6tSq1JrMJTPR8SBjg75FTHpYXiOyYkRujnuYq6RRPSSA/WMQnYDxnD3f1A9xN1J7T3HIsTUUtNTlyNrQpd4WrbXR+Z5cip3kYlrrVAZOyWHDqPU6ktQ9aa/X2DtwyjADMF9Avekoz3Z/DMjgNPUp0XvGWqyX8OizHp2s0gjqmoK8r8xJTZg/o5cRlESJW4bpGR3mSS+P+X5k5rvqOfLr/ow5KeGVZXE+EBclcoxSNGwyZIAfW4+AI3loSlw4SfwlpBKDgr3ycWwYNoWvmYowY3C0UUROjpUkvmYZ+YQl6Stun8DT3zYweXOvXhIU7LYUepPRtazQbdZzhfHwe84lJeupxEmggvxAHDCZVirdws4P/yw1MJJQhTjiRG7jLq5Hi91Wo+TV5N7X02NQknFXxHgYe1YEkZ+9BUinOG94dvstPfm2x4IuEUC03sXkjllx214vND5mUDXoBpKDtqkb6829hnlr57ZJxJ+lZrPjP75u1iX/gE+6bKfMfhq5sB9+NrfDan47KnO9XjNvtNWWvUfiN+BF+IYlLQaGLFwlXQFGiiaNVgALdz8bgiukhcEZ3tFGRCkh/mK0DiUDLY/tUrstxXZQU+CTaOCT49hjiYkjV5l3YZmUY=
*/