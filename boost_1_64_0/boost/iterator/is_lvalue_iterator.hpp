// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef IS_LVALUE_ITERATOR_DWA2003112_HPP
# define IS_LVALUE_ITERATOR_DWA2003112_HPP

#include <boost/detail/workaround.hpp>

#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/iterator/detail/any_conversion_eater.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#include <iterator>

// should be the last #includes
#include <boost/type_traits/integral_constant.hpp>
#include <boost/iterator/detail/config_def.hpp>

#ifndef BOOST_NO_IS_CONVERTIBLE

namespace boost {

namespace iterators {

namespace detail
{
#ifndef BOOST_NO_LVALUE_RETURN_DETECTION
  // Calling lvalue_preserver( <expression>, 0 ) returns a reference
  // to the expression's result if <expression> is an lvalue, or
  // not_an_lvalue() otherwise.
  struct not_an_lvalue {};

  template <class T>
  T& lvalue_preserver(T&, int);

  template <class U>
  not_an_lvalue lvalue_preserver(U const&, ...);

# define BOOST_LVALUE_PRESERVER(expr) detail::lvalue_preserver(expr,0)

#else

# define BOOST_LVALUE_PRESERVER(expr) expr

#endif

  // Guts of is_lvalue_iterator.  Value is the iterator's value_type
  // and the result is computed in the nested rebind template.
  template <class Value>
  struct is_lvalue_iterator_impl
  {
      // Eat implicit conversions so we don't report true for things
      // convertible to Value const&
      struct conversion_eater
      {
          conversion_eater(typename add_lvalue_reference<Value>::type);
      };

      static char tester(conversion_eater, int);
      static char (& tester(any_conversion_eater, ...) )[2];

      template <class It>
      struct rebind
      {
          static It& x;

          BOOST_STATIC_CONSTANT(
              bool
            , value = (
                sizeof(
                    is_lvalue_iterator_impl<Value>::tester(
                        BOOST_LVALUE_PRESERVER(*x), 0
                    )
                ) == 1
            )
          );
      };
  };

#undef BOOST_LVALUE_PRESERVER

  //
  // void specializations to handle std input and output iterators
  //
  template <>
  struct is_lvalue_iterator_impl<void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
  template <>
  struct is_lvalue_iterator_impl<const void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

  template <>
  struct is_lvalue_iterator_impl<volatile void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

  template <>
  struct is_lvalue_iterator_impl<const volatile void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };
#endif

  //
  // This level of dispatching is required for Borland.  We might save
  // an instantiation by removing it for others.
  //
  template <class It>
  struct is_readable_lvalue_iterator_impl
    : is_lvalue_iterator_impl<
          BOOST_DEDUCED_TYPENAME std::iterator_traits<It>::value_type const
      >::template rebind<It>
  {};

  template <class It>
  struct is_non_const_lvalue_iterator_impl
    : is_lvalue_iterator_impl<
          BOOST_DEDUCED_TYPENAME std::iterator_traits<It>::value_type
      >::template rebind<It>
  {};
} // namespace detail

template< typename T > struct is_lvalue_iterator
: public ::boost::integral_constant<bool,::boost::iterators::detail::is_readable_lvalue_iterator_impl<T>::value>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_lvalue_iterator,(T))
};

template< typename T > struct is_non_const_lvalue_iterator
: public ::boost::integral_constant<bool,::boost::iterators::detail::is_non_const_lvalue_iterator_impl<T>::value>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_non_const_lvalue_iterator,(T))
};

} // namespace iterators

using iterators::is_lvalue_iterator;
using iterators::is_non_const_lvalue_iterator;

} // namespace boost

#endif

#include <boost/iterator/detail/config_undef.hpp>

#endif // IS_LVALUE_ITERATOR_DWA2003112_HPP

