
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_TO_SEQUENCE_HPP_INCLUDED
#define BOOST_FT_DETAIL_TO_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/function_types/is_callable_builtin.hpp>

namespace boost { namespace function_types { namespace detail {

// wrap first arguments in components, if callable builtin type
template<typename T>
struct to_sequence
{
  typedef typename
   mpl::eval_if
   < is_callable_builtin<T>
   , to_sequence< components<T> >
   , mpl::identity< T >
   >::type
  type;
};

// reduce template instantiations, if possible
template<typename T, typename U>
struct to_sequence< components<T,U> > 
{
  typedef typename components<T,U>::types type;
};

} } } // namespace ::boost::function_types::detail

#endif


/* to_sequence.hpp
1fNEFS9GBNWVa7JeQcfCrBilGWPTuSOXeWi3uaPnT0D7z23sDLsS7zgxl7SQcvfEjWb+qUa5G9jCEtVK6+WWSDBX+q2tKncsRCLBxf+qfoc827Zx2bS8Ul8+DBL7Td3Knvrl8as73ecwnc9ggqZRkDxb5p4S/gEa/vSWlqieSIi2J74iQMVV4TeVoLQiSsuyCop5zRQUnZ+rzxF+6/ul2DxHl4pb17051F+Pw+20Gu/kMrke
*/