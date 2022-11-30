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


#ifndef BOOST_NUMERIC_ODEINT_UTIL_SAME_SIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_SAME_SIZE_HPP_INCLUDED

#include <boost/numeric/odeint/util/is_resizeable.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_fused.hpp>
#include <boost/fusion/include/all.hpp>

#include <boost/range.hpp>


namespace boost {
namespace numeric {
namespace odeint {
    
template< typename State1 , typename State2 , class Enabler = void >
struct same_size_impl_sfinae
{
    static bool same_size( const State1 &x1 , const State2 &x2 )
    {
        return ( boost::size( x1 ) == boost::size( x2 ) );
    }

};

// same_size function
// standard implementation relies on boost.range
template< class State1 , class State2 >
struct same_size_impl
{
    static bool same_size( const State1 &x1 , const State2 &x2 )
    {
        return same_size_impl_sfinae< State1 , State2 >::same_size( x1 , x2 );
    }
};


// do not overload or specialize this function, specialize resize_impl<> instead
template< class State1 , class State2 >
bool same_size( const State1 &x1 , const State2 &x2 )
{
    return same_size_impl< State1 , State2 >::same_size( x1 , x2 );
}

namespace detail {

struct same_size_fusion
{
    typedef bool result_type;

    template< class S1 , class S2 >
    bool operator()( const S1 &x1 , const S2 &x2 ) const
    {
        return same_size_op( x1 , x2 , typename is_resizeable< S1 >::type() );
    }

    template< class S1 , class S2 >
    bool same_size_op( const S1 &x1 , const S2 &x2 , boost::true_type ) const
    {
        return same_size( x1 , x2 );
    }

    template< class S1 , class S2 >
    bool same_size_op( const S1 &/*x1*/ , const S2 &/*x2*/ , boost::false_type ) const
    {
        return true;
    }
};

} // namespace detail



template< class FusionSeq >
struct same_size_impl_sfinae< FusionSeq , FusionSeq , typename boost::enable_if< typename boost::fusion::traits::is_sequence< FusionSeq >::type >::type >
{
    static bool same_size( const FusionSeq &x1 , const FusionSeq &x2 )
    {
        typedef boost::fusion::vector< const FusionSeq& , const FusionSeq& > Sequences;
        Sequences sequences( x1 , x2 );
        return boost::fusion::all( boost::fusion::zip_view< Sequences >( sequences ) ,
                                   boost::fusion::make_fused( detail::same_size_fusion() ) );
    }
};


}
}
}



#endif // BOOST_NUMERIC_ODEINT_UTIL_SAME_SIZE_HPP_INCLUDED

/* same_size.hpp
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
*/