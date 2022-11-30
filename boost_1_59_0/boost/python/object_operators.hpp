// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef OBJECT_OPERATORS_DWA2002617_HPP
# define OBJECT_OPERATORS_DWA2002617_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/object_core.hpp>
# include <boost/python/call.hpp>
# include <boost/iterator/detail/enable_if.hpp>
# include <boost/mpl/bool.hpp>

# include <boost/iterator/detail/config_def.hpp>

namespace boost { namespace python { namespace api {

template <class X>
char is_object_operators_helper(object_operators<X> const*);
    
typedef char (&no_type)[2];
no_type is_object_operators_helper(...);

template <class X> X* make_ptr();

template <class L, class R = L>
struct is_object_operators
{
    enum {
        value 
        = (sizeof(api::is_object_operators_helper(api::make_ptr<L>()))
           + sizeof(api::is_object_operators_helper(api::make_ptr<R>()))
           < 4
        )
    };
    typedef mpl::bool_<value> type;
};

# if !defined(BOOST_NO_SFINAE) && !defined(BOOST_NO_IS_CONVERTIBLE)
template <class L, class R, class T>
struct enable_binary
  : boost::iterators::enable_if<is_object_operators<L,R>, T>
{};
#  define BOOST_PYTHON_BINARY_RETURN(T) typename enable_binary<L,R,T>::type
# else
#  define BOOST_PYTHON_BINARY_RETURN(T) T
# endif

template <class U>
object object_operators<U>::operator()() const
{
    object_cref2 f = *static_cast<U const*>(this);
    return call<object>(f.ptr());
}


template <class U>
inline
object_operators<U>::operator bool_type() const
{
    object_cref2 x = *static_cast<U const*>(this);
    int is_true = PyObject_IsTrue(x.ptr());
    if (is_true < 0) throw_error_already_set();
    return is_true ? &object::ptr : 0;
}

template <class U>
inline bool
object_operators<U>::operator!() const
{
    object_cref2 x = *static_cast<U const*>(this);
    int is_true = PyObject_IsTrue(x.ptr());
    if (is_true < 0) throw_error_already_set();
    return !is_true;
}

# define BOOST_PYTHON_COMPARE_OP(op, opid)                              \
template <class L, class R>                                             \
BOOST_PYTHON_BINARY_RETURN(object) operator op(L const& l, R const& r)    \
{                                                                       \
    return PyObject_RichCompare(                                    \
        object(l).ptr(), object(r).ptr(), opid);                        \
}
# undef BOOST_PYTHON_COMPARE_OP
    
# define BOOST_PYTHON_BINARY_OPERATOR(op)                               \
BOOST_PYTHON_DECL object operator op(object const& l, object const& r); \
template <class L, class R>                                             \
BOOST_PYTHON_BINARY_RETURN(object) operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
BOOST_PYTHON_BINARY_OPERATOR(-)
BOOST_PYTHON_BINARY_OPERATOR(*)
BOOST_PYTHON_BINARY_OPERATOR(/)
BOOST_PYTHON_BINARY_OPERATOR(%)
BOOST_PYTHON_BINARY_OPERATOR(<<)
BOOST_PYTHON_BINARY_OPERATOR(>>)
BOOST_PYTHON_BINARY_OPERATOR(&)
BOOST_PYTHON_BINARY_OPERATOR(^)
BOOST_PYTHON_BINARY_OPERATOR(|)
# undef BOOST_PYTHON_BINARY_OPERATOR

        
# define BOOST_PYTHON_INPLACE_OPERATOR(op)                              \
BOOST_PYTHON_DECL object& operator op(object& l, object const& r);      \
template <class R>                                                      \
object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
BOOST_PYTHON_INPLACE_OPERATOR(-=)
BOOST_PYTHON_INPLACE_OPERATOR(*=)
BOOST_PYTHON_INPLACE_OPERATOR(/=)
BOOST_PYTHON_INPLACE_OPERATOR(%=)
BOOST_PYTHON_INPLACE_OPERATOR(<<=)
BOOST_PYTHON_INPLACE_OPERATOR(>>=)
BOOST_PYTHON_INPLACE_OPERATOR(&=)
BOOST_PYTHON_INPLACE_OPERATOR(^=)
BOOST_PYTHON_INPLACE_OPERATOR(|=)
# undef BOOST_PYTHON_INPLACE_OPERATOR

}}} // namespace boost::python

#include <boost/iterator/detail/config_undef.hpp>

#endif // OBJECT_OPERATORS_DWA2002617_HPP

/* object_operators.hpp
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
*/