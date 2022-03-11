// Copyright (C) 2018 Alain Miniussi <alain.miniussi@oca.eu>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Request implementation dtails

// This header should be included only after the communicator and request 
// classes has been defined.
#ifndef BOOST_MPI_REQUEST_HANDLERS_HPP
#define BOOST_MPI_REQUEST_HANDLERS_HPP

#include <boost/mpi/skeleton_and_content_types.hpp>

namespace boost { namespace mpi {

namespace detail {
/**
 * Internal data structure that stores everything required to manage
 * the receipt of serialized data via a request object.
 */
template<typename T>
struct serialized_irecv_data {
  serialized_irecv_data(const communicator& comm, T& value)
    : m_ia(comm), m_value(value) {}

  void deserialize(status& stat) 
  { 
    m_ia >> m_value; 
    stat.m_count = 1;
  }

  std::size_t     m_count;
  packed_iarchive m_ia;
  T&              m_value;
};

template<>
struct serialized_irecv_data<packed_iarchive>
{
  serialized_irecv_data(communicator const&, packed_iarchive& ia) : m_ia(ia) { }

  void deserialize(status&) { /* Do nothing. */ }

  std::size_t      m_count;
  packed_iarchive& m_ia;
};

/**
 * Internal data structure that stores everything required to manage
 * the receipt of an array of serialized data via a request object.
 */
template<typename T>
struct serialized_array_irecv_data
{
  serialized_array_irecv_data(const communicator& comm, T* values, int n)
    : m_count(0), m_ia(comm), m_values(values), m_nb(n) {}

  void deserialize(status& stat);

  std::size_t     m_count;
  packed_iarchive m_ia;
  T*              m_values;
  int             m_nb;
};

template<typename T>
void serialized_array_irecv_data<T>::deserialize(status& stat)
{
  T* v = m_values;
  T* end =  m_values+m_nb;
  while (v < end) {
    m_ia >> *v++;
  }
  stat.m_count = m_nb;
}

/**
 * Internal data structure that stores everything required to manage
 * the receipt of an array of primitive data but unknown size.
 * Such an array can have been send with blocking operation and so must
 * be compatible with the (size_t,raw_data[]) format.
 */
template<typename T, class A>
struct dynamic_array_irecv_data
{
  BOOST_STATIC_ASSERT_MSG(is_mpi_datatype<T>::value, "Can only be specialized for MPI datatypes.");

  dynamic_array_irecv_data(std::vector<T,A>& values)
    : m_count(-1), m_values(values) {}

  std::size_t       m_count;
  std::vector<T,A>& m_values;
};

template<typename T>
struct serialized_irecv_data<const skeleton_proxy<T> >
{
  serialized_irecv_data(const communicator& comm, skeleton_proxy<T> proxy)
    : m_isa(comm), m_ia(m_isa.get_skeleton()), m_proxy(proxy) { }

  void deserialize(status& stat) 
  { 
    m_isa >> m_proxy.object;
    stat.m_count = 1;
  }

