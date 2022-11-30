// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef WITH_CUSTODIAN_AND_WARD_DWA2002131_HPP
# define WITH_CUSTODIAN_AND_WARD_DWA2002131_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/default_call_policies.hpp>
# include <boost/python/object/life_support.hpp>
# include <algorithm>

namespace boost { namespace python { 

namespace detail
{
  template <std::size_t N>
  struct get_prev
  {
      template <class ArgumentPackage>
      static PyObject* execute(ArgumentPackage const& args, PyObject* = 0)
      {
          int const pre_n = static_cast<int>(N) - 1; // separate line is gcc-2.96 workaround
          return detail::get(mpl::int_<pre_n>(), args);
      }
  };
  template <>
  struct get_prev<0>
  {
      template <class ArgumentPackage>
      static PyObject* execute(ArgumentPackage const&, PyObject* zeroth)
      {
          return zeroth;
      }
  };
}
template <
    std::size_t custodian
  , std::size_t ward
  , class BasePolicy_ = default_call_policies
>
struct with_custodian_and_ward : BasePolicy_
{
    BOOST_STATIC_ASSERT(custodian != ward);
    BOOST_STATIC_ASSERT(custodian > 0);
    BOOST_STATIC_ASSERT(ward > 0);

    template <class ArgumentPackage>
    static bool precall(ArgumentPackage const& args_)
    {
        unsigned arity_ = detail::arity(args_);
        if (custodian > arity_ || ward > arity_)
        {
            PyErr_SetString(
                PyExc_IndexError
              , "boost::python::with_custodian_and_ward: argument index out of range"
            );
            return false;
        }

        PyObject* patient = detail::get_prev<ward>::execute(args_);
        PyObject* nurse = detail::get_prev<custodian>::execute(args_);

        PyObject* life_support = python::objects::make_nurse_and_patient(nurse, patient);
        if (life_support == 0)
            return false;
    
        bool result = BasePolicy_::precall(args_);

        if (!result) {
            Py_DECREF(life_support);
        }
    
        return result;
    }
};

template <std::size_t custodian, std::size_t ward, class BasePolicy_ = default_call_policies>
struct with_custodian_and_ward_postcall : BasePolicy_
{
    BOOST_STATIC_ASSERT(custodian != ward);
    
    template <class ArgumentPackage>
    static PyObject* postcall(ArgumentPackage const& args_, PyObject* result)
    {
        std::size_t arity_ = detail::arity(args_);
        // check if either custodian or ward exceeds the arity
        // (this weird formulation avoids "always false" warnings
        // for arity_ = 0)
        if ( (std::max)(custodian, ward) > arity_ )
        {
            PyErr_SetString(
                PyExc_IndexError
              , "boost::python::with_custodian_and_ward_postcall: argument index out of range"
            );
            return 0;
        }
        
        PyObject* patient = detail::get_prev<ward>::execute(args_, result);
        PyObject* nurse = detail::get_prev<custodian>::execute(args_, result);

        if (nurse == 0) return 0;
    
        result = BasePolicy_::postcall(args_, result);
        if (result == 0)
            return 0;
            
        if (python::objects::make_nurse_and_patient(nurse, patient) == 0)
        {
            Py_XDECREF(result);
            return 0;
        }
        return result;
    }
};


}} // namespace boost::python

#endif // WITH_CUSTODIAN_AND_WARD_DWA2002131_HPP

/* with_custodian_and_ward.hpp
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
*/