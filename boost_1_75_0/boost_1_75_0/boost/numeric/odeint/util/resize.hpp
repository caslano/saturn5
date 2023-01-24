/*
 [auto_generated]
 boost/numeric/odeint/util/state_wrapper.hpp

 [begin_description]
 State wrapper for the state type in all stepper. The state wrappers are responsible for construction,
 destruction, copying construction, assignment and resizing.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_RESIZE_HPP_INCLUDED

#include <boost/range.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_fused.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template< class StateOut , class StateIn , class Enabler = void >
struct resize_impl_sfinae
{
    static void resize( StateOut &x1 , const StateIn &x2 )
    {
        x1.resize( boost::size( x2 ) );
    }
};

// resize function
// standard implementation relies on boost.range and resize member function
template< class StateOut , class StateIn >
struct resize_impl
{
    static void resize( StateOut &x1 , const StateIn &x2 )
    {
        resize_impl_sfinae< StateOut , StateIn >::resize( x1 , x2 );
    }
};


// do not overload or specialize this function, specialize resize_impl<> instead
template< class StateOut , class StateIn >
void resize( StateOut &x1 , const StateIn &x2 )
{
    resize_impl< StateOut , StateIn >::resize( x1 , x2 );
}


namespace detail {

    struct resizer
    {
        typedef void result_type;

        template< class StateOut , class StateIn >
        void operator()( StateOut &x1 , const StateIn &x2 ) const
        {
            resize_op( x1 , x2 , typename is_resizeable< StateOut >::type() );
        }

        template< class StateOut , class StateIn >
        void resize_op( StateOut &x1 , const StateIn &x2 , boost::true_type ) const
        {
            resize( x1 , x2 );
        }

        template< class StateOut , class StateIn >
        void resize_op( StateOut &/*x1*/ , const StateIn &/*x2*/ , boost::false_type ) const
        {
        }

    };
} // namespace detail


/*
 * specialization for fusion sequences
 */
template< class FusionSeq >
struct resize_impl_sfinae< FusionSeq , FusionSeq ,
    typename boost::enable_if< typename boost::fusion::traits::is_sequence< FusionSeq >::type >::type >
{
    static void resize( FusionSeq &x1 , const FusionSeq &x2 )
    {
        typedef boost::fusion::vector< FusionSeq& , const FusionSeq& > Sequences;
        Sequences sequences( x1 , x2 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( detail::resizer() ) );
    }
};




}
}
}



#endif // BOOST_NUMERIC_ODEINT_UTIL_RESIZE_HPP_INCLUDED

/* resize.hpp
KtSMFNnfTPJBL90O+s+vNph1xFWq2rkvCJqMEdze/lGlRRorc9NcPouavOoXUFNT1OBMSAzW+wnq/l7W/KZlocZtpFLRELgPzt4apBucjG9M8560S7ae6JCaP6H6RnH9Sc3kr4cJvUQFqcO7v25/m+q8xwN3r1OFnjJ6IRDgfsYv7GOS/ma2/3tttcDD8JfnYMPyD1L+ct55pRTvI0vf6syNPoxN39VZ2HH23OgZaO7LKt7jirc6inH71S77DpzMf6jm0D1w9la/b+Bl9oKUL7l7+e+ury69348YYmRbPnn45XtgLjY4KrHOS2MJWlYNhJ0fSY69g+rSJrBG3kW9mcwfKiu6BXfC/6N4ei/or41ou2NruWni4saG9KW/dP2/j74//RIY+rq1+hWfbLIe0vDKuTZvPX1Xh3OGnWN4GQjitujBYtJZiflVdcWvHoZcUZrt+/kG4m9T6b8tnFy1/Pd7/+fhcB+F+QVt00uzinIz6IjicSNjNz+ZyL05DCcpvQv1lekdL7tqM70rPg8MOdEWFhxDPw1Y+2L/CQR5Wu/qGLxe9ethdhfjorGSppXp1euO+ymBWapHmeHScoXng1FSu4iOgR0/VYJ2la+O/W7x2fv5fu+b0HkxqFLwzPVYd4XsymAzye8QnK/971rUNh+xIByciiYEFRnooYWGrRoG2c+TtQmCqTdUp+Sp7DDmFhB2g3McWWzbbSaS
*/