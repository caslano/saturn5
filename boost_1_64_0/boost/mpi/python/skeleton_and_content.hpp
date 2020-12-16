// (C) Copyright 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
#ifndef BOOST_MPI_PYTHON_SKELETON_AND_CONTENT_HPP
#define BOOST_MPI_PYTHON_SKELETON_AND_CONTENT_HPP

/** @file skeleton_and_content.hpp
 *
 *  This file reflects the skeleton/content facilities into Python.
 */
#include <boost/python.hpp>
#include <boost/mpi.hpp>
#include <boost/function/function1.hpp>
#define BOOST_MPI_PYTHON_FORWARD_ONLY
#include <boost/mpi/python.hpp>
#include <boost/mpi/python/serialize.hpp>


namespace boost { namespace mpi { namespace python {

/**
 * INTERNAL ONLY
 *
 * This @c content class is a wrapper around the C++ "content"
 * retrieved from get_content. This wrapper is only needed to store a
 * copy of the Python object on which get_content() was called.
 */
class content : public boost::mpi::content
{
  typedef boost::mpi::content inherited;

 public:
  content(const inherited& base, boost::python::object object) 
    : inherited(base), object(object) { }

  inherited&       base()       { return *this; }
  const inherited& base() const { return *this; }

  boost::python::object object;
};

/**
 * INTERNAL ONLY
 *
 * A class specific to the Python bindings that mimics the behavior of
 * the skeleton_proxy<T> template. In the case of Python skeletons, we
 * only need to know the object (and its type) to transmit the
 * skeleton. This is the only user-visible skeleton proxy type,
 * although instantiations of its derived classes (@c
 * skeleton_proxy<T>) will be returned from the Python skeleton()
 * function.
 */
class skeleton_proxy_base 
{
public:
  skeleton_proxy_base(const boost::python::object& object) : object(object) { }

  boost::python::object object;
};

/**
 * INTERNAL ONLY
 *
 * The templated @c skeleton_proxy class represents a skeleton proxy
 * in Python. The only data is stored in the @c skeleton_proxy_base
 * class (which is the type actually exposed as @c skeleton_proxy in
 * Python). However, the type of @c skeleton_proxy<T> is important for
 * (de-)serialization of @c skeleton_proxy<T>'s for transmission.
 */
template<typename T>
class skeleton_proxy : public skeleton_proxy_base
{
 public:
  skeleton_proxy(const boost::python::object& object) 
    : skeleton_proxy_base(object) { }
};

namespace detail {
  using boost::python::object;
  using boost::python::extract;
   
  extern BOOST_MPI_DECL boost::python::object skeleton_proxy_base_type;

  template<typename T>
  struct skeleton_saver
  {
    void 
    operator()(packed_oarchive& ar, const object& obj, const unsigned int)
    {
      packed_skeleton_oarchive pso(ar);
      pso << extract<T&>(obj.attr("object"))();
    }
  };

  template<typename T> 
  struct skeleton_loader
  {
    void 
    operator()(packed_iarchive& ar, object& obj, const unsigned int)
    {
      packed_skeleton_iarchive psi(ar);
      extract<skeleton_proxy<T>&> proxy(obj);
      if (!proxy.check())
        obj = object(skeleton_proxy<T>(object(T())));

      psi >> extract<T&>(obj.attr("object"))();
    }
  };

  /**
   * The @c skeleton_content_handler structure contains all of the
   * information required to extract a skeleton and content from a
   * Python object with a certain C++ type.
   */
  struct skeleton_content_handler {
    function1<object, const object&> get_skeleton_proxy;
    function1<content, const object&> get_content;
  };

  /**
   * A function object that extracts the skeleton from of a Python
   * object, which is actually a wrapped C++ object of type T.
   */
  template<typename T>
  struct do_get_skeleton_proxy
  {
    object operator()(object value) {
      return object(skeleton_proxy<T>(value));
    }
  };

  /**
   * A function object that extracts the content of a Python object,
   * which is actually a wrapped C++ object of type T.
   */
  template<typename T>
  struct do_get_content
  {
    content operator()(object value_obj) {
      T& value = extract<T&>(value_obj)();
      return content(boost::mpi::get_content(value), value_obj);
    }
  };

  /**
   * Determine if a skeleton and content handler for @p type has
   * already been registered.
   */
  BOOST_MPI_PYTHON_DECL bool
  skeleton_and_content_handler_registered(PyTypeObject* type);
 
  /**
   * Register a skeleton/content handler with a particular Python type
   * (which actually wraps a C++ type).
   */
  BOOST_MPI_PYTHON_DECL void 
  register_skeleton_and_content_handler(PyTypeObject*, 
                                        const skeleton_content_handler&);
} // end namespace detail

template<typename T>
void register_skeleton_and_content(const T& value, PyTypeObject* type)
{
  using boost::python::detail::direct_serialization_table;
  using boost::python::detail::get_direct_serialization_table;
  using namespace boost::python;

  // Determine the type
  if (!type)
    type = object(value).ptr()->ob_type;

  // Don't re-register the same type.
  if (detail::skeleton_and_content_handler_registered(type))
    return;

  // Register the skeleton proxy type
  {
    boost::python::scope proxy_scope(detail::skeleton_proxy_base_type);
    std::string name("skeleton_proxy<");
    name += typeid(T).name();
    name += ">";
    class_<skeleton_proxy<T>, bases<skeleton_proxy_base> >(name.c_str(), 
                                                           no_init);
  }

  // Register the saver and loader for the associated skeleton and
  // proxy, to allow (de-)serialization of skeletons via the proxy.
  direct_serialization_table<packed_iarchive, packed_oarchive>& table = 
    get_direct_serialization_table<packed_iarchive, packed_oarchive>();
  table.register_type(detail::skeleton_saver<T>(), 
                      detail::skeleton_loader<T>(), 
                      skeleton_proxy<T>(object(value)));

  // Register the rest of the skeleton/content mechanism, including
  // handlers that extract a skeleton proxy from a Python object and
  // extract the content from a Python object.
  detail::skeleton_content_handler handler;
  handler.get_skeleton_proxy = detail::do_get_skeleton_proxy<T>();
  handler.get_content = detail::do_get_content<T>();
  detail::register_skeleton_and_content_handler(type, handler);
}

} } } // end namespace boost::mpi::python

