// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef IS_READABLE_ITERATOR_DWA2003112_HPP
# define IS_READABLE_ITERATOR_DWA2003112_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>

#include <boost/iterator/detail/any_conversion_eater.hpp>

#include <iterator>

// should be the last #include
#include <boost/type_traits/integral_constant.hpp>
#include <boost/iterator/detail/config_def.hpp>

#ifndef BOOST_NO_IS_CONVERTIBLE

namespace boost {

namespace iterators {

namespace detail
{
  // Guts of is_readable_iterator.  Value is the iterator's value_type
  // and the result is computed in the nested rebind template.
  template <class Value>
  struct is_readable_iterator_impl
  {
      static char tester(typename add_lvalue_reference<Value>::type, int);
      static char (& tester(any_conversion_eater, ...) )[2];

      template <class It>
      struct rebind
      {
          static It& x;

          BOOST_STATIC_CONSTANT(
              bool
            , value = (
                sizeof(
                    is_readable_iterator_impl<Value>::tester(*x, 1)
                ) == 1
            )
          );
      };
  };

#undef BOOST_READABLE_PRESERVER

  //
  // void specializations to handle std input and output iterators
  //
  template <>
  struct is_readable_iterator_impl<void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
  template <>
  struct is_readable_iterator_impl<const void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

  template <>
  struct is_readable_iterator_impl<volatile void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

  template <>
  struct is_readable_iterator_impl<const volatile void>
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
  struct is_readable_iterator_impl2
    : is_readable_iterator_impl<
          BOOST_DEDUCED_TYPENAME std::iterator_traits<It>::value_type const
      >::template rebind<It>
  {};
} // namespace detail

template< typename T > struct is_readable_iterator
: public ::boost::integral_constant<bool,::boost::iterators::detail::is_readable_iterator_impl2<T>::value>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_readable_iterator,(T))
};

} // namespace iterators

using iterators::is_readable_iterator;

} // namespace boost

#endif

#include <boost/iterator/detail/config_undef.hpp>

#endif // IS_READABLE_ITERATOR_DWA2003112_HPP

/* is_readable_iterator.hpp
X46f/Pt/WXmpfP4/Bd//bza+/2eE0RadcxLngfZ0wBzGSzJnOmrKzIxpkzML8wpzF5p+1+gj337OFGn1HPpCS/GW5V9m+CXcIufHYF7KYTeXivS+/vjnouz2c/uaV38/KMgvyrOf2zd5wyP819PvkPO9rDaQrOmbGMb0J12TXt8vnMhGf5eDDBBHGZj+4VkvznVzfhzl9/Ehvj0c/4z1HWNBf4nF3NnLZhtBQdhGXrkhzpB7V+EfidrZ+htAfrZyt2sj8NrJ3b6NTN4Sr9z1nHWGnI/T+mIpWeV5fWqny/kO+jsE2uSk3+Xq+WrUckB72MjeeQLZ7+fC6TmU/WzQy/HQCV/ZF0H4drJnHa8T/ukBZV9JGTX13jN2cgdf8PdG5cvB3xse3pa6DQqzKwrytG/z1sDHhaebfzuynbbK+UTZr6IWOjsPslsnfidaOaObNY5whjXX+TvM/Hn/rZX03UUGUkCrRF/7FjnXTmx7fqwexNS/Lxt0T3rsLSo55Xcb9WI9aLoq6Cv17C0uXji3z7y8CuoC6vVZK8WP6Ll5iLLtP5mHw/g+JYLy+omR83OsNvg/1b4P1Xk01W21QMt5lZxrxH4PHkkk3M/qibimLKNH9urnhXJ+iNHu5YUlhm73k/MXW50hIe7FAf/Anr7z5N8M49lG6rpxWjb6fgUiXsvA2eLrjugTnOG4GkSbm3+Jry1MFvcD+Lvlxd/FQz/rtw0S5+CZ2ye/qNySeieJrHNs2wRpg/IPGoPyiX68Cn4jPIThllajFn3cv5MnTOo9yGJcijduoCeumzdugCcuyRvX3xOX6I3r54mL9cb19cTFeOPO8sRFeeP6eOLCvHG9PXHHX9FxqXLPIu4rHTdIwod1eKCEP9XhARLer8P9JfyxDveT8Ec63FfbVSRJ2+fUa18Xb/IOYHbSx8AsdWO85tu+uO/6QJ/8+2W7NkZ6XzsB6JzRP22U883s77fXfP0q5RTkKx72jSvkfCa+ibSlT3LcMRL3lNUVsRmonUqbJPnl0PfXKPRz/BYmvI3AM1Jsbdxpt4AHaaTwqK5UFfLgd+I+wnPA6oLaXQt6CtTU+4zV34VbKj7UqqnOa4G2S8iSc09bkyDp69R7EX2X17C+Zn+RyP7JJeeaOEajvL9Emt8CjboV+Nat2KjbMaNuhizn5Rvvaavl/DCcT7K6ob+JMt7TZrcQ0r7IQdp/WVQQ37ft3hegC7r/QZzIn3qpfbQd88YV+O4dsLKZv43t2fhX8rqpr+olW5wbG+/Yi3oHeEYwrcPk7RPAFx14fd8tinTfXi7nTrN7f0A6W19h+pm8Rs5H6z1GrpUwdETrRA7K7223CjmfbHW0wk/6TKj/Pg05+PpZZn1pc8BneVE9uR/hHgnnsz7TQB9AqWvqyx2NXZCTXW7p5xvGNmUI6vvjDeFvZMXTz9VWCfe1IhHXGf9tx0CUndHvlObYtw94bcZLhg/4t17XdjwI8/qoZVPEdUIOdm3HPI37vUC323NybpzVE+9pq6Gb6yCnzqhoeBL2FGsUFt04uht+NG4UPTY6GT/wpPWTjfY3tlny6o1SdA4kH18ZaN2rFb7uvvXW+vKknO+H+nQKVHe/+iWocZzwnCnvisG+H5bIPY66+Y4TWOaWpp6xnKauwde9HMNoUzGUupb0hr+ulSzxk6eWSYrwJ9vpFPKy1SmtJz3kfC9bHUNaex1jOybL+TPsdAlpA+tSqpxLOdH9PP5UyvmKlnz2W16f6oNUX+on5yJ02H7PfS3nCuGPt+9bWV/bsQrlVQ4e+714dHpzHKPb6DI51+qke73YPY/izXELy+T77rvFZi+BoZBPtVs+nHBS8hFX05nI17A=
*/