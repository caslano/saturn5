/*
 [auto_generated]
 boost/numeric/odeint/util/is_resizeable.hpp

 [begin_description]
 Metafunction to determine if a state type can resized. For usage in the steppers.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_IS_RESIZEABLE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_IS_RESIZEABLE_HPP_INCLUDED


#include <vector>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/front.hpp>
#include <boost/fusion/include/is_sequence.hpp>

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace odeint {
   
/*
 * by default any type is not resizable
 */
template< typename Container , typename Enabler = void >
struct is_resizeable_sfinae : boost::false_type {};

template< typename Container >
struct is_resizeable : is_resizeable_sfinae< Container > {};



/*
 * specialization for std::vector
 */
template< class V, class A >
struct is_resizeable< std::vector< V , A  > > : boost::true_type {};


/*
 * sfinae specialization for fusion sequences
 */
template< typename FusionSequence >
struct is_resizeable_sfinae<
    FusionSequence ,
    typename boost::enable_if< typename boost::fusion::traits::is_sequence< FusionSequence >::type >::type >
{
    typedef typename boost::mpl::find_if< FusionSequence , is_resizeable< boost::mpl::_1 > >::type iter;
    typedef typename boost::mpl::end< FusionSequence >::type last;

    typedef typename boost::mpl::if_< boost::is_same< iter , last > , boost::false_type , boost::true_type >::type type;
    const static bool value = type::value;
};






} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_UTIL_IS_RESIZEABLE_HPP_INCLUDED

/* is_resizeable.hpp
5BdoO8E4X09byHfHKN8llOY/bQt5p6h/uA1u0app6N15rW4jR6fLuMvaeufTOXq4IlXeUXd9Lim8s94N/Hn5yr0721X5ZIiTQ1fr86PjlckQKyej19El6sC4ke8ab5fxF/jnlaNGGzRH+1ROtcFYa3Wcpz2El9ixauzl431UxS+6TI3F3tbw+4fa5lPxxPnv3ZqUYYYwzqjf5V56Tu3HURvUnTvFtdF7AWgqkcw0QnRxmZpW
*/