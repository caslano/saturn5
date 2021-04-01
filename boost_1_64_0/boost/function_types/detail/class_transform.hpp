
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_CLASS_TRANSFORM_HPP_INCLUDED
#define BOOST_FT_DETAIL_CLASS_TRANSFORM_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace function_types { namespace detail {

using mpl::placeholders::_;

// Transformation metafunction for the class type of member function pointers.
template<typename T, typename L>
struct class_transform
{ typedef typename mpl::apply1<L,T>::type type; };


// We can short-circuit the mechanism implemented in the primary template for 
// the most common lambda expression and save both the "un-lambdaing" and the
// type traits invocation (we know that T can only be a class type).

template<typename T> struct class_transform< T, mpl::identity<_> >
{ typedef T type; };

template<typename T> struct class_transform< T, add_reference<_> > 
{ typedef T & type; };

template<typename T> struct class_transform< T, add_pointer<_> >
{ typedef T * type; };

template<typename T> struct class_transform< T, remove_cv<_> >
{ typedef typename boost::remove_cv<T>::type type; };

template<typename T> struct class_transform< T, add_reference< remove_cv<_> > >
{ typedef typename boost::remove_cv<T>::type & type; };

template<typename T> struct class_transform< T, add_pointer< remove_cv<_> > >
{ typedef typename boost::remove_cv<T>::type * type; };

template<typename T, typename U> struct class_transform< T, mpl::always<U> >
{ typedef U type; };


} } } // namespace ::boost::function_types::detail

#endif


/* class_transform.hpp
b9FHKLiBYrGqNEEtk2GKurFCb+1L8USFd4if/nSPksNuuuBqTW7Mc+8h6aatoeE+LCt3teX27qYgj1O085JTkpRLKyW1OOK9OCMFeeff3Womb8UWzoSZ1XkJvux7X0uUfitut0AYc/0xkjMVVdvkyimo3NV+mVw9JWorSY1SI8v0THFGVgA9vMFx+FUPhAHFVLBJmfrjQdRitpUhMupSEdMoSd2jflKCJd41G3lSJYPX+rqfOtE2X9SUAsbVhGF+7koafIInGUS4mCKJD86lMnNQs1YfFlRb1+LGU0h7ON1QOPYcoit7CKNKxYUEJW48CFCYYC2BqreUcJQH10KH7p8cHUWuorFM49UH03VX1mNoo3JVXSM10niGCRHjI5ZzgfRZB5ZC7j9jqOLuCYozP7OtIrYALiG7m0OCfD1uu7xnxGPB3zI0+LWFIgTklcmQ6+YX2snsjkRmFSBuefjVSAFhV9lWjG5QHXXMfZp6qUQqxWM4rxgrLMiwiUVHd8Le3eoDlnKMsuCI9Vcx75VNOH6Snfg2A1dP0Lqipd2zNPXGl2WKxaiQHHvIzw==
*/