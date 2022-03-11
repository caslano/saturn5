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