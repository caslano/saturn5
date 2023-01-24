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
ZnlPRTMeiN9PamQNYrZI7FwCFORaBIllFICgRwav4ria6GlNWP0hfVM4AW0ezOl3xVJ5bSu54DBuCVac3YRSMxXn6GKjucswR2iUoN2ZFiVNZJnsliDpK6H21Jz7NYqqE7+ma0gZtpAp6dlAvohGBccIaBzQKlTfnIuNl0NyF3CHgn8VTsfiwC2uVEV+Q6SqeEm9GiEL5cDA2dwvisLmDO4HzOTi+IYC0299DY3iztD+YnDCVqY5V6H9/Fam2O1W1eOa50Zv7weej46nmAgFqx24Vk6RP46+nAPwf83JdZt2RiMzcj8zx0yxazX94eJfNGPJRaZwOpQpHGinYoau3Mf3b31gyj6AxDT6yYYoNpUqGZvmAFNia1H9nM5UxkR1gj5hwVv4gYIKEJsCxM+bvJb0/GSo6yPp/sbICNSidzsStbycA+w7z+b9jSESn/DIufANWjq0oY4sWifNhKb6i6a2VrX3FwE772K4ZgkWorL0Tmjk1KBPgeVRZYS7INEPi5CQ0s29QrndaPiHqkgglL6nqX2W2vvHuJ5D5a/MrIn7mmBi5bI1PBCKmoAShHFNhgBHDGexx9pewEt4vymOmg3ktHbmRbf3U/LqBe0llBUgRE3MoJqV8yLlocKFLShYCOtDZiciVbw/7orMIHIaAD1rMwUgEFpP0rpiiw/78R/oukdks6sncliCWGXYoaZW/caRjEEZzLIHKKFp
*/