// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file request.hpp
 *
 *  This header defines the class @c request, which contains a request
 *  for non-blocking communication.
 */
#ifndef BOOST_MPI_REQUEST_HPP
#define BOOST_MPI_REQUEST_HPP

#include <boost/mpi/config.hpp>
#include <boost/mpi/status.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/mpi/packed_iarchive.hpp>

namespace boost { namespace mpi {

class status;
class communicator;

/**
 *  @brief A request for a non-blocking send or receive.
 *
 *  This structure contains information about a non-blocking send or
 *  receive and will be returned from @c isend or @c irecv,
 *  respectively.
 */
class BOOST_MPI_DECL request 
{
 public:
  /**
   *  Constructs a NULL request.
   */
  request();

  /**
   * Send a known number of primitive objects in one MPI request.
   */
  template<typename T>
  static request make_trivial_send(communicator const& comm, int dest, int tag, T const& value);
  template<typename T>
  static request make_trivial_send(communicator const& comm, int dest, int tag, T const* values, int n);
  static request make_packed_send(communicator const& comm, int dest, int tag, void const* values, std::size_t n);

  static request make_bottom_send(communicator const& comm, int dest, int tag, MPI_Datatype tp);
  static request make_empty_send(communicator const& comm, int dest, int tag);
  /**
   * Receive a known number of primitive objects in one MPI request.
   */
  template<typename T>
  static request make_trivial_recv(communicator const& comm, int dest, int tag, T& value);
  template<typename T>
  static request make_trivial_recv(communicator const& comm, int dest, int tag, T* values, int n);

  static request make_bottom_recv(communicator const& comm, int dest, int tag, MPI_Datatype tp);
  static request make_empty_recv(communicator const& comm, int dest, int tag);
  /**
   * Construct request for simple data of unknown size.
   */
  static request make_dynamic();
  /**
   *  Constructs request for serialized data.
   */
  template<typename T>
  static request make_serialized(communicator const& comm, int source, int tag, T& value);
  /**
   *  Constructs request for array of complex data.
   */  
  template<typename T>
  static request make_serialized_array(communicator const& comm, int source, int tag, T* values, int n);
  /**
   *  Request to recv array of primitive data.
   */
  template<typename T, class A>
  static request
  make_dynamic_primitive_array_recv(communicator const& comm, int source, int tag, 
                                    std::vector<T,A>& values);
  /**
   *  Request to send array of primitive data.
   */
  template<typename T, class A>
  static request
  make_dynamic_primitive_array_send(communicator const& comm, int source, int tag, 
                                    std::vector<T,A> const& values);
  /**
   *  Wait until the communication associated with this request has
   *  completed, then return a @c status object describing the
   *  communication.
   */
  status wait() { return m_handler ? m_handler->wait() : status(); }

  /**
   *  Determine whether the communication associated with this request
   *  has completed successfully. If so, returns the @c status object
   *  describing the communication. Otherwise, returns an empty @c
   *  optional<> to indicate that the communication has not completed
   *  yet. Note that once @c test() returns a @c status object, the
   *  request has completed and @c wait() should not be called.
   */
  optional<status> test() { return active() ? m_handler->test() : optional<status>(); }

  /**
   *  Cancel a pending communication, assuming it has not already been
   *  completed.
   */
  void cancel() { if (m_handler) { m_handler->cancel(); } m_preserved.reset(); }
  
  /**
   * The trivial MPI requet implenting this request, provided it's trivial.
   * Probably irrelevant to most users.
   */
  optional<MPI_Request&> trivial() { return (m_handler
					     ? m_handler->trivial()
					     : optional<MPI_Request&>()); }

  /**
   * Is this request potentialy pending ?
   */
  bool active() const { return bool(m_handler) && m_handler->active(); }
  
  // Some data might need protection while the reqest is processed.
  void preserve(boost::shared_ptr<void> d);

  class handler {
  public:
    virtual BOOST_MPI_DECL ~handler() = 0;
    virtual status wait() = 0;
    virtual optional<status> test() = 0;
    virtual void cancel() = 0;
    
    virtual bool active() const = 0;
    virtual optional<MPI_Request&> trivial() = 0;
  };
  
 private:
  
  request(handler *h) : m_handler(h) {};

  // specific implementations
  class legacy_handler;
  class trivial_handler;  
  class dynamic_handler;
  template<typename T> class legacy_serialized_handler;
  template<typename T> class legacy_serialized_array_handler;
  template<typename T, class A> class legacy_dynamic_primitive_array_handler;
#if BOOST_MPI_VERSION >= 3
  template<class Data> class probe_handler;
#endif
 private:
  shared_ptr<handler> m_handler;
  shared_ptr<void>    m_preserved;
};

} } // end namespace boost::mpi

#endif // BOOST_MPI_REQUEST_HPP

/* request.hpp
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
*/