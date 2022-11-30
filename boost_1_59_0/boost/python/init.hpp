///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002, Joel de Guzman, 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////
#ifndef INIT_JDG20020820_HPP
#define INIT_JDG20020820_HPP

# include <boost/python/detail/prefix.hpp>

#include <boost/python/detail/type_list.hpp>
#include <boost/python/args_fwd.hpp>
#include <boost/python/detail/make_keyword_range_fn.hpp>
#include <boost/python/def_visitor.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/back.hpp>

#include <boost/python/detail/type_traits.hpp>

#include <boost/preprocessor/enum_params_with_a_default.hpp>
#include <boost/preprocessor/enum_params.hpp>

#include <utility>

///////////////////////////////////////////////////////////////////////////////
#define BOOST_PYTHON_OVERLOAD_TYPES_WITH_DEFAULT                                \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(                                        \
        BOOST_PYTHON_MAX_ARITY,                                                 \
        class T,                                                                \
        mpl::void_)                                                             \

#define BOOST_PYTHON_OVERLOAD_TYPES                                             \
    BOOST_PP_ENUM_PARAMS_Z(1,                                                   \
        BOOST_PYTHON_MAX_ARITY,                                                 \
        class T)                                                                \

#define BOOST_PYTHON_OVERLOAD_ARGS                                              \
    BOOST_PP_ENUM_PARAMS_Z(1,                                                   \
        BOOST_PYTHON_MAX_ARITY,                                                 \
        T)                                                                      \

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace python {

template <BOOST_PYTHON_OVERLOAD_TYPES_WITH_DEFAULT>
class init; // forward declaration


template <BOOST_PYTHON_OVERLOAD_TYPES_WITH_DEFAULT>
struct optional; // forward declaration

namespace detail
{
  namespace error
  {
    template <int keywords, int init_args>
    struct more_keywords_than_init_arguments
    {
        typedef char too_many_keywords[init_args - keywords >= 0 ? 1 : -1] BOOST_ATTRIBUTE_UNUSED;
    };
  }

  //  is_optional<T>::value
  //
  //      This metaprogram checks if T is an optional
  //

    template <class T>
    struct is_optional
      : mpl::false_
    {};

    template <BOOST_PYTHON_OVERLOAD_TYPES>
    struct is_optional<optional<BOOST_PYTHON_OVERLOAD_ARGS> >
      : mpl::true_
    {};
  

  template <int NDefaults>
  struct define_class_init_helper;

} // namespace detail

template <class DerivedT>
struct init_base : def_visitor<DerivedT>
{
    init_base(char const* doc_, detail::keyword_range const& keywords_)
        : m_doc(doc_), m_keywords(keywords_)
    {}
        
    init_base(char const* doc_)
        : m_doc(doc_)
    {}

    DerivedT const& derived() const
    {
        return *static_cast<DerivedT const*>(this);
    }
    
    char const* doc_string() const
    {
        return m_doc;
    }

    detail::keyword_range const& keywords() const
    {
        return m_keywords;
    }

    static default_call_policies call_policies()
    {
        return default_call_policies();
    }

 private:
    //  visit
    //
    //      Defines a set of n_defaults + 1 constructors for its
    //      class_<...> argument. Each constructor after the first has
    //      one less argument to its right. Example:
    //
    //          init<int, optional<char, long, double> >
    //
    //      Defines:
    //
    //          __init__(int, char, long, double)
    //          __init__(int, char, long)
    //          __init__(int, char)
    //          __init__(int)
    template <class classT>
    void visit(classT& cl) const
    {
        typedef typename DerivedT::signature signature;
        typedef typename DerivedT::n_arguments n_arguments;
        typedef typename DerivedT::n_defaults n_defaults;
    
        detail::define_class_init_helper<n_defaults::value>::apply(
            cl
          , derived().call_policies()
          , signature()
          , n_arguments()
          , derived().doc_string()
          , derived().keywords());
    }
    
    friend class python::def_visitor_access;
    
 private: // data members
    char const* m_doc;
    detail::keyword_range m_keywords;
};

template <class CallPoliciesT, class InitT>
class init_with_call_policies
    : public init_base<init_with_call_policies<CallPoliciesT, InitT> >
{
    typedef init_base<init_with_call_policies<CallPoliciesT, InitT> > base;
 public:
    typedef typename InitT::n_arguments n_arguments;
    typedef typename InitT::n_defaults n_defaults;
    typedef typename InitT::signature signature;

    init_with_call_policies(
        CallPoliciesT const& policies_
        , char const* doc_
        , detail::keyword_range const& keywords
        )
        : base(doc_, keywords)
        , m_policies(policies_)
    {}

    CallPoliciesT const& call_policies() const
    {
        return this->m_policies;
    }
    
 private: // data members
    CallPoliciesT m_policies;
};

//
// drop1<S> is the initial length(S) elements of S
//
namespace detail
{
  template <class S>
  struct drop1
    : mpl::iterator_range<
          typename mpl::begin<S>::type
        , typename mpl::prior<
              typename mpl::end<S>::type
          >::type
      >
  {};
}

template <BOOST_PYTHON_OVERLOAD_TYPES>
class init : public init_base<init<BOOST_PYTHON_OVERLOAD_ARGS> >
{
    typedef init_base<init<BOOST_PYTHON_OVERLOAD_ARGS> > base;
 public:
    typedef init<BOOST_PYTHON_OVERLOAD_ARGS> self_t;

    init(char const* doc_ = 0)
        : base(doc_)
    {
    }

    template <std::size_t N>
    init(char const* doc_, detail::keywords<N> const& kw)
        : base(doc_, kw.range())
    {
        typedef typename detail::error::more_keywords_than_init_arguments<
            N, n_arguments::value + 1
            >::too_many_keywords assertion BOOST_ATTRIBUTE_UNUSED;
    }

    template <std::size_t N>
    init(detail::keywords<N> const& kw, char const* doc_ = 0)
        : base(doc_, kw.range())
    {
        typedef typename detail::error::more_keywords_than_init_arguments<
            N, n_arguments::value + 1
            >::too_many_keywords assertion BOOST_ATTRIBUTE_UNUSED;
    }

    template <class CallPoliciesT>
    init_with_call_policies<CallPoliciesT, self_t>
    operator[](CallPoliciesT const& policies) const
    {
        return init_with_call_policies<CallPoliciesT, self_t>(
            policies, this->doc_string(), this->keywords());
    }

    typedef detail::type_list<BOOST_PYTHON_OVERLOAD_ARGS> signature_;

    typedef detail::is_optional<
        typename mpl::eval_if<
            mpl::empty<signature_>
          , mpl::false_
          , mpl::back<signature_>
        >::type
    > back_is_optional;
    
    typedef typename mpl::eval_if<
        back_is_optional
      , mpl::back<signature_>
      , mpl::vector0<>
    >::type optional_args;

    typedef typename mpl::eval_if<
        back_is_optional
      , mpl::if_<
            mpl::empty<optional_args>
          , detail::drop1<signature_>
          , mpl::joint_view<
                detail::drop1<signature_>
              , optional_args
            >
        >
      , signature_
    >::type signature;

    // TODO: static assert to make sure there are no other optional elements

    // Count the number of default args
    typedef mpl::size<optional_args> n_defaults;
    typedef mpl::size<signature> n_arguments;
};

///////////////////////////////////////////////////////////////////////////////
//
//  optional
//
//      optional<T0...TN>::type returns a typelist.
//
///////////////////////////////////////////////////////////////////////////////
template <BOOST_PYTHON_OVERLOAD_TYPES>
struct optional
    : detail::type_list<BOOST_PYTHON_OVERLOAD_ARGS>
{
};

namespace detail
{
  template <class ClassT, class CallPoliciesT, class Signature, class NArgs>
  inline void def_init_aux(
      ClassT& cl
      , Signature const&
      , NArgs
      , CallPoliciesT const& policies
      , char const* doc
      , detail::keyword_range const& keywords_
      )
  {
      cl.def(
          "__init__"
        , detail::make_keyword_range_constructor<Signature,NArgs>(
              policies
            , keywords_
            , (typename ClassT::metadata::holder*)0
          )
        , doc
      );
  }

  ///////////////////////////////////////////////////////////////////////////////
  //
  //  define_class_init_helper<N>::apply
  //
  //      General case
  //
  //      Accepts a class_ and an arguments list. Defines a constructor
  //      for the class given the arguments and recursively calls
  //      define_class_init_helper<N-1>::apply with one fewer argument (the
  //      rightmost argument is shaved off)
  //
  ///////////////////////////////////////////////////////////////////////////////
  template <int NDefaults>
  struct define_class_init_helper
  {

      template <class ClassT, class CallPoliciesT, class Signature, class NArgs>
      static void apply(
          ClassT& cl
          , CallPoliciesT const& policies
          , Signature const& args
          , NArgs
          , char const* doc
          , detail::keyword_range keywords)
      {
          detail::def_init_aux(cl, args, NArgs(), policies, doc, keywords);

          if (keywords.second > keywords.first)
              --keywords.second;

          typedef typename mpl::prior<NArgs>::type next_nargs;
          define_class_init_helper<NDefaults-1>::apply(
              cl, policies, Signature(), next_nargs(), doc, keywords);
      }
  };

  ///////////////////////////////////////////////////////////////////////////////
  //
  //  define_class_init_helper<0>::apply
  //
  //      Terminal case
  //
  //      Accepts a class_ and an arguments list. Defines a constructor
  //      for the class given the arguments.
  //
  ///////////////////////////////////////////////////////////////////////////////
  template <>
  struct define_class_init_helper<0> {

      template <class ClassT, class CallPoliciesT, class Signature, class NArgs>
      static void apply(
          ClassT& cl
        , CallPoliciesT const& policies
        , Signature const& args
        , NArgs
        , char const* doc
        , detail::keyword_range const& keywords)
      {
          detail::def_init_aux(cl, args, NArgs(), policies, doc, keywords);
      }
  };
}

}} // namespace boost::python

#undef BOOST_PYTHON_OVERLOAD_TYPES_WITH_DEFAULT
#undef BOOST_PYTHON_OVERLOAD_TYPES
#undef BOOST_PYTHON_OVERLOAD_ARGS
#undef BOOST_PYTHON_IS_OPTIONAL_VALUE
#undef BOOST_PYTHON_APPEND_TO_INIT

///////////////////////////////////////////////////////////////////////////////
#endif // INIT_JDG20020820_HPP









/* init.hpp
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
*/