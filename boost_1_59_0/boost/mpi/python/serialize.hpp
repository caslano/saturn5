// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor

/** @file serialize.hpp
 *
 *  This file provides Boost.Serialization support for Python objects
 *  within Boost.MPI. Python objects can be serialized in one of two
 *  ways. The default serialization method involves using the Python
 *  "pickle" module to pickle the Python objects, transmits the
 *  pickled representation, and unpickles the result when
 *  received. For C++ types that have been exposed to Python and
 *  registered with register_serialized(), objects are directly
 *  serialized for transmissing, skipping the pickling step.
 */
#ifndef BOOST_MPI_PYTHON_SERIALIZE_HPP
#define BOOST_MPI_PYTHON_SERIALIZE_HPP

#include <boost/mpi/python/config.hpp>

#include <boost/python/object.hpp>
#include <boost/python/str.hpp>
#include <boost/python/extract.hpp>

#include <map>

#include <boost/function/function3.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/array_wrapper.hpp>
#include <boost/smart_ptr/scoped_array.hpp>

#include <boost/assert.hpp>

#include <boost/type_traits/is_fundamental.hpp>

#define BOOST_MPI_PYTHON_FORWARD_ONLY
#include <boost/mpi/python.hpp>

#include "bytesobject.h"

/************************************************************************
 * Boost.Python Serialization Section                                   *
 ************************************************************************/
#if !defined(BOOST_NO_SFINAE) && !defined(BOOST_NO_IS_CONVERTIBLE)
/**
 * @brief Declare IArchive and OArchive as a Boost.Serialization
 * archives that can be used for Python objects.
 *
 * This macro can only be expanded from the global namespace. It only
 * requires that Archiver be forward-declared. IArchiver and OArchiver
 * will only support Serialization of Python objects by pickling
 * them. If the Archiver type should also support "direct"
 * serialization (for C++ types), use
 * BOOST_PYTHON_DIRECT_SERIALIZATION_ARCHIVE instead.
 */
#  define BOOST_PYTHON_SERIALIZATION_ARCHIVE(IArchiver, OArchiver)        \
namespace boost { namespace python { namespace api {    \
  template<typename R, typename T>                      \
  struct enable_binary< IArchiver , R, T> {};           \
                                                        \
  template<typename R, typename T>                      \
  struct enable_binary< OArchiver , R, T> {};           \
} } } 
# else
#  define BOOST_PYTHON_SERIALIZATION_ARCHIVE(IArchiver, OArchiver)
#endif

/**
 * @brief Declare IArchiver and OArchiver as a Boost.Serialization
 * archives that can be used for Python objects and C++ objects
 * wrapped in Python.
 *
 * This macro can only be expanded from the global namespace. It only
 * requires that IArchiver and OArchiver be forward-declared. However,
 * note that you will also need to write
 * BOOST_PYTHON_DIRECT_SERIALIZATION_ARCHIVE_IMPL(IArchiver,
 * OArchiver) in one of your translation units.

DPG PICK UP HERE
 */
#define BOOST_PYTHON_DIRECT_SERIALIZATION_ARCHIVE(IArchiver, OArchiver) \
BOOST_PYTHON_SERIALIZATION_ARCHIVE(IArchiver, OArchiver)                \
namespace boost { namespace python { namespace detail {                 \
template<>                                                              \
BOOST_MPI_PYTHON_DECL direct_serialization_table< IArchiver , OArchiver >& \
 get_direct_serialization_table< IArchiver , OArchiver >();             \
}                                                                       \
                                                                        \
template<>                                                              \
struct has_direct_serialization< IArchiver , OArchiver> : mpl::true_ { }; \
                                                                        \
template<>                                                              \
struct output_archiver< IArchiver > { typedef OArchiver type; };        \
                                                                        \
template<>                                                              \
struct input_archiver< OArchiver > { typedef IArchiver type; };         \
} }

/**
 * @brief Define the implementation for Boost.Serialization archivers
 * that can be used for Python objects and C++ objects wrapped in
 * Python.
 *
 * This macro can only be expanded from the global namespace. It only
 * requires that IArchiver and OArchiver be forward-declared. Before
 * using this macro, you will need to declare IArchiver and OArchiver
 * as direct serialization archives with
 * BOOST_PYTHON_DIRECT_SERIALIZATION_ARCHIVE(IArchiver, OArchiver).
 */