#endif // BOOST_MPI_PYTHON_SKELETON_AND_CONTENT_HPP

/* skeleton_and_content.hpp
sgqBOGPu3wmEvgDbp7PDdFRoNq9H6G/1bNf0HCKYpJLZN3ppHUKfmFQ5uy5NkjIe8ZprkOdkDSI30uq+UHf8yaafg6iBEnx0uaxOjF/brd+VxJnLZd0hSl7ZvRUIA3rT7Y61RJLgkM/UC2dVMs0GeYBAWgxKlj7UoOpfE201tCHJMgLIaqpc+e+0sydxdtkKQh9ygrw+1a7lTIAskRZOD9hl89HCVdJ8XX6sub54YpqtKXcjQHXBnIjWqwXVC46V8j89+mNDkr+M7o1z5D+F/BVU1bIKVTxNLyiOY8JiV4tVtJpA3pb7Y+h9rEnvNYSByIlponI+9de6Js/gkvlYOsyjpcNurNBpscIUsMKum4UVCnmJN/YzrDOE4MNz7Xb2o1xV1UBfyp8A+db6ezv7C0LKArGhcgkyiZCo79StU+2+epVAWMZWE/EvEgw9Ztp9vto8dUKeHYKK69Fa6/Df2lXdauLJmPM2ILOjwu266kikNZQtWtfidaSv2+nCqrtkkTMCLxk6Vmtb7Jxy9aZjWI4jCGGAeZJ50/125oGUSRFQB2HunFOhrnDkfYTA0sQaUuxcOwsn5XWc3Tmj1UGO7hNXsRU2Wz36KzvzN/Z6S/eLsOAKaxl0+vX26ukqbcu7dYG9eipGz2eph2hnSEpSJGS1pcpeFp1OncNLJ/rLE2H6rOpFTDBXecIDWhq/AFUkgSpebIxaS0231lJ4yqhdb66lSpYVDvOGDtORjbrLoR1KLledVY5VE2CXFA7zMaysuXaITyvk/AsOWAmgZpSr1QJgLgbVAwKD+HOGnut76rm+O7QmWVtpPbClDKI4FwoR+cbMr/fWVOfBKSOPOqLeEyj3mGyCOfQiWWfSOqywcl7ooMBoK7dkHpGn5LIaFPJBL7hzAloEjeTVS6OsxEMewisoZ9ntZtZ0a72Vuvi79dZ3P/+lP9gvll01YqZM5+5ZHgJRhX3WfjKcJRPtv68hW48VEbktTmBkY7wdGFmkrg6M3Fv9wNqc57yXYyIiI5KjbHkGfm3PPw/q6MQLL7aiE0OCIHpy1eXO6MnXA6WOatGuzkWuPi090RFmeK347eFguL7hKSKP5o0X/7pIT5EH4AzLGwt0YGEu/wLe9KWCpX4rwjB1jkyUfDNaYQWFDga2uwQeyR2FFX5K5m+ao5PbyGMlaKJs3f9ixhFPbO4NXzF+KM4z3T8f98MkpAeLVhT/Z0YaLXLzmdcpemw46VjH3RUHaZtbD0wQPrIDckT16PnD0POHj4u/57jv59TLtDuhnpVydUqHnsgO0intCC6eC0/078GrLGu3s67zb7CjV9faX0gwckaawsObLuehH2kP1YcvdToLwu9L2CDURyieovZrEGVedk8TnLLO5qtLb7Cn857hdF2c1EdqVHgESKbsVvtkW7E8y90z8sy41FEahnwn+8kzvurje7vsBbD/fuz7D2+x4tEm6Xi0Bc54tLT+e6fBGY92u8uKR3ttYEpPHZruwEDieLR5NddkOePR5lFcaTseLS0c377ajkebK/Fou6lrJkbFip1zX8QZj3b7r6Li0T4nr5oCH5dXTR0PyKsOLLtEXgNs++JPEI/AG675j7r0xo0vl7/f4sn6YuPJGnuMJxsy48nWnE/xZPllaWhv4snm0vmqRQniyeZFxZPt85M9xpPdMZf89YbRICBeRF3McYBgieQUU/TzNDV2tvZqmKzjyea4GckL15txWwtwtqWA48mOdJbsLyWDZUjETHD7VB1PNpul4/EzTBR5EgeioZSXU7QIZHkzwhlV9twf2VFlz5FKjkAlj9bI+vExR1TZfIoq+/qdJup8tC5fR5WlJcRUcS93RlTg050XONE=
*/