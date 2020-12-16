/*
 [auto_generated]
 boost/numeric/odeint/algebra/algebra_dispatcher.hpp

 [begin_description]
 Algebra dispatcher to automatically chose suitable algebra.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <boost/numeric/odeint/config.hpp>

#include <complex>
#include <boost/type_traits/is_floating_point.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/array_algebra.hpp>
#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>

#include <boost/array.hpp>


namespace boost {
namespace numeric {
namespace odeint {
    
template< class StateType , class Enabler = void >
struct algebra_dispatcher_sfinae
{
    // range_algebra is the standard algebra
    typedef range_algebra algebra_type;
};

template< class StateType >
struct algebra_dispatcher : algebra_dispatcher_sfinae< StateType > { };

// specialize for array
template< class T , size_t N >
struct algebra_dispatcher< boost::array< T , N > >
{
    typedef array_algebra algebra_type;
};

//specialize for some integral types
template< typename T >
struct algebra_dispatcher_sfinae< T , typename boost::enable_if< typename boost::is_floating_point< T >::type >::type >
{
    typedef vector_space_algebra algebra_type;
};

template< typename T >
struct algebra_dispatcher< std::complex<T> >
{
    typedef vector_space_algebra algebra_type;
};

///* think about that again....
// specialize for ublas vector and matrix types
template< class T , class A >
struct algebra_dispatcher< boost::numeric::ublas::vector< T , A > >
{
    typedef vector_space_algebra algebra_type;
};

template< class T , class L , class A >
struct algebra_dispatcher< boost::numeric::ublas::matrix< T , L , A > >
{
    typedef vector_space_algebra algebra_type;
};
//*/

}
}
}

#ifdef BOOST_NUMERIC_ODEINT_CXX11

// c++11 mode: specialization for std::array if available

#include <array>

namespace boost {
namespace numeric {
namespace odeint {
    
// specialize for std::array
template< class T , size_t N >
struct algebra_dispatcher< std::array< T , N > >
{
    typedef array_algebra algebra_type;
};

} } }

#endif


#endif

/* algebra_dispatcher.hpp
Bv4g7LwD5SqqOHx233u7e98WViIlGOBShIAIS6+BBUIIEODSg7SlBAKk3BQSmrIoLYC6VqQoK0VBRVYMAiKwlNAEufQWdQFRkbZ0BAR/eYl5D3zzjX8kGz7PLXNn5pQ5c2aB4h8g3xQ/ndrn7h67FPzf5n09tgvw+gM9Nlc/1nStPzzC/l8kTvNf7OEN8TH0fcVHQH2j6mNaHyD/RHwy1Rd4nOXLT7B8Uxz9S/FlUm79VH5K/QPsh/CZHuuAf1p9Vv4LxLc6C3tsPvivyZ97rJkSc64f99gF5F939PzA4+d4fmiLv64fo131Gf6h+Bn0j9o/eX7oio+F949eUvyV9I84rW9X/sXzR1Mc+4c4zR/hyz32o4H50/F9uj12B8Un3lB8L6XndMTvorf4+zTFD8l8+nynHb8zeD5Z88Meq1L7i9P71T7S9Wn8i29G8+t/5B/S+pc45reJ11OfPr/m3Q0G36/+ieZP0i/iu4J/WtWfJ3+GH3X84PU7+vPbcH5OM9WL69+VdK/VgSfi9H3Dnl67BPpPV/zpFOQ3Znox/lAX3xd4V/xx+L6W68XvH4nT92+Jo/4WPxfaLw56rQz+QdLvad98r10G1++K797n1r+NZbl9E/Gzqf1H9NraML93Vdxkf2i/2nLcfrH429B/Wsv32j2gv1orYPsNFLZ+GM43LY/stV/A+VjxqF48/6Xh4S0PT8QXQv2K7srcfrYK87J4m9pn1V47n+xX8Y8Nvn/Yq/8O+79W67Us8LI45u975CPxyZRfL07x3XD1XozvVsUxvi0+mexH8ROA19fg/puIj4P5M/4ij++WOOmf8lo8/8XimB8u/hzZL2vz/NsVvx7u3xnda039Pdah31rr9GJ9qdqXeu3YjvRcapDv9u3B9d/ujn126Gee7+aJg/o1Hts3GH8eRv/aTn0WUn6E+OqL1w+X8teU8LLMkvyZ5rg+tc+S/j1Mfk1X/BgYf/HOfTYV5k8b32dXQPsm4g2T/nC0b2OXPtsU2jfcTc8nA+JHDvuw+XKf7UHrl6/02eEU3xan+FZLfB6tj7/aZ6No/Uic2rf8Wp/9mvSvOPmn5df1/Sl+Kr4K7U8Sx/EnjvFrz/0Tz/2ty/cviz8I/a/8Rp/tRvsD3+yz7cTXc/Dq2322gfhoB2+/02c7pj89/++07JDx9X7fgOzQ9//GcZL9n/0svk760+vv2543RP7DPkvp4g8MkX9/CG/1ZWzeGmI9g3y5bw7ycKOMZWH/VkX8gZR7/T/eJGN/lv80f8j3OeD8weuXx2Qsrw94SXqQ/24Ibx6RsWL60+138ZDnr0zK2FnioWv/1OQM1qdriN8L6z+NYzO2PNSPq0zJ2HEU3xXH+O4Ufj6bmrFz4Pla4jR+EnFc/xUfD/NjY3pGDOYvcVy/me65v/hatH40Q+1D9qs4zq8e+Y6Hl2cyr3p47OFND0/EZ1D8YFbGtqX3F59H8rMzNpnOtxZfD3jlhAzuz2qLX0D7u+Zk7LzB/LX/O/89PjFjm9H1xedQfuJJ6l/Uf8RXp+uLb0j++ckZ64D+DU/JKH/eXZ80ER8zIO+on3ZqxrYf4I7zj8QP0Px64hD59/YcnB/jMzJ8fp74pXC+W+esjLUhvzQ5O2Pzs9Ivjvz4+ncyto2eL3bw6MKM/UA/1hvgS/Mbl37/8qUZS0v+bdf5uj/L2KF9+k4OXrsmY1sP6EfxYa5faWUG1ifLQ/hNuw/yRJzWh7vieH7JbzzzhzjWNxLfq1/fNzX8+VPRrRnrgfWB5m2Sp/yqdsZGDOS3OuLPd2YwPm93Z2ySvn9lSPst+MJg+1UfytjfPmNfTV9vkNeSjB1B/pP4Wfo7dNjnjYc=
*/