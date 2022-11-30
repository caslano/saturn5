// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef KEYWORDS_DWA2002323_HPP
# define KEYWORDS_DWA2002323_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/args_fwd.hpp>
# include <boost/config.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/python/detail/type_list.hpp>
# include <boost/python/detail/type_traits.hpp>

# include <boost/preprocessor/enum_params.hpp>
# include <boost/preprocessor/repeat.hpp>
# include <boost/preprocessor/facilities/intercept.hpp>
# include <boost/preprocessor/iteration/local.hpp>

# include <boost/python/detail/mpl_lambda.hpp>
# include <boost/python/object_core.hpp>

# include <boost/mpl/bool.hpp>

# include <cstddef>
# include <algorithm>

namespace boost { namespace python {

typedef detail::keywords<1> arg;
typedef arg arg_; // gcc 2.96 workaround

namespace detail
{
  template <std::size_t nkeywords>
  struct keywords_base
  {
      BOOST_STATIC_CONSTANT(std::size_t, size = nkeywords);
      
      keyword_range range() const
      {
          return keyword_range(elements, elements + nkeywords);
      }

      keyword elements[nkeywords];

      keywords<nkeywords+1>
      operator,(python::arg const &k) const;

      keywords<nkeywords + 1>
      operator,(char const *name) const;
  };
  
  template <std::size_t nkeywords>
  struct keywords : keywords_base<nkeywords>
  {
  };

  template <>
  struct keywords<1> : keywords_base<1>
  {
      explicit keywords(char const *name)
      {
          elements[0].name = name;
      }
    
      template <class T>
      python::arg& operator=(T const& value)
      {
          object z(value);
          elements[0].default_value = handle<>(python::borrowed(object(value).ptr()));
          return *this;
      }
    
      operator detail::keyword const&() const
      {
          return elements[0];
      }
  };

  template <std::size_t nkeywords>
  inline
  keywords<nkeywords+1>
  keywords_base<nkeywords>::operator,(python::arg const &k) const
  {
      keywords<nkeywords> const& l = *static_cast<keywords<nkeywords> const*>(this);
      python::detail::keywords<nkeywords+1> res;
      std::copy(l.elements, l.elements+nkeywords, res.elements);
      res.elements[nkeywords] = k.elements[0];
      return res;
  }

  template <std::size_t nkeywords>
  inline
  keywords<nkeywords + 1>
  keywords_base<nkeywords>::operator,(char const *name) const
  {
      return this->operator,(python::arg(name));
  }

  template<typename T>
  struct is_keywords
  {
      BOOST_STATIC_CONSTANT(bool, value = false); 
  };

  template<std::size_t nkeywords>
  struct is_keywords<keywords<nkeywords> >
  {
      BOOST_STATIC_CONSTANT(bool, value = true);
  };
  template <class T>
  struct is_reference_to_keywords
  {
      BOOST_STATIC_CONSTANT(bool, is_ref = detail::is_reference<T>::value);
      typedef typename detail::remove_reference<T>::type deref;
      typedef typename detail::remove_cv<deref>::type key_t;
      BOOST_STATIC_CONSTANT(bool, is_key = is_keywords<key_t>::value);
      BOOST_STATIC_CONSTANT(bool, value = (is_ref & is_key));
      
      typedef mpl::bool_<value> type;
      BOOST_PYTHON_MPL_LAMBDA_SUPPORT(1,is_reference_to_keywords,(T))
  };
}

inline detail::keywords<1> args(char const* name)
{ 
    return detail::keywords<1>(name);
}

#  define BOOST_PYTHON_ASSIGN_NAME(z, n, _) result.elements[n].name = name##n;
#  define BOOST_PP_LOCAL_MACRO(n)                                               \
inline detail::keywords<n> args(BOOST_PP_ENUM_PARAMS_Z(1, n, char const* name)) \
{                                                                               \
    detail::keywords<n> result;                                                 \
    BOOST_PP_REPEAT_1(n, BOOST_PYTHON_ASSIGN_NAME, _)                           \
    return result;                                                              \
}
#  define BOOST_PP_LOCAL_LIMITS (2, BOOST_PYTHON_MAX_ARITY)
#  include BOOST_PP_LOCAL_ITERATE()

}} // namespace boost::python


# endif // KEYWORDS_DWA2002323_HPP

/* args.hpp
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
*/