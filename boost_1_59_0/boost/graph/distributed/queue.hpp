// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_QUEUE_HPP
#define BOOST_GRAPH_DISTRIBUTED_QUEUE_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/parallel/process_group.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace boost { namespace graph { namespace distributed {

/// A unary predicate that always returns "true".
struct always_push
{
  template<typename T> bool operator()(const T&) const { return true; }
};



/** A distributed queue adaptor.
 *
 * Class template @c distributed_queue implements a distributed queue
 * across a process group. The distributed queue is an adaptor over an
 * existing (local) queue, which must model the @ref Buffer
 * concept. Each process stores a distinct copy of the local queue,
 * from which it draws or removes elements via the @ref pop and @ref
 * top members.
 *
 * The value type of the local queue must be a model of the @ref
 * GlobalDescriptor concept. The @ref push operation of the
 * distributed queue passes (via a message) the value to its owning
 * processor. Thus, the elements within a particular local queue are
 * guaranteed to have the process owning that local queue as an owner.
 *
 * Synchronization of distributed queues occurs in the @ref empty and
 * @ref size functions, which will only return "empty" values (true or
 * 0, respectively) when the entire distributed queue is empty. If the
 * local queue is empty but the distributed queue is not, the
 * operation will block until either condition changes. When the @ref
 * size function of a nonempty queue returns, it returns the size of
 * the local queue. These semantics were selected so that sequential
 * code that processes elements in the queue via the following idiom
 * can be parallelized via introduction of a distributed queue:
 *
 *   distributed_queue<...> Q;
 *   Q.push(x);
 *   while (!Q.empty()) {
 *     // do something, that may push a value onto Q
 *   }
 *
 * In the parallel version, the initial @ref push operation will place
 * the value @c x onto its owner's queue. All processes will
 * synchronize at the call to empty, and only the process owning @c x
 * will be allowed to execute the loop (@ref Q.empty() returns
 * false). This iteration may in turn push values onto other remote
 * queues, so when that process finishes execution of the loop body
 * and all processes synchronize again in @ref empty, more processes
 * may have nonempty local queues to execute. Once all local queues
 * are empty, @ref Q.empty() returns @c false for all processes.
 *
 * The distributed queue can receive messages at two different times:
 * during synchronization and when polling @ref empty. Messages are
 * always received during synchronization, to ensure that accurate
 * local queue sizes can be determines. However, whether @ref empty
 * should poll for messages is specified as an option to the
 * constructor. Polling may be desired when the order in which
 * elements in the queue are processed is not important, because it
 * permits fewer synchronization steps and less communication
 * overhead. However, when more strict ordering guarantees are
 * required, polling may be semantically incorrect. By disabling
 * polling, one ensures that parallel execution using the idiom above
 * will not process an element at a later "level" before an earlier
 * "level".
 *
 * The distributed queue nearly models the @ref Buffer
 * concept. However, the @ref push routine does not necessarily
 * increase the result of @c size() by one (although the size of the
 * global queue does increase by one).
 */
template<typename ProcessGroup, typename OwnerMap, typename Buffer,
         typename UnaryPredicate = always_push>
class distributed_queue
{
  typedef distributed_queue self_type;

  enum {
    /** Message indicating a remote push. The message contains a
     * single value x of type value_type that is to be pushed on the
     * receiver's queue.
     */
    msg_push,
    /** Push many elements at once. */
    msg_multipush
  };

 public:
  typedef ProcessGroup                     process_group_type;
  typedef Buffer                           buffer_type;
  typedef typename buffer_type::value_type value_type;
  typedef typename buffer_type::size_type  size_type;

  /** Construct a new distributed queue.
   *
   * Build a new distributed queue that communicates over the given @p
   * process_group, whose local queue is initialized via @p buffer and
   * which may or may not poll for messages.
   */
  explicit
  distributed_queue(const ProcessGroup& process_group,
                    const OwnerMap& owner,
                    const Buffer& buffer,
                    bool polling = false);

  /** Construct a new distributed queue.
   *
   * Build a new distributed queue that communicates over the given @p
   * process_group, whose local queue is initialized via @p buffer and
   * which may or may not poll for messages.
   */
  explicit
  distributed_queue(const ProcessGroup& process_group = ProcessGroup(),
                    const OwnerMap& owner = OwnerMap(),
                    const Buffer& buffer = Buffer(),
                    const UnaryPredicate& pred = UnaryPredicate(),
                    bool polling = false);

