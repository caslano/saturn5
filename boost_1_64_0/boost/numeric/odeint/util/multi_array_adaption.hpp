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
XIMtQhOYxVHFx4+tQzAqBvaNxSES6BCEMEmHxmNZV0NK1tEOTwqJ+mJElhaXX2K6R55zDRv/h9p64TcRKCeNx8vDWfRWEZRE/qFi7XU0XmhifqGgd7FKyx1iYfBY+bGQSYSf945tEHxe+yq8KfDS57Mu9t8zo33tWMoQUZwudleNxTIHgjKI2t+7Et1AzuVUYQ4xKcRSBarV+1KZGIGy35Nx5nRV3L0rzBw33dq9tORzgwh/ZuMXZM2hqrSzLVD6QuBBNXQYg/lgJSVwB4jCGNzcrJ6vhzs3LLGfwI/SbaCumfaXUj3YQX4um/ADCvCTZBjqamFtu2HedAGL+xcYcUc1O72SplZvtF+9eoUmXrgx1C1vfSgYtgEtZSZz61bdly28Tig56AOUfMhMj582uR60LG9RENKAsaobJNhwd7xWCMkOYM5DRTRYBad8wDtXtbGLovY16yxu0Eh4ZFhxOaJJUl5WT1YZeP0USmKha/6tHiIHh2hmzV/dwBpWlhstd0P90U2kWGoXmhJ2tgxwJZNJSHFK//U7srI0bXW2CXw2iiuB21BROE8BYQ==
*/