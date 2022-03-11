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