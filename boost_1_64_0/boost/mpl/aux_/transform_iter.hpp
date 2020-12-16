
#ifndef BOOST_MPL_AUX_TRANSFORM_ITER_HPP_INCLUDED
#define BOOST_MPL_AUX_TRANSFORM_ITER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl { 

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Iterator
    , typename LastIterator
    , typename F
    >
struct transform_iter
{
    typedef Iterator base;
    typedef forward_iterator_tag category;
    typedef transform_iter< typename mpl::next<base>::type,LastIterator,F > next;
    
    typedef typename apply1<
          F
        , typename deref<base>::type
        >::type type;
};

template<
      typename LastIterator
    , typename F
    >
struct transform_iter< LastIterator,LastIterator,F >
{
    typedef LastIterator base;
    typedef forward_iterator_tag category;
};

#else

template<
      typename Iterator
    , typename LastIterator
    , typename F
    >
struct transform_iter;

template< bool >
struct transform_iter_impl 
{
    template<
          typename Iterator
        , typename LastIterator
        , typename F
        >
    struct result_
    {
        typedef Iterator base;
        typedef forward_iterator_tag category;
        typedef transform_iter< typename mpl::next<Iterator>::type,LastIterator,F > next;
        
        typedef typename apply1<
              F
            , typename deref<Iterator>::type
            >::type type;
    };
};

template<>
struct transform_iter_impl<true>
{
    template<
          typename Iterator
        , typename LastIterator
        , typename F
        >
    struct result_
    {
        typedef Iterator base;
        typedef forward_iterator_tag category;
    };
};

template<
      typename Iterator
    , typename LastIterator
    , typename F
    >
struct transform_iter
    : transform_iter_impl<
          ::boost::is_same<Iterator,LastIterator>::value
        >::template result_< Iterator,LastIterator,F >
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3, aux::transform_iter)

}}

#endif // BOOST_MPL_AUX_TRANSFORM_ITER_HPP_INCLUDED

/* transform_iter.hpp
IgjctwueTqlDX207ME20wuk6bng9I4ccDWYFK0Vd2siYhMYf5pHY8HY86qWEsvgYlQLf0/PL36Cj8ACUFIxgq9ZSMNXbjNcfrqJhMsuxsrsY5O4NwHbROjqz+AAUdMSA6uZ4MLgdR0ZaDsLh5W8hl3s9nLzCSXl9zqGIwB6UqlgBt85sxgLvj9CdVUifBRSghpQuSDxvg8KvoyDTxoV1gcXEc0AAkzsO0W2ShXgihw+FMiJQ1u8rlGvPAV5rGTimCHAicRfl68iHkk0f4bzlRSzRnUb4s/bgJ453QA5fxJNdgBV9faB4axB6GffxjXMsLXbfhW+2PQI3oQ5s4SjDKdEf0a3zGdV00AUjLgUq22iN4S9NyH3ThXCuloty1svBs5vLaf3VTnw6jXkfPuID582OUlItAmcWriXL7j5AfWeg3SkRMDPxHVT43IQaI6CHz+2GHCVN8OvOhspmxMaAxzjOaQIKctmD3DkCX6ePotClOZTrWB3s5VlKl5jFwORnq+jTiQZYfs+Bhi26DwvHDlKb5I1ADl/AR5qWkJh2F8TIJzh4K51OMtXCniO92BlagOXGb6ByjgjUlE+C6c3GmHbuLgzVeIBS7gAdl7IZtjrFwrLV4jjV3xF81lVBi2QYed6hCl9rZ8HAlOvINsWVMiJqMI9XBrc5PELN/U+IcqgosjZPpS18SjgZG6n4hCrUvxdJH+s+wcHhIfQcXgvNQ/qw8+BaaBg0gEkn34Jk1nhikGiNbLNP0s6MVdh+hh95pGOh1XwVde4fxY2aBmTzizDUSqQ0sOEzdApFURMxc3ggJEPqBxQgNSUHv2g4wOVzs6HplQn2795ARy3M8emz3Uj98zGoSA5XPryB5YZy4OQYi5eirIiH2Vt0PT9AbMoZcHtnG7ixbYdzc3dT9946nNxzHi/FTMfcN7w4wh+F+zfOgaEUPuy5UYlyfqexNNsR3rw7A5z2e8gDL1b4EKQNcmyL0a7hElV89BWUnqiDsQmgtHgFHHTjxe4AKVImPh+zZWaS4493ocQyT0g7bI1lgdp0zcBHHFy2h2ov6sNxBl/oaKo+BiiHAL/tTJxvyUPm80aBapsrlQk2g5DkM8R1dhRkTHAjEy7wwE6LdvQSPABqCyeSzpzlwIfGGC9yG5UDmmBKZj+g+RTUXeoDfgpniNmnq8jb3kqlb+riKl1RsBt8BvfdV4HEVzkIvPcC6i7chuVu1jRnmhckH7iKDzMC0GdxNl6bVIEqGeEw4ZEoHFp6lGjES0FLoyfdNrEfzbexk0E1b1wlOp1E6RlikeII/ejaiY2+QmS/lg3utjInIdV8aBcRQ1r35MFzaRnqszEA84g2QHw4mgh24aPwMxh3BWCXZwqyzZpKJ9oPgXB+BPp3ngEXJTVUflqA3e/mUkGFOBTg6iXJisUw93gg9lw4jIb3DKkzZUGDTBPqZmKAVx0mw/QzwzDcwgI6xvtAs0SDcO18i/F71UiN41F0XIJUY4YGDmVGULdTihC2thwbF8djfMEDDFTxwT6nMVCSrICbZ5AeW94Dl7hvIWdyKZzb9xwdTh1GK8/X9EaQLboJvUDPjTxob8tHdpVoQuogL7K+V0LR1dGk5TqFnkMnyNEdtzBI15OO6aXCzswbpL9RH/coJmDNsck48VgAVHu9QMNn5/Fjezs6O12gF22MQPb5OPLUvQxPVXjSiUZquJxjN02NZsPKa8agHmcHDYuk6UydBnB1d4S1a9fglKANePxQHvZPk6HHehbD4wunyL1IFdSLVoU7HjuB8eE9cc23RBb+k5iv3g7y9wxIg7oh6vi3kWr2dmiybye7ug4gxw52Ms6UQLjGSZT9fBNbbziQFYU=
*/