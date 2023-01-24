
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
4108DDcyy/sM49PuaDM0FHXwxT0x/3ym/5oILpBmDDvvuNT0gBRxWoTJgVkEtx7fbYWEDboQKq4yWI87QCcxnooJhWVbAvkklhxAgsp3bUqYmau7ni+SBttDCtBdCznIf2zke55b/IAFntCWbivEFqwVF4VWDLW+YyOJdZA1FGtrSCcKmyDZiGcruch+h+moHvJhS02Zil5ULLnL0cB0adqEfjvjVWA6q14LlfTGhJ60ChIvwf3fcUmDduRdfY2uhasdDa2FEutaKAlZCwF7U9bCtB0NrYUPezS0FkBEd/fDoa4Luvq0wh7iuDC1RHotOJvotWDRgmZXTC1xlW0Ff4XJ6K9AKPmEiZIWF4X3ZdSMwQXKRaHKJl0Ubg92UbA05RFNYQNBzgmTQysWnERR484JE1r/F84Je7fFqwgJIYrTNRchVi27SNr66HbO1bOaYNtd3yqsbXce2Ha/mhbGtjvHwmlMzfH6x+eGs+3OUbbd1Y+Ft+0uaNUU2+69XxNaWmy7N6Y2YNu9Z+bpbbuPtmzUtjvPaNFb2nbnWJdWTsjSmt+yKUvrnJA+cPybFGnbnZPSoG1385mN2Hb3bBlq253Htt22lmjbLXB3QI602s5RVtvWeYQXTbMA546/1aIptt3nf9UE2+55uG5jus5QAlz0a/L9BNsqim1NT/I+LcgurQDRdSeafmdP/8VefqFu9VUIlZSydK4w4OwM
*/