/* is_lvalue_iterator.hpp
3b9ah39joqXXNBzk3NnprEeKIvyrfUO+D03OGDNp6tQJmZcUIivPt79BXSycUxGltt+GkFZ/++sjvKV5ZQsLys21H5+Bx3avXSN9DNNjJqzMMr4775Xz7eX7do3bF7KVgYGzs6nlDHeedI+XerYcqi5xrIvn22EfiTPLPKjFLrkm5ppxzlyHVR7hv/b0DMjPtc1GfvBmgPbT9YIMCy3Dd0BHSfOC9bT9+kDk6bsfdvHcuZm52Uvsv7tp/njwt/TwK8unsrwcy85O1v8aOKTgS/KyS7X8LxKeC/QaEh9eFMid9zGea+k9d2kur3vQPx1K5bV1XyvXGKr3tI6vz1tYXFSu7bSO4LxnLd1N0O0q2lrFBrEuUNqa7VBvX2tDtomIFzkx3pQh0ogMJI1XVhJ/zIynXBDPujOeMlHxxzW/lodc+4gRb9bd1MNYDl/XcW6oCtRf2R28aaeHuflz59KuI0K+U6Ns3rUCd0iaNnY6yPwcZlrdbqpO970ZeD2JmTY1xW0TUFxoo4e2vOXFnvZ2GbwuzWvqrKof9Yn9TZnwDDX1uphtqHU1xqurxWgVQ78ZL+XFGUPvmB/PSY7UWaZjeahMWk7FUp7+lldvQdRbVxD9lpJ9HNuN38UZJ+2hbdIhO8SJnCXOpeNEnr56qmUCXtad8ag1eFlnT542umvIwbSX6hFF//WcO70BNADlqHPrJxxl5GWqqyzEauIipcO6j1tip4dM5zD4CvU6+j/LuW7+OmibLtdO/zSf73PEGcAWSeqOssaYfYiUCe2gw7n19n3b7pYJYrzYH/1R1Vsik3rP3L7yvMichhg7eTCNI2i7CpVfHPNTzzek188306axItq75rEZ6DZQH7RbtbuM7vbic824VwvNtUfPC+9su3Ijn4Y906rfavgzzZNG7m/d39n2JeC17d+EN9bgjSXviZ6VIu+3wYPU+vnF8rKK2nbzSclrsRWOUhRBMjbPTd13JEqeSf55zqONOa+9X/IM0/al90l4nTUccZX4ZfdMNdM3ketEaLudtYnWSW0qqV/oY37cc9XdVwF9+rlYo5/z7WOSlYLSBqUV6CNQX5Qj621TV9HLoLfhfUUdEvHa6SfSsr/Q+rDEXy9t+Qr9ddGWL9dWD02+loZvj3j1fUfOhRvnLvX2fX7nJmi9eVfORWr701IJ34jvSJEnXU/tble2FeUVYz532Pc5Gfb0fS4dztW2WlGOwDZZvaIciF+TXzfo6eb7f/GPs0c7uz9wU0ogW6eG2yjZ23wFsoFquK2WvQ1aYFuwrwxZZ8S7bXKO0M4o3TMW4vgswcfepTm/w50ObE5f4a3ooz2WPt9TDJ/tKz3v9xyvJPjsxTEGfNHA8bSHmAwcDzwPeBFwOvAS2k8UA2fwu+Es4FLaTzxGe4kXaCfxOu0j3qJdxjsqzPLUeN7d+N6awPt2A8uTa3HvDH7HnAfsCbyK9gX5wAnA+fQdX0B7qiLatxQDc7knRD7tKxbQvqIUWE67DZDYbVSwHktol3AZcBX3iKjidT3fg+tYbnU+wed7cA34VPhx7u3wJNP10M9paUdp6zBQO6b7K78Ho/21fVY1+W/ndbR9Fr/vOrjXQxt+lz2HezdMAlZRLmu5Z9TPKJ+bgXO4V8PF9MV/JfBeymED5XAf8DraDy0HPkC7oI20b3mQe3Q8xPpV6H4LfTDL6wQVsLxPUy6bgZHAZ4DdgFtod/M8y/0CsAj4Isu1lXt+vAR8Cvgy8A3gK8CPgK8C0Ub6W2sJ6DAod4j5/dT97XQLaAj9wnu+jV5rfPdcb3zLzAWZ3yrnZOG7I6ga9CpoP+g4KCE79O0wdISO0BE6QkfoCB2hI3SEjtAROv4=
*/