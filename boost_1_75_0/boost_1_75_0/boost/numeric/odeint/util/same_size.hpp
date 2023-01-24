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
EtXHbbiGx/dBgcN8ps4E1PgOqvCb9sGwjgFD42vPkXbdjo/2GEkfEcmBJ6PLl1i/DUMi0+dT1L4hzFN4P8LFB/Jtj2paJa7DICMAexf7p4SbTg2MpRMeQVcDbGUFiiy7n9C/hVPbjkYXvxzxXdoxAh1WmycozhO83O4b3osivtkmI3X6GXKaIdPyAKom538z68WQ1L9fNUnXQzJHakJNFKWRAxNpvuhDh/NMlxlhxXD+dinPMcjsszt+X7/HCGVPL+w9oTlgcCc/04KJJ9e1eRadvenorNeWdUNLLeHLPwMjLwZ2Fx8DTW77zw236YhY4mFjyrbeyKO+KpNhrQfkD+deNb13rfOdMvbYheYL/2g3VoRL3u7IrDNSM+wHLNcZrTxFlOemQ72MdpYFesDGt/2y1i5Hq69lNm58S0xOW87ZyYlk4LS3DSksq79vuNpvqn8eVtZ/rq0Zf2oOdTP3gsrtyQA88s9ENZwqYxi/1eGgVqOICph6RcgHfnWhRaX6GijOz/OAWi+rZtL1qdyD6mHjhtLaibiuou0UW9iooJV2DJFr8i+1wHPmo7TrMZ8ls7ZgTeBPCjP6Llbxo6f6beuwQJ3vKVNODTcIKUmTG+v/LmsnHI/ebMyeR7wH9/zewX77tiCAHCBR9HzdVTAre0iUd4EFdxebam+6G2///pzQxAmd7Xu4HZxw43bO/cmAzyaQXo4i6WfnmMlD
*/