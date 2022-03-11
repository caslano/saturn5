//
// buffered_stream.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BUFFERED_STREAM_HPP
#define BOOST_ASIO_BUFFERED_STREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffered_read_stream.hpp>
#include <boost/asio/buffered_write_stream.hpp>
#include <boost/asio/buffered_stream_fwd.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Adds buffering to the read- and write-related operations of a stream.
/**
 * The buffered_stream class template can be used to add buffering to the
 * synchronous and asynchronous read and write operations of a stream.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Stream>
class buffered_stream
  : private noncopyable
{
public:
  /// The type of the next layer.
  typedef typename remove_reference<Stream>::type next_layer_type;

  /// The type of the lowest layer.
  typedef typename next_layer_type::lowest_layer_type lowest_layer_type;

  /// The type of the executor associated with the object.
  typedef typename lowest_layer_type::executor_type executor_type;

  /// Construct, passing the specified argument to initialise the next layer.
  template <typename Arg>
  explicit buffered_stream(Arg& a)
    : inner_stream_impl_(a),
      stream_impl_(inner_stream_impl_)
  {
  }

  /// Construct, passing the specified argument to initialise the next layer.
  template <typename Arg>
  explicit buffered_stream(Arg& a, std::size_t read_buffer_size,
      std::size_t write_buffer_size)
    : inner_stream_impl_(a, write_buffer_size),
      stream_impl_(inner_stream_impl_, read_buffer_size)
  {
  }

  /// Get a reference to the next layer.
  next_layer_type& next_layer()
  {
    return stream_impl_.next_layer().next_layer();
  }

  /// Get a reference to the lowest layer.
  lowest_layer_type& lowest_layer()
  {
    return stream_impl_.lowest_layer();
  }

  /// Get a const reference to the lowest layer.
  const lowest_layer_type& lowest_layer() const
  {
    return stream_impl_.lowest_layer();
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return stream_impl_.lowest_layer().get_executor();
  }

  /// Close the stream.
  void close()
  {
    stream_impl_.close();
  }

  /// Close the stream.
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    stream_impl_.close(ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Flush all data from the buffer to the next layer. Returns the number of
  /// bytes written to the next layer on the last write operation. Throws an
  /// exception on failure.
  std::size_t flush()
  {
    return stream_impl_.next_layer().flush();
  }

  /// Flush all data from the buffer to the next layer. Returns the number of
  /// bytes written to the next layer on the last write operation, or 0 if an
  /// error occurred.
  std::size_t flush(boost::system::error_code& ec)
  {
    return stream_impl_.next_layer().flush(ec);
  }

  /// Start an asynchronous flush.
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_flush(
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return stream_impl_.next_layer().async_flush(
        BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
  }

  /// Write the given data to the stream. Returns the number of bytes written.
  /// Throws an exception on failure.
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    return stream_impl_.write_some(buffers);
  }

  /// Write the given data to the stream. Returns the number of bytes written,
  /// or 0 if an error occurred.
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return stream_impl_.write_some(buffers, ec);
  }

  /// Start an asynchronous write. The data being written must be valid for the
  /// lifetime of the asynchronous operation.
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_write_some(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return stream_impl_.async_write_some(buffers,
        BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
  }

  /// Fill the buffer with some data. Returns the number of bytes placed in the
  /// buffer as a result of the operation. Throws an exception on failure.
  std::size_t fill()
  {
    return stream_impl_.fill();
  }

  /// Fill the buffer with some data. Returns the number of bytes placed in the
  /// buffer as a result of the operation, or 0 if an error occurred.
  std::size_t fill(boost::system::error_code& ec)
  {
    return stream_impl_.fill(ec);
  }

  /// Start an asynchronous fill.
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_fill(
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return stream_impl_.async_fill(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
  }

  /// Read some data from the stream. Returns the number of bytes read. Throws
  /// an exception on failure.
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    return stream_impl_.read_some(buffers);
  }

  /// Read some data from the stream. Returns the number of bytes read or 0 if
  /// an error occurred.
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return stream_impl_.read_some(buffers, ec);
  }

  /// Start an asynchronous read. The buffer into which the data will be read
  /// must be valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_read_some(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return stream_impl_.async_read_some(buffers,
        BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
  }

  /// Peek at the incoming data on the stream. Returns the number of bytes read.
  /// Throws an exception on failure.
  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers)
  {
    return stream_impl_.peek(buffers);
  }

  /// Peek at the incoming data on the stream. Returns the number of bytes read,
  /// or 0 if an error occurred.
  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return stream_impl_.peek(buffers, ec);
  }

  /// Determine the amount of data that may be read without blocking.
  std::size_t in_avail()
  {
    return stream_impl_.in_avail();
  }

  /// Determine the amount of data that may be read without blocking.
  std::size_t in_avail(boost::system::error_code& ec)
  {
    return stream_impl_.in_avail(ec);
  }

private:
  // The buffered write stream.
  typedef buffered_write_stream<Stream> write_stream_type;
  write_stream_type inner_stream_impl_;

  // The buffered read stream.
  typedef buffered_read_stream<write_stream_type&> read_stream_type;
  read_stream_type stream_impl_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BUFFERED_STREAM_HPP

/* buffered_stream.hpp
SNkVtng3ycSxeISByRNqNVZrYmZSzOT3TO8bj2fCKa0Nicrh6FaWNG0b5bpWAJl2J3+/CMzj8BB/LAz/fnIMDnLrkChr64EtQdPl9T8K6qGRqJm1pOz9ftWOW4wKDI5LBq5pTjDlptnVMIoudAEqry38hy38kjECSn2r65ODTyRNiThEBCd2E/E4yAQreJsTTvqfAWaExobvAT4aRqk/uxoQaereJ3qLlT0NdJrNOxqqgqTPOxqsgqTROxougsV8UIf4xu8FwtM9VdEu2oE9aEpHOTTvA8CZPu67LSI3LWD0pa0YHd+JPiyRAqvjSyJzkxqDfdNzfd8nxMeeaXfNcNOU0aKkpjD5pteqpKbjSP0+0rIKiEs7xcd4yCm3JucO9Obqad23dBOAAYVpSUFFF1LO35kdM9AzZACFeh1AvSi3VjQ6YKEA+nl5Brl5+gb6+ru7+nt6eQTdgvyuT8+wlIyYuKyAvListLQEFDygBAw0kLS0JOCoNL9xkooKEBQdj4yJjgea6sGRDAAUzRfuNgCgk3qcHMAepdcRHuDBJAoMGPjz6UFxPMJv92liHBbyTg2Z+J2YPVET6E+45f4D0i7q4AwLHjYAAsAkk6VK370WMpqyVQ58fTm/CAuB2J0awne1yXcRyIfeFl57vlO8aFDcE2IvnyevUQMKeWNtIH07cHQvGn53/x9C533Qe4BvQsV4sWszPrrvhcejd3hYXVPR5x+BAHScW3ihF5Pb7tI53Z8CtNuXg6aC+1u42x2f76CctD8/QtGmbn9vfrDFjH4eN3eqQAHM/0CIk6+iY+1FtPTh4+d+GwKLiSgBBbgGROddJj7AZ+eA8/7QYI7bm9M0mdzU3oKlYcezkkI1FT0IG6WGizv8idbbx4tTVjXVWsaq3sGWfjql/SfeurazxuOwotrFkaU9ZzECGUtXgmrTdi/PB6ubQZskkOdTKFaR8U5E021hlJyekYRhynAXjB4Fk4ZCep7bjNZkbJT8uJhb399zrlf8o/zD+C23Dvpt9MUlsS+P8xqSdX6of2SN8efY1ETariV5Y3N34juxrArjuO6fYnfwqkJptnQl+GJR/diHVnSKMQ96URFjos3PbILDkTnHTzlb2k8L2w/eYgb1T5lM9JvPPGkI4OsIODPAZU/TRBUNH8jnFDHEBxLWJ4a+PcS7ECgYfiAIAAIuMOXM93MgOITnV/yjHkfOE9/x548E1s4P6kkBvRX5J4AvXXnfD039aW42Pz5An3TSvV2Xn+Tx+6Pea/YVX1Nk3Sc83it9bY8sKZ3Un8MdGvtdfYRSydO/5uOyCT9PCbqLpkIPU2QDuwGVHTVU9dct70Q1aij09uEFavDoOwcodk4dDDQ1r/ThrXeW6ylIZkefcddLZ63fzgPWvvXdtS6tes/vdvGdtS6rPmN24fPiA99x3qFUdK5UunTdvec0ZRZ/01sXtSwfWl3/nkX7LC1d/pRVmxp++TirWeXp/FQF9DLewKtd+CWBMwIzSkKx4FfrzX9H9N7/6zSJTZrdOTcI5iLZpxbhK+3HxJip5JQUxEwz7uIpRbmt4Uw68OF6+nHLes9x13vsIev7+ckE+VGqUf5+ubzFY+ei/xnZ3vjsaWD74bNEQGDu//v/Ph7O2tgyLbS+hICCELEAfVte9v9+R8quLUHgLqO4PcR1nw7SpoE9GX0rPOcpyc3LVVePV/O247VdzsMIDlpTuZqzGrqOnMpKeUn4G1711E+dRvqPz86HT8GNidEHXZobKysaHJzL8w8a08xbDsNDp/VmJV140sVPYJrZj16aW7TPxGTDFxMT3fD0ACXB2NDEAA3JMMH4+NgAIeX4eD9FXx8lwXQ/xRiNMCV+Xz/l8NDQeP80CenwxDjREOn4b6VCQUo6PTZAOk1B8J3D+NCp/QNrinv8Aq1LrAtmqEhfK35LX1tzZaC/MzrQ2z0U4CeyFeQn0uLr59UCCBzBAAQckQQNHHH1+14BCRwhBwgsZQ8HLMUMCiyFfZ/D8LjJTd35A4/4iF1ZeNn5E5yT4uL8/PoaUvgZsQcy+iNTBsysLZO1yfu9dzbl9e2S0DONgvS+Evm9w/TFR/bIwd76DS24w3Bmdgg1sUHHsVWCdSyT0F5PETm7TGStF7CS0iQjYUlhQTHyQvzITAu3YOHaiq4cezJQPNja8NKK0rI5NjKNYwA8valH5o9L//vjJsvrC5XQ3TPkoKooPNSKUKYqKMBAxnsllCZAh/0djFjGHh7Uy9GLEcXyyEmtT7iHbNO9jphTJ6H2IUe1sTsQlXut8b7yPmA9XT5Wo83/G01NbLKlPKckn9SkDLoX2ayDeZbMYmxbgt+AX2NCVgWTS0ajTLVVqXgecnZq/U4roEQQIKUYfSWcXYLxeMm8Gt2THl1N6bKTIFxqnWgVTvR1lrkOibxtfsJCZqYJrIK0boIZW4FqRtGxvwpku1ptR4J9sEedmXKScXbTknhuL5E/HNuNDurY+rB4uHSXi3OR52OyAR9Y0rNyGUe6XKoak5YFGtTDpKP66hluQ8D/qpcqdUO+mW0w2r4XapxXxqZ+xuBrUfP2fRDx9rErUTcON9VB73xbdxGZvI0dgy+yH6TLjsuMMg8cGJZx0qDWMX7NrfuCZ9jHVi7L1InYtcgmYz9rO+khG1/0W2EI7t14xE3zvN7SPh1XqgKXZf1Yb32jWQA8/L32ybFNcfe7iJAIf7JDef9hBfyZafzoqb22/hFsb/iBPpm++zf+xZc7PCS9Rf2TCJlbWFlcUD6Cf25pdZ5benfP6szkw7GxOPYlV57Be7GzUVK4AB1tk1UJWI9GRzO4vBUiAZZrfG7+do/+9bDxLgdsAGjObsW59g34xafw7tOUwdf2JSXwXTJ8mHn587h9ov9VssLLRcevM7c49X1zgfAdMgzATO/0Ywnj+xJy/7li5Iuuhnk3k0l81MFny4J9SfXqI+sf5IGBq99pJjI4SEhkxgT7tjLgmxHxFIY/L0Cl5djvjdODcka2nM66nVuTf1eQ6719iscW+Rf++Di7eob+RnBsHqpg61ZazknC9uMjpjlntD7IYtECwqERBSsSwiyJN3EnAhqEEpXiL7SK8WrTQ7IJo7mez533qOKoE9TsUfqTy8LhXDmvqIDAm1KpASsWlvlAtyMGGWQnmqIaqmmXa/zQ4WIQj7nOgCxEHRDPqO8waaYLOZ2PWXdtg/EwnkrIa5mGBVSSmHfz8uiyY+aL7sO7+jPwsZlN6BVdwfgg9JtoSljROSlXWrz0PW0u0nCSkGW7gY71rjV/Rnrh4A08vAYitIae3rXMFrGqq8xeKU5F3mIpigKHBuats4YjFUYD0uvWdtb26mVR6QZSCJpHD2Zaghvwo+kCPdbxC+PX36Z3/iFfhy5Oh5llscnWWTboKswNtWdNNMmH4R2daScnp++UMf3Vn4xNBnCym56A7R8p36EfLP0fwLoaXf0wgJ93u9Agj7AfYP0fwUsPGGpWJUZVBRVphxSfKPXTgZycGrqcGUtYiZ4G2L+CtZQ0bpVKJGwoGMYjc9ov6zo2M2tJRPNfqPhAf/8cHhpHOWoMlfshRcMONTMNQxI/L0sFpc++NEF/ER0LS8/VMDTs7Mcn5EDQyDAZJTduYwbRXWh83/cyiKalW5ZiQSZEcH5fRUwYYu2Ziyzd0phco94PWuU+VGAqwYxEoRTLrw0LZ4n+K5aUAcTMa6/o4vHqYrQrArgYoJAX6gIjd4z+qjyARTtYMXfzUC0O3x7GK5TkTXrLCbPBoLm08SYqmsBb07qS+0BxerbvBtbyIotMQ5T7ZANalPLi83QxrGkesxJmNjWbFSKQI283cujLz3j2Seo9Nv3wATd29akyfFdriLqlw9nL0Y17xYH5xKs5w0My2Ntu6DeKLUuP/7Fy2pLNWvFDvDKNHn6snx9fWB4eOY0KnWeJKDUDdAVtMmNQLsvBwdgYk5KRGXdySv0z7i2LPtGJDLBS7HAv4MOEFk3h7C618HE5I9e5z/wH60dAtfngEJERH3wL72dP61CLh2eCFyuVJ1XHmyOJDugFKuufb3fdsklrPeFC02Z2+InLMYZoSYitvu/X3KcNA9zy6F9mrdUM/VS1mrAtbdeaZ9VEIM82BsdIwrrTn1r5ghU0VW/rS3+L6FWl6B+DlAc+EV/HeoevnsWjzzP7b0RYuiwoGOr+Hb14umk47Hm+wp+qCQIjI3QVZwMVopFPvXbsXD6dBbBGeYiZO9VRj6+oAxqVIq3XZTvKD2kDJGPfv2yPrvke9tUyPfcRygPzTDA/G36SeJg5QZBTvYGX9WJQAlMLG/ZDD3uWDzctG+ssSt94E+hkfH3AmZwGSliRBqLJFQMLqYndZm/+XtpmcKfHFYUJaYXj9blgeV4OaupaQ7LFGUHdcbSzpMl4VFYm4MSzOx0p0aVuKed5T3FPMaDpQ2Jub4oEZTJ0GjQq4Fq4Mz+EwxWU4kLuXDXFCPMd1cX6c1x9caEj47yibyLhZBtRsrVZ9HxjLPcFZv6q0znU8ezWpDpp0wKiBAEywPXd4ocXwsoeBjejiNfqwDuYIZZ29rn9kuelF4XWHkbfPKuCnhOYVwbfoJyTrL7ucYcwV3dWiFX2bqNZBxq0wpVnekVbmPgYxxx4voGudqCkeZ3vWwEfPkmzZiY/PuBZP3A0/q87+YlkCx6N+vr249zGukrf7hj2f5Km4+OB4mT09b0iWPz5KORBB/Cxjcu+nI9+AINqzM+vbSXKf/bJP9MUX2+4PS3UlHJ8Rty+Tk5mxr9y+LxvSByRNy93Ic6axhSSLm9D9XmpliM3kkJQ7YBUK0LYICricpfGk85Kk9ROTI4rIw829StkqhUAUoZmDFHnj8vIidOg7WSFE2Gd141ZHNkhCOWXbye08mrXv65UE+hkcbPsaRcdl4X+XKMo6G1MST9CqwtHFdiTuLS1ovN2e1B5ca7KlUzn9n648/cxy09SF2U+/mNasTZE4mJLDd6OG7r6BJd6JFNJZmuEoK8GPAz4oeD6wXMT269HOue1vU6O9in2151WcmmqdfK6CxcHZXdtY29lbyNu42h1/eWmoR4IYJm83Ez3cusmYeIlkbRveLD/aaT28vo61zd/J0dT28nuT5dmyS41IUme7v1pdnNO53MWQ3ds+XE347S6kyL8owTbo31/EsjXNPN886ZW+eNi6B/11ZOeSh+ppnxu4Ia+DN4RIKoghM5CjWVojpgvptpB8AVlYwRorqiphKHAdtonRGoTX100ER/K9Bcz1k4HF0EeiVOhfrjjMWhKKbQkVGUMUOMHH3+VxdNzTU+Fdjs8FWfJKEb7QAiS0+qHvAO5Lm+Adx8GsAcj7Cb8h6FvUR2JHPAOFnecmDdP7EpXz4/1o4Mx8IiD5CdzSzLZ1DJPJ8zU618OZcKnpyq3GziDSRK89esRs2upOlX/jCGsRox2ZE/K28GWipqiYxkQZ1SGjyLmKJ3o6TYDUCQR05mdCNw/6O6yROmQSrzjwJtk6IllToLPksnqUzzw1a+hLtM9oFB3zR/Y20ztSoC/CzE+4DwvE1r3dtH1XBQLOW1HKWSWV6Ljd2o0oV9pSob7+/ufVGGJUUFBRzWTMD+SXmVAUs0+msvfI7cpyF89vdLLW4t9y9qLY+t98YlHRQQeP1UI1nRpQIt6syUi4wMPdEvfdPSAp59dvpmVnT8AYNk+wGAusri4zT14tfH39fa1tT9qG/K4cYx1xHSus53dJh8+IDGMiEj7HBo79n29bywsfpB6Ep/b/Ad7HBwBH+/Z+xct8JemmtSB+fF2PUt79cEgD8fpFF7emXhZQhdhkRmtbW6Xo22QrqSQsnRcazt85FXub5mn3cXvkwKUMdID0X9SChy5VEa36Vi3H9u6hx7uVcUr5gZgkib/Ejbi1MBxhSno/1tn8H1EjIkUtxKUO6itul2dgce4IcLEOHwgHKcteHFr+LrpBReq28Zie0+cs/7mHC51XYCM1JNCloZxAizxQh5URutiphxmnUTDNsf+RAoIoLgjw9bNH3HS0ZCgOv2Qy9GrSkkutAqnwXCdj73SDN3hIZRHZeKECMVRCHgod9yosKIRRtf6Bw0Z6+VUCqVcMsDMgdUsrlq1LTD5OJQapuXTyJl67S7BpdCWsRf3ZPQMZmmmgrImNpvMWDL2vlJkbj5C1JEUdQngx0VhhLqI/ujgAiPkRBknGcjOBrmSQ+GHRNCBbXqnCDoq1HR+N2QY7VlZv59rhw0xaoKUs1gdxroUr65YRYxwN8hFXrqT/WNM1zWiPlA4uTu62/hDocq1YNhokDvFVsNxPbe7PKf6s4VnE1dU1fXcEGCW5BDvMu6Z77y8N8pacgxOf36Nw4RGhOGzTAB7NoslXr9hlFtaTUPXWHMkgdwUNl0UHmW0jrZVKpLZ5FaG9IdttCL3/MpF71jpyaRlskWSrcNzgf/Lkq6D21C3HMBR71nJzx7ktgtUOz0xk1qQQoXh1vB2JqWLrJJcY7UI03Sjjsv027+QAnARCwT6lDWxW9Xn3r8stKIK7viYh7bz4PxI7cQC2nWgC4IJ8CIR/4FrSOarfBtvQOsxzqLrY/4djQssOaYmazcB1LaLjiQt868By2z0X9VqAvQW9eo/Aduxk/LPGboS1CKEObbJgu4WfzUY7E/4X/Tr8NdaxlPWmjM1cPjduJkYhRDyOjU/ifciWjBlNi9gSH0V1183PiZ6MJpwN5IwHn/O8AgVIuzGJJhU4vInmIkJl8lyc+yIomBFm00aknqkUIwioovl8RT1IxYAyuHv4psjYVjVc5uNJwEGwBn6eJsYru6zIZFJU2YMzSkRzwb2czBsT+1OZ9/sgGkuBCWUQ3V4XRYJM0FDIXCtN8lgEd7/CaTrTa7h6U2OUW+NG4L7NcZI5JWcr2WbxQxcmvsR8jry1QRvKV8DtXgZgxhARfFlg8KI5TljfsB8CZeA3rJhveGPQp4091A8FXlJ+7TVxr2w2m8Anw09egz804pbpg+hzhvyp8bUfM2krjtuf9ZvvEplHpfLcJHOOC4ad4HKOEjxLKAUjrfCJ55zIJ53IEbc+8EwYoAxYgAzYkABbo+lFxfKyK2UzE4gIyDG2cPzBwQlgbFcIFWuiK85kdT2STlNjLztAdQ/lbQEfAvBzbFAllUZu1EZDXIkASIhxOU14kdHBgNshBwuP/bbF4KvC5N3LY/Y91zO5f658PRp1AZuvAEzd0MKc0Lsc6NN3BGQQMKkCNMLwSGSXDwcnTA2JolfYlBO0KvMVL5huZEw7m1HcM+5LVBD/N73OxQoV8RNH69HyrT8U24kgcSEStcT6oRIUkqXQtd9morOJcBw9I9WQwNy5HGwRqqAQi8FpHSbTXw8biOK+ClFuZyk/Bxd6Zht2V6Sw5R4mCbPRg7ZDlhI5wWnXRJ+UGtTRHOTRLN3B/YVqg9hL7GvmBIyFKptL6I0vqY8tqY8HhpJVFtSWDtcRFtSRDtc1PeBBNeQ5E+CsX4pPTFhrQPJoDmytzxxZ3JB5OBqTP8q/EgOaZ7DxKRZkJpBgJoJtIpBhUT9abWKnRaOz0U0/Xt4+yNTlviqIe0CAmhiYzq4XDznAEcjQi4rfsnXVeJiQa0JS42eU5XM8GwzskSB6Bdxbm640CuRzYZkayRBfY/uzMYQTJi2QZmrBrRwFhWPmqVOSUJM58h1J6D+SpHNSpHRShHNSkfQldSakz607Jhcx8uub2naIQ4d81QL7wWKGod7StHEDplqLbAs5ot8OnGUVtp1ME7JcVY+p87jBRl2yWxWPtDWE53fxGHry9PmSKk51LPjGSUFUbUGTSuQDGqbFgSTPWZOJFt02jSQnYw3TWb+32c0b4ssA4khPgU/rQv9JpFr5oI1nPExarjHye6rAg9qtRD7iws68hyvauN52Vkoya9Zwc9Ybz5j0L7oaURWQJ+Kk650zr1YgXRiR3isjKdhPnOcmQkXiqbs4Xshmjqy+onYG3YFR9vsMf6GR6rCZywKTepv89au/ZZJJ1Sqm1ORCLB6dImap/F8DkmGPzzzjOyy92nydPtVWtUxKInHEoynWg/1PRe0KA50JIa2qb8zDYuxrTpt57GEP7RTwg6MDpcyChVCsB68rteT/uF657IVSuXwlHtwkz7ZgjNIdT1QaNaqzsrpzMJsfiDGt2Ew/OwVx28uUzlBZ/A29AL+VIzTkWg45a+j9tND7/b1ctmoDxqJkk8zQ+xxNmrrJCXeDanPZ6InS0+Ko9LHUWO7VfpYSm1zET++aI5diuKpV+jW/r4YVROLtFkLHpdiAYlgAPVnYhnT33zsDIz1DvfODafnnkMLhIUyU4maOmjaTV46+KAwGvrCRzno6w4qDWMyS11BLaOZxNH7lyuGv2mlNbuxdvaZZe863Tt4DfE4paentKXWxeTD+5GLKr6Aqtvl7BjtdPEhjPmo4cpt5rjPjTr+JNzFS9sp4IALvuWF72roHu11DddPn6jsMjZYxPJBu0BF8fwsJEdHUxEPFOyeU6kxxxaeRe6uAnVZerbN3KCIeyaNefyPyMvOchFmNI2hqSf5Zb5DmRWratZS5K+tezszi9WMMIVt+rI41CybqOZLvrU3u92Tql2J+sDejTMnXVfSgxmE58qTSisbPUFZkeHtRHg4Msk//2/9o+entXR5qdPwc8ij69i957AKByklUgBImBEpb2BhTFObuLHi7FA8wIOMkGUYN3hNFA5s9b6VJepqdvZrT6u6cd1MHof2Y9dGqL6DzhkIHBZHqj1QxHSqullj6Zh9jaTz/nJn0aQa1/t29wKd8IPKoLrBjvybIKymA2p8yB39b+G7YBlfWl52Tz7HgGZx/MsTckcnUWDy1/b9KJNtsHoXrw9Widj00T/izhZAPSnatFTdKS7kA0uodbR+PtU+E8q966jttOm0+Z2U2bTH2hIMyVz2ggzJbHLS44kdXODSaY9CcovpMFERORmR4cAOMkBJyJhkTKRI3Hil2fTWZJEt5cgQL2htRLNeXa8vBiB4+i96/7g78aAmvPur1De97IGLQKOcFT5egZePtERI/Qu1CAC/iT++BPT3BhO0QYQ0Hsdm1kCHPHy5cuM06KtD7RJL1zq8wtnijYXER/QYgmyMec9SvYZQAyaKLuLc1OzCRMCRA8hokicgE/uOaotjILqnE18=
*/