  std::size_t              m_count;
  packed_skeleton_iarchive m_isa;
  packed_iarchive&         m_ia;
  skeleton_proxy<T>        m_proxy;
};

template<typename T>
struct serialized_irecv_data<skeleton_proxy<T> >
  : public serialized_irecv_data<const skeleton_proxy<T> >
{
  typedef serialized_irecv_data<const skeleton_proxy<T> > inherited;

  serialized_irecv_data(const communicator& comm, const skeleton_proxy<T>& proxy)
    : inherited(comm, proxy) { }
};
}

#if BOOST_MPI_VERSION >= 3
template<class Data>
class request::probe_handler
  : public request::handler,
    protected Data {

protected:
  template<typename I1>
  probe_handler(communicator const& comm, int source, int tag, I1& i1)
    : Data(comm, i1),
      m_comm(comm),
      m_source(source),
      m_tag(tag) {}
  // no variadic template for now
  template<typename I1, typename I2>
  probe_handler(communicator const& comm, int source, int tag, I1& i1, I2& i2)
    : Data(comm, i1, i2),
      m_comm(comm),
      m_source(source),
      m_tag(tag) {}

public:
  bool active() const { return m_source != MPI_PROC_NULL; }
  optional<MPI_Request&> trivial() { return boost::none; }
  void cancel() { m_source = MPI_PROC_NULL; }

  status wait() {
    MPI_Message msg;
    status stat;
    BOOST_MPI_CHECK_RESULT(MPI_Mprobe, (m_source,m_tag,m_comm,&msg,&stat.m_status));
    return unpack(msg, stat);
  }
  
  optional<status> test() {
    status stat;
    int flag = 0;
    MPI_Message msg;
    BOOST_MPI_CHECK_RESULT(MPI_Improbe, (m_source,m_tag,m_comm,&flag,&msg,&stat.m_status));
    if (flag) {
      return unpack(msg, stat);
    } else {
      return optional<status>();
    } 
  }

protected:
  friend class request;

  status unpack(MPI_Message& msg, status& stat) {
    int count;
    MPI_Datatype datatype = this->Data::datatype();
    BOOST_MPI_CHECK_RESULT(MPI_Get_count, (&stat.m_status, datatype, &count));
    this->Data::resize(count);
    BOOST_MPI_CHECK_RESULT(MPI_Mrecv, (this->Data::buffer(), count, datatype, &msg, &stat.m_status));
    this->Data::deserialize();
    m_source = MPI_PROC_NULL;
    stat.m_count = 1;
    return stat;
  }
  
  communicator const& m_comm;
  int m_source;
  int m_tag;
};
#endif // BOOST_MPI_VERSION >= 3

namespace detail {
template<class A>
struct dynamic_primitive_array_data {
  dynamic_primitive_array_data(communicator const&, A& arr) : m_buffer(arr) {}
  
  void* buffer() { return m_buffer.data(); }
  void  resize(std::size_t sz) { m_buffer.resize(sz); }
  void  deserialize() {}
  MPI_Datatype datatype() { return get_mpi_datatype<typename A::value_type>(); }
  
  A& m_buffer;
};

template<typename T>
struct serialized_data {
  serialized_data(communicator const& comm, T& value) : m_archive(comm), m_value(value) {}

  void* buffer() { return m_archive.address(); }
  void  resize(std::size_t sz) { m_archive.resize(sz); }
  void  deserialize() { m_archive >> m_value; }
  MPI_Datatype datatype() { return MPI_PACKED; }

  packed_iarchive m_archive;
  T& m_value;
};

template<>
struct serialized_data<packed_iarchive> {
  serialized_data(communicator const& comm, packed_iarchive& ar) : m_archive(ar) {}
  
  void* buffer() { return m_archive.address(); }
  void  resize(std::size_t sz) { m_archive.resize(sz); }
  void  deserialize() {}
  MPI_Datatype datatype() { return MPI_PACKED; }

  packed_iarchive& m_archive;
};

template<typename T>
struct serialized_data<const skeleton_proxy<T> > {
  serialized_data(communicator const& comm, skeleton_proxy<T> skel)
    : m_proxy(skel),
      m_archive(comm) {}
  
  void* buffer() { return m_archive.get_skeleton().address(); }
  void  resize(std::size_t sz) { m_archive.get_skeleton().resize(sz); }
  void  deserialize() { m_archive >> m_proxy.object; }
  MPI_Datatype datatype() { return MPI_PACKED; }

  skeleton_proxy<T> m_proxy;
  packed_skeleton_iarchive m_archive;
};

template<typename T>
struct serialized_data<skeleton_proxy<T> >
  : public serialized_data<const skeleton_proxy<T> > {
  typedef serialized_data<const skeleton_proxy<T> > super;
  serialized_data(communicator const& comm, skeleton_proxy<T> skel)
    : super(comm, skel) {}
};

template<typename T>
struct serialized_array_data {
  serialized_array_data(communicator const& comm, T* values, int nb)
    : m_archive(comm), m_values(values), m_nb(nb) {}

  void* buffer() { return m_archive.address(); }
  void  resize(std::size_t sz) { m_archive.resize(sz); }
  void  deserialize() {
    T* end = m_values + m_nb;
    T* v = m_values;
    while (v != end) {
      m_archive >> *v++;
    }
  }
  MPI_Datatype datatype() { return MPI_PACKED; }

