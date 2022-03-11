// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Revision History:

// 04 Oct 2001   David Abrahams
//      Changed name of "bind" to "select" to avoid problems with MSVC.

#ifndef BOOST_DETAIL_NAMED_TEMPLATE_PARAMS_HPP
#define BOOST_DETAIL_NAMED_TEMPLATE_PARAMS_HPP

#include <boost/type_traits/conversion_traits.hpp>
#include <boost/type_traits/composite_traits.hpp> // for is_reference
#if defined(__BORLANDC__)
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

#if defined(__BORLANDC__)
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
#if defined(__BORLANDC__)
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