  /** Construct a new distributed queue.
   *
   * Build a new distributed queue that communicates over the given @p
   * process_group, whose local queue is default-initalized and which
   * may or may not poll for messages.
   */
  distributed_queue(const ProcessGroup& process_group, const OwnerMap& owner,
                    const UnaryPredicate& pred, bool polling = false);

  /** Virtual destructor required with virtual functions.
   *
   */
  virtual ~distributed_queue() {}

  /** Push an element onto the distributed queue.
   *
   * The element will be sent to its owner process to be added to that
   * process's local queue. If polling is enabled for this queue and
   * the owner process is the current process, the value will be
   * immediately pushed onto the local queue.
   *
   * Complexity: O(1) messages of size O(sizeof(value_type)) will be
   * transmitted.
   */
  void push(const value_type& x);

  /** Pop an element off the local queue.
   *
   * @p @c !empty()
   */
  void pop() { buffer.pop(); }

  /**
   * Return the element at the top of the local queue.
   *
   * @p @c !empty()
   */
  value_type& top() { return buffer.top(); }

  /**
   * \overload
   */
  const value_type& top() const { return buffer.top(); }

  /** Determine if the queue is empty.
   *
   * When the local queue is nonempty, returns @c true. If the local
   * queue is empty, synchronizes with all other processes in the
   * process group until either (1) the local queue is nonempty
   * (returns @c true) (2) the entire distributed queue is empty
   * (returns @c false).
   */
  bool empty() const;

  /** Determine the size of the local queue.
   *
   * The behavior of this routine is equivalent to the behavior of
   * @ref empty, except that when @ref empty returns true this
   * function returns the size of the local queue and when @ref empty
   * returns false this function returns zero.
   */
  size_type size() const;

  // private:
  /** Synchronize the distributed queue and determine if all queues
   * are empty.
   *
   * \returns \c true when all local queues are empty, or false if at least
   * one of the local queues is nonempty.
   * Defined as virtual for derived classes like depth_limited_distributed_queue.
   */
  virtual bool do_synchronize() const;

 private:
  // Setup triggers
  void setup_triggers();

  // Message handlers
  void 
  handle_push(int source, int tag, const value_type& value, 
              trigger_receive_context);

  void 
  handle_multipush(int source, int tag, const std::vector<value_type>& values, 
                   trigger_receive_context);

  mutable ProcessGroup process_group;
  OwnerMap owner;
  mutable Buffer buffer;
  UnaryPredicate pred;
  bool polling;

  typedef std::vector<value_type> outgoing_buffer_t;
  typedef std::vector<outgoing_buffer_t> outgoing_buffers_t;
  shared_ptr<outgoing_buffers_t> outgoing_buffers;
};

/// Helper macro containing the normal names for the template
/// parameters to distributed_queue.
#define BOOST_DISTRIBUTED_QUEUE_PARMS                           \
  typename ProcessGroup, typename OwnerMap, typename Buffer,    \
  typename UnaryPredicate

/// Helper macro containing the normal template-id for
/// distributed_queue.
#define BOOST_DISTRIBUTED_QUEUE_TYPE                                    \
  distributed_queue<ProcessGroup, OwnerMap, Buffer, UnaryPredicate>

/** Synchronize all processes involved with the given distributed queue.
 *
 * This function will synchronize all of the local queues for a given
 * distributed queue, by ensuring that no additional messages are in
 * transit. It is rarely required by the user, because most
 * synchronization of distributed queues occurs via the @c empty or @c
 * size methods.
 */
template<BOOST_DISTRIBUTED_QUEUE_PARMS>
inline void
synchronize(const BOOST_DISTRIBUTED_QUEUE_TYPE& Q)
{ Q.do_synchronize(); }

/// Construct a new distributed queue.
template<typename ProcessGroup, typename OwnerMap, typename Buffer>
inline distributed_queue<ProcessGroup, OwnerMap, Buffer>
make_distributed_queue(const ProcessGroup& process_group,
                       const OwnerMap& owner,
                       const Buffer& buffer,
                       bool polling = false)
{
  typedef distributed_queue<ProcessGroup, OwnerMap, Buffer> result_type;
  return result_type(process_group, owner, buffer, polling);
}

} } } // end namespace boost::graph::distributed

#include <boost/graph/distributed/detail/queue.ipp>

#undef BOOST_DISTRIBUTED_QUEUE_TYPE
#undef BOOST_DISTRIBUTED_QUEUE_PARMS

#endif // BOOST_GRAPH_DISTRIBUTED_QUEUE_HPP

