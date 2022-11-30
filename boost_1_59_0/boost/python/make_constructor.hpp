// Copyright David Abrahams 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef MAKE_CONSTRUCTOR_DWA20011221_HPP
# define MAKE_CONSTRUCTOR_DWA20011221_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/default_call_policies.hpp>
# include <boost/python/args.hpp>
# include <boost/python/object_fwd.hpp>

# include <boost/python/object/function_object.hpp>
# include <boost/python/object/make_holder.hpp>
# include <boost/python/object/pointer_holder.hpp>
# include <boost/python/converter/context_result_converter.hpp>

# include <boost/python/detail/caller.hpp>
# include <boost/python/detail/none.hpp>

# include <boost/mpl/size.hpp>
# include <boost/mpl/int.hpp>
# include <boost/mpl/push_front.hpp>
# include <boost/mpl/pop_front.hpp>
# include <boost/mpl/assert.hpp>

namespace boost { namespace python {

namespace detail
{
  template <class T>
  struct install_holder : converter::context_result_converter
  {
      install_holder(PyObject* args_)
        : m_self(PyTuple_GetItem(args_, 0)) {}

      PyObject* operator()(T x) const
      {
          dispatch(x, is_pointer<T>());
          return none();
      }

   private:
      template <class U>
      void dispatch(U* x, detail::true_) const
      {
#if defined(BOOST_NO_CXX11_SMART_PTR)
	std::auto_ptr<U> owner(x);
	dispatch(owner, detail::false_());
#else
	std::unique_ptr<U> owner(x);
	dispatch(std::move(owner), detail::false_());
#endif
      }
      
      template <class Ptr>
      void dispatch(Ptr x, detail::false_) const
      {
          typedef typename pointee<Ptr>::type value_type;
          typedef objects::pointer_holder<Ptr,value_type> holder;
          typedef objects::instance<holder> instance_t;

          void* memory = holder::allocate(this->m_self, offsetof(instance_t, storage), sizeof(holder));
          try {
#if defined(BOOST_NO_CXX11_SMART_PTR)
              (new (memory) holder(x))->install(this->m_self);
#else
              (new (memory) holder(std::move(x)))->install(this->m_self);
#endif
          }
          catch(...) {
              holder::deallocate(this->m_self, memory);
              throw;
          }
      }
      
      PyObject* m_self;
  };
  
  struct constructor_result_converter
  {
      template <class T>
      struct apply
      {
          typedef install_holder<T> type;
      };
  };

  template <class BaseArgs, class Offset>
  struct offset_args
  {
      offset_args(BaseArgs base_) : base(base_) {}
      BaseArgs base;
  };

  template <int N, class BaseArgs, class Offset>
  inline PyObject* get(mpl::int_<N>, offset_args<BaseArgs,Offset> const& args_)
  {
      return get(mpl::int_<(N+Offset::value)>(), args_.base);
  }
  
  template <class BaseArgs, class Offset>
  inline unsigned arity(offset_args<BaseArgs,Offset> const& args_)
  {
      return arity(args_.base) - Offset::value;
  }

  template <class BasePolicy_ = default_call_policies>
  struct constructor_policy : BasePolicy_
  {
      constructor_policy(BasePolicy_ base) : BasePolicy_(base) {}
      
      // If the BasePolicy_ supplied a result converter it would be
      // ignored; issue an error if it's not the default.
      BOOST_MPL_ASSERT_MSG(
         (is_same<
              typename BasePolicy_::result_converter
            , default_result_converter
          >::value)
        , MAKE_CONSTRUCTOR_SUPPLIES_ITS_OWN_RESULT_CONVERTER_THAT_WOULD_OVERRIDE_YOURS
        , (typename BasePolicy_::result_converter)
      );
      typedef constructor_result_converter result_converter;
      typedef offset_args<typename BasePolicy_::argument_package, mpl::int_<1> > argument_package;
  };

