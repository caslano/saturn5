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
oNm57Qgkq92zOdgpzd45k4FQ0+U/K0Idh9/3cgWcSeogW4o+9+CXxAWHaoq9gXgHNxEFM2kdVTXY/o4Sc1miV43go6fa17JVxyqgnFDJGL9keQUBY9QNlBff98UKEztg6h5ktxsfNZy1erJwrDV5B4HLQ+AkA/xYgCXpGVtFv1of8jH0EG5ycCPxuBwbHj7RcR2QYQzVjbXNaYA3h+gSoT+aeBr78SHmtNuF3tX7lvpYtHBfTRXPu2QuumAGOpG2z+xTJOl0s1IXKJXFb7ATuW7YRHMb0YxYX+aGMXa8XcFp04tIeMMyDevTH1BbG6XOwf0C2aLycCHlwaqg6k6Hc71sBT6BgbmibY7BFfyL8YVWLfdRo7t2f1s3TaejOMA61dwIpIjiFK8phzz1juGHNZ9RfZG831Nu4BRzZlYtMB0A9RwygHq4rrQ1HTIoj/9EgtLnNCD1vy7/Uw36mWcrC/l8yVIXEuxxn4CXk2Epx5iHtDG5Ri7cahiAAdci6TCt61joThW1/m8mKL77eRaz/IgztcVrzIVlaDiustf5JiLuAantvRvS4Fo8LA==
*/