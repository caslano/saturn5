
#ifndef BOOST_MPL_AUX_JOINT_ITER_HPP_INCLUDED
#define BOOST_MPL_AUX_JOINT_ITER_HPP_INCLUDED

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

#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Iterator1
    , typename LastIterator1
    , typename Iterator2
    >
struct joint_iter
{
    typedef Iterator1 base;
    typedef forward_iterator_tag category;
};

template<
      typename LastIterator1
    , typename Iterator2
    >
struct joint_iter<LastIterator1,LastIterator1,Iterator2>
{
    typedef Iterator2 base;
    typedef forward_iterator_tag category;
};


template< typename I1, typename L1, typename I2 >
struct deref< joint_iter<I1,L1,I2> >
{
    typedef typename joint_iter<I1,L1,I2>::base base_;
    typedef typename deref<base_>::type type;
};

template< typename I1, typename L1, typename I2 >
struct next< joint_iter<I1,L1,I2> >
{
    typedef joint_iter< typename mpl::next<I1>::type,L1,I2 > type;
};

template< typename L1, typename I2 >
struct next< joint_iter<L1,L1,I2> >
{
    typedef joint_iter< L1,L1,typename mpl::next<I2>::type > type;
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template<
      typename Iterator1
    , typename LastIterator1
    , typename Iterator2
    >
struct joint_iter;

template< bool > struct joint_iter_impl
{
    template< typename I1, typename L1, typename I2 > struct result_
    {
        typedef I1 base;
        typedef forward_iterator_tag category;
        typedef joint_iter< typename mpl::next<I1>::type,L1,I2 > next;
        typedef typename deref<I1>::type type;
    };
};

template<> struct joint_iter_impl<true>
{
    template< typename I1, typename L1, typename I2 > struct result_
    {
        typedef I2 base;
        typedef forward_iterator_tag category;
        typedef joint_iter< L1,L1,typename mpl::next<I2>::type > next;
        typedef typename deref<I2>::type type;
    };
};

template<
      typename Iterator1
    , typename LastIterator1
    , typename Iterator2
    >
struct joint_iter
    : joint_iter_impl< is_same<Iterator1,LastIterator1>::value >
        ::template result_<Iterator1,LastIterator1,Iterator2>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3, joint_iter)

}}

#endif // BOOST_MPL_AUX_JOINT_ITER_HPP_INCLUDED

/* joint_iter.hpp
soKOz7YJU6QfNd3cXpS8N3AUgd28sDD+goj6G+Up0e83f1Z4KjlSI5Rx5szP86/1qMbdIZOX3pipe8Inb+2ug9lOF0SihJfGvWHOdrXXKSjUE02qGTZC6fqJ/XFH59YdcDkX+HFH2KkPaxMyD73vHrwtMsY7ZHJDzsnifaRxSjpuoknWctNyrcwUm7Zt9Z0QutPW/1HT2uhHE35kC+94kPfNoKW12VR30rWZmm0Z9Fq3Ee+YS26+WcSYVaZGmhAdIVraesFKXnGLRR4zKnrJ2PkRGS9zvak+O86aCHseUlkibDXj2Iv57+3nrjn3edAUk2dmJyQlPNso6ipt3QUE0pBvEsdOsQstps5erHlJQ/T5T7l197/rH0xnORltJDp9G7rw1Suz58+KTYyTC28fqP2yzTHI/qAUuVLa6tbt9zZqSXuz75m+1Jd6a553cYGRYYGVoukqX3eR87EeZEnb+CsUse9ZsudGp6VvGZ54Im3y8RXHi9RTtr2giWx4KntsVYHehIrn6omyfsMTovWaa4d4Lru3ZJei09TZg5+JsIu27SrKnOv6xuz97PcdqktrwuxEGQ9KQq47Kaq0ijxVMDIxt6sddKF4uN2kPFmv66EjSYSNnrVNZnI57XUJfu6GtEcpRxZuV5IJ+DR5LCX61p7H5ooyFqL7hk/70Lz2c0fnpy2jr1zIibNQUGM6NGacjH/zVmyWVEbBSKvpKq/VUzqELN3PPw/VkVZ9nf1ohdUCzdth3qmlbnpRBbQdF6QUbqa+fbnRx+LXvq+6YmoH3H98thylOk56xHilwLRiJZEDw7zPyMr9iPt99F2YesnbTQ5FjYtvz9l/32T+Se3uTGJrrVHJvukxl5dqTA0lbT0cIb2v/KP5Jv2ao3NbRy7Rj/PXPqOhwAwS1klyqn1PU9gVZJBfJrf5UtA7td/G5AoG+VDWDFbh+N1MN/GcnGr5F4fuFmWUfTwwOjjw8IzDO+KWfDl1XG1VyJ22S0rnI4flel6cHmo0PcK64PRIi+o3OYY/zmlcVRL33Z6dG7BsXvaPTflzLYO3LTdpT9Ft3BKw4YPMQtmIQTrLx0o9Um++lVf3YnP2hamp+5Z8m8JIHKrcXbJ4+2bH4iHvxAru+Rro+TQ5P12rbVgU2/r53dS33TeNgz5o/2ZZpH98Kj9xZuPZkBb5mTTbejkr+pmXHx3eHj60R8EjpqbS426H7VfbW4UXo1pVzT1CqRr3bHLS1J7cmrQ0I8rJtckzeKHl57zgCscRq/1zFy//tefMrWslwxXmr2ffjRRfucRp6an1kwlX/EV3OisdZZ8MlidILRo2crXt1Lff/CSsvh5VDWJOGLa+LXGMzbwNqz+9D3hUYz40ZprJi/RA9se7Bz4vtY4zSilfskB4f45nu5Lfk9aWsVueBh06EHmwWEjixq/DlOnP74gv0Jttn7PE2KGEGl7dVZqjJlVVw6q5t9yPlvYsINzaLrwx1Pj6jSemVgk57dqW9O7YT681rBQmWp5YO2pXY/OPo4trIqZbvvlhvXCjygi378Y6kRt/0BVsfjwkJetFfy2KIOx+mDBc5GHUV/qYsw/P2h0PInjqfR+v5ugwfAvbQ0PeevmqK6q/Nk06vq5wc1XtV6aDfm7Ye9GiK0u3XCJXxh6ZT1l617BA691mm/Fdfs1Oms+2id05rJnqqf1Vh+LzLGO0WGfsmTfB8s8jCJHOj/delYr4uDpPa/fvCR6ZR5e1CNVnFp559HV2ulr5ofcBJlXZe1LLbUdGW4/N+U0/v/TL08OPx39c5S5r/qOjVHWyYqyrYdieEae2NL5ld8SZGdn51/54bRPRSU+94/5NrHNLwe8nRyZbO2g=
*/