  template <class InnerSignature>
  struct outer_constructor_signature
  {
      typedef typename mpl::pop_front<InnerSignature>::type inner_args;
      typedef typename mpl::push_front<inner_args,object>::type outer_args;
      typedef typename mpl::push_front<outer_args,void>::type type;
  };

  // ETI workaround
  template <>
  struct outer_constructor_signature<int>
  {
      typedef int type;
  };
  
  //
  // These helper functions for make_constructor (below) do the raw work
  // of constructing a Python object from some invokable entity. See
  // <boost/python/detail/caller.hpp> for more information about how
  // the Sig arguments is used.
  //
  // @group make_constructor_aux {
  template <class F, class CallPolicies, class Sig>
  object make_constructor_aux(
      F f                             // An object that can be invoked by detail::invoke()
    , CallPolicies const& p           // CallPolicies to use in the invocation
    , Sig const&                      // An MPL sequence of argument types expected by F
  )
  {
      typedef typename outer_constructor_signature<Sig>::type outer_signature;

      typedef constructor_policy<CallPolicies> inner_policy;
      
      return objects::function_object(
          objects::py_function(
              detail::caller<F,inner_policy,Sig>(f, inner_policy(p))
            , outer_signature()
          )
      );
  }
  
  // As above, except that it accepts argument keywords. NumKeywords
  // is used only for a compile-time assertion to make sure the user
  // doesn't pass more keywords than the function can accept. To
  // disable all checking, pass mpl::int_<0> for NumKeywords.
  template <class F, class CallPolicies, class Sig, class NumKeywords>
  object make_constructor_aux(
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
    
      typedef typename outer_constructor_signature<Sig>::type outer_signature;

      typedef constructor_policy<CallPolicies> inner_policy;
      
      return objects::function_object(
          objects::py_function(
              detail::caller<F,inner_policy,Sig>(f, inner_policy(p))
            , outer_signature()
          )
          , kw
      );
  }
  // }

  //
  //   These dispatch functions are used to discriminate between the
  //   cases when the 3rd argument is keywords or when it is a
  //   signature.
  //
  //   @group Helpers for make_constructor when called with 3 arguments. {
  //
  template <class F, class CallPolicies, class Keywords>
  object make_constructor_dispatch(F f, CallPolicies const& policies, Keywords const& kw, mpl::true_)
  {
      return detail::make_constructor_aux(
          f
        , policies
        , detail::get_signature(f)
        , kw.range()
        , mpl::int_<Keywords::size>()
      );
  }

  template <class F, class CallPolicies, class Signature>
  object make_constructor_dispatch(F f, CallPolicies const& policies, Signature const& sig, mpl::false_)
  {
      return detail::make_constructor_aux(
          f
        , policies
        , sig
      );
  }
  // }
}

//   These overloaded functions wrap a function or member function
//   pointer as a Python object, using optional CallPolicies,
//   Keywords, and/or Signature. @group {
//
template <class F>
object make_constructor(F f)
{
    return detail::make_constructor_aux(
        f,default_call_policies(), detail::get_signature(f));
}

template <class F, class CallPolicies>
object make_constructor(F f, CallPolicies const& policies)
{
    return detail::make_constructor_aux(
        f, policies, detail::get_signature(f));
}

template <class F, class CallPolicies, class KeywordsOrSignature>
object make_constructor(
    F f
  , CallPolicies const& policies
  , KeywordsOrSignature const& keywords_or_signature)
{
    typedef typename
        detail::is_reference_to_keywords<KeywordsOrSignature&>::type
        is_kw;
    
    return detail::make_constructor_dispatch(
        f
      , policies
      , keywords_or_signature
      , is_kw()
    );
}

template <class F, class CallPolicies, class Keywords, class Signature>
object make_constructor(
    F f
  , CallPolicies const& policies
  , Keywords const& kw
  , Signature const& sig
 )
{
    return detail::make_constructor_aux(
          f
        , policies
        , sig
        , kw.range()
        , mpl::int_<Keywords::size>()
      );
}
// }

}} 


#endif // MAKE_CONSTRUCTOR_DWA20011221_HPP

/* make_constructor.hpp
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
*/