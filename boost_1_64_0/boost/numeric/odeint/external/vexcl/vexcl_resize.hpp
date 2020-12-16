/*
 [auto_generated]
 boost/numeric/odeint/external/vexcl/vexcl_resize.hpp

 [begin_description]
 Enable resizing for vexcl vector and multivector.
 [end_description]

 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky
 Copyright 2012 Denis Demidov

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

namespace boost {
namespace numeric {
namespace odeint {



/*
 * specializations for vex::vector< T >
 */
template< typename T >
struct is_resizeable< vex::vector< T > > : boost::true_type { };

template< typename T >
struct resize_impl< vex::vector< T > , vex::vector< T > >
{
    static void resize( vex::vector< T > &x1 , const vex::vector< T > &x2 )
    {
        x1.resize( x2.queue_list() , x2.size() );
    }
};

template< typename T >
struct same_size_impl< vex::vector< T > , vex::vector< T > >
{
    static bool same_size( const vex::vector< T > &x1 , const vex::vector< T > &x2 )
    {
        return x1.size() == x2.size();
    }
};





/*
 * specializations for vex::multivector< T >
 */
template< typename T , size_t N >
struct is_resizeable< vex::multivector< T , N > > : boost::true_type { };

template< typename T , size_t N >
struct resize_impl< vex::multivector< T , N > , vex::multivector< T , N > >
{
    static void resize( vex::multivector< T , N > &x1 , const vex::multivector< T , N > &x2 )
    {
        x1.resize( x2.queue_list() , x2.size() );
    }
};

template< typename T , size_t N >
struct same_size_impl< vex::multivector< T , N > , vex::multivector< T , N > >
{
    static bool same_size( const vex::multivector< T , N > &x1 , const vex::multivector< T , N > &x2 )
    {
        return x1.size() == x2.size();
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED

/* vexcl_resize.hpp
BPSK8L3fN9U+nx8H2SBPeJ/vLdk3RF5BGSuLyc/sG/49WEejbco6+u2J4bN172j+QP1TZARN9hn3pT+9fyNumt6Ly7bFlmBMl7k2473svOS96HE95jyvSNXa6PznV4fJwy//f81485FQGcJrLK9Ol6PJZ5X14zGizpYlunXYdkHdou5z76LvWqftLJe+W52sl0GHfch3EpSDP11fo7xRdfwmwjRyBz3KZkZ6u9eJfV0Fje9W5v51v9nmHOCH6oIw4p3tLKkQu9pp7GovKRtoYldFtKsi0OcOod+1urV9Tkmdbs88S0ZZxtTxHkld0C6eUO1ib6bLnvtBWMs/TuQHLVf+cuLRXnP2tP24fc09+H2dnvXbhsH9h+Iid3bay5xn3j9kZ270bWlairtWTg0qDA2oMwHQsa1bjL91QZ/3CNuAxkM3Ofga4jF+5X9bbGCZnJ4ngs8IvllZVyfnTHR4nglP53ckhLWsTlf1ddbHHcbROl0etg1Tno8Ye/1YBfttnnG91D+vyJ/gCrwG4e1wxxTjpzHgPVPsA3njZ+p7lrQrvsMtv7T5pjQb2FNC6yXnTNPjmzOQqLMXj9DIuydB2H9mJnuneTTiXD/GcBHe8eoO+VWLp3pmxDJpWCfd8S1Bv4n4YK9hFISfo2ywQuaZ6hy0iVO2eFxF9Fn1g+vY1ojR34fm1sl9QYYVv+CM1qElYX6NdeHvg5+E/ZAeyeONsoCP5tHMfEHn2R3WKdPsNPOCRcbmitnupK/BHQK2oTGmX1pax3JrfyF1tEfDD3QlF/yF1IXlqjLfOg8zfdceRbQ99oX6LK6dM7RImRz25YizRUeEximh+1h3B0DKQTp+2ncn7yUebfKK8n/zKYM5JEKeY8WWgAmX/TjV7ooqBi57q+QFbHTZ26XswOSWfZ2UnfTosneYvKLKvsFgosreJXXNMVjKu3OQuu4V/sBGl3cT+YPGcVrPr/OXL214R5Vvs8FElW+Lqr99B6m/E4QfsNHlOVHV374R9XeSlI/06PKdbPKKKt8pBhNVvm2m/varUPIgPKtSwmzLqj1EnwX4kplrvWj6rS+b9mv7ta+I3IG/2AI59wE5XB5fNXUXJcfZko9bo7w0LqzrcxWPz5dF8zivTu6Ky3vuEn6S/XwTx/QVakznfBh54GfWYudrHXEuredzFxq6nYt/29ArDf1iNe/eOYR596Wmn4uav1yWM/8X28T8nD/zDa4uvH5bw7nvC2rue5WZ+17NNB/huxbXcAy71PhfAM7dTbquLizn9QxjHsX0wnsMaZDf0W6UtAyb9m7Kptv7dqkDt4dWZMbTH5H3rjIWSN7qPD70aM/j47tbOO1PmBbxOdgHDfYOYh80+RRF5FNtZLyHYcQTG6bvRfrOCDk8w+t+hhGfg6012F8wXGvyraqwcoTrbUwE7zuNPh4iFvE52B0G+xtiEZ+DfdRgHyf2UYWlrTNM/6dmvfN0XehsO+iB3T4jbRB7QILR8/xn2RZuMjyfMzxvIs/niX/Q4F8w+AeJf5F42EoI/weDL6I8LxNfbdZJrxg86A7/R+J3Gnn+bPA7Kc+rxHuG/18M3iP/14mvNfg3Db6W+L8SX2XK+zeDr2J5/67qaKnC6Dn32+R5pynjPw0edIf/F/E7DP5dg99B/HvEP2rw/xW8sktQJvENW1PGXRCv8fuyjLsiXo/P9l7LbooOu8yhj1L0myLS767oD0bQP6ToRRH891R02FUO/cOKvjOCf7GiexHpxyh6bQR9rKJXRchXpuhjItKPV/Q7I+TbR9F3RND3VfRHI+j7K/q+EfIdAHrTwN9gevBFEi45kl3Byb2IeO55V08aaG/GsNGp6bt7wiQ=
*/