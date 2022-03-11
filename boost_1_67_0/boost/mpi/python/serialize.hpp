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
  static str dumps(object obj, int protocol = -1);
  static object loads(str s);
  
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
  boost::python::str py_string = boost::python::pickle::dumps(obj);
  int len = boost::python::extract<int>(py_string.attr("__len__")());
  const char* string = boost::python::extract<const char*>(py_string);
  ar << len << boost::serialization::make_array(string, len);
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

  boost::scoped_array<char> string(new char[len]);
  ar >> boost::serialization::make_array(string.get(), len);
  boost::python::str py_string(string.get(), len);
  obj = boost::python::pickle::loads(py_string);
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
4f6AI11KwQeyx3JyCXjROTsaVk/c3G/sZumKJSGAfcDoLIpXx7bcIYbA1X1nc1RuQ4oFesVWH5XtRhW7cSbcv0/cRXzNtNr9+QlXPw5TfWRpwHPvK1S8yW/VL6BcCubMTeoY1+S2/hrl2eJIkP4Hssnu5aOjV1/mSvZraDAqKuFePQ8ygEq5L8wzeQ4upPBfHmvwldi/ojlxyz8TJ97K8F26kYB5Lhob8Fi5mFzb7/OaO34F4690ZiS89Tvx2R/EYiQ/PeLc1KL5TOVM2IN+s2pi8snKJ2T7NVlIYNHxv+Vd6Qjk4yi9p00XhBWOS3PMb+sKxG7d1zsmEGhbEMcKSwpLNNiVZKyRCusTLqwgsi8vC+Au/zsqocw95j1Pz/6HL7LHJ+G+GbnshzXSIQJFU4nz/QRBCmX3yqZD9LfrBb/Lk2Q+OtxpdIJUymVk6UlnlWgVMQNFnF/BzETKFDsqwHnYclVzJfDmGxb8I4e4UqTvv9N9LQh6zPmoV98s6N8WcyfTExEvE4xakU7rx67P8PCgMIF3L03KNqqUd5bX3RGIfWw68oyQxKclnSXlwapgT97OmcGPFffNjArMXgY/TjdZ1pJE+sKPgxKbO7KU1ZuHExpEk3yiF5549QGxyKqNiNh937n5rSdBP563S6xBuQ/Yt/zsbrsuQlCyTQLf2ypdOKPwgKATcYGt7gxl7/amVLwRdYCbslXoibKlyxJP/kcueM0V9UadGlRXOb5QKkl8+zGb2NqSPhnzNOYnNVqB/G5/85vyJVdSGW8OH+3NN5NkfzvgIMNDxqmj56fnMVY5Xi9rTLFy8Toc46S8//nMuyH0SJ+sLumsMuXNKtXaMzALlDsXI4ypS0aOJL9BmiKz6aL0ND25GGH6wL7gSvBL45PS+5aWvwQ+QoLNrWha2JO2beUppGuen9MhsNMas5x37cnjnUvnbjFUFxJ7j7XPkpWLDb05qd9x1o9m6vmGMB5K772iK9ZeXzm0mKtHPcBvH31dCdPjcTaa+pJuZPRFX4WA5yTUACQOcjvpA2T8UoE59qUAB8BJFpZb0rvwl7tKBpuTcZ6l0mW8l8OOC9b08ZchVaRLjkZnF+M49q0J5IcxLlztoxwNRgvVrVFOUj6NNose+WweXINi/1QqkjRh1/tRVLbdNz7zkHMJykLvLI9j/+M7FnvyBPT4YZvgcpA6C+bsW9LeA+VbSRxVtykFnNUilXLtP5A++ScQs48GjVT5aXdsMalR+MfowxERmqkr4z7vLK9d+nsEF9IN6CPXOW+cgUvZLsYegmnt1Zi2ITgB0SVUAAAs/9NkgeVQM3S55GyrKa1pnIjS+Ir8eJ25zLh9bxF5D7azlxY8NewCTOiHUxreVyiwl/uHeYznsHu7vbEU59oeez8ci/O3mF+0FAYHDyY4SoHS+JquqPM19Xd/w86x9wSyqmX9Um0du62Jcaf0Kagf6wcdbdQd6fI/QAqh1ZOa54do+XovznDyItj82z22S6oxZ0B8sWG/LMxT9OVWJm9Vp9GF3zYrqvYta4cwlQSjHMZZig1l1iYCUYS+sdymuxSq/8nt03exBEQr2vVea9GbWAh0tEGvVkqBpVqyIx/yBzDUrEIXxPlwPHncuMjyH8ZEXA69VPmjLmE/jjWFemT5r621fwUs4cVM24XEvDwqeDBx/sjInP7pEo4TFL6EKyFytOJ/klU1aZJvgWN4IVIxJ6QTK3AONsr77BT8BPmV508Be/Kv7z68pRhtvJzEx9B/W+uGGki/YQYjAPEOCBxfxMExD6G+yKU2S+Hso7Gtj/qXdrMmbEyRJUjswOYBlZPxL0uWXKkiSO2RdGXES/BB79/XB1ag4FUrTogcZAQCsVSwKk84jb5lufRrqGg4GcV7LblUc3rxIOHMu9P0vnlRpYLLdBwBv2zsGFGUGn797wUM5hNRgeZyCaGM3KU6PrQ93GNnDG8TCHSlV9yY1FzMq7sPIk6pzfIiLytIRxDOv4BUwC1OfU54Lv/8e10cm+CPtU28lnKx7ctk7o3MhwPyP6XU4M+pRyxXq3ykPm8dKD6OsQMl3uF5wbj5GGNipqmR026Y7kFlxS7Vgubck/YN2w8nDGyGRn6UUoGtriYSlLH4wSCbokxpbhQ/yQL1BtL0TNrFWUexJl6szo78WI30J4U9z7zg6y+u18CnJKkHrBlU8QBsDIJ2j9ntRaNwQ4hxFVhM3a/+q4lIAvFeyEhXjA2G5Q1uEHmxThoTuld3TWeLo40IIfPHUKSePSq0BTgIQmoXCeSEKkSFD6vTN/Er+YrMqORUuXUiyQ1BfUFiUWjlTf9ySm7QCNKbDJEq2grbiRSlz9kdCb/bL1sayamsjZZcPoREFa63/uRlH3AuXtrkpIhSKwUgalT+aNHuZ9lSIaapQDbkYqzguKjfie9qPgQtV7PPPmqoSgG7/4WoKnZ9gOuhC/9rbWK82ShfePxwVMIPBNma2SGVktloITe66XZHWwYfH8dcpr3iYcGLtkTz0IR/0F34aSPzhJpTSwcP5fPhgasnhIry3YUgVyF4RO2TU9BaJ76RR7eUdYxjAHVUfhz6o5lt5G7YXgRfBVZq6NqF+7HeO/XH3kDSDx62MANwRnWl0gI5PqbsjzZrQ+fTYdyM6Z+Xm1Y1aN5ikXDGUI33zE3/OlFGlgZ5IlFLMfoMa2C6+cQV2NMPcP83kKEPaqjhx9YprGs2klnZcdraTcqY32r8cUOtst8uJTjjsZNig/jwEioa85KRNAefZ9xUB5DFm5U76rSYHAYIeX2d5dRzmf9dQppy8fcrGHnAGIMcGxhFsUB+n7SjjRGW3Lnbse7PrlzOevdFXbmiswoB87GrpbTQzA0rt8a/OcW6SV5XFj6T8bjW3ALrRRjA3En6GpeqVaBk+pvNjTurZISMvWdVXRcrDn+weB0ZarTZZfkzNOvSl51n19ca7nka9Uf80u03PJh+jOWQBEij9y/g0DVpzcZEviKLZxDVfGEunWMAXo7DTVlBsWOcO+OM+ciVBm6d0JvyLAH4ZoF+f/9f6AJAB/zjdAGRf+dW49JmYqIvdO5zP+IxJWsreUX1CdjgS33eQOa9X1fWOyaBFp6csueWnvZOhNaQYRj+nCtrSJcHl7HcWG01rGECtv5xcWXHMRl/5XwU1FxZ54MsVF6gyWiyR78rA2pz8zBbSlk8Hezx/404khwxoKbcuPB2LzWTWGz0AUSCPOWYOAvw+ctNNaMNFQqgZP/fIT8VYqmTif1wyNfT8pYjev6CfTZ4J2boQ93duuvHxYDdTLZbLkoXh7Bx+/E32RtayOzC0A5gXNeLFf7UcMv/PAtvjEAqI3vfL/Awg4JWN+uJuagkcxXTjzhgYQadVzrB5jfuhC1Fnf7iDDKN/oxQ+YdXNAmO0eV+LOOG7Knul/P58uLm3jUc6xLuOCUTeIw8AwjHr3A+fyP010LN5hVW/yQgoBYYl5MkYMfW3USpds0Xeu5vUjhQeX+D1Z0r+Q93lOfbhNkZzFdDlj+EgNwvMXm0I91De4pNnhg6ER2HW60/+11VaO+2z5FJolTLrHjMONyKXSwi5u65Z7H/PfEhcL8LptvmXsQyqlWhfpy6gtBSeoPGX7PBkuZPrAZ/PK60dscbFR6MI7nRCOTJHFvvvQPGfsPajs2fQ3mBL7tlP5GrlzCul2gSy/IcXS6SMt+MlDkfRvSX0OzXRoSikhA/bIX534lBHb7KVIyGYr/FPvNnKZKU6Ll7KiWHz47EcY/1YQMfqa8UeW4iyf3n5gE9DIUbTkZCcwZSC6mVtZHFTSM7GOSjWeKpOhzFqKnTUr7511YG4oK9qtN6mYjetyx2ZBHPYxvOgRKEzCXMx/37yckXUYKxPijzKUAEmsdaJSTESs7LGOEauG3SEKFVvArFydmQf0t99YEfixXGDM8MDOAnGYM9lS20bZN77KQS8B8PxmwxIBU3iAhcZPtIFOTEKx02pDa/oFoNyS/ZTzh2fEtvbxk7yYpiIbzHh+pAhGLK5LnfP+nwknbl3N41Dp10PnHilklR/cjTFInIXacRkU4hWudEsllEmniuftW8jDbLxF88vR21B5qpx3QftFsxVGjhefYxnIb4uLuY/LZagWcUEwjWOgY2N4VB0VJFGcn8qBXAElohK8dRBQU4DGzM5eHPoTovO54OcPyEpu9ZnApfm+tCyntzPpMhFyBzDU1IM7UJL2/jepLZZT6AGJN1Yt8PhAVelCZAW7xI4zi+MiYalYQX1VJaC9n5OAyllZqSk+uqQs1ZpTkdXKBk0D+xEbKV5MGdcee3ej7/zMd4WzY5a7lnGqfksklbyJzLraGsky6Cejcu4CJGtbAHD6e3NtNgQrjvk7yv0G3WUaIT3heUiOfXK82Xpa5fpYtz0tsmoUY75ELfc91rlVsh8qy2pwh10ntZd7n1nmL7AUyEqNhA10TyOa4ouyutE71YXIdXx3jZ9/FO4g39KJ1zpMA9bYz/zf2I41mYAO1k/HDMjY2jqzTLCNcNLp3dTOBaIi4EQxhXHW3sv1lz6RxhRhdrBfFCfbQTNANYWCVZfkBjtWCFrHlBt8Y0BpKPkpcVxEohCOR+whVmbRaoGozwToiJYFeWcQAdN2n1301BsGOS2DezyayQGLV4E0m0P/XsXaLbnAgfdQdOOWnUQ/G4dVVn4MXH6UToTQ4NiBZ/Qu1LNwvj3QTOn0C+KOLgnNtr4pq47LEiL9Jol8Dd/52WFlxyPx/5L34u/jux0mj9fgz982w/27eruzv8hc8OTf5bnRvtSu7Submbm4up+pKmGp7CpcJ2oT32RXKLD6pvne1srRHf7HhGNuCGYqixFrEOrA/+uBiwrd6DNUvf+/m6qDelovYMaGjEnMdq+XGq08LMygJ/nCL4SJB+xv7o/WZ8Mfos3P3QIugeWWaP15i26JxgFLdpmOpL3jyekw0b59nWwO7BM3nOKcN9z9F5UxSvfK/ajc9IobkSNsSK64w/wMIn8kLjuxCG++b1L+I2pyhuJ8hkpwthGgyJPTDsA52dIUiHyT5d74rGcDge6UI5Yj71i8UIYZ7GVBzA6ccihs/nQZVYep7xePkqwf5QDPvk3v3HaivZ/QAAvcNv5eey/HRgCTyjc8vCuIu36M6W0U0xi8estvqUpWqzxvt25GE2d8JPk5Ccgeb34LrNrd0weYBhNLnsPYNz293SqnSzsET60dLQJooxAEgz6GJoxOEjHnh4BwQIuooXiF+A3CLMzgpkun2RKW/9LASMaooV5li3lsO6he3MpG1tMpSK/a7Awq9wP4wVepIqvyfK74rYsLMnD2OipVlvxigoFUfaYvyeMCR88ffEKCdqyT0Z2nXRnycXdWK4uSUXzceRyY9wA8TGgSzan13xgPXfNdXeCqRceEiNzjG7mRe2RyYQ9ArQDrxUficAmXwA0VS7d/Ak/0IgCZ6CsqABQ4Af25BQFC5nwILNcglym2D4DqlCBcXLkaYYMOUO7Xa3uDIxrnfx1om3fyr/U7eWrKM/p7Iwmpu5Lj8sbAq8HYaxkfrJmgNHYU/No8qPQx/JjQmuvIA4QXsF1LUlar+a07ECT1KEJm/dEmPm2nZ3zoOvJ1A5A9637cj7NjFc3OHLrYZWP9Oipq7SA6IfR+On4Tw0bqpvDMvnKNMjWOFmDovzB5pJEmIIE8RfNTV5kRL5jBoVQ11hTLe8wbZDhCDdLKnKN2XeOYzRfxMqh/3OvHt/+t315rrWtuc5kMOoYTtCLyfv/mAanyfE8MZ1XpHzb0mVAYxhLVKrL+vGVToo5Ay68mBiiSnIp9TnEiNdq0cN2wHv9gVpkaep6yExDz0weBhbw0knqIyTT92Hz5euSJAII45+Qd210HHu49teFtyGt4ISD1FfY7xQaDtTVFLCU1zG5dbGGxfClFkQTpZLUkMg+u9++inMY4bBU1J3hrfCD3QpLrn5RMhOyAe6ry15vZxSVmhwOP8j60zUsx9Zi96hz2EFTnwU0xmBYdjHS+3BhGLsJttAAoBTEup+WeSDynGGSIggao66DhWKOwTPcy1B5r4LRW3K3uFopvwJc21JpTLrm8bwdegH/LkY67kx65dUy+dHPSfoaz99d2UZT1jOR1WTk9tsSGykZjaFDAsvlZtj9jx+fve+n4CVEAxex0lX6L1QJY285IBoJK6+hHPDugVfqrXP2ohBB3L4N1h279+5BbhqbvUQk2TIbv9dOBigFlMxx2Y2v390fUHrk+qPG5s1fo8LW8szf70U0KdO+48iSzsTZxCi0R5gApW7xPoTMg98dgsZlIkNdrsV9Ok9DCYsc6HPPE4GuGEbetHHQvXZbxO5tSD3lywDghf51RKBTXH9/bwXcfhwDHeKO3d44LjxVXCJrK1MBQMNfj+QeIVrQa5sIq5RDjdOp2F+x7iQgzTUrSPPwaMFME8ZQq02o/rpfwA74+213Rdn2LBAgbgKmy3r8cUHXq//K3eYKHxcDfO0yzhIxykKNzW380B8VhUK1TZVeB6z38fsvOL14jDlnU9LUaESOymRB/e/4ebxNiNRhw5mSvS38xLeL3YqnHYV7x4lHAuKqt722GJ7hcy/a4KYqbfACrce5j/BcXCYw8+fbxoeCJR+pwdazekIUi9AdF2P//zbZIHtTbHSKSQV/YVEd2Bf83A+Y71Pz1Yj5SJjMK0I/csLsW4Eww+g45/25U9SEgebCJkJbf3TnwJunUWXtODMmmA1o4pLHruqCrRUbtDxDHWOVP8eyE3I50p14lmbcCA5XXzOcfy/DE6VP+SiU6jOJpOwVWl/8ZrLqC7YGpZdzU16KD21XUdleqQ08tKSz41zzKJZcuqqxhznSlTQROtRP5aZe27uf30ssmnEQzk4ZSfrIVvGHqPXnysBQv1/VHg0+xsgHswFdnpDhnClGNiMjS55UUM3ajDXOp/kKaBL3iuPtOPxE+CYrpVwcs/i+xYHmPNdN9EPbCs49lcwh95FAMb1bgaGHrNuKHt0VVXtmbul+ULng+iGVZu/QrQnE63vsmTI+UerbHmmoM8pxtA1MOx78vfBuWg815bahXKjsr4SG4ghZmzc8gF6ydP9xtYNt0HeAQFK1vNDMVqaKXpahePK5TyLaMbhObzczcjBctbjxxeMWQNhxubOvRlRTSNpd+2sIZ62EQ+KJM6Y38b6EKT72bdqw9uU4bYw5l+w1zdkEnuPi2GOUfxDDNR+MqnNWkWtjw9Q4CveCiPnAuAA+czNPZsnaU9fncidRJPOoMem5PXvu1DK4fg+OhwZGi1Ee9wMegYbcTRcxgZDdAL3D4/lwgJa7uibZMd6SVZyfdjZD/qP/+15LNtFSkbEXdb+6lN+1sLRP5+yb0UEy8qekRIp62x17eKztc/wuqj3vvlI/ZIFths0DLNYiuEnmSYiNdC7E383RYbAn8u7tnoFfYaFa1Z76bbbZYYttc0jeTFkiGPz2Zf7EbULi1/X68k4h/XNBCNN6cGrrFUS5q+iFhKbo50F7no0VKya6ugNFCmWVkmzRyh1i/NpHV3qHzOFhER1NIwZGPlcab148g7vc1kT0v9Kl1N/j2tnFqzLOtqU5vFUiB5rUIWT05CbkeeJp09gNtMg1OWZm18QzYi66J0x6NeWP5Tq9UEVhh/1R7AqEBZrhyzGiNKk+MdPmLxjtcv3jiGFYL+zTcqcNGdx2AiCnFA7lgLZe//5hqiDTfhJhLNwxr2B8bZQu6rkTcSXt6QnT/+IfTWowqesYs+xbBI/28xHl03XX5ZFL1qXDZroEjBqj5IbBwki75BeMWOzgqN0w0/r9vfIRSOzAq34H29wwpidKy9EWg4vt4PSkoLQrlNXbheCsSax2tdYhy/CFxaL1SvYTFv0VdgPadK6Pi0bNzUfO1q9kDWtmVPnTCNjURdcjPWs0yxbXZnRMuWTa43mpKEbdKXtTEhvSh2BG/uPxlvedDvvH7J108e0Xi1jR776UgZfIiNjbt/cPPbBmDvmfvR/KrSjo345/92erLABbSVyDwQp4nnlLDbYbd37rfrkhAOn0n+cWuIifdXG+/DiMzFbN4JZ9mC9McVbW+oBts95c87V89yVCaw4cN4cF+O30ZuzI63G1M6yTZUfJALX6aUN5NX6RysgsoLhsH4gb8b6ex9nSymDCjJcd7PWB9220P/JUSByIow0XoYcoyiMTeD1IzZJO0g2rD9Ag02Cs+LqaYLWwN2Zu1dtlY73Hd568O0e+4yqyDt2ANodZBrak/dKSEromDTrUm2VRpGlPEvQJbltSHou1vpmXeKJB/FmV4Dr4DuTmODc6Hs2qPXkHwh+ZPYJiTfXkF+/ZS42rd7+7PShepLIN5hcghiJbJ7cbEOO5QNZn9hfP4J+DU1lH+Ev/Nr2D6hLXDtWde4i3CeWU6vNvUXnR1cXi1bxWTP2H4cy5AMZ/fZC+TsXsWdbfzP4l6LvR1PUp7UumPWu7t8q5H/UtKG7XUqMGpUSX8LlZgJmlYx7kZzETEUrfnEM0eBc4a8Lu7jY9Hd5VsdKaItnDnFZ6806G/EuaNF4TOEV4qn/yHNLydi+hq9IGyxbEmQBkfwaioO08Hi2PLxmceENYA708QuykLHvq7RudJsYA6d871gch2VA74MNf2M9Wa+8XLgtY8bi6TrpdOE8l8Hd0yydfCkG2dr4L8rXhXQli2lS/RzT6fOIw/U7QhGpjEZ6WdVBqaUoZ1ZiKz/NIfxHLpthX1xAJ2LPr1e5V/kDJeDxcvkb3HuqUOjBVVOdBKik5Mngx/beZZkwDcML3E62LIR2U/LL4kANXK64z9J3jrr45bvQsBvm11nXaxumDF6an/7Lx2dpbtWKxtd/G5ei34uUvIEkqMdfEQvvSGUwwt4QX9o++4tZ20WdmEPMqLJ2tv7mdpnrnkUsPbZJ9PoksdvOCp+enZwtubGRPKn6lvjqdzp/8RP4d5W0EOww57P3O/14mUcEc8Bf5fuxhZr73z1F+dje+nhB8PMc0eyMCznPCAljGjl75wgSKlOKJifTl98VqbPw3nNFu7hkB9b/bp4955Q5x/2fIQoqsfc53aa3e07hA0jkfsNWRPXeU4W3hnv5pdVi00OOeQ537UTb0gpC5iml1J1gvDIdbsyx014dMIc1i/tVztIbO38oEuoTlSLsVsiB9basWwo=
*/