// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Revision History:

// 04 Oct 2001   David Abrahams
//      Changed name of "bind" to "select" to avoid problems with MSVC.

#ifndef BOOST_DETAIL_NAMED_TEMPLATE_PARAMS_HPP
#define BOOST_DETAIL_NAMED_TEMPLATE_PARAMS_HPP

#include <boost/config.hpp>
#include <boost/type_traits/conversion_traits.hpp>
#include <boost/type_traits/composite_traits.hpp> // for is_reference
#if defined(BOOST_BORLANDC)
#include <boost/type_traits/ice.hpp>
#endif

namespace boost {
  namespace detail {
    
    struct default_argument { };

    struct dummy_default_gen {
      template <class Base, class Traits>
      struct select {
        typedef default_argument type;
      };
    };

   // This class template is a workaround for MSVC.
   template <class Gen> struct default_generator {
     typedef detail::dummy_default_gen type;
   };

    template <class T> struct is_default { 
      enum { value = false };  
      typedef type_traits::no_type type;
    };
    template <> struct is_default<default_argument> { 
      enum { value = true }; 
      typedef type_traits::yes_type type;
    };

    struct choose_default {
      template <class Arg, class DefaultGen, class Base, class Traits>
      struct select {
        typedef typename default_generator<DefaultGen>::type Gen;
        typedef typename Gen::template select<Base,Traits>::type type;
      };
    };
    struct choose_arg {
      template <class Arg, class DefaultGen, class Base, class Traits>
      struct select {
        typedef Arg type;
      };
    };

#if defined(BOOST_BORLANDC)
    template <class UseDefault>
    struct choose_arg_or_default { typedef choose_arg type; };
    template <>
    struct choose_arg_or_default<type_traits::yes_type> {
      typedef choose_default type;
    };
#else
    template <bool UseDefault>
    struct choose_arg_or_default { typedef choose_arg type; };
    template <>
    struct choose_arg_or_default<true> {
      typedef choose_default type;
    };
#endif
    
    template <class Arg, class DefaultGen, class Base, class Traits>
    class resolve_default {
#if defined(BOOST_BORLANDC)
      typedef typename choose_arg_or_default<typename is_default<Arg>::type>::type Selector;
#else
      // This usually works for Borland, but I'm seeing weird errors in
      // iterator_adaptor_test.cpp when using this method.
      enum { is_def = is_default<Arg>::value };
      typedef typename choose_arg_or_default<is_def>::type Selector;
#endif
    public:
      typedef typename Selector
        ::template select<Arg, DefaultGen, Base, Traits>::type type;
    };

    // To differentiate an unnamed parameter from a traits generator
    // we use is_convertible<X, iter_traits_gen_base>.
    struct named_template_param_base { };

    template <class X>
    struct is_named_param_list {
      enum { value  = is_convertible<X, named_template_param_base>::value };
    };
    
    struct choose_named_params {
      template <class Prev> struct select { typedef Prev type; };
    };
    struct choose_default_arg {
      template <class Prev> struct select { 
        typedef detail::default_argument type;
      };
    };

    template <bool Named> struct choose_default_dispatch_;
    template <> struct choose_default_dispatch_<true> {
      typedef choose_named_params type;
    };
    template <> struct choose_default_dispatch_<false> {
      typedef choose_default_arg type;
    };
    // The use of inheritance here is a Solaris Forte 6 workaround.
    template <bool Named> struct choose_default_dispatch
      : public choose_default_dispatch_<Named> { };

    template <class PreviousArg>
    struct choose_default_argument {
      enum { is_named = is_named_param_list<PreviousArg>::value };
      typedef typename choose_default_dispatch<is_named>::type Selector;
      typedef typename Selector::template select<PreviousArg>::type type;
    };

    // This macro assumes that there is a class named default_##TYPE
    // defined before the application of the macro.  This class should
    // have a single member class template named "select" with two
    // template parameters: the type of the class being created (e.g.,
    // the iterator_adaptor type when creating iterator adaptors) and
    // a traits class. The select class should have a single typedef
    // named "type" that produces the default for TYPE.  See
    // boost/iterator_adaptors.hpp for an example usage.  Also,
    // applications of this macro must be placed in namespace
    // boost::detail.

#define BOOST_NAMED_TEMPLATE_PARAM(TYPE) \
    struct get_##TYPE##_from_named { \
      template <class Base, class NamedParams, class Traits> \
      struct select { \
          typedef typename NamedParams::traits NamedTraits; \
          typedef typename NamedTraits::TYPE TYPE; \
          typedef typename resolve_default<TYPE, \
            default_##TYPE, Base, NamedTraits>::type type; \
      }; \
    }; \
    struct pass_thru_##TYPE { \
      template <class Base, class Arg, class Traits> struct select { \
          typedef typename resolve_default<Arg, \
            default_##TYPE, Base, Traits>::type type; \
      };\
    }; \
    template <int NamedParam> \
    struct get_##TYPE##_dispatch { }; \
    template <> struct get_##TYPE##_dispatch<1> { \
      typedef get_##TYPE##_from_named type; \
    }; \
    template <> struct get_##TYPE##_dispatch<0> { \
      typedef pass_thru_##TYPE type; \
    }; \
    template <class Base, class X, class Traits>  \
    class get_##TYPE { \
      enum { is_named = is_named_param_list<X>::value }; \
      typedef typename get_##TYPE##_dispatch<is_named>::type Selector; \
    public: \
      typedef typename Selector::template select<Base, X, Traits>::type type; \
    }; \
    template <> struct default_generator<default_##TYPE> { \
      typedef default_##TYPE type; \
    }

    
  } // namespace detail
} // namespace boost

#endif // BOOST_DETAIL_NAMED_TEMPLATE_PARAMS_HPP

/* named_template_params.hpp
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
*/