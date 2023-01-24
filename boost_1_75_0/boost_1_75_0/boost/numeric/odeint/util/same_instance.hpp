/*
 [auto_generated]
 boost/numeric/odeint/util/same_instance.hpp

 [begin_description]
 Basic check if two variables are the same instance
 [end_description]

 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_SAME_INSTANCE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_SAME_INSTANCE_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

template< class T1 , class T2 , class Enabler=void >
struct same_instance_impl
{ 
    static bool same_instance( const T1& /* x1 */ , const T2& /* x2 */ )
    {
        return false;
    }
};

template< class T >
struct same_instance_impl< T , T >
{ 
    static bool same_instance( const T &x1 , const T &x2 )
    {
        // check pointers
        return (&x1 == &x2);
    }
};


template< class T1 , class T2 >
bool same_instance( const T1 &x1 , const T2 &x2 )
{
    return same_instance_impl< T1 , T2 >::same_instance( x1 , x2 );
}


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif

/* same_instance.hpp
8ozGDv3etmuNe34efyRNMotJLRZckvpilU0kfce4GuDOOOA00XlfWq+Qwe7XXCbtzzovajJEP7rnFY2I1czwCUCjwZXIzWVey0tz6hXaWkk0IAfqyjmsahP+0/FtVUHeW2Fsm57OcUDmtasKV25qHncYennIzahrRHf+gGr6tjdZtejUqyueRloFnJHWmdqMsHNX9V7tTaS+s72Rj1CfHNXZRS0f1w3YTt7xXfpPHD5AAqN5jS+SOUdq2FXpLcYfFuQMrxyx+VJgqIXuD/66/ut9lNOfiuZDvfeV/4rJnlbKS9snh2U6FsGhgZmnv/1DQ1AeAZkNrxDVBN2jQ3XfP1yRP3mwHWDgCuwA7c8n7o+DHHeE3Fs7+oN8kQJM6GJz9vBgGPy2o5dYzXQl6satGCu6wyVC4N19s7itnWAOr6lK4aQZnYiA17GXJWqHvP/1mLLdrNAUt4OtlYDTP10OmTBM356QC/10NKhShXVK2sK+k7HzgtbnPzW3JVEPLpjiXRs1btjE0kmwigkdeKd2AN7zNmtXlP/OUwH5QvCL3ybdLocxvk+qvj8C9VXtMC/dL34RB/YBGQULXsmuOqhUko9Xp39NGdk+UJUWLNwfhB6Xly5iPydZ3d1hY+YQuKgHEh99ERQlPtV52D3+1UAjabKhZtH7uwfyyM6YB9jw4v017X5rFm+q+bpEq3XKaalWq5j6OI6iKnqinBeD
*/