  packed_iarchive m_archive;
  T*  m_values;
  int m_nb;
};

}

class BOOST_MPI_DECL request::legacy_handler : public request::handler {
public:
  legacy_handler(communicator const& comm, int source, int tag);
  
  void cancel() {
    for (int i = 0; i < 2; ++i) {
      if (m_requests[i] != MPI_REQUEST_NULL) {
        BOOST_MPI_CHECK_RESULT(MPI_Cancel, (m_requests+i));
      }
    }
  }
  
  bool active() const;
  optional<MPI_Request&> trivial();
  
  MPI_Request      m_requests[2];
  communicator     m_comm;
  int              m_source;
  int              m_tag;
};

template<typename T>
class request::legacy_serialized_handler 
  : public request::legacy_handler, 
    protected detail::serialized_irecv_data<T> {
public:
  typedef detail::serialized_irecv_data<T> extra;
  legacy_serialized_handler(communicator const& comm, int source, int tag, T& value)
    : legacy_handler(comm, source, tag),
      extra(comm, value)  {
    BOOST_MPI_CHECK_RESULT(MPI_Irecv,
			   (&this->extra::m_count, 1, 
			    get_mpi_datatype(this->extra::m_count),
			    source, tag, comm, m_requests+0));
    
  }

  status wait() {
    status stat;
    if (m_requests[1] == MPI_REQUEST_NULL) {
      // Wait for the count message to complete
      BOOST_MPI_CHECK_RESULT(MPI_Wait,
                             (m_requests, &stat.m_status));
      // Resize our buffer and get ready to receive its data
      this->extra::m_ia.resize(this->extra::m_count);
      BOOST_MPI_CHECK_RESULT(MPI_Irecv,
                             (this->extra::m_ia.address(), this->extra::m_ia.size(), MPI_PACKED,
                              stat.source(), stat.tag(), 
                              MPI_Comm(m_comm), m_requests + 1));
    }

    // Wait until we have received the entire message
    BOOST_MPI_CHECK_RESULT(MPI_Wait,
                           (m_requests + 1, &stat.m_status));

    this->deserialize(stat);
    return stat;    
  }
  
  optional<status> test() {
    status stat;
    int flag = 0;
    
    if (m_requests[1] == MPI_REQUEST_NULL) {
      // Check if the count message has completed
      BOOST_MPI_CHECK_RESULT(MPI_Test,
                             (m_requests, &flag, &stat.m_status));
      if (flag) {
        // Resize our buffer and get ready to receive its data
        this->extra::m_ia.resize(this->extra::m_count);
        BOOST_MPI_CHECK_RESULT(MPI_Irecv,
                               (this->extra::m_ia.address(), this->extra::m_ia.size(),MPI_PACKED,
                                stat.source(), stat.tag(), 
                                MPI_Comm(m_comm), m_requests + 1));
      } else
        return optional<status>(); // We have not finished yet
    } 

    // Check if we have received the message data
    BOOST_MPI_CHECK_RESULT(MPI_Test,
                           (m_requests + 1, &flag, &stat.m_status));
    if (flag) {
      this->deserialize(stat);
      return stat;
    } else 
      return optional<status>();
  }
};

template<typename T>
class request::legacy_serialized_array_handler 
  : public    request::legacy_handler,
    protected detail::serialized_array_irecv_data<T> {
  typedef detail::serialized_array_irecv_data<T> extra;

public:
  legacy_serialized_array_handler(communicator const& comm, int source, int tag, T* values, int n)
    : legacy_handler(comm, source, tag),
      extra(comm, values, n) {
    BOOST_MPI_CHECK_RESULT(MPI_Irecv,
                           (&this->extra::m_count, 1, 
                            get_mpi_datatype(this->extra::m_count),
                            source, tag, comm, m_requests+0));
  }

  status wait() {
    status stat;
    if (m_requests[1] == MPI_REQUEST_NULL) {
      // Wait for the count message to complete
      BOOST_MPI_CHECK_RESULT(MPI_Wait,
                             (m_requests, &stat.m_status));
      // Resize our buffer and get ready to receive its data
      this->extra::m_ia.resize(this->extra::m_count);
      BOOST_MPI_CHECK_RESULT(MPI_Irecv,
                             (this->extra::m_ia.address(), this->extra::m_ia.size(), MPI_PACKED,
                              stat.source(), stat.tag(), 
                              MPI_Comm(m_comm), m_requests + 1));
    }

    // Wait until we have received the entire message
    BOOST_MPI_CHECK_RESULT(MPI_Wait,
                           (m_requests + 1, &stat.m_status));

    this->deserialize(stat);
    return stat;
  }
  
  optional<status> test() {
    status stat;
    int flag = 0;
    
    if (m_requests[1] == MPI_REQUEST_NULL) {
      // Check if the count message has completed
      BOOST_MPI_CHECK_RESULT(MPI_Test,
                             (m_requests, &flag, &stat.m_status));
      if (flag) {
        // Resize our buffer and get ready to receive its data
        this->extra::m_ia.resize(this->extra::m_count);
        BOOST_MPI_CHECK_RESULT(MPI_Irecv,
                               (this->extra::m_ia.address(), this->extra::m_ia.size(),MPI_PACKED,
                                stat.source(), stat.tag(), 
                                MPI_Comm(m_comm), m_requests + 1));
      } else
        return optional<status>(); // We have not finished yet
    } 

    // Check if we have received the message data
    BOOST_MPI_CHECK_RESULT(MPI_Test,
                           (m_requests + 1, &flag, &stat.m_status));
    if (flag) {
      this->deserialize(stat);
      return stat;
    } else 
      return optional<status>();
  }
};

template<typename T, class A>
class request::legacy_dynamic_primitive_array_handler 
  : public request::legacy_handler,
    protected detail::dynamic_array_irecv_data<T,A>
{
  typedef detail::dynamic_array_irecv_data<T,A> extra;

public:
  legacy_dynamic_primitive_array_handler(communicator const& comm, int source, int tag, std::vector<T,A>& values)
    : legacy_handler(comm, source, tag),
      extra(values) {
    BOOST_MPI_CHECK_RESULT(MPI_Irecv,
                           (&this->extra::m_count, 1, 
                            get_mpi_datatype(this->extra::m_count),
                            source, tag, comm, m_requests+0));
  }

  status wait() {
    status stat;
    if (m_requests[1] == MPI_REQUEST_NULL) {
      // Wait for the count message to complete
      BOOST_MPI_CHECK_RESULT(MPI_Wait,
                             (m_requests, &stat.m_status));
      // Resize our buffer and get ready to receive its data
      this->extra::m_values.resize(this->extra::m_count);
      BOOST_MPI_CHECK_RESULT(MPI_Irecv,
                             (&(this->extra::m_values[0]), this->extra::m_values.size(), get_mpi_datatype<T>(),
                              stat.source(), stat.tag(), 
                              MPI_Comm(m_comm), m_requests + 1));
    }
    // Wait until we have received the entire message
    BOOST_MPI_CHECK_RESULT(MPI_Wait,
                           (m_requests + 1, &stat.m_status));
    return stat;    
  }

  optional<status> test() {
    status stat;
    int flag = 0;
    
    if (m_requests[1] == MPI_REQUEST_NULL) {
      // Check if the count message has completed
      BOOST_MPI_CHECK_RESULT(MPI_Test,
                             (m_requests, &flag, &stat.m_status));
      if (flag) {
        // Resize our buffer and get ready to receive its data
        this->extra::m_values.resize(this->extra::m_count);
        BOOST_MPI_CHECK_RESULT(MPI_Irecv,
                               (&(this->extra::m_values[0]), this->extra::m_values.size(), get_mpi_datatype<T>(),
                                stat.source(), stat.tag(), 
                                MPI_Comm(m_comm), m_requests + 1));
      } else
        return optional<status>(); // We have not finished yet
    } 

    // Check if we have received the message data
    BOOST_MPI_CHECK_RESULT(MPI_Test,
                           (m_requests + 1, &flag, &stat.m_status));
    if (flag) {
      return stat;
    } else 
      return optional<status>();
  }
};

class BOOST_MPI_DECL request::trivial_handler : public request::handler {

public:
  trivial_handler();
  
