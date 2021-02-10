/*
  [auto_generated]
  boost/numeric/odeint/util/multi_array_adaption.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_UTIL_MULTI_ARRAY_ADAPTION_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_UTIL_MULTI_ARRAY_ADAPTION_HPP_DEFINED



#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/multi_array.hpp>


namespace boost {
namespace numeric {
namespace odeint {
    
template< typename T >
struct is_multi_array
{
    typedef boost::false_type type;
    const static bool value = type::value;
};
    
template< typename T >
struct is_resizeable_multi_array
{
    typedef boost::false_type type;
    const static bool value = type::value;
};



template< typename V , size_t Dim , typename A >
struct is_multi_array< boost::multi_array< V , Dim , A > >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};

template< typename V , size_t Dim , typename A >
struct is_resizeable_multi_array< boost::multi_array< V , Dim , A > >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};




template< typename T  >
struct is_resizeable_sfinae< T , typename boost::enable_if< typename is_resizeable_multi_array< T >::type >::type >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};





template< typename T1 , typename T2  >
struct same_size_impl_sfinae< T1 , T2 ,
                       typename boost::enable_if<
                           typename boost::mpl::and_< 
                               is_multi_array< T1 > ,
                               is_multi_array< T2 > ,
                               boost::mpl::bool_< T1::dimensionality == T2::dimensionality >
                           >::type
                       >::type >
{
    static bool same_size( T1 const &x1 , T2 const &x2 )
    {
        for( size_t i=0 ; i<T1::dimensionality ; ++i )
        {
            if( x1.shape()[i] != x2.shape()[i] ) return false;
            if( x1.index_bases()[i] != x2.index_bases()[i] ) return false;
        }
        return true;
    }
};


template< typename T1 , typename T2 >
struct resize_impl_sfinae< T1 , T2 ,
                    typename boost::enable_if<
                        typename boost::mpl::and_<
                            is_resizeable_multi_array< T1 > ,
                            is_multi_array< T2 > ,
                            boost::mpl::bool_< T1::dimensionality == T2::dimensionality >
                        >::type
                    >::type >
{
    static void resize( T1 &x1 , const T2 &x2 )
    {
        boost::array< int , T1::dimensionality > extents;
        for( size_t i=0 ; i<T1::dimensionality ; ++i ) extents[i] = x2.shape()[i];
        x1.resize( extents );
        boost::array< int , T1::dimensionality > origins;
        for( size_t i=0 ; i<T1::dimensionality ; ++i ) origins[i] = x2.index_bases()[i];
        x1.reindex( origins );
    }
};
                            


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_MULTI_ARRAY_ADAPTION_HPP_DEFINED

/* multi_array_adaption.hpp
RG/GeuzXhePhNlFfPrfOhsZ2YCxEDCIOpLqNOfkUaC+AGh0jTTvyRUBiS7QEDdve4LfiVWcw/KhfU5rI/OaKoxCCR6eSjq0aLdBP76B/0es1H10YM6mM2e+sW/oX2ejRFw0tBD3tWgdAKFJSs5gujIvziBDzpEKvq5oOFdvB+F87xvM0FizAZ47HtrYSOuxCadZVjQIQUm+HRiwIKi+LbTulx0uYl3bLT60plO3R+ddvfWw7UMZkHpCA5a0IRy6G9kcHXpIOtmTVd9t9d9Rr99+7HxyoxCK5rq6pcCucThcRjMikikg1dv3tZG73z6pNHRUAlIesrsn7+Qy0/ovo+4H6x2oME0iCQXbzv7YFKhLtoLcowtBT/501tPAJm3JoPNceJgiM0k1GTzNMMGGlvKb//Spa5C8BHqEoNr6vWooi1vpihok4MOcuCaKzma5NWCJ0Cablo3Jyyj5jcYeHoVAQC/EZC/DP3EjN1gIV6z70DYrinM4GDV6ctOQuNg80HskPje+QIL7ZGzf74kOeWOyOxHzCkg/7X2MrXo+lgsYW3nfHf7b0ncYG37lrBu0oP84GhQio/w0l+cOfLQr1J0J02xp+i/0Utn4qI+jKe2+9jNf3APw9oEqc4/iAVGEr7ufwXT8mbB2zEeJZ
*/