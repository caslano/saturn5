/*
 [auto_generated]
 boost/numeric/odeint/external/viennacl/viennacl_resize.hpp

 [begin_description]
 Enable resizing for viennacl vector.
 [end_description]

 Copyright 2012 Denis Demidov
 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_RESIZE_HPP_INCLUDED

#include <viennacl/vector.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

namespace boost {
namespace numeric {
namespace odeint {



/*
 * specializations for viennacl::vector< T >
 */
template< typename T >
struct is_resizeable< viennacl::vector< T > > : boost::true_type { };

template< typename T >
struct resize_impl< viennacl::vector< T > , viennacl::vector< T > >
{
    static void resize( viennacl::vector< T > &x1 , const viennacl::vector< T > &x2 )
    {
        x1.resize( x2.size() , false );
    }
};

template< typename T >
struct same_size_impl< viennacl::vector< T > , viennacl::vector< T > >
{
    static bool same_size( const viennacl::vector< T > &x1 , const viennacl::vector< T > &x2 )
    {
        return x1.size() == x2.size();
    }
};



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_RESIZE_HPP_INCLUDED

/* viennacl_resize.hpp
c6WW9aOKkwprKgc/7V+z3MrOELkvTNyL3jAAOcc2c4e3QHyqf5yIOvJRtoKzyXA40YyjatJ7QZcv6g8wqLyp6kvj6endgKOo4cx6+aPW6fbKeBO5rNMTQJ2r77dpe98DYaNZNeKlAcqA7afzA5ZkqASePAq+pMquMWs9FJO2Dqa0mDq+JFzM408OtKtayV9VY7dw6bOqxBMr7y7VwuhAL85g7xX6jxWSfxghJ4ZbmUdnOHKvDjySzJ3MT8BNayLpl2zU2D25iX8tva6Ie79Rs5NV6XHt5tRJ7wZPHfnPOhea13ggY0oiSzz48JxGWtLd73it2ip4BssLUp28DRW2hvSyHINgcOFOxr0Am/FZLC4fVpD8fRtnKTBt/k3rN8kEgU1hTSC/S61D02pSyqUkJ+uGhRlXJYZfKH3DHrRA+dLu9pcRI8tlXv6njLmjROj9mM5dfpSMLoLuLyL/YllysSOwLoLyuOPxzZED2GaS2HuomTvNs0N9zmRc35424JcFoa/dqNWJATen204VUnd9KjS0NbRrKmTJBPMStb29C++nIOn0Qv7emkl65A==
*/