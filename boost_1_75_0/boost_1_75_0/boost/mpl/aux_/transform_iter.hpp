
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
vg8vFHl2/9QdoLGK+fXmPGkj9vwwFycXp1ri9H1P9L2ZU00JDj0ClK+Mi1pkBivtu14BRvuYq1hGeubSWuqvPcwTpyLqDWd4K2ED60qKi0rVWOUVS+POdy+lnOQO5mgrlasBdtOavv3QlWvyh9szsf6l0ughylbWrWj3zMlYXRqSM05WK56TE7XpZBZsBskUvnrn+w7LveIq9xvbnBUc+v0D+tKWQt97QYD7+iovKPc+LQeeZse/UCoq4g3yoU5jByuL8ueCdhfbWeL3LTlv+3ErkrhO4iy+IS9SloYO1RI7poD9JwdH+NKq+pf4KG+3CplMhVkHvyedrrP0jdSTCWubClcX6pfNni6oI3/KcMtzYWUBIhvJkm7esIDv+bQuMsisp7lszg+9YXuLVoBOD01VW0K4SGNILOWn016VhddnSstRSbKBITJZIojCUKCAB0lphMQGu1InUX60CMJfGMo46cDPkb1oKxGJCtGz9EWdeEWUhciuhIPMsplMvtc6ZIYWdnVI20vOK+dxW/ZcBw6PAnAc2oM4m8CzIsn4XdWv2pXS3QqPr+CM3kyUF0kwRiEJ+ceGcWEx2UP2A3EYpW2Jr1Tq1Ue5B5346y/erxLnZ01AFdEisvQHyePzMyBX/QXfj9dGUU5dr5eeUem38WA0wtKqoHCrCUkTiXJ2K8vJnEyL9JRuULWYftEEU7aHHIUuO3gGInOwL7hW
*/