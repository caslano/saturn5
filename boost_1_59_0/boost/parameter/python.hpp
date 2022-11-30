// Copyright Daniel Wallin 2006. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_PYTHON_060209_HPP
# define BOOST_PARAMETER_PYTHON_060209_HPP

# include <boost/mpl/vector.hpp>
# include <boost/mpl/fold.hpp>
# include <boost/mpl/prior.hpp>
# include <boost/mpl/shift_right.hpp>
# include <boost/mpl/shift_left.hpp>
# include <boost/mpl/bitand.hpp>
# include <boost/mpl/pair.hpp>
# include <boost/mpl/size.hpp>
# include <boost/mpl/push_back.hpp>
# include <boost/mpl/or.hpp>
# include <boost/mpl/count_if.hpp>
# include <boost/mpl/transform.hpp>
# include <boost/mpl/front.hpp>
# include <boost/mpl/iterator_range.hpp>
# include <boost/mpl/next.hpp>
# include <boost/mpl/begin_end.hpp>
# include <boost/mpl/not.hpp>
# include <boost/mpl/empty.hpp>
# include <boost/python/def.hpp>
# include <boost/python/make_constructor.hpp>
# include <boost/python/init.hpp>
# include <boost/python/to_python_converter.hpp>
# include <boost/parameter/aux_/maybe.hpp>
# include <boost/parameter/aux_/python/invoker.hpp>

namespace boost { namespace parameter { namespace python 
{
  namespace python_ = boost::python;
}}}

namespace boost { namespace parameter { namespace python { namespace aux 
{

  inline PyObject* unspecified_type()
  {
      static PyTypeObject unspecified = {
          PyVarObject_HEAD_INIT(NULL,0)
          "Boost.Parameter.Unspecified",    /* tp_name        */
          PyType_Type.tp_basicsize,         /* tp_basicsize   */
          0,                                /* tp_itemsize    */
          0,                                /* tp_dealloc     */
          0,                                /* tp_print       */
          0,                                /* tp_getattr     */
          0,                                /* tp_setattr     */
          0,                                /* tp_compare     */
          0,                                /* tp_repr        */
          0,                                /* tp_as_number   */
          0,                                /* tp_as_sequence */
          0,                                /* tp_as_mapping  */
          0,                                /* tp_hash        */
          0,                                /* tp_call        */
          0,                                /* tp_str         */
          0,                                /* tp_getattro    */
          0,                                /* tp_setattro    */
          0,                                /* tp_as_buffer   */
          Py_TPFLAGS_DEFAULT,               /* tp_flags       */
          0,                                /* tp_doc         */
      };
      
      if (Py_TYPE(&unspecified) == 0)
      {
          Py_TYPE(&unspecified) = &PyType_Type;
          PyType_Ready(&unspecified);
      }
      
      return (PyObject*)&unspecified;
  }

  struct empty_tag {};

  struct empty_tag_to_python
  {
      static PyObject* convert(empty_tag)
      {
          return python_::xincref(unspecified_type());
      }
  };

}}}} // namespace boost::parameter::python::aux

namespace boost { namespace python 
{

  // Converts a Python value to a maybe<T>
  template <class T>
  struct arg_from_python<parameter::aux::maybe<T> >
    : arg_from_python<T>
  {
      arg_from_python(PyObject* p)
        : arg_from_python<T>(p)
        , empty(parameter::python::aux::unspecified_type() == p)
      {}

      bool convertible() const
      {
          return empty || arg_from_python<T>::convertible();
      }

      parameter::aux::maybe<T> operator()()
      {
          if (empty)
          {
              return parameter::aux::maybe<T>();
          }
          else
          {
              return parameter::aux::maybe<T>(
                  arg_from_python<T>::operator()()
              );
          }
      }

      bool empty;
  };

}} // namespace boost::python

namespace boost { namespace parameter { namespace python {

namespace aux
{

  template <class K>
  struct is_optional
    : mpl::not_<
          mpl::or_<typename K::required, typename K::optimized_default>
      >
  {};

  template <class K, class Required, class Optimized, class T>
  struct arg_spec
  {
      typedef K keyword;
      typedef Required required;
      typedef T type;
      typedef Optimized optimized_default;
  };
  
  template <class K, class T, class Optimized = mpl::false_>
  struct make_arg_spec_impl
  {
      typedef arg_spec<
          typename K::first, typename K::second, Optimized, T
      > type;
  };

  template <class K, class T>
  struct make_arg_spec_impl<K, T, typename K::third>
  {
      typedef arg_spec<
          typename K::first, typename K::second, typename K::third, T
      > type;
  };

  template <class K, class T>
  struct make_arg_spec
    : make_arg_spec_impl<K, T>
  {
  };

