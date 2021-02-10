/*
  [auto_generated]
  boost/numeric/odeint/external/blaze/blaze_resize.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_RESIZE_HPP_INCLUDED

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

#include <blaze/math/dense/DynamicVector.h>

namespace boost {
namespace numeric {
namespace odeint {

template< typename T , bool TF >
struct is_resizeable< blaze::DynamicVector< T , TF > > 
{ 
    typedef boost::true_type type;
    const static bool value = type::value;
};

template< typename T1 , bool TF1, typename T2 , bool TF2 >
struct same_size_impl< blaze::DynamicVector< T1 , TF1 > , blaze::DynamicVector< T2 , TF2 > >
{
    static bool same_size( const blaze::DynamicVector< T1 , TF1 > &x1 , const blaze::DynamicVector< T2 , TF2 > &x2 )
    {
        return x1.size() == x2.size();
    }
};

template< typename T1 , bool TF1, typename T2 , bool TF2 >
struct resize_impl< blaze::DynamicVector< T1 , TF1 > , blaze::DynamicVector< T2 , TF2 > >
{
    static void resize( blaze::DynamicVector< T1 , TF1 > &x1 , const blaze::DynamicVector< T2 , TF2 > &x2 )
    {
        x1.resize( x2.size() );
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_RESIZE_HPP_INCLUDED

/* blaze_resize.hpp
oR3S4fPd5CmkyQ+1lcLRk33yW4UTmUsqxDoUxn5ZvDzxp9e9tnVelPljiTcuy/yo+9oT//Xku71DJhiVrm753mHbP9mbPSuhlrQ9bfw1dMLpefRP9C9QSwMECgAAAAgALWdKUvBJ+rVHAwAAYgcAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE5MDcuY1VUBQABtkgkYK1UbW/bNhD+rl9xU5FBNrQo7bfFWVHHkTtjgR3YTotsKQRaOlkcKFIgqbxg2X/fkbIjZ92QfqgMi9TpnnvunjsxGX6/K4AhvHpl/p/RRatHXGn1J+b2v72z7Am6H6FuaX2NJIEe8pQN4HXIE0Qeku1Yztw+y14junW5uVvikLeZ25KFYA45Uc2j5tvKQjQZwLuTtz/DT7S8O4nhgkmOAlYW5Qb1Noazwls+VOzh4djg+xjQAhPHu1DrihswqrT3TCPQXvAcpcECmIECTa75hh64BFshlFwgTBZXN7P5xxjuK55XLsijasFUqhUFVOwOQWOO/K6L0TBtQZUEp+AFN5YCtpYreUzcCBZ1bVwMR8+EUcDuGBdsQ0TMQmVtY06TJG+1oOyTQuUmyfflH1e2fq7khpKo2SOoxoJV0BqMwXnGUKuCl24lQcjYtBvB
*/