/* queue.hpp
RWi9L6opA+kn+pz+SpuBRbk2JKUsH40FZe/RyoBSa1hPCu4usO/obt6Tn7v8OrINvup1QS8noV/0/bYUYSmSKrbdRDfi7tD6boDkl/PEAegQQvR9m4JZZPU+xAzKZxw+tIp0U+m7+DoyL/fm42zIDsHt30SkyUkFOKCT0be/X5RHTJY/j65v3viLXW1fnc30zXom3DeXR+cZ3jBFwnEuAWX6eoQ8rDbnxsoonDSXXYhF+oDFhb5owxrPMzfy8gBPXrjvuKCU33+Q4i38HaG1m1CCs7P/9vHMgMIShb6086JTcsLJZeHc3zRjFjkJggf81ugWnXkvaYW7mJ6rhgVse7K9uFeWxdmPYoAtlAyGEF/jRb9WU5F0BfHIVwmXu8WtNQpYm8tkAH9sTtrsbdPJR7ZhCjpAqtqo0j0RKytWA54tZHjitoWXtWcFI/1+RS7WwYHcCeMQebBrzBkqZZ69LllR7oun3SUpf0VZG9Cyip2pyqwNSpK4RrnbRL7wuQYsNL5GPxSTsPewPBWbStAKxMmSsmG/CEj6BDavAByHR09/E7SYwhaHBmWxenEW27MkKlTJZ4uKGpm+gsfdikKSuf5NSoY0dsnEq/k60TruHs/NDxc1+SjseaBohQr85yKahFEt8JPoOlabHtND6B9ebVIb+gvQeipm//at44NhUhBx95+G/peUdiRQHkNz34MuX5hfyWEtiOJBZ/OahFitXGVjBzl1HLdKUzJJNeeThSnuyduxmH5ABlJ9hLOzRvKyX3CnSHxzBdIO2CNvEHmoiHjY5G9OADZobLL1pSe5trw3ydwdeYkJfyq/zAdLBaSjPNFF2sSqvh6rKI8uroTnp7VwQEKhEs/Xai/Ch6ro0FMpX/+yTroLgvgk7ohao/gwvfn6qhdVvjEeCM0nvvn68GpASiEMtNmmSIz3/k5CZrMGk4gYUOvUQgDJxZVYnjEb1+71VwMq8zAn3m0PjOl9QThKNHr2XIXlo9QbdOpZR4sXHZ8383DQ5PROo0iIDqt3KDlWerMaGsuuuJl6HbULSjYpsdgL+ATkoOhyHLa95q4tyHU5kR+GKhXwPhNFJVpDDEmYScFR88Z7TauIm0BJRuCFcXdX+Q6lImZZshS/yU5Af9nXf0mEybb1hoqlYj+0caJPGwC35og2cp5vxW97WCOBrnn46Z2O5k9EW2l88gt6sXgDHt2h3ZCNKMcePm7qPcnyarJdEdSoRg41KwpWYYaRQaE8+/NRfRC/rGi8Z1XJybYARCGRig0oO9WWVApQcrCvGIprXTUpKerMhcsH6AXyIwsskUnu9EHzFHlueS81Rvhb4KMo5lXduAo49Pn886KOrrc8jXSwR//xO0KV07h3DQJlzGVYcdgF+eIHDke4xf4Xpt0nYSQWzyV1TegTDmCLWFDl7CJHlnDG9EspiMZ70nogexlWgX2g+QPs6qdm3K1hH5f8X2W0V94BdGKGC9xxk6ikWQlLgh+g6r//Us17DOz5UXCbyRcZSHQB7k1wQyjpp+4rK/35d8h63ntCfX8xHdgYQTn34pPXIh7QWHObalmUyP3fCE8EryDVjYAhp8R7zFgUg/SyKETpBEzlP43DqNbGBMqfLn0gWYabLa9KwISHUdKQ09pAFkFpR3lQ8Xf8xlvSB1wSqGqZKdPTyjAKuX7cpxOjMrb978wkudY8pJ4om8jSoataZeadosTTO23CdZD1bO+X1ZsIO6rwHSzI3736HMzloWoh9CqHQH81EPz8O1aUp0ifgtsBwVZJRlShioBgKVcN106VgsMZcLi/lPI+ml/9N7KGB0J+3N/IPTZTRt0ky2vwfmC29ZMC6a9zlM6AfoMp7mDr+hXtTy5E9jEmRPaPu/MUu8KfZikj7xdAqjtCSzMEHn+zBqbhKc3HHAvZ+GP9NeBu2YUQjvBlHQd2Axh6R20i6BhU7cN+wZiE81O8J63LjKlC1UBN1dvM1VWmKlIY5SKNXV/nMh79tNa7Cm4I0h4whamgpE1riumJpJACexHA8H6mwA1+VTEhXf97OcXRwSx8uyl7zWU+JN0Q5x3aRhM6Lz1pyniDUwTkYB1eNsC4wmVc+uUwNyq9K54cWfrlHAAYIqKpNkhaWGg9DgaveFNp3deRm1q6OUqehS4STgNr0FFzntIyjtYpaR6mvyEjz0yG7EA6ZOvQ56++MoZqrghL35bKTAh84Se5q09uuEkYcTbya83tg20uGanHZvL52ZFjkBhF2uLE2utYU5AaTDHQwUXv8uB2ngO+tuwnhGnaJ50HAF+YB6esLjmDCrRodKrjpCKJskxc8e/gdR1EUuWBIp50lUHpHAQkq0TnKTV+uXoGYva+9p5bAZmiWGKEiO53bjkJPYOuzoqN2MmQsDuUrX9MCykM2YICM0X8pTKmjaiPfVMNcsPeg5v/L0pRGpmHojoMVBHxxxnLwxIkqxAwUoMiWXmMuYIf+l+utPBcVZWpceRbShCyqXb2f+LbszbKtjigvC1kXmsoY1ngl+d1RWPVGM/zT6rQZZn+oop7RHXEpAE1BPXzZ55pC9CHLkqDHhUOHDb8zOMBZB52REwmJ59M81h8KvEK9uuB4XNlHL0izrifYXVK1Yrfoo5ALhUxS/p8Ty84c45ptRAdzl7/2ZSsd+CJVbC33zC5dbpu477tFrOg1msDNUBkNLF9cHEbZlC/fFcVS1LHybZpzlOplaFrcuJgIre1LS/E7U3mSXwHD4xLKeyDjh+yV+Jxc7XDI+fDVysGntDukIv5zvg6k9KmxozMHlmg3X8fzbaE5c0OdIsQYTAe078DU9EJSnl2utv3xvreuyYxthkrhaQPB2VabyN9kGSh5hGEXGEvA2O4vVBxvIYAVVHbLFWjTHy1zmflwS74pbbc96rmPMio5iiroqUk7291ki7bT0XTahSIczm9GFAyxmtaHAAwPKOoaUZ+ChSooFaoiFgsa+s55tNUHfjkaZAYggWM0ufhX5FljcVgV4sCqUhV4+4/ePnryhTZwNZSMAdbHeEaEDG9wifcoQGGIyUV/CPEF7F+EXWslKjcmsHLDcMv1rh2+QHiPumiiJtYETfwlXvH+biGLMy9tcSNXBGKPKvZjBLWz7OP9QG9jvgwABL2fIfwv8Mu/0+P7W6bPeR0WGrszNps7zITuQRja3T0DW6DLB4rBInz61C+oIURy80Fz6ba762eMvpq+44s5c4mPTu8cAtQBU6Uzyr5fVxbUKUUAjpvBQbeV2u0eqpbfij8zjQlnGxdDJLKgFFEomE+vHNdzGCY4nc4NBPExg015glUnu9yDM4XE3oLkdcQ1guLWTs39LdYwGlqVBOTXvT9ulTufJ+rQWaf7Xrri6yByjRPNqpf7svYDaR3TnG6TO6L/j5dbSrThfEAoXp/AGxKwI6MdQ9VcZ1WH7f81uhmQ27Kv8mwxioygU7+Fq0+WGT7M6nczvOjc8Y1/5MUEbOgi6my1bez3RdmzzVI95N6gL2QPVN4iQHRaK03flFQjxOo+8U7g6teSJGLeKsee0ou7LkQd8fh3dxbmll+IRVxdUVviIbH64cuwOtZxvD9JiSHk4VXBoanGzfnxJWX4WWtUSIWkANcmn6cC80fYz6kLW6mR+mQwLcmn0hzFd5ZOwn155VEXDQeVmoaCJy0QT/9fvoOt6tDoYhJWuihHVaqJO+S73VEamTpmOFUfM+AlxFevQf1NLjvjtB89hsABn2XJqjOzQxyXMcpcsqvwCrSbro575TQ980yWOb+MTSiLl5iENiYu5tY9pAe0+f6udjo5jGUMnzmdrdBdQ99h4ufcHqK1fCWH3ZccbXAShUSgcWDR+l8lTRh9SmK0k/vvNPedXsN1XnbA2pGmW2PzhrYgz1muEXtOVWTHBV6JBeCr95uCCBZ1tZGcscN05JprefLz1OrERhafdYjQpbg12kePPEDpVmoyRa6+aq/3oXO5YWCQ9aiLmDTwly6eMxuPr5mbTWTiZiaDzdweQxthL6+njGAMYcveG298ANFmqZCFWa2Cl3f0wSOk+i/F9lbYAX/MRHcb5F5FWEUrU9KzutMq+0zIlbwxrCIQEZVhqpucWDUhLxCVLPEMu0s+H8QKZJejfHzZ5XLg2HlGD0DKN1hCr1Lt4py5VLU02mFF/ryoKZ1Pf7OzKRf/e5Dt45qq3WueQ+8yL3gK0Wh3sO6fU/x2txfcGlThtmmwGuuNFGPomPHLTeQY5if7mjovqGzWf1fMzeDo/LlrJxt/EFCNe9y9HymWykQcqJUT87MEmRt9q+S7Mu1nZEGeCtq77O+9mgapAP5nt1XYauVvOFy1h4NORFiRzpFpWgFpcRGurqTsJOHe60xEUZ3m28lFXkt/rBq8tilz9klg3Q/XE5jKPbz+qJt/1iDpH0HzMGJrhjYio9cscOKUJOtYSturJopTJWUaoRqlYXcLZR4g0dfm/RS/gvK/I9/ELSgnTLk+Vso7AXRZ7gJRPgzLDT0QfYyo3NucGt9CUN3tx+Sph51MwC3x4jWuRLjdRAMjcxx0J4iDMw3bQrA2ye+EeVj1wZ1elSruOHHM4DQ2mYhVUNdXYCv+HzSESa5Hp5V1mz5mbUSX5X5OjELaV/W8yBGNbF1Hnv2SD/PadO9f+tebWDIN1Ww++umqKkolaT5AWNK6lLcG11/6NXjrbqR/+OpkTFWiuZxb5fy3jVeNhVtf5XSOwe8N+RW3cgitU8YsMM+xZ32iqcHz2bVUkUObzf2kg6/P6nA0GBoC1omLEki9Cw2y/VxZW+/szaYpeHmPMghSuhdR5GoExfPsqiQbesfwmwrVKCKapzfY25akGH6nX2xH5nLkY9r/gY5sPXu9ImpEFb19uz2oyI9fmdfxHUHzUew7iV23DcQCFy3nFLxpy6US/vAd+OhOXIeiFoD09fAtnKlx+KZOlzmREAjT1hMxijhflgbroKbW7uVRQkOgmSmwGPif7GGDC55sW/gW8Em1RKsDQruv6fFr5MeztLuYkmWJOxzbSlNmHJ9MU0zx6U6BMRAzZMI0oWEDy5+OKez+zriYgrE2eKEz4Qb9czvCX0UlEZ5PWFUu1YR0KGi/Z6m+mp+1Rku2wghjNWNqDBOqVsW/iwVwUfD9KJn+bgxY4+37xEWK4LBFpxpsBUkCSf+pbCKnjDi07W3OFLZdqw2zs8EPe4WBtq4D3dyjnKXs1YDytS7TkUGBDr3PSw/Pxk7Z3qWiGy9ghF4kI5b/KdSDVFaozdACEOnu5IDXrcF1f1cvY00b/+9eUE04PKt3323s77xM9V2OmrenboKnO49ei002tp4+vPemx723iutttCwh6B5Clryetqw0QAtsJawxVqLtTq59LSk1xDyXiDCbwY2Rocygkeb35jigLadXIsKXrlQLUT381BBU6AHL0hyMaYO7Lk9uUZ7k8q5OCohwehW7jzs3xclyYPOjRBvfSP5d8J7yNABHl1zi/BnSz04Dkw+aLthe+IshRA/oea0/XiD2f3+14osikNz6VBfNWmu/njdp3C/bUYZfBD831HnXDBPaLuDsrSXrjqI7wNcYRCxh15zcMxS85yXtYLPy4CqEs70VesakFuwavNTbN80tJvUC3qbu39oLwMs9Qi/D+uuAwupm3eJjojDoCTmXUPPfyPIlLMn2fKibUx8m0VXIujObly7ixkFcu45BsJW262XHWaPQOhZbhN+JUZaInici3mqHcCujqpLg6bx5ebUI7DvckVdEYzTNdR7yEwMp+WI3p/oGhK96WQvtQrNY0BoKZIzLGGiyHGwWRfYgEaR8avAK25W1a75EAspnrgCxuQgwwhB09Uai+ttLG7vIXfY7z7Sxknj79ySo6+GX9saA76vSNXJ+obVRn4CTCwmeedtxW5zLZoHvjVSnDzAGy7YwAuivFDCMQ3tnCfMrkaeowmnXebEs+Pwg0gAijqrqJuAsa43f3+UUfyxEqXsPZDtsSnAthJ3pddtEwZAxqUqSTVVjhrdX1WGOj97Zzqt9/3XeQNdc4cjKExFGKngZuOj8t+tk9Exv66BeR8mYtilg5Dnsb/jm/Y7fyEbI4ueB65PwjoBTrFWyNXgIu3xM8llVkl3V/Y2fLfRsuYbaMp262nYEX9I3SC8eu90W0BtQ+XgtDyt491een+ecx+xvFKSJSDT2J0iMFpSVY9BTFbPrRs0kgvl1Plo+aZX064gei0UGx4ab74WPQyeEks8RtWVeFgYlsshb1hsGnaHxnc8Y8ZnZDOsgopXthL4N9EznbFt8D6BO/4zt2bYoCunyFvfZWD9ZJph+BRf1n5xBh5TOwTZY1+BWe6b+kwo4TXYUUSTc8xgtgtmtlu3UNn/1dsTtRoH/sfCYr6H5K5Qj6ZsqLPjQJuYZjUlZhJLEQOf9Z3mP819MrEU2qcgRZKoQbKrax2dptVnzaaijpX4/dqcnFDYyixTTkPRCEZdJW0z/XhGddyR8gv0sd+p1LcDINog/BQb82BAaC0fFfNgUyuOfRztRohK5JT0Sqc09yUGw4XOVaWcnx38C+ymaSA8Kfj/02/T3fBayiob7D7gYOh2SQr94gwK9eS/+USgBWDQTHqQsLBwcUAaBoddakWvlNUBbUTjz6yZnbbWLz6V080bPbcfKputfE3fg3YYNFSNK+Q02zqVg3CbBQmy/lu3j1mOt9lcYSc3n9/evL0/U8c5njccp7ynHLPuOafcvmczAeM5dqGMCZ951uY/jNLYjrCBm1+1/swPROuHXHWW70ppq7X0IazQstcSZt7o0Uk6k6UMPF0CgxvoD/18YEd90/gm8pl9KQU29WW7tlzJPWCH431MuvMU0stokfbEvqCvyraKThFgxMQYIuh3rVZy39hltDRNACCp6cvCCa4nhXtpyf7zLcGamlzLVbY/2BigdMcCEWThXS21saRweASg481+8p13EvgaRSxDMF6JXZ1hCSKlXNY01JdD3m2E8iLfeVIT4gGzrqdC7Uq8Iy5mrhxb6vCcw27fv7+/AccAAIF/gv4E/wn5E/on7E/4n4g/kX+i/kT/ifkT+yfuT/yfhD+Jf5L+JP9J+ZP6J+1P+p+MP5l/sv5k/8n5k/sn70/+n4I/hX+K/hT/KflT+qfsT/mfij+Vf6r+VP+p+VP7p+5P/Z+GP41/mv40/2n50/qn7U/7n44/nX+6/nT/6fnT+6fvT/+fgT+Df4b+DP8Z+TP6Z+zP+J+JP5N/pv5M/5n5M/tn7s/8n4U/i3+W/iz/Wfmz+mftz/qfjT+bf7b+bP/Z+bP7Z+/P/p+DP4d/jv4c/zn5c/rn7M/5n4s/l3+u/lz/uflz++fuz/2fhz+Pf57+PP95+fP65+3P+5+PP59/vv58//n5A3Dy9/6LfXWRLEX7YBmqtXKktMZ8oUW8OpWHAE1DmchK4AEOpEqCr8Sngw1oa4zmzLJ9JTsVW2Ym4GvzHd2o9a6P6XR35coDi6XkKnVvaQm/WrOBNUbrWw9LapIBNo6H6aCRwtZLAGbODm3H746n5QoKba+tiDXsisKk9StNb2eLicJ0R4YGbdeUTufXTjMMlyvhGX0rs5aWYjYkcaGg9NErXuvL5DoPN+egJhPKyo0a/kJjeZfGLEsqvg8CkTyJjySB7UNSsmv+
*/