  template <class Spec, class State>
  struct combinations_op
  {
      typedef typename State::second bits;
      typedef typename State::first result0;

      typedef typename mpl::if_<
          mpl::or_<
              typename Spec::required
            , typename Spec::optimized_default
            , mpl::bitand_<bits, mpl::long_<1> >
          >
        , typename mpl::push_back<result0, Spec>::type
        , result0
      >::type result;

      typedef typename mpl::if_<
          mpl::or_<
              typename Spec::required
            , typename Spec::optimized_default
          >
        , bits
        , typename mpl::shift_right<bits, mpl::long_<1> >::type
      >::type next_bits;

      typedef mpl::pair<
          result
        , next_bits
      > type;
  };

  // Used as start value in the recursive arg() composition below.
  struct no_keywords
  {
      template <class T>
      T const& operator,(T const& x) const
      {
          return x;
      }
  };

  template <class Def, class F, class Iter, class End, class Keywords>
  void def_combination_aux0(
      Def def, F f, Iter, End, Keywords const& keywords, mpl::false_)
  {
      typedef typename mpl::deref<Iter>::type spec;
      typedef typename spec::keyword kw;

      def_combination_aux(
          def, f, typename mpl::next<Iter>::type(), End()
        , (
              keywords, boost::python::arg(kw::keyword_name())
          )
      );
  }

  template <class Def, class F, class Iter, class End, class Keywords>
  void def_combination_aux0(
      Def def, F f, Iter, End, Keywords const& keywords, mpl::true_)
  {
      typedef typename mpl::deref<Iter>::type spec;
      typedef typename spec::keyword kw;

      def_combination_aux(
          def, f, typename mpl::next<Iter>::type(), End()
        , (
              keywords, boost::python::arg(kw::keyword_name()) = empty_tag()
          )
      );
  }

  inline void initialize_converter()
  {
      static python_::to_python_converter<empty_tag, empty_tag_to_python> x;
  }

  template <class Def, class F, class Iter, class End, class Keywords>
  void def_combination_aux(
      Def def, F f, Iter, End, Keywords const& keywords)
  {
      typedef typename mpl::deref<Iter>::type spec;

      typedef typename mpl::and_<
          typename spec::optimized_default
        , mpl::not_<typename spec::required>
      >::type optimized_default;
      
      def_combination_aux0(
          def, f, Iter(), End(), keywords, optimized_default()
      );
  }

  template <class Def, class F, class End, class Keywords>
  void def_combination_aux(
      Def def, F f, End, End, Keywords const& keywords)
  {
      def(f, keywords);
  } 

  template <class Def, class F, class End>
  void def_combination_aux(
      Def def, F f, End, End, no_keywords const&)
  {
      def(f);
  }

  template <
      class Def, class Specs, class Bits, class Invoker
  >
  void def_combination(
      Def def, Specs*, Bits, Invoker*)
  {
      typedef typename mpl::fold<
          Specs
        , mpl::pair<mpl::vector0<>, Bits>
        , combinations_op<mpl::_2, mpl::_1>
      >::type combination0;

      typedef typename combination0::first combination;

      typedef typename mpl::apply_wrap1<
          Invoker, combination
      >::type invoker;

      def_combination_aux(
          def
        , &invoker::execute
        , typename mpl::begin<combination>::type()
        , typename mpl::end<combination>::type()
        , no_keywords()
      );
  }

  template <
      class Def, class Specs, class Bits, class End, class Invoker
  >
  void def_combinations(
      Def def, Specs*, Bits, End, Invoker*)
  {
      initialize_converter();

      def_combination(def, (Specs*)0, Bits(), (Invoker*)0);

      def_combinations(
          def
        , (Specs*)0
        , mpl::long_<Bits::value + 1>()
        , End()
        , (Invoker*)0
      );
  }

  template <
      class Def, class Specs, class End, class Invoker
  >
  void def_combinations(
      Def, Specs*, End, End, Invoker*)
  {}

  struct not_specified {};

  template <class CallPolicies>
  struct call_policies_as_options
  {
      call_policies_as_options(CallPolicies const& call_policies)
        : call_policies(call_policies)
      {}

      CallPolicies const& policies() const
      {
          return call_policies;
      }

      char const* doc() const
      {
          return 0;
      }

      CallPolicies call_policies;
  };

  template <class Class, class Options = not_specified>
  struct def_class
  {
      def_class(Class& cl, char const* name, Options options = Options())
        : cl(cl)
        , name(name)
        , options(options)
      {}

      template <class F>
      void def(F f, not_specified const*) const
      {
          cl.def(name, f);
      }

