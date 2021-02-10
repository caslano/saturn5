
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
4DlaF8Eq8uP4Euf1QB9nDTedGr7s1R9vIyJkV/x9u1nFmWzr3dG/jlcI21b/kz+Z+ieT6SRZOX6ed7f+/uD14AGIdVvTPEDZza3lQU9ztx8Zzt3IoPmzmxkIv+wzl7nuELUIkuViDp/86TJwFhznGA4uyjlIwwsQhUUsl/TvQO72B8v5xTy8nKehHY8khLx0aZj0isskDc/SWTALFys6puuNw7Vlika2iszOwJKzGicOy3gXyyAOAvCncYg3ycniqX7BAGmJDbh/ho3ZbTv/AVBLAwQKAAAACAAtZ0pSSSBzqHIEAACRCQAAMQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfU1NMRU5HSU5FLjNVVAUAAbZIJGCtVW1vo0YQ/s6vGLlfnIjgS1MpvWt6KnHIhQaDZfClliKhNSxhm/UuYpc4vqb/vbOAz05SKflwWGZhduaZt2cW53YAhz/sshwDB29eaftP8cJ1azSt5d800/9vkKZP0P3Q8BbXd7gawc7qKT2Ad1k9wbC1SntfZ+Y5Td/h7tYEaW4jY3ybmkeUdJa9/VhWm5rdlRqG4wM4/vjxVziCnz8cn9pwQQSjHGJNxZLWdzac5a3kj5I8PjqKfraBaiDceQaYlEyB
*/