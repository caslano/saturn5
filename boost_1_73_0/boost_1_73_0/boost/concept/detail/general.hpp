// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_GENERAL_DWA2006429_HPP
# define BOOST_CONCEPT_DETAIL_GENERAL_DWA2006429_HPP

# include <boost/config.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept/detail/has_constraints.hpp>
#  include <boost/type_traits/conditional.hpp>
# endif

// This implementation works on Comeau and GCC, all the way back to
// 2.95
namespace boost { namespace concepts {

template <class ModelFn>
struct requirement_;

namespace detail
{
  template <void(*)()> struct instantiate {};
}

template <class Model>
struct requirement
{
    static void failed() { ((Model*)0)->~Model(); }
};

struct failed {};

template <class Model>
struct requirement<failed ************ Model::************>
{
    static void failed() { ((Model*)0)->~Model(); }
};

# ifdef BOOST_OLD_CONCEPT_SUPPORT

template <class Model>
struct constraint
{
    static void failed() { ((Model*)0)->constraints(); }
};
  
template <class Model>
struct requirement_<void(*)(Model)>
  : boost::conditional<
        concepts::not_satisfied<Model>::value
      , constraint<Model>
      , requirement<failed ************ Model::************>
    >::type
{};
  
# else

// For GCC-2.x, these can't have exactly the same name
template <class Model>
struct requirement_<void(*)(Model)>
    : requirement<failed ************ Model::************>
{};
  
# endif

#  define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )             \
    typedef ::boost::concepts::detail::instantiate<          \
    &::boost::concepts::requirement_<ModelFnPtr>::failed>    \
      BOOST_PP_CAT(boost_concept_check,__LINE__)             \
      BOOST_ATTRIBUTE_UNUSED

}}

#endif // BOOST_CONCEPT_DETAIL_GENERAL_DWA2006429_HPP

/* general.hpp
GfXTqqCe5O2WmhlgSdMinnpPel7Pcfq7iaNn3pFlNxuG57MJvO+Pz4fOjBv8maBt+oeRf0aZJtnvCDfYPKl/gtQbzydnE//DJPLtBUFGKKq6MbSC4RD648DH+/HV7Ha9QQv7MKr5liC2C84/UEsDBAoAAAAIAC1nSlKJsLg6+AQAAMsKAAA4AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fQ09ORElUSU9OX1VOTUVULjNVVAUAAbZIJGCtVe9znDYQ/c5fsaXT9uzBnC92Jj+blpzPNc0Zbg6c1DM3w+hAGDWAqCTsuE3+964k7hzbycQfgucMSNp9q6f3Fn/lwu53uxxfp4NvXpn5ZXjhfRO0EPxvmqsvB2TZR7B/GLjC+wOgxnAT9THbgQdFfYSRicoGrJf6OcseALfSRep/Yx28yvQjjtjIIX7Ku2vBLioFo+kOTJ49ewp78Gj/0b4HR6RltIZE0XZNxYUHLwsz8ntFPnzwJX3lAVVAav9WwrRiEiQv1RURFPC5ZjltJS2ASCiozAVb4wtrQVUUSlZTmMaL8zD6w4OriuXVkOea9yAr3tcFVOSSgqA5ZZc2TUeEAl5iBsxfMKkwZ68Yb32Ep6CoaOSQRhdBasmBXBJW
*/