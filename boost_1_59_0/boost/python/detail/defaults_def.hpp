///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002, Joel de Guzman, 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_PP_IS_ITERATING)

#ifndef DEFAULTS_DEF_JDG20020811_HPP
#define DEFAULTS_DEF_JDG20020811_HPP

#include <boost/python/detail/defaults_gen.hpp>
#include <boost/python/detail/type_traits.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/python/class_fwd.hpp>
#include <boost/python/scope.hpp>
#include <boost/preprocessor/debug/line.hpp>
#include <boost/python/detail/scope.hpp>
#include <boost/python/detail/make_keyword_range_fn.hpp>
#include <boost/python/object/add_to_namespace.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace python {

struct module;

namespace objects
{
  struct class_base;
}

namespace detail
{
  // Called as::
  //
  //    name_space_def(ns, "func", func, kw, policies, docstring, &ns)
  //
  // Dispatch to properly add f to namespace ns.
  //
  // @group define_stub_function helpers { 
  template <class Func, class CallPolicies, class NameSpaceT>
  static void name_space_def(
      NameSpaceT& name_space
      , char const* name
      , Func f
      , keyword_range const& kw
      , CallPolicies const& policies
      , char const* doc
      , objects::class_base*
      )
  {
      typedef typename NameSpaceT::wrapped_type wrapped_type;
      
      objects::add_to_namespace(
          name_space, name,
          detail::make_keyword_range_function(
              f, policies, kw, get_signature(f, (wrapped_type*)0))
        , doc
      );
  }

  template <class Func, class CallPolicies>
  static void name_space_def(
      object& name_space
      , char const* name
      , Func f
      , keyword_range const& kw
      , CallPolicies const& policies
      , char const* doc
      , ...
      )
  {
      scope within(name_space);

      detail::scope_setattr_doc(
          name
          , detail::make_keyword_range_function(f, policies, kw)
          , doc);
  }

  // For backward compatibility -- is this obsolete?
  template <class Func, class CallPolicies, class NameSpaceT>
  static void name_space_def(
      NameSpaceT& name_space
      , char const* name
      , Func f
      , keyword_range const& kw // ignored
      , CallPolicies const& policies
      , char const* doc
      , module*
      )
  {
      name_space.def(name, f, policies, doc);
  }
  // }


  //  Expansions of ::
  //
  //      template <typename OverloadsT, typename NameSpaceT>
  //      inline void
  //      define_stub_function(
  //          char const* name, OverloadsT s, NameSpaceT& name_space, mpl::int_<N>)
  //      {
  //          name_space.def(name, &OverloadsT::func_N);
  //      }
  //
  //  where N runs from 0 to BOOST_PYTHON_MAX_ARITY.
  //
  //  The set of overloaded functions (define_stub_function) expects:
  //
  //      1. char const* name:        function name that will be visible to python
  //      2. OverloadsT:              a function overloads struct (see defaults_gen.hpp)
  //      3. NameSpaceT& name_space:  a python::class_ or python::module instance
  //      4. int_t<N>:                the Nth overloaded function (OverloadsT::func_N)
  //                                  (see defaults_gen.hpp)
  //      5. char const* name:        doc string
  //
  // @group define_stub_function<N> {
  template <int N>
  struct define_stub_function {};

#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/defaults_def.hpp>))

#include BOOST_PP_ITERATE()
  
  // }
  
  //  This helper template struct does the actual recursive
  //  definition.  There's a generic version
  //  define_with_defaults_helper<N> and a terminal case
  //  define_with_defaults_helper<0>. The struct and its
  //  specialization has a sole static member function def that
  //  expects:
  //
  //    1. char const* name:        function name that will be
  //                                visible to python
  //
  //    2. OverloadsT:              a function overloads struct
  //                                (see defaults_gen.hpp)
  //
  //    3. NameSpaceT& name_space:  a python::class_ or
  //                                python::module instance
  //
  //    4. char const* name:        doc string
  //
  //  The def static member function calls a corresponding
  //  define_stub_function<N>. The general case recursively calls
  //  define_with_defaults_helper<N-1>::def until it reaches the
  //  terminal case case define_with_defaults_helper<0>.
  template <int N>
  struct define_with_defaults_helper {

