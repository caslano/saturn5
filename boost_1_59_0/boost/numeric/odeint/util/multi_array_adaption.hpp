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
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
*/