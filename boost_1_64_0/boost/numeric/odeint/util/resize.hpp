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
/rQjKgkyhgJKU3uka6nNIXGowTAeSFfUHBjfh5HUQ6pWG8GZNtcnloioIa6YOpOicQ80E2NDfT2wAYZyaWqAqQKk+a3KKwOXHocBEbvR3Vq2KVcSBkko4vwhVKiXid5LFWEMm3DcHn1BarwnPKx6wsqQSTO/YrpMNtZM3gpy7vFyosjxQwtlA6YDHfggeDDELcJ85SnWwDj9LcwsF+gp+nwnBNbsgTMh4OaAMribIYR4cgxkOc5bvSdL2TTOzkbMezu4jaAkYSiAF50B4AokuHPj4OKA3ASUAUA3JAN6kYwL9iYTEPVAr9LfBjxCWuyOQwp0grSjxYRkIaS3joDELJW4BlbTW+bsfJmzA4UeC9SzdZW511uSMtfcBcjxmE+T4VkcXcKr+4LwGhpSuoQ38ljgjYrBO4sQALEzkA9FEpBfdwFkpAQwxGjKDGvgJNkA/RIBrVGAAOHVo0Jw27uCMOc4IDi7zMPg44Hg6ArCH//8eRAKzP6TCMjTZWHuPhIQfDg+GIQQqfXl1wcZyiGl/KrMcV0hzlwsp8j4eGZ0nfkw8sOGlZkYyky4axZmppDBbOQjcag++a6Zj5cTgDAfLFA+5/vE8rjRvIVdledb78bLg/gc7wpOctVKWdeuIJz1uRDyJYSvxiEM7C4nb79jwtnZGU7X/d3deZ544J3EeYL93QSiY0eirTEbge0TsddyjwLImV6xfFH8LNsF2s/ijXXjLeDw/fzISfkA3HFGId6I/igAJUzHuZWl5eJ6zIBIfaqk7eGw9FxwNH0mljmEwrMIWagyL1XLaFUIIXr+DcXYnk7l5O3VY0YHrcXkougvQW8U5I1iqqMCJyfFxvWqHyImo2mNZp7LxbNVhgIO9MPt8aLdW5XUD0UlCqW3y3Avx8PNTw5n6A/LMcaLxB2yxM2ILE9oQkp6mDvgio70i6FwkyMAHXo+T5T8WtsXB3wqAOMsdHVcbgFR3pep2eOpaXviMVpvZowdMog7HoQck2i2eBLu4TxEJpdET1Gi/KsVPK2iv8XtC2eLZ9DSCLtZDUK9yYRBac7MLwFb+f/z3/50IW+FrpWKIxxBW1ciUZIV3u/2jqhrbYO8G8J5gwNURRL/uhShUvz4j1ZTH3lT6gYTob3rhx3RTVUkYbaRJBiE7hoSJltPB0UQwwonAdXgUs48cKOXHO4h44e220HdD3V4521rSm0wAG6SxMy2OauiC+zipSpA4FhTEJg3Cojo6T1k+NZzvCJyoyGpvlJ63nii9n2rudUtxEdcLgM4zcRGzHs4VEBAOFsUPFG7MxZ4IQMPNwIXzGAI+N8V899K/97KvzIaoY741K1GpjV32E40v9mwm1ygmJjCuVXdiSmcUtWdmEJ6lSmmYH/w42mSHO1sSr0LSWRxa58e6s06cBh5wStzksmcxNJ97ubu0n3w5u7SvQ0+Zrr2y81015jp9qyR6VKYNynpYZ2Szu826SHdJu2BD/ti/mBLEOmwOu+3HJFObqd0Xrupu3QabuounUfhk5RO9ZHplHZK55pu05nabTrj4SN3X7HEejOdB+l0BkuWf38Q7chu5P5fPxbrWss+1f0sIysstKojCp3BqC7OSt0HNuQ/Od9VWiAbU3kVr5ACprlKne5SZznua2iMXu8UV32/s2McUPfw5ih4V3YF74QvAG+Ggte3K3hbvncs8KR6KL9P4mjiswUmk+IEn3gvZlG3FHnFPriYbGV52AP3hoEq09uHbmsvE2VIsPUEMN8o5CjdvGLBbep2Aog2PqrgITdR5OYYVC/E8udYpxTRc5S4KJbmFbf/UGmrb4aUw0zDGcfxVn3fcO62zJyCvFr17VZ3pbVymLwyq3B8Lng=
*/