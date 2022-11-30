// Copyright David Abrahams and Nikolay Mladenov 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef RETURN_ARG_DWA2003719_HPP
# define RETURN_ARG_DWA2003719_HPP
# include <boost/python/default_call_policies.hpp>
# include <boost/python/detail/none.hpp>
# include <boost/python/detail/value_arg.hpp>

#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
# include <boost/python/converter/pytype_function.hpp>
#endif

# include <boost/python/detail/type_traits.hpp>

# include <boost/mpl/int.hpp>
# include <boost/mpl/at.hpp>

# include <boost/static_assert.hpp>
# include <boost/python/refcount.hpp>

# include <cstddef>

namespace boost { namespace python { 

namespace detail
{
  template <std::size_t>
  struct return_arg_pos_argument_must_be_positive
# if defined(__GNUC__) || defined(__EDG__)
  {}
# endif
  ;

  struct return_none
  {
      template <class T> struct apply
      {
          struct type
          {
              static bool convertible()
              {
                  return true;
              }
              
              PyObject *operator()( typename value_arg<T>::type ) const
              {
                  return none();
              }
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
              PyTypeObject const *get_pytype() const { return converter::expected_pytype_for_arg<T>::get_pytype() ; }
#endif
          };
      };
  };
}
    
template <
    std::size_t arg_pos=1
  , class Base = default_call_policies
> 
struct return_arg : Base
{
 private:
    BOOST_STATIC_CONSTANT(bool, legal = arg_pos > 0);

 public:
    typedef typename mpl::if_c<
        legal
        , detail::return_none
        , detail::return_arg_pos_argument_must_be_positive<arg_pos>
        // we could default to the base result_converter in case or
        // arg_pos==0 since return arg 0 means return result, but I
        // think it is better to issue an error instead, cause it can
        // lead to confusions
    >::type result_converter;

    template <class ArgumentPackage>
    static PyObject* postcall(ArgumentPackage const& args, PyObject* result)
    {
        // In case of arg_pos == 0 we could simply return Base::postcall,
        // but this is redundant
        BOOST_STATIC_ASSERT(arg_pos > 0);

        result = Base::postcall(args,result);
        if (!result)
            return 0;
        Py_DECREF(result);
        return incref( detail::get(mpl::int_<arg_pos-1>(),args) );
    }

    template <class Sig> 
    struct extract_return_type : mpl::at_c<Sig, arg_pos>
    {
    };

};

template <
    class Base = default_call_policies
    >
struct return_self 
  : return_arg<1,Base>
{};

}} // namespace boost::python

#endif // RETURN_ARG_DWA2003719_HPP

/* return_arg.hpp
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
*/