#define BOOST_PYTHON_DIRECT_SERIALIZATION_ARCHIVE_IMPL(IArchiver, OArchiver) \
namespace boost { namespace python { namespace detail {                 \
template                                                                \
  class BOOST_MPI_PYTHON_DECL direct_serialization_table< IArchiver , OArchiver >; \
                                                                        \
template<>                                                              \
 BOOST_MPI_PYTHON_DECL                                                  \
 direct_serialization_table< IArchiver , OArchiver >&                   \
 get_direct_serialization_table< IArchiver , OArchiver >( )             \
{                                                                       \
  static direct_serialization_table< IArchiver, OArchiver > table;      \
  return table;                                                         \
}                                                                       \
} } }

namespace boost { namespace python {

/**
 * INTERNAL ONLY
 *
 * Provides access to the Python "pickle" module from within C++.
 */
class BOOST_MPI_PYTHON_DECL pickle {
  struct data_t;

public:
  static object dumps(object obj, int protocol = -1);
  static object loads(object s);
  
private:
  static void initialize_data();

  static data_t* data;
};

/**
 * @brief Whether the input/output archiver pair has "direct"
 * serialization for C++ objects exposed in Python.
 *
 * Users do not typically need to specialize this trait, as it will be
 * specialized as part of the macro
 * BOOST_PYTHON_DIRECT_SERIALIZATION_ARCHIVE.
 */
template<typename IArchiver, typename OArchiver>
struct has_direct_serialization : mpl::false_ { };

/**
 *  @brief A metafunction that determines the output archiver for the
 *  given input archiver.
 *
 * Users do not typically need to specialize this trait, as it will be
 * specialized as part of the macro
 * BOOST_PYTHON_DIRECT_SERIALIZATION_ARCHIVE.
 */
template<typename IArchiver> struct output_archiver { };

/**
 *  @brief A metafunction that determines the input archiver for the
 *  given output archiver.
 *
 * Users do not typically need to specialize this trait, as it will be
 * specialized as part of the macro
 * BOOST_PYTHON_DIRECT_SERIALIZATION_ARCHIVE.
 *
 */
template<typename OArchiver> struct input_archiver { };

namespace detail {

  /**
   * INTERNAL ONLY
   *
   * This class contains the direct-serialization code for the given
   * IArchiver/OArchiver pair. It is intended to be used as a
   * singleton class, and will be accessed when (de-)serializing a
   * Boost.Python object with an archiver that supports direct
   * serializations. Do not create instances of this class directly:
   * instead, use get_direct_serialization_table.
   */
  template<typename IArchiver, typename OArchiver>
  class BOOST_MPI_PYTHON_DECL direct_serialization_table
  {
  public:
    typedef boost::function3<void, OArchiver&, const object&, const unsigned int>
      saver_t;
    typedef boost::function3<void, IArchiver&, object&, const unsigned int>
      loader_t;

    typedef std::map<PyTypeObject*, std::pair<int, saver_t> > savers_t;
    typedef std::map<int, loader_t> loaders_t;

    /**
     * Retrieve the saver (serializer) associated with the Python
     * object @p obj.
     *
     *   @param obj The object we want to save. Only its (Python) type
     *   is important.
     *
     *   @param descriptor The value of the descriptor associated to
     *   the returned saver. Will be set to zero if no saver was found
     *   for @p obj.
     *
     *   @returns a function object that can be used to serialize this
     *   object (and other objects of the same type), if possible. If
     *   no saver can be found, returns an empty function object..
     */
    saver_t saver(const object& obj, int& descriptor)
    {
      typename savers_t::iterator pos = savers.find(obj.ptr()->ob_type);
      if (pos != savers.end()) {
        descriptor = pos->second.first;
        return pos->second.second;
      }
      else {
        descriptor = 0;
        return saver_t();
      }
    }

    /**
     * Retrieve the loader (deserializer) associated with the given
     * descriptor.
     *
     *  @param descriptor The descriptor number provided by saver()
     *  when determining the saver for this type.
     *
     *  @returns a function object that can be used to deserialize an
     *  object whose type is the same as that corresponding to the
     *  descriptor. If the descriptor is unknown, the return value
     *  will be an empty function object.
     */
    loader_t loader(int descriptor)
    {
      typename loaders_t::iterator pos = loaders.find(descriptor);
      if (pos != loaders.end())
        return pos->second;
      else
        return loader_t();
    }

