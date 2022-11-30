// Copyright David Abrahams 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef MAKE_FUNCTION_DWA20011221_HPP
# define MAKE_FUNCTION_DWA20011221_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/default_call_policies.hpp>
# include <boost/python/args.hpp>
# include <boost/python/detail/caller.hpp>

# include <boost/python/object/function_object.hpp>

# include <boost/mpl/size.hpp>
# include <boost/mpl/int.hpp>

namespace boost { namespace python {

namespace detail
{
  // make_function_aux --
  //
  // These helper functions for make_function (below) do the raw work
  // of constructing a Python object from some invokable entity. See
  // <boost/python/detail/caller.hpp> for more information about how
  // the Sig arguments is used.
  template <class F, class CallPolicies, class Sig>
  object make_function_aux(
      F f                               // An object that can be invoked by detail::invoke()
      , CallPolicies const& p           // CallPolicies to use in the invocation
      , Sig const&                      // An MPL sequence of argument types expected by F
      )
  {
      return objects::function_object(
          detail::caller<F,CallPolicies,Sig>(f, p)
      );
  }

  // As above, except that it accepts argument keywords. NumKeywords
  // is used only for a compile-time assertion to make sure the user
  // doesn't pass more keywords than the function can accept. To
  // disable all checking, pass mpl::int_<0> for NumKeywords.
  template <class F, class CallPolicies, class Sig, class NumKeywords>
  object make_function_aux(
      F f
      , CallPolicies const& p
      , Sig const&
      , detail::keyword_range const& kw // a [begin,end) pair of iterators over keyword names
      , NumKeywords                     // An MPL integral type wrapper: the size of kw
      )
  {
      enum { arity = mpl::size<Sig>::value - 1 };
      
      typedef typename detail::error::more_keywords_than_function_arguments<
          NumKeywords::value, arity
          >::too_many_keywords assertion BOOST_ATTRIBUTE_UNUSED;
    
      return objects::function_object(
          detail::caller<F,CallPolicies,Sig>(f, p)
        , kw);
  }

  //   Helpers for make_function when called with 3 arguments.  These
  //   dispatch functions are used to discriminate between the cases
  //   when the 3rd argument is keywords or when it is a signature.
  //
  // @group {
  template <class F, class CallPolicies, class Keywords>
  object make_function_dispatch(F f, CallPolicies const& policies, Keywords const& kw, mpl::true_)
  {
      return detail::make_function_aux(
          f
        , policies
        , detail::get_signature(f)
        , kw.range()
        , mpl::int_<Keywords::size>()
      );
  }

  template <class F, class CallPolicies, class Signature>
  object make_function_dispatch(F f, CallPolicies const& policies, Signature const& sig, mpl::false_)
  {
      return detail::make_function_aux(
          f
        , policies
        , sig
      );
  }
  // }
  
 }

//   These overloaded functions wrap a function or member function
//   pointer as a Python object, using optional CallPolicies,
//   Keywords, and/or Signature.
//
//   @group {
template <class F>
object make_function(F f)
{
    return detail::make_function_aux(
        f,default_call_policies(), detail::get_signature(f));
}

template <class F, class CallPolicies>
object make_function(F f, CallPolicies const& policies)
{
    return detail::make_function_aux(
        f, policies, detail::get_signature(f));
}

template <class F, class CallPolicies, class KeywordsOrSignature>
object make_function(
    F f
  , CallPolicies const& policies
  , KeywordsOrSignature const& keywords_or_signature)
{
    typedef typename
        detail::is_reference_to_keywords<KeywordsOrSignature&>::type
        is_kw;
    
    return detail::make_function_dispatch(
        f
      , policies
      , keywords_or_signature
      , is_kw()
    );
}

template <class F, class CallPolicies, class Keywords, class Signature>
object make_function(
    F f
  , CallPolicies const& policies
  , Keywords const& kw
  , Signature const& sig
 )
{
    return detail::make_function_aux(
          f
        , policies
        , sig
        , kw.range()
        , mpl::int_<Keywords::size>()
      );
}
// }

}} 


#endif // MAKE_FUNCTION_DWA20011221_HPP

/* make_function.hpp
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
*/