      template <class F>
      void def(F f, void const*) const
      {
          cl.def(name, f, options.doc(), options.policies());
      }
      
      template <class F>
      void operator()(F f) const
      {
          this->def(f, &options);
      }

      template <class F, class Keywords>
      void def(F f, Keywords const& keywords, not_specified const*) const
      {
          cl.def(name, f, keywords);
      }

      template <class F, class Keywords>
      void def(F f, Keywords const& keywords, void const*) const
      {
          cl.def(name, f, keywords, options.doc(), options.policies());
      }

      template <class F, class Keywords>
      void operator()(F f, Keywords const& keywords) const
      {
          this->def(f, keywords, &options);
      }

      Class& cl;
      char const* name;
      Options options;
  };

  template <class Class, class CallPolicies = boost::python::default_call_policies>
  struct def_init
  {
      def_init(Class& cl, CallPolicies call_policies = CallPolicies())
        : cl(cl)
        , call_policies(call_policies)
      {}

      template <class F>
      void operator()(F f) const
      {
          cl.def(
              "__init__"
            , boost::python::make_constructor(f, call_policies)
          );
      }

      template <class F, class Keywords>
      void operator()(F f, Keywords const& keywords) const
      {
          cl.def(
              "__init__"
            , boost::python::make_constructor(f, call_policies, keywords)
          );
      }

      Class& cl;
      CallPolicies call_policies;
  };

  struct def_function
  {
      def_function(char const* name)
        : name(name)
      {}
      
      template <class F>
      void operator()(F f) const
      {
          boost::python::def(name, f);
      }

      template <class F, class Keywords>
      void operator()(F f, Keywords const& keywords) const
      {
          boost::python::def(name, f, keywords);
      }

      char const* name;
  };

} // namespace aux

template <class M, class Signature>
void def(char const* name, Signature)
{
    typedef mpl::iterator_range<
        typename mpl::next<
            typename mpl::begin<Signature>::type
        >::type
      , typename mpl::end<Signature>::type
    > arg_types;

    typedef typename mpl::transform<
        typename M::keywords
      , arg_types
      , aux::make_arg_spec<mpl::_1, mpl::_2>
      , mpl::back_inserter<mpl::vector0<> >
    >::type arg_specs;

    typedef typename mpl::count_if<
        arg_specs
      , aux::is_optional<mpl::_1>
    >::type optional_arity;
    
    typedef typename mpl::front<Signature>::type result_type;
    typedef typename mpl::shift_left<mpl::long_<1>, optional_arity>::type upper;

    aux::def_combinations(
        aux::def_function(name)
      , (arg_specs*)0
      , mpl::long_<0>()
      , mpl::long_<upper::value>()
      , (aux::make_invoker<M, result_type>*)0
    );
}

template <class M, class Class, class Signature>
void def(Class& cl, char const* name, Signature)
{
    typedef mpl::iterator_range<
        typename mpl::next<
            typename mpl::begin<Signature>::type
        >::type
      , typename mpl::end<Signature>::type
    > arg_types;

    typedef typename mpl::transform<
        typename M::keywords
      , arg_types
      , aux::make_arg_spec<mpl::_1, mpl::_2>
      , mpl::back_inserter<mpl::vector0<> >
    >::type arg_specs;

    typedef typename mpl::count_if<
        arg_specs
      , aux::is_optional<mpl::_1>
    >::type optional_arity;
    
    typedef typename mpl::front<Signature>::type result_type;
    typedef typename mpl::shift_left<mpl::long_<1>, optional_arity>::type upper;

    aux::def_combinations(
        aux::def_class<Class>(cl, name)
      , (arg_specs*)0
      , mpl::long_<0>()
      , mpl::long_<upper::value>()
      , (aux::make_invoker<M, result_type>*)0
    );
}

namespace aux
{

  template <class K>
  struct keyword
  {
      typedef K type;
  };

  template <class K>
  struct keyword<K*>
  {
      typedef K type;
  };

  template <class K>
  struct keyword<K**>
  {
      typedef K type;
  };

  template <class K>
  struct required
  {
      typedef mpl::true_ type;
  };

  template <class K>
  struct required<K*>
  {
      typedef mpl::false_ type;
  };

  template <class K>
  struct optimized
  {
      typedef mpl::true_ type;
  };

  template <class K>
  struct optimized<K**>
  {
      typedef mpl::false_ type;
  };

  template <class T>
  struct make_kw_spec;

