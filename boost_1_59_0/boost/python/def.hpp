// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef DEF_DWA200292_HPP
# define DEF_DWA200292_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/object_fwd.hpp>
# include <boost/python/make_function.hpp>
# include <boost/python/detail/def_helper.hpp>
# include <boost/python/detail/overloads_fwd.hpp>
# include <boost/python/scope.hpp>
# include <boost/python/signature.hpp>
# include <boost/python/detail/scope.hpp>

namespace boost { namespace python {

namespace detail
{
  namespace error
  {
    // Compile-time error messages
    template <bool> struct multiple_functions_passed_to_def;
    template <> struct multiple_functions_passed_to_def<false> { typedef char type; };
  }
  
  //
  // def_from_helper --
  //
  // Use a def_helper to define a regular wrapped function in the current scope.
  template <class F, class Helper>
  void def_from_helper(
      char const* name, F const& fn, Helper const& helper)
  {
      // Must not try to use default implementations except with method definitions.
      typedef typename error::multiple_functions_passed_to_def<
          Helper::has_default_implementation
          >::type assertion BOOST_ATTRIBUTE_UNUSED;
      
      detail::scope_setattr_doc(
          name, boost::python::make_function(
              fn
              , helper.policies()
              , helper.keywords())
          , helper.doc()
          );
  }

  //
  // These two overloads discriminate between def() as applied to
  // regular functions and def() as applied to the result of
  // BOOST_PYTHON_FUNCTION_OVERLOADS(). The final argument is used to
  // discriminate.
  //
  template <class Fn, class A1>
  void
  def_maybe_overloads(
      char const* name
      , Fn fn
      , A1 const& a1
      , ...)
  {
      detail::def_from_helper(name, fn, def_helper<A1>(a1));
  }

  template <class StubsT, class SigT>
  void def_maybe_overloads(
      char const* name
      , SigT sig
      , StubsT const& stubs
      , detail::overloads_base const*)
  {
      scope current;
      
      detail::define_with_defaults(
          name, stubs, current, detail::get_signature(sig));
  }

  template <class T>
  object make_function1(T fn, ...) { return make_function(fn); }

  inline
  object make_function1(object const& x, object const*) { return x; }
}

template <class Fn>
void def(char const* name, Fn fn)
{
    detail::scope_setattr_doc(name, detail::make_function1(fn, &fn), 0);
}

template <class Arg1T, class Arg2T>
void def(char const* name, Arg1T arg1, Arg2T const& arg2)
{
    detail::def_maybe_overloads(name, arg1, arg2, &arg2);
}

template <class F, class A1, class A2>
void def(char const* name, F f, A1 const& a1, A2 const& a2)
{
    detail::def_from_helper(name, f, detail::def_helper<A1,A2>(a1,a2));
}

template <class F, class A1, class A2, class A3>
void def(char const* name, F f, A1 const& a1, A2 const& a2, A3 const& a3)
{
    detail::def_from_helper(name, f, detail::def_helper<A1,A2,A3>(a1,a2,a3));
}

}} // namespace boost::python

#endif // DEF_DWA200292_HPP

/* def.hpp
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
*/