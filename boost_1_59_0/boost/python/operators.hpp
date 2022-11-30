// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef OPERATORS_DWA2002530_HPP
# define OPERATORS_DWA2002530_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/def_visitor.hpp>
# include <boost/python/converter/arg_to_python.hpp>
# include <boost/python/detail/operator_id.hpp>
# include <boost/python/detail/not_specified.hpp>
# include <boost/python/back_reference.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/eval_if.hpp>
# include <boost/python/self.hpp>
# include <boost/python/other.hpp>
# include <boost/lexical_cast.hpp>
# include <boost/python/refcount.hpp>
# include <boost/python/detail/unwrap_wrapper.hpp>
# include <string>
# include <complex>

namespace boost { namespace python { 

namespace detail
{
  // This is essentially the old v1 to_python(). It will be eliminated
  // once the public interface for to_python is settled on.
  template <class T>
  PyObject* convert_result(T const& x)
  {
      return converter::arg_to_python<T>(x).release();
  }

  // Operator implementation template declarations. The nested apply
  // declaration here keeps MSVC6 happy.
  template <operator_id> struct operator_l
  {
      template <class L, class R> struct apply;
  };
  
  template <operator_id> struct operator_r
  {
      template <class L, class R> struct apply;
  };

  template <operator_id> struct operator_1
  {
      template <class T> struct apply;
  };

  // MSVC6 doesn't want us to do this sort of inheritance on a nested
  // class template, so we use this layer of indirection to avoid
  // ::template<...> on the nested apply functions below
  template <operator_id id, class L, class R>
  struct operator_l_inner
      : operator_l<id>::template apply<L,R>
  {};
      
  template <operator_id id, class L, class R>
  struct operator_r_inner
      : operator_r<id>::template apply<L,R>
  {};

  template <operator_id id, class T>
  struct operator_1_inner
      : operator_1<id>::template apply<T>
  {};
      
  // Define three different binary_op templates which take care of
  // these cases:
  //    self op self
  //    self op R
  //    L op self
  // 
  // The inner apply metafunction is used to adjust the operator to
  // the class type being defined. Inheritance of the outer class is
  // simply used to provide convenient access to the operation's
  // name().

  // self op self
  template <operator_id id>
  struct binary_op : operator_l<id>
  {
      template <class T>
      struct apply : operator_l_inner<id,T,T>
      {
      };
  };

  // self op R
  template <operator_id id, class R>
  struct binary_op_l : operator_l<id>
  {
      template <class T>
      struct apply : operator_l_inner<id,T,R>
      {
      };
  };

  // L op self
  template <operator_id id, class L>
  struct binary_op_r : operator_r<id>
  {
      template <class T>
      struct apply : operator_r_inner<id,L,T>
      {
      };
  };

  template <operator_id id>
  struct unary_op : operator_1<id>
  {
      template <class T>
      struct apply : operator_1_inner<id,T>
      {
      };
  };

