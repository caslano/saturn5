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
                             (detail::c_data(this->extra::m_values), this->extra::m_values.size(), get_mpi_datatype<T>(),
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
                               (detail::c_data(this->extra::m_values), this->extra::m_values.size(), get_mpi_datatype<T>(),
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