
#ifndef BOOST_MPL_AUX_SINGLE_ELEMENT_ITER_HPP_INCLUDED
#define BOOST_MPL_AUX_SINGLE_ELEMENT_ITER_HPP_INCLUDED

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

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl { 

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {

template< typename T, BOOST_MPL_AUX_NTTP_DECL(int, is_last_) >
struct sel_iter;

template< typename T >
struct sel_iter<T,0>
{
    typedef random_access_iterator_tag category;
    typedef sel_iter<T,1> next;
    typedef T type;
};

template< typename T >
struct sel_iter<T,1>
{
    typedef random_access_iterator_tag category;
    typedef sel_iter<T,0> prior;
};

} // namespace aux

template< typename T, BOOST_MPL_AUX_NTTP_DECL(int, is_last_), typename Distance >
struct advance< aux::sel_iter<T,is_last_>,Distance>
{
    typedef aux::sel_iter<
          T
        , ( is_last_ + BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Distance) )
        > type;
};

template< 
      typename T
    , BOOST_MPL_AUX_NTTP_DECL(int, l1)
    , BOOST_MPL_AUX_NTTP_DECL(int, l2) 
    >
struct distance< aux::sel_iter<T,l1>, aux::sel_iter<T,l2> >
    : int_<( l2 - l1 )>
{
};

#else

namespace aux {

struct sel_iter_tag;

template< typename T, BOOST_MPL_AUX_NTTP_DECL(int, is_last_) >
struct sel_iter
{
    enum { pos_ = is_last_ };
    typedef aux::sel_iter_tag tag;
    typedef random_access_iterator_tag category;

    typedef sel_iter<T,(is_last_ + 1)> next;
    typedef sel_iter<T,(is_last_ - 1)> prior;
    typedef T type;
};

} // namespace aux

template<> struct advance_impl<aux::sel_iter_tag>
{
    template< typename Iterator, typename N > struct apply
    {
        enum { pos_ = Iterator::pos_, n_ = N::value };
        typedef aux::sel_iter<
              typename Iterator::type
            , (pos_ + n_)
            > type;
    };
};

template<> struct distance_impl<aux::sel_iter_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        enum { pos1_ = Iter1::pos_, pos2_ = Iter2::pos_ };
        typedef int_<( pos2_ - pos1_ )> type;
        BOOST_STATIC_CONSTANT(int, value = ( pos2_ - pos1_ ));
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_AUX_SINGLE_ELEMENT_ITER_HPP_INCLUDED

/* single_element_iter.hpp
fWd8bWspx+pY8n2qxI+fOqgxzOfxUX9gXlCNdZpqUO5TIZsdXYmlHTew/OF8bC9MleeL9nGOa5To67ATibHewnJ5Fr5rn4SVyWYq5drJrf8ymeatJ+82Anf/RLLq4zMeKHiI7jW+mDDVTnx1c8TAP5vF/A6j6VuqiZXPHnCd32VaqWkhb3QDwubsRPDIEOHxyR1XZ2rAoCEI+c+m8PEma64+8wXJzbbzTOgVMfxnCKNmXxALR9TT6545Z+QF87lBhdj14SZLbzXSdlt7pkfEsku/HmzlMkXesC3Fd9u5XGaQyx9PDqN0VwQtX5nIa/Vzec7ssBjyygiufZ+ju2omz5xUxzyb4/yac1uE7/2MD29biawkZXwZaiz+rU1FVssk3vdJxolOj7Bq1ly2H6DE22pusBz+QsaGrYHhoyKODuvBI0c2i4Xxm5jSJYiBxk3zfquD0DBowwupuSIkV5kL1SLwytUGA932yvkYwqwGO+kRYcMvy7fJGRsH0XKAlnR4ooRM/0y4Bt9D8tV0WdimilYBm6TRZwsMWdlFtpy9ln7nfsI+KBe1uwtwf9Us7O98HIvvDEFXg2TuGLMJFyetk/vVN+HJhyj0jj6CmUsskHZbkQlzZothdplo6O9DL4XnNA4bJEYNTsftFwpSeeY2bEtrx4l1V+ijGsgnI57QyaYMcx1+cmfBCo4vHQylehtmF5/D+7dtxLT/0jlS9z8s3q+JoNbx8mfNflgM3QPb/GC0376aT/y+8ujP32wWvI0VO0eIppPcVLvdNEi4yH3jZ4pZF1tB39gJignHObzpX9G7fBVh3QfJk3MNsPbcd6EcsIGtvt8T16wMmb3XXV6rC+FudXU5ZYE9fBujxLdhTY4f9pib79Zz2+iVIvKjKWperoaBRTeODpok/p7sxv5blMTc3Fv8618jrjwaAN3sBQhdeAl5L6bLlAOWaPhwV3oETKK1x3y56XxreASYouT+By5qeILZyh95cVoBqt/GYWm73lw7SZXBYz7BTl7Apa/eYsjozfz+oo6Wt97h0feFcmFwAr/dz8LwdrbovX4R+5enwfdCL1F5LJh+mfeBPebcqHONCbkH8Hithhh2OQVta/PkVqsK9NXpJS57T0fvofHyRt1wjJgUJqMTH3Khx0Fmycc8rfYLVUr3UR1ZC2ezfqzpsYhK86L4YeYrHg+ajvy5eaLmVSqPLAoVxuem0sgzSdiVLsMTLS/4jjBB6x6d8e3YPZwqOIztEwZj7+zeyK5thqIh28S8lCuoiFwi5t/4gB3Tb8iaF5voqttSJt01wL8OjmLfJH9YhPUTozzUeTneW/73xRXTn7oywNyeM3b9FGVrT7N9drB4ZF6Nys/z2KdKjfEr94izfjo4ppsgqx2XYJnFbdG1+Vi03zkUcVuWsu8afZnkkoXtRV0wMWYEtnuPkweWRPFr7mF0KYrithnv5Tuz13SJuAlbXyP20X0ulMOncE6Mv1TuYIPw/J0i8uVIxji0FoWXXdnxTAAX2X1AieUaceBPc87bU8K+v6yY9zZdRtpGYkL/r9wxaiRa2tTwUsYF+Bp2w6j3NxHgNkIYvomm6tsyWfLGmsqDAsTujWfwuygHB8wuMXxBDxzIu4B/2hMQOssPUTlX0GxjA+3U10PZfi+Shv4U6yMrmV+TJdZfz8CQEfXo+OkjAjs0eYjsxZ9pm+i5RxPJgbVyV9u+jD8ei0cP3fGra1+xMNQU/cabwjfvAWsRi/gfPZG95h02rjjEXcMuCvN17Rk9wlQMM8xG8pMeXLYjkaeX3aPX8VuYM7GWj1bP4R+5R6bdd6btHEO0WmLFrpLywegutCn1ZL+GKfi+3hDVB7fi9fc=
*/