    /**
     * Register the type T for direct serialization.
     *
     *  @param value A sample value of the type @c T. This may be used
     *  to compute the Python type associated with the C++ type @c T.
     *
     *  @param type The Python type associated with the C++ type @c
     *  T. If not provided, it will be computed from the same value @p
     *  value.
     */
    template<typename T>
    void register_type(const T& value = T(), PyTypeObject* type = 0)
    {
      // If the user did not provide us with a Python type, figure it
      // out for ourselves.
      if (!type) {
        object obj(value);
        type = obj.ptr()->ob_type;
      }

      register_type(default_saver<T>(), default_loader<T>(type), value, type);
    }

    /**
     * Register the type T for direct serialization.
     *
     *  @param saver A function object that will serialize a
     *  Boost.Python object (that represents a C++ object of type @c
     *  T) to an @c OArchive.
     *
     *  @param loader A function object that will deserialize from an
     *  @c IArchive into a Boost.Python object that represents a C++
     *  object of type @c T.
     *
     *  @param value A sample value of the type @c T. This may be used
     *  to compute the Python type associated with the C++ type @c T.
     *
     *  @param type The Python type associated with the C++ type @c
     *  T. If not provided, it will be computed from the same value @p
     *  value.
     */
    template<typename T>
    void register_type(const saver_t& saver, const loader_t& loader, 
                       const T& value = T(), PyTypeObject* type = 0)
    {
      // If the user did not provide us with a Python type, figure it
      // out for ourselves.
      if (!type) {
        object obj(value);
        type = obj.ptr()->ob_type;
      }

      int descriptor = savers.size() + 1;
      if (savers.find(type) != savers.end())
        return;

      savers[type] = std::make_pair(descriptor, saver);
      loaders[descriptor] = loader;
    }

  protected:
    template<typename T>
    struct default_saver {
      void operator()(OArchiver& ar, const object& obj, const unsigned int) {
        T value = extract<T>(obj)();
        ar << value;
      }
    };

    template<typename T>
    struct default_loader {
      default_loader(PyTypeObject* type) : type(type) { }

      void operator()(IArchiver& ar, object& obj, const unsigned int) {
        // If we can, extract the object in place.
        if (!is_fundamental<T>::value && obj && obj.ptr()->ob_type == type) {
          ar >> extract<T&>(obj)();
        } else {
          T value;
          ar >> value;
          obj = object(value);
        }
      }

    private:
      PyTypeObject* type;
    };

    savers_t savers;
    loaders_t loaders;
  };

