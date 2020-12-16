/*
  [auto_generated]
  boost/numeric/odeint/util/multi_array_adaption.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_UTIL_MULTI_ARRAY_ADAPTION_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_UTIL_MULTI_ARRAY_ADAPTION_HPP_DEFINED



#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/multi_array.hpp>


namespace boost {
namespace numeric {
namespace odeint {
    
template< typename T >
struct is_multi_array
{
    typedef boost::false_type type;
    const static bool value = type::value;
};
    
template< typename T >
struct is_resizeable_multi_array
{
    typedef boost::false_type type;
    const static bool value = type::value;
};



template< typename V , size_t Dim , typename A >
struct is_multi_array< boost::multi_array< V , Dim , A > >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};

template< typename V , size_t Dim , typename A >
struct is_resizeable_multi_array< boost::multi_array< V , Dim , A > >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};




template< typename T  >
struct is_resizeable_sfinae< T , typename boost::enable_if< typename is_resizeable_multi_array< T >::type >::type >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};





template< typename T1 , typename T2  >
struct same_size_impl_sfinae< T1 , T2 ,
                       typename boost::enable_if<
                           typename boost::mpl::and_< 
                               is_multi_array< T1 > ,
                               is_multi_array< T2 > ,
                               boost::mpl::bool_< T1::dimensionality == T2::dimensionality >
                           >::type
                       >::type >
{
    static bool same_size( T1 const &x1 , T2 const &x2 )
    {
        for( size_t i=0 ; i<T1::dimensionality ; ++i )
        {
            if( x1.shape()[i] != x2.shape()[i] ) return false;
            if( x1.index_bases()[i] != x2.index_bases()[i] ) return false;
        }
        return true;
    }
};


template< typename T1 , typename T2 >
struct resize_impl_sfinae< T1 , T2 ,
                    typename boost::enable_if<
                        typename boost::mpl::and_<
                            is_resizeable_multi_array< T1 > ,
                            is_multi_array< T2 > ,
                            boost::mpl::bool_< T1::dimensionality == T2::dimensionality >
                        >::type
                    >::type >
{
    static void resize( T1 &x1 , const T2 &x2 )
    {
        boost::array< int , T1::dimensionality > extents;
        for( size_t i=0 ; i<T1::dimensionality ; ++i ) extents[i] = x2.shape()[i];
        x1.resize( extents );
        boost::array< int , T1::dimensionality > origins;
        for( size_t i=0 ; i<T1::dimensionality ; ++i ) origins[i] = x2.index_bases()[i];
        x1.reindex( origins );
    }
};
                            


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_MULTI_ARRAY_ADAPTION_HPP_DEFINED

/* multi_array_adaption.hpp
+m5feAYITQ6MfmrRppPKrUlZ8IsfKfg+MWwzAvlFkHZF7fuIC/y9FKnB/JkZXbsUJvHgGnOGpFz89TK0Y9R1mevaka96gY9r/GbAKYNPdH4Vr0csF16ZMldvxQvpiQAWFVVVFYRcIWTbKzpX81Mc2NGKI2dfVyXy60K8+zNzE7Y2g/IvdZSCEdWoJn9THV34iO0IpeCP8ItN0mIPS2/U3qnapiOr/p6fytoDCxFZFWtlFAc47TDE6xJr0RecoP/JjzrrpN2PIsCQKipR/gfJUUP76b1pyG4A4fzuhsZji38O4mfvkBAeMMCg2e/eHO5Njt2RQFq2IUKi/XnYk+ar6Aj1FXfDj3jyEfvbG7CMqqsZhmvRVDSJZzlQomolSOfkX3z9Ycbl4CGtDCODgEizDNsHFzBE1ftcEqhVVXPrcz36VDCJ5kJe2incW+VuDVGBSrgXnB84exJQigWzooN/2TzF6t70aJ3d3erbtLsWv0mb3uevdNMGOhZtaliB3+hQ096aKGflBbjdatnhKVLFi2Dch+h/8qZH+eu3qZ4/56YGxk3dtNoP4ZEJ0YL7GLEYkup2n4y4t8LqXi8THbm+kL9z1zcz4pD1U2g7bb1M++T1Eky/9bsk0PWrlhHoegKt6VBCKo9JKcYBJP53ZC3wBS6+LNThci3jQHCtrdugUnsIv3W7AaPFDfd1+2hKo2k/TYctMB2m6W80OXSYBE3NdHsLJiRmRf6/Gjg99JfCQD98XLXrGSKLYTfQ5KHpKZpW0rRGxbLxNpFVdF1N1+8p12rAKgmMgSkLprMCA2BykB6Ivxuc5qvWDUPo1m+ue5S/2evy+ZsGz0J4Tlg3kdaL183gbxxcUREEQpNVAUG6wVPXVTHA6euu4e+UdfX8eegJKkH6OtQhqnJdM1xDh7IW5AXOj4yLYiFcMB2NtE9V20786mewzifXz+bvkvpq/sbXX8NfQf1y/kbWHJK1c3Kgb6i1MJCKT6unfp9Mtf79OpnqIeQIqdarVOvfh6eOGdhLpftlk/1SB9xce/SCfRhusAyDZv4H5Q7DpDE6oEdi0GSr+xy8N+M9j/+ENxdvAO8svHPwXmu4W+yf/1jt/9hjs/97nxTokLoL5bwP78N4H8P7DN4teJ/HuwPvLtaD1WGTiqDUY3d0flIdn/+kOb7cJz2t3Op24z0Z72C8X8XrmcJ8p9pSU1NT8PKxF8BtPN7JeG/GewneFV2E2/n/50t7iL/LM6WFQIsnygMnjcn+6xvm4l7gHUCo5qwaZQs4i0JbHKGDjnkfZTcA643K06m6/VdbEaqxq/0UsJ6+1CsGQeFUvSiXqidzGrtRKY5w2AEh5Fn6ZM+6heDTjOobcBaGNuNkiEel2G6muK0K3oSSnN8MI78Zifl1Juc3s6v8Mj4OLjR2grfQgOdMhNcjGV5Vd/CArAGmvbG+Xe8yv1j/05SfXpgp9x+wr8F0rK7mOW1DRzQpfxk4p4sjusmpxeVPXEuLrORpjXoghsxTokBi+5HQhVHeVDvGtayNRwMhgJiGYNo56QaiUukU236kttjk/Z0NTtk791MsIBagiBRVIpcFCAeUKlJsnTl9VmN4ACgC4mwgPA94r0slknqDD9JxDEPqx8Ix2gUmCJ+4ZrXNAsg6IeeaztoFyKUJfO9quWzIHRDBm0AHAOgAE2iAjLzi+w1RAAbT8uOJpKtEzmQiY+LZb12tnRFLMjshyWtlkh6ZJEAdh+DNF3xUe8bHnFY9E2JgU1BQEbzXpuqRK2an8JbG5P7VQ/aUsvtslqRxJQFwEIZ709TJLybP4oHSfr0gH4LQlb21/WGKXUd/q0gp6euJiLROxG7MsiLRo2dkqhU=
*/