  // This type is what actually gets returned from operators used on
  // self_t
  template <operator_id id, class L = not_specified, class R = not_specified>
  struct operator_
    : def_visitor<operator_<id,L,R> >
  {
   private:
      template <class ClassT>
      void visit(ClassT& cl) const
      {
          typedef typename mpl::eval_if<
              is_same<L,self_t>
            , mpl::if_<
                  is_same<R,self_t>
                , binary_op<id>
                , binary_op_l<
                      id
                    , BOOST_DEDUCED_TYPENAME unwrap_other<R>::type
                  >
              >
            , mpl::if_<
                  is_same<L,not_specified>
                , unary_op<id>
                , binary_op_r<
                      id
                    , BOOST_DEDUCED_TYPENAME unwrap_other<L>::type
                  >
              >
          >::type generator;
      
          cl.def(
              generator::name()
            , &generator::template apply<
                 BOOST_DEDUCED_TYPENAME ClassT::wrapped_type
              >::execute
          );
      }
    
      friend class python::def_visitor_access;
  };
}

# define BOOST_PYTHON_BINARY_OPERATION(id, rid, expr)       \
namespace detail                                            \
{                                                           \
  template <>                                               \
  struct operator_l<op_##id>                                \
  {                                                         \
      template <class L, class R>                           \
      struct apply                                          \
      {                                                     \
          typedef typename unwrap_wrapper_<L>::type lhs;    \
          typedef typename unwrap_wrapper_<R>::type rhs;    \
          static PyObject* execute(lhs& l, rhs const& r)    \
          {                                                 \
              return detail::convert_result(expr);          \
          }                                                 \
      };                                                    \
      static char const* name() { return "__" #id "__"; }   \
  };                                                        \
                                                            \
  template <>                                               \
  struct operator_r<op_##id>                                \
  {                                                         \
      template <class L, class R>                           \
      struct apply                                          \
      {                                                     \
          typedef typename unwrap_wrapper_<L>::type lhs;    \
          typedef typename unwrap_wrapper_<R>::type rhs;    \
          static PyObject* execute(rhs& r, lhs const& l)    \
          {                                                 \
              return detail::convert_result(expr);          \
          }                                                 \
      };                                                    \
      static char const* name() { return "__" #rid "__"; }  \
  };                                                        \
} 

# define BOOST_PYTHON_BINARY_OPERATOR(id, rid, op)      \
BOOST_PYTHON_BINARY_OPERATION(id, rid, l op r)          \
namespace self_ns                                       \
{                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
BOOST_PYTHON_BINARY_OPERATOR(and, rand, &)
BOOST_PYTHON_BINARY_OPERATOR(xor, rxor, ^)
BOOST_PYTHON_BINARY_OPERATOR(or, ror, |)
BOOST_PYTHON_BINARY_OPERATOR(gt, lt, >)
BOOST_PYTHON_BINARY_OPERATOR(ge, le, >=)
BOOST_PYTHON_BINARY_OPERATOR(lt, gt, <)
BOOST_PYTHON_BINARY_OPERATOR(le, ge, <=)
BOOST_PYTHON_BINARY_OPERATOR(eq, eq, ==)
BOOST_PYTHON_BINARY_OPERATOR(ne, ne, !=)
# undef BOOST_PYTHON_BINARY_OPERATOR
    
// pow isn't an operator in C++; handle it specially.
BOOST_PYTHON_BINARY_OPERATION(pow, rpow, pow(l,r))
# undef BOOST_PYTHON_BINARY_OPERATION
    
namespace self_ns
{
# ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
  template <class L, class R>
  inline detail::operator_<detail::op_pow,L,R>
  pow(L const&, R const&)
  {
      return detail::operator_<detail::op_pow,L,R>();
  }
# else
  // When there's no argument-dependent lookup, we need these
  // overloads to handle the case when everything is imported into the
  // global namespace. Note that the plain overload below does /not/
  // take const& arguments. This is needed by MSVC6 at least, or it
  // complains of ambiguities, since there's no partial ordering.
  inline detail::operator_<detail::op_pow,self_t,self_t>
  pow(self_t, self_t)
  {
      return detail::operator_<detail::op_pow,self_t,self_t>();
  }
  template <class R>
  inline detail::operator_<detail::op_pow,self_t,R>
  pow(self_t const&, R const&)
  {
      return detail::operator_<detail::op_pow,self_t,R>();
  }
  template <class L>
  inline detail::operator_<detail::op_pow,L,self_t>
  pow(L const&, self_t const&)
  {
      return detail::operator_<detail::op_pow,L,self_t>();
  }
# endif 
}


# define BOOST_PYTHON_INPLACE_OPERATOR(id, op)                  \
namespace detail                                                \
{                                                               \
  template <>                                                   \
  struct operator_l<op_##id>                                    \
  {                                                             \
      template <class L, class R>                               \
      struct apply                                              \
      {                                                         \
          typedef typename unwrap_wrapper_<L>::type lhs;        \
          typedef typename unwrap_wrapper_<R>::type rhs;        \
          static PyObject*                                      \
          execute(back_reference<lhs&> l, rhs const& r)         \
          {                                                     \
              l.get() op r;                                     \
              return python::incref(l.source().ptr());          \
          }                                                     \
      };                                                        \
      static char const* name() { return "__" #id "__"; }       \
  };                                                            \
}                                                               \
namespace self_ns                                               \
{                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
BOOST_PYTHON_INPLACE_OPERATOR(isub,-=)
BOOST_PYTHON_INPLACE_OPERATOR(imul,*=)
BOOST_PYTHON_INPLACE_OPERATOR(idiv,/=)
BOOST_PYTHON_INPLACE_OPERATOR(imod,%=)
BOOST_PYTHON_INPLACE_OPERATOR(ilshift,<<=)
BOOST_PYTHON_INPLACE_OPERATOR(irshift,>>=)
BOOST_PYTHON_INPLACE_OPERATOR(iand,&=)
BOOST_PYTHON_INPLACE_OPERATOR(ixor,^=)
BOOST_PYTHON_INPLACE_OPERATOR(ior,|=)
    
# define BOOST_PYTHON_UNARY_OPERATOR(id, op, func_name)         \
namespace detail                                                \
{                                                               \
  template <>                                                   \
  struct operator_1<op_##id>                                    \
  {                                                             \
      template <class T>                                        \
      struct apply                                              \
      {                                                         \
          typedef typename unwrap_wrapper_<T>::type self_t;     \
          static PyObject* execute(self_t& x)                   \
          {                                                     \
              return detail::convert_result(op(x));             \
          }                                                     \
      };                                                        \
      static char const* name() { return "__" #id "__"; }       \
  };                                                            \
}                                                               \
namespace self_ns                                               \
{                                                               \
  inline detail::operator_<detail::op_##id>                     \
  func_name(self_t const&)                                      \
  {                                                             \
      return detail::operator_<detail::op_##id>();              \
  }                                                             \
}
# undef BOOST_PYTHON_INPLACE_OPERATOR

BOOST_PYTHON_UNARY_OPERATOR(neg, -, operator-)
BOOST_PYTHON_UNARY_OPERATOR(pos, +, operator+)
BOOST_PYTHON_UNARY_OPERATOR(abs, abs, abs)
BOOST_PYTHON_UNARY_OPERATOR(invert, ~, operator~)
#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_UNARY_OPERATOR(bool, !!, operator!)
#else
BOOST_PYTHON_UNARY_OPERATOR(nonzero, !!, operator!)
#endif
BOOST_PYTHON_UNARY_OPERATOR(int, long, int_)
BOOST_PYTHON_UNARY_OPERATOR(long, PyLong_FromLong, long_)
BOOST_PYTHON_UNARY_OPERATOR(float, double, float_)
BOOST_PYTHON_UNARY_OPERATOR(complex, std::complex<double>, complex_)
BOOST_PYTHON_UNARY_OPERATOR(str, lexical_cast<std::string>, str)
BOOST_PYTHON_UNARY_OPERATOR(repr, lexical_cast<std::string>, repr)
# undef BOOST_PYTHON_UNARY_OPERATOR

}} // namespace boost::python

# ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
using boost::python::self_ns::abs;
using boost::python::self_ns::int_;
using boost::python::self_ns::long_;
using boost::python::self_ns::float_;
using boost::python::self_ns::complex_;
using boost::python::self_ns::str;
using boost::python::self_ns::repr;
using boost::python::self_ns::pow;
# endif

#endif // OPERATORS_DWA2002530_HPP

/* operators.hpp
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
*/