  /**
   * @brief Retrieve the direct-serialization table for an
   * IArchiver/OArchiver pair.
   *
   * This function is responsible for returning a reference to the
   * singleton direct-serialization table. Its primary template is
   * left undefined, to force the use of an explicit specialization
   * with a definition in a single translation unit. Use the macro
   * BOOST_PYTHON_DIRECT_SERIALIZATION_ARCHIVE_IMPL to define this
   * explicit specialization.
   */
  template<typename IArchiver, typename OArchiver>
  direct_serialization_table<IArchiver, OArchiver>&
  get_direct_serialization_table();
} // end namespace detail 

/**
 * @brief Register the type T for direct serialization.
 *
 * The @c register_serialized function registers a C++ type for direct
 * serialization with the given @c IArchiver/@c OArchiver pair. Direct
 * serialization elides the use of the Python @c pickle package when
 * serializing Python objects that represent C++ values. Direct
 * serialization can be beneficial both to improve serialization
 * performance (Python pickling can be very inefficient) and to permit
 * serialization for Python-wrapped C++ objects that do not support
 * pickling.
 *
 *  @param value A sample value of the type @c T. This may be used
 *  to compute the Python type associated with the C++ type @c T.
 *
 *  @param type The Python type associated with the C++ type @c
 *  T. If not provided, it will be computed from the same value @p
 *  value.
 */
template<typename IArchiver, typename OArchiver, typename T>
void
register_serialized(const T& value = T(), PyTypeObject* type = 0)
{
  detail::direct_serialization_table<IArchiver, OArchiver>& table = 
    detail::get_direct_serialization_table<IArchiver, OArchiver>();
  table.register_type(value, type);
}

namespace detail {

/// Save a Python object by pickling it.
template<typename Archiver>
void 
save_impl(Archiver& ar, const boost::python::object& obj, 
          const unsigned int /*version*/,
          mpl::false_ /*has_direct_serialization*/)
{
  boost::python::object bytes = boost::python::pickle::dumps(obj);
  int   sz    = PyBytes_Size(bytes.ptr());
  char *data  = PyBytes_AsString(bytes.ptr());  
  ar << sz << boost::serialization::make_array(data, sz);
}

/// Try to save a Python object by directly serializing it; fall back
/// on pickling if required.
template<typename Archiver>
void 
save_impl(Archiver& ar, const boost::python::object& obj, 
          const unsigned int version,
          mpl::true_ /*has_direct_serialization*/)
{
  typedef Archiver OArchiver;
  typedef typename input_archiver<OArchiver>::type IArchiver;
  typedef typename direct_serialization_table<IArchiver, OArchiver>::saver_t
    saver_t;

  direct_serialization_table<IArchiver, OArchiver>& table = 
    get_direct_serialization_table<IArchiver, OArchiver>();

  int descriptor = 0;
  if (saver_t saver = table.saver(obj, descriptor)) {
    ar << descriptor;
    saver(ar, obj, version);
  } else {
    // Pickle it
    ar << descriptor;
    detail::save_impl(ar, obj, version, mpl::false_());
  }
}

/// Load a Python object by unpickling it
template<typename Archiver>
void 
load_impl(Archiver& ar, boost::python::object& obj, 
          const unsigned int /*version*/, 
          mpl::false_ /*has_direct_serialization*/)
{
  int len;
  ar >> len;
  boost::scoped_array<char> data(new char[len]);
  ar >> boost::serialization::make_array(data.get(), len);
  boost::python::object bytes(boost::python::handle<>(PyBytes_FromStringAndSize(data.get(), len)));
  obj = boost::python::pickle::loads(bytes);
}

/// Try to load a Python object by directly deserializing it; fall back
/// on unpickling if required.
template<typename Archiver>
void 
load_impl(Archiver& ar, boost::python::object& obj, 
          const unsigned int version,
          mpl::true_ /*has_direct_serialization*/)
{
  typedef Archiver IArchiver;
  typedef typename output_archiver<IArchiver>::type OArchiver;
  typedef typename direct_serialization_table<IArchiver, OArchiver>::loader_t
    loader_t;

  direct_serialization_table<IArchiver, OArchiver>& table = 
    get_direct_serialization_table<IArchiver, OArchiver>();

  int descriptor;
  ar >> descriptor;

  if (descriptor) {
    loader_t loader = table.loader(descriptor);
    BOOST_ASSERT(loader);

    loader(ar, obj, version);
  } else {
    // Unpickle it
    detail::load_impl(ar, obj, version, mpl::false_());
  }
}

} // end namespace detail

template<typename Archiver>
void 
save(Archiver& ar, const boost::python::object& obj, 
     const unsigned int version)
{
  typedef Archiver OArchiver;
  typedef typename input_archiver<OArchiver>::type IArchiver;
  detail::save_impl(ar, obj, version, 
                    has_direct_serialization<IArchiver, OArchiver>());
}

template<typename Archiver>
void 
load(Archiver& ar, boost::python::object& obj, 
     const unsigned int version)
{
  typedef Archiver IArchiver;
  typedef typename output_archiver<IArchiver>::type OArchiver;
  detail::load_impl(ar, obj, version, 
                    has_direct_serialization<IArchiver, OArchiver>());
}

template<typename Archive>
inline void 
serialize(Archive& ar, boost::python::object& obj, const unsigned int version)
{
  boost::serialization::split_free(ar, obj, version);
}

} } // end namespace boost::python

/************************************************************************
 * Boost.MPI-Specific Section                                           *
 ************************************************************************/
namespace boost { namespace mpi {
 class packed_iarchive;
 class packed_oarchive;
} } // end namespace boost::mpi

BOOST_PYTHON_DIRECT_SERIALIZATION_ARCHIVE(
  ::boost::mpi::packed_iarchive,
  ::boost::mpi::packed_oarchive)

namespace boost { namespace mpi { namespace python {

template<typename T>
void
register_serialized(const T& value, PyTypeObject* type)
{
  using boost::python::register_serialized;
  register_serialized<packed_iarchive, packed_oarchive>(value, type);
}

} } } // end namespace boost::mpi::python

#endif // BOOST_MPI_PYTHON_SERIALIZE_HPP

/* serialize.hpp
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
*/