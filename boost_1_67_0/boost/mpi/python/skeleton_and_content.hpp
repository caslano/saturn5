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
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
*/