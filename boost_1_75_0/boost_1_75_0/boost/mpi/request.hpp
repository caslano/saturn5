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
Ug2mlOTs1IRMw8bEBMNGPXXSBv3GhBRjkmFTRmaGIdmU+l5UT2rq1Kon6SLDRm/3D7rqmR7/XI3ET0V8CHTP+5v/67Ozc5IzN2UnpGbnpND40ZSZYCTVk7BpY3bixk2bcrKSc/RTs/bDrIo+kHoov6KhZlcVMYmqRzXOF9zI3KhPSk6mqUJSNrHEYMrZlJBJ7CFu5CRuyjRmZxgzTe9BFSXqk6dWRSmJU6sib/cPuiqaHv9c7cV/XfzXa6P3zteUbINho9G0KSHFsIlUfGIm6aFU4mtWin5TziZDpj4pI/OifP0wq6IP7rgoq6HeXrsnY5evMkpJpOKnZicmpCYmmhIMBlNSQkaGISPBlJqdnWRKzkg1bsp8L8poY8pFlNFFpmTe7h+oSe0MG/+vdPr0+OfSPX4q4r9eob/v8wGmpBxTMklUgnFTqjHBoM9ITMhMzM5JyEk15iQbcvSbsgxZU/P2w6zUp6XPiyp23VqxW+hryaE7DKbkVEOq3pBg2picmpCYWLkxIRO81+sz9FmbsnKysrPdm6XV9Q1oxfaGyupaVe+gE/wXrFfUxvQ4HVZSYbdYrdV2i8lq9VRzXOlYrW6FQyUrKdxWnJW9w5Sfr4Tn3ooq7FXefooySnMVT166QKVbLTUNKnYgrulxRKS2PlGfuD7RVTV+6qXgYy0Mx2twRAd/6XlQObfDLv7DMZ05lzw2hx0Pe3LVYFD+
*/