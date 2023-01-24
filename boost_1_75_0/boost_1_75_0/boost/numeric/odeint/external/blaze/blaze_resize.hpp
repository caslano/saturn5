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
P4Xi3+tgKW+1hqlUiWc0oaRDvYJ5CgBTBJzm624MVsHT1UBRg0DFsaViyp6wnwHGq8OepwDudYANYrYaMKpBjFYgRj/Ckz1yePI/NfvbPxJWyYhVeUFnWG2P6j3jRN1rLmkrOK+aWaFL2rWG3iNyLgPY+E8u/kPBM4VuxeUC6sylbAz7S0jtWfkwqT3N0SO7tz5BeyHPPsAP9xfHqUC9oZ1BKGgzYlQg/Op9WrJ4CBfFLX2QimpIgdU4ik5cKiVNaEVr/su1omB3zT7/oMnU9EZnylGzur1EV45SMfzo9MqRfdxZKUcZdM1VI6EoFWIial1Ryg0XpArYKSqqwNpS6aInvnDBAKFC3alXlH7lcVKicPwQ1kVCidIZ17sePqnNfGFWcCWKakR31KHiZ/bZT+JnFhkMWQJZNMTIuuLmM3URcZu6h4jbxMwnKyMBVHsfT9JZzJUoKoVCOhVXnthwmlqhVrHh2cRIhw+APzAZw+lcdSFOTV+uYWHLXzweO+ftVKweaYJ1bfpBqFgBfdAeKONKFh+0FQuFkqUP2kK3cI13qmTF7eXfn7UKRozHBiRN+1hf7IUSJrJvINH9Pre6PsbtPuJapLjsjVNcFCkNxgsMdn+FOqmUyH/lvThcd1V0Iq8r1K/LCPH9uryuFfK6EHAEYV3BRTM8aOBXuTDXg4iRYMGxGcQqgCeU4C0XsIPlv+KtQuQOq2iccEd0
*/