  template <class K, class T>
  struct make_kw_spec<K(T)>
  {
      typedef arg_spec<
          typename keyword<K>::type
        , typename required<K>::type
        , typename optimized<K>::type
        , T
      > type;
  };

} // namespace aux

template <class ParameterSpecs, class CallPolicies = boost::python::default_call_policies>
struct init 
  : boost::python::def_visitor<init<ParameterSpecs, CallPolicies> >
{
    init(CallPolicies call_policies = CallPolicies())
      : call_policies(call_policies)
    {}

    template <class CallPolicies1>
    init<ParameterSpecs, CallPolicies1> 
    operator[](CallPolicies1 const& call_policies) const
    {
        return init<ParameterSpecs, CallPolicies1>(call_policies);
    }

    template <class Class>
    void visit_aux(Class& cl, mpl::true_) const
    {
        cl.def(boost::python::init<>()[call_policies]);
    }

    template <class Class>
    void visit_aux(Class& cl, mpl::false_) const
    {
        typedef typename mpl::transform<
            ParameterSpecs
          , aux::make_kw_spec<mpl::_>
          , mpl::back_inserter<mpl::vector0<> >
        >::type arg_specs;

        typedef typename mpl::count_if<
            arg_specs
          , aux::is_optional<mpl::_>
        >::type optional_arity;

        typedef typename mpl::shift_left<mpl::long_<1>, optional_arity>::type upper;

        aux::def_combinations(
            aux::def_init<Class, CallPolicies>(cl, call_policies)
          , (arg_specs*)0
          , mpl::long_<0>()
          , mpl::long_<upper::value>()
          , (aux::make_init_invoker<typename Class::wrapped_type>*)0
        );
    }

    template <class Class>
    void visit(Class& cl) const
    {
        visit_aux(cl, mpl::empty<ParameterSpecs>());
    }

    CallPolicies call_policies;
};

template <class ParameterSpecs, class CallPolicies = boost::python::default_call_policies>
struct call 
  : boost::python::def_visitor<call<ParameterSpecs, CallPolicies> >
{
    call(CallPolicies const& call_policies = CallPolicies())
      : call_policies(call_policies)
    {}

    template <class CallPolicies1>
    call<ParameterSpecs, CallPolicies1>
    operator[](CallPolicies1 const& call_policies) const
    {
        return call<ParameterSpecs, CallPolicies1>(call_policies);
    }

    template <class Class>
    void visit(Class& cl) const
    {
        typedef mpl::iterator_range<
            typename mpl::next<
                typename mpl::begin<ParameterSpecs>::type
            >::type
          , typename mpl::end<ParameterSpecs>::type
        > arg_types;

        typedef typename mpl::front<ParameterSpecs>::type result_type;

        typedef typename mpl::transform<
            arg_types
          , aux::make_kw_spec<mpl::_>
          , mpl::back_inserter<mpl::vector0<> >
        >::type arg_specs;

        typedef typename mpl::count_if<
            arg_specs
          , aux::is_optional<mpl::_>
        >::type optional_arity;

        typedef typename mpl::shift_left<mpl::long_<1>, optional_arity>::type upper;

        typedef aux::call_policies_as_options<CallPolicies> options;

        aux::def_combinations(
            aux::def_class<Class, options>(cl, "__call__", options(call_policies))
          , (arg_specs*)0
          , mpl::long_<0>()
          , mpl::long_<upper::value>()
          , (aux::make_call_invoker<typename Class::wrapped_type, result_type>*)0
        );
    }

    CallPolicies call_policies;
};

template <class Fwd, class ParameterSpecs>
struct function 
  : boost::python::def_visitor<function<Fwd, ParameterSpecs> >
{
    template <class Class, class Options>
    void visit(Class& cl, char const* name, Options const& options) const
    {
        typedef mpl::iterator_range<
            typename mpl::next<
                typename mpl::begin<ParameterSpecs>::type
            >::type
          , typename mpl::end<ParameterSpecs>::type
        > arg_types;

        typedef typename mpl::front<ParameterSpecs>::type result_type;

        typedef typename mpl::transform<
            arg_types
          , aux::make_kw_spec<mpl::_>
          , mpl::back_inserter<mpl::vector0<> >
        >::type arg_specs;

        typedef typename mpl::count_if<
            arg_specs
          , aux::is_optional<mpl::_>
        >::type optional_arity;

        typedef typename mpl::shift_left<mpl::long_<1>, optional_arity>::type upper;

        aux::def_combinations(
            aux::def_class<Class, Options>(cl, name, options)
          , (arg_specs*)0
          , mpl::long_<0>()
          , mpl::long_<upper::value>()
          , (aux::make_member_invoker<
                Fwd, result_type, typename Class::wrapped_type
            >*)0
        );
    }
};

}}} // namespace boost::parameter::python

#endif // BOOST_PARAMETER_PYTHON_060209_HPP


/* python.hpp
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
*/