  status wait();
  optional<status> test();
  void cancel();
  
  bool active() const;
  optional<MPI_Request&> trivial();

private:
  friend class request;
  MPI_Request      m_request;
};

class request::dynamic_handler : public request::handler {
  dynamic_handler();
  
  status wait();
  optional<status> test();
  void cancel();
  
  bool active() const;
  optional<MPI_Request&> trivial();

private:
  friend class request;
  MPI_Request      m_requests[2];
};

template<typename T> 
request request::make_serialized(communicator const& comm, int source, int tag, T& value) {
#if defined(BOOST_MPI_USE_IMPROBE)
  return request(new probe_handler<detail::serialized_data<T> >(comm, source, tag, value));
#else
  return request(new legacy_serialized_handler<T>(comm, source, tag, value));
#endif
}

template<typename T>
request request::make_serialized_array(communicator const& comm, int source, int tag, T* values, int n) {
#if defined(BOOST_MPI_USE_IMPROBE)
  return request(new probe_handler<detail::serialized_array_data<T> >(comm, source, tag, values, n));
#else
  return request(new legacy_serialized_array_handler<T>(comm, source, tag, values, n));
#endif
}

template<typename T, class A>
request request::make_dynamic_primitive_array_recv(communicator const& comm, int source, int tag, 
                                                   std::vector<T,A>& values) {
#if defined(BOOST_MPI_USE_IMPROBE)
  return request(new probe_handler<detail::dynamic_primitive_array_data<std::vector<T,A> > >(comm,source,tag,values));
#else
  return request(new legacy_dynamic_primitive_array_handler<T,A>(comm, source, tag, values));
#endif
}

template<typename T>
request
request::make_trivial_send(communicator const& comm, int dest, int tag, T const* values, int n) {
  trivial_handler* handler = new trivial_handler;
  BOOST_MPI_CHECK_RESULT(MPI_Isend,
                         (const_cast<T*>(values), n, 
                          get_mpi_datatype<T>(),
                          dest, tag, comm, &handler->m_request));
  return request(handler);
}

template<typename T>
request
request::make_trivial_send(communicator const& comm, int dest, int tag, T const& value) {
  return make_trivial_send(comm, dest, tag, &value, 1);
}

template<typename T>
request
request::make_trivial_recv(communicator const& comm, int dest, int tag, T* values, int n) {
  trivial_handler* handler = new trivial_handler;
  BOOST_MPI_CHECK_RESULT(MPI_Irecv,
                         (values, n, 
                          get_mpi_datatype<T>(),
                          dest, tag, comm, &handler->m_request));
  return request(handler);
}

template<typename T>
request
request::make_trivial_recv(communicator const& comm, int dest, int tag, T& value) {
  return make_trivial_recv(comm, dest, tag, &value, 1);
}

template<typename T, class A>
request request::make_dynamic_primitive_array_send(communicator const& comm, int dest, int tag, 
                                                   std::vector<T,A> const& values) {
#if defined(BOOST_MPI_USE_IMPROBE)
  return make_trivial_send(comm, dest, tag, values.data(), values.size());
#else
  {
    // non blocking recv by legacy_dynamic_primitive_array_handler
    // blocking recv by status recv_vector(source,tag,value,primitive)
    boost::shared_ptr<std::size_t> size(new std::size_t(values.size()));
    dynamic_handler* handler = new dynamic_handler;
    request req(handler);
    req.preserve(size);
    
    BOOST_MPI_CHECK_RESULT(MPI_Isend,
                           (size.get(), 1,
                            get_mpi_datatype(*size),
                            dest, tag, comm, handler->m_requests+0));
    BOOST_MPI_CHECK_RESULT(MPI_Isend,
                           (const_cast<T*>(values.data()), *size, 
                            get_mpi_datatype<T>(),
                            dest, tag, comm, handler->m_requests+1));
    return req;
  }
#endif
}

inline
request::legacy_handler::legacy_handler(communicator const& comm, int source, int tag)
  : m_comm(comm),
    m_source(source),
    m_tag(tag)
{
  m_requests[0] = MPI_REQUEST_NULL;
  m_requests[1] = MPI_REQUEST_NULL;
}
    
}}

#endif // BOOST_MPI_REQUEST_HANDLERS_HPP

/* request_handlers.hpp
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
*/