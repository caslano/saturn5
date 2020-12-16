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
/OrHhlpyH5WvaWq3YwcZYieOqR3W8U2Yr37NVe1LBu1XFh2P05aMZ171j1nlulAvmzznkiXjm0P94JeqJ9G0tx+fpXLSTe3nXLU/Q11kfAJ0XCJlf0Tl+tEEaRfSStodt9RPblU7n0njmLZy3bWSOk4qB8nFLbnvLrVj3dUeVnOcZ/1Mrit1Wn7fGaN6onFPNS9L+ltT9mU+tYmetZV2OT/QOOA1U+R2hiF7vV/jm6pf7+g4VZPn3Wmg9uCB+uvShvQvq9qPfhonHZXjC+aqHk9R+1DBcR/+ezWGXK/3ieup/fAzZK9x1LgIOR+TX/3lHH3vZNXPOjp+6VS/9up1r6u9aKZ+5aReN1n1KZu23yd7v34aX9xQOzzbJuNUScdhok3u94bazfvqN9OonVyq8YTuk+ulkecuVP/03BQ5bWTJvOt7NCypcWFpHafjOu+eav8X63tPkOO+YRqnNdH51PEI/UrtXwWNS0fpfO1Uu1Vc9W+e+oMW6n/HGHLfGmonPNQvdpLrgvap33tmiF74qTx4yXFzkSnjoHHWulaqbwsMmW/k0LEP1n6cUXuq9q2Qvt/xa+ov9b0TW6j9Wa/xRRHVv+cqf0FqB+I1zuujfr+Mxo27dZyeqp9Z+/P8aBxYxJL+jlD5S1C92qbxdU/1n601Ptmt/s7HkDizsDxng7fqjcafe0NV/3qqn02j86/yn7jdEruVX9pPU/s6JFztVSmb9lfOp9P7x2qcb1p6PEjt0/vqr+I1jtHrZ7rIvlScXOfXVeOj3Grf39d44VWNJ/3l/Kqemr+M1vnSuNF1gPqlgirf5TROGqV5gIfaYeJfR7vblsh3qNrD6WpXVqu+qT5Umq9xwS1L7rvLJnropnoxUeOps+qnVM7KqB8KV3+ep6m0D5mk41dF47Iaam9qazz+vSF29JbGv2p/TTe1ryo36w7o+6mfuqj2PUjl8pH6vZzLDdUnlReV4yH6HN/9pvTrkvartfqpihofJWs8Gq3jlFH7M1flO8qQ4xp3NS6m87NQ9Sun+vkeep2Oe8441Ychmv/dt4l859M8p5DKfXX1331VL99XeY/XvOSJJfdtbBM93av9fKhy0FCO9zd1/h/ocwZrnpdFx3E/62fsi0JP8CHPvjHQxQh8nbNs+aFiEGCvq45PY8yxzzk5x4XVrCvRJBJypKNdIH+2yVrNNtZ7Xs/Nvzfhs8HyfMPBuk2zPYDd35yF4/ZvGTJzfCbt8Nk3uvA3VqzddMnB9/0RnOdec3SdLLCYrF0d5roGOXnHrHxDUYtPLrwNx38HbT6+2SNE1sEu06aNl/yN38dutC3KtSUgL8/w5DxMzc63GrR5yn1re9Kec4Eh8t/SWzsX8vA3MGc478pzDO7TCNjn5nupYVoQmUi+cwBumIzJy7Tl3/dYtLOxrga9waAPVzl+meNtLDnewKK/Fs83aQNhJudpE6Zj2AU+5dKBJuOkv3vAVPt9XBlvi2dlob2N98xAO47b361iBtoY9IPj2wy59x6D6w32Sjygrpynrf7uor8HZpTf89PJ76s2+d3OkN/vAC6TjXs1YlwKs75m0Bfa3TT5dxvdhfSQATKCK7iBO3hAJsgMWSArZIPs4Ak5ICd4QS7IDXkgL+SD/OANBeAVKAiFoDAUgaJQDIpDCSgJpeBVKA3lTXwJLIRFsBjiYAkstY85LIPlsAJWwipYDWtgLayDz2A9xMMG2AibdK62wOew1T6msB2+gC9hB+yEXbDbPjewF/bBfjgACXAQDsFhOAJH4Rh8BcfhBJyEU5AIp+EMnIUkOAfn4QJchEvwtV3GIBm+gStwFa7BdfjWFDkuZx8nqAAVoRJUhipQFapBdXg=
*/