      template <class StubsT, class CallPolicies, class NameSpaceT>
      static void
      def(
          char const* name,
          StubsT stubs,
          keyword_range kw,
          CallPolicies const& policies,
          NameSpaceT& name_space,
          char const* doc)
      {
          //  define the NTH stub function of stubs
          define_stub_function<N>::define(name, stubs, kw, policies, name_space, doc);

          if (kw.second > kw.first)
              --kw.second;

          //  call the next define_with_defaults_helper
          define_with_defaults_helper<N-1>::def(name, stubs, kw, policies, name_space, doc);
      }
  };

  template <>
  struct define_with_defaults_helper<0> {

      template <class StubsT, class CallPolicies, class NameSpaceT>
      static void
      def(
          char const* name,
          StubsT stubs,
          keyword_range const& kw,
          CallPolicies const& policies,
          NameSpaceT& name_space,
          char const* doc)
      {
          //  define the Oth stub function of stubs
          define_stub_function<0>::define(name, stubs, kw, policies, name_space, doc);
          //  return
      }
  };

  //  define_with_defaults
  //
  //      1. char const* name:        function name that will be
  //                                  visible to python
  //
  //      2. OverloadsT:              a function overloads struct
  //                                  (see defaults_gen.hpp)
  //
  //      3. CallPolicies& policies:  Call policies
  //      4. NameSpaceT& name_space:  a python::class_ or
  //                                  python::module instance
  //
  //      5. SigT sig:                Function signature typelist
  //                                  (see defaults_gen.hpp)
  //
  //      6. char const* name:        doc string
  //
  //  This is the main entry point. This function recursively
  //  defines all stub functions of StubT (see defaults_gen.hpp) in
  //  NameSpaceT name_space which can be either a python::class_ or
  //  a python::module. The sig argument is a typelist that
  //  specifies the return type, the class (for member functions,
  //  and the arguments. Here are some SigT examples:
  //
  //      int foo(int)        mpl::vector<int, int>
  //      void bar(int, int)  mpl::vector<void, int, int>
  //      void C::foo(int)    mpl::vector<void, C, int>
  //
  template <class OverloadsT, class NameSpaceT, class SigT>
  inline void
  define_with_defaults(
      char const* name,
      OverloadsT const& overloads,
      NameSpaceT& name_space,
      SigT const&)
  {
      typedef typename mpl::front<SigT>::type return_type;
      typedef typename OverloadsT::void_return_type void_return_type;
      typedef typename OverloadsT::non_void_return_type non_void_return_type;

      typedef typename mpl::if_c<
          is_same<void, return_type>::value
          , void_return_type
          , non_void_return_type
      >::type stubs_type;

      BOOST_STATIC_ASSERT(
          (stubs_type::max_args) <= mpl::size<SigT>::value);

      typedef typename stubs_type::template gen<SigT> gen_type;
      define_with_defaults_helper<stubs_type::n_funcs-1>::def(
          name
          , gen_type()
          , overloads.keywords()
          , overloads.call_policies()
          , name_space
          , overloads.doc_string());
  }

} // namespace detail

}} // namespace boost::python

#endif // DEFAULTS_DEF_JDG20020811_HPP

#else // defined(BOOST_PP_IS_ITERATING)
// PP vertical iteration code


template <>
struct define_stub_function<BOOST_PP_ITERATION()> {
    template <class StubsT, class CallPolicies, class NameSpaceT>
    static void define(
        char const* name
        , StubsT const&
        , keyword_range const& kw
        , CallPolicies const& policies
        , NameSpaceT& name_space
        , char const* doc)
    {
        detail::name_space_def(
            name_space
            , name
            , &StubsT::BOOST_PP_CAT(func_, BOOST_PP_ITERATION())
            , kw
            , policies
            , doc
            , &name_space);
    }
};

#endif // !defined(BOOST_PP_IS_ITERATING)

/* defaults_def.hpp
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
*/