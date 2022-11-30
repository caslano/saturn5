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
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
*/