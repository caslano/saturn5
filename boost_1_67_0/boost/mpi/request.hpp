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