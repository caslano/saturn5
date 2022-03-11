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