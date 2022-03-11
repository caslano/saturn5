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