
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
rMbHCkdcigqzczOJSVH++RzGfOS+z0JxM9I1LvhnzuvvFKxn3JcVZRflZ+ZwMLVru1vduI9F6Hv7TrHT9oj9ngfkemPTdrfP9OmP1CH2JOQxzyI+2pnexAOzGvGQtO2jactNRQ1WDwchzQn0bl/a0nLPKyzLmpyfq6XFr6yY908c3Httdd0U7JLG6i//6jrPplb3sXCPfZ3QtcK2W3qrez3bWd3L8Ix7n9Npv0lS1fc/diy6
*/