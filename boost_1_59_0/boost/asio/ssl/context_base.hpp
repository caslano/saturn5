//
// ssl/context_base.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_CONTEXT_BASE_HPP
#define BOOST_ASIO_SSL_CONTEXT_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ssl/detail/openssl_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// The context_base class is used as a base for the basic_context class
/// template so that we have a common place to define various enums.
class context_base
{
public:
  /// Different methods supported by a context.
  enum method
  {
    /// Generic SSL version 2.
    sslv2,

    /// SSL version 2 client.
    sslv2_client,

    /// SSL version 2 server.
    sslv2_server,

    /// Generic SSL version 3.
    sslv3,

    /// SSL version 3 client.
    sslv3_client,

    /// SSL version 3 server.
    sslv3_server,

    /// Generic TLS version 1.
    tlsv1,

    /// TLS version 1 client.
    tlsv1_client,

    /// TLS version 1 server.
    tlsv1_server,

    /// Generic SSL/TLS.
    sslv23,

    /// SSL/TLS client.
    sslv23_client,

    /// SSL/TLS server.
    sslv23_server,

    /// Generic TLS version 1.1.
    tlsv11,

    /// TLS version 1.1 client.
    tlsv11_client,

    /// TLS version 1.1 server.
    tlsv11_server,

    /// Generic TLS version 1.2.
    tlsv12,

    /// TLS version 1.2 client.
    tlsv12_client,

    /// TLS version 1.2 server.
    tlsv12_server,

    /// Generic TLS version 1.3.
    tlsv13,

    /// TLS version 1.3 client.
    tlsv13_client,

    /// TLS version 1.3 server.
    tlsv13_server,

    /// Generic TLS.
    tls,

    /// TLS client.
    tls_client,

    /// TLS server.
    tls_server
  };

  /// Bitmask type for SSL options.
  typedef long options;

#if defined(GENERATING_DOCUMENTATION)
  /// Implement various bug workarounds.
  static const long default_workarounds = implementation_defined;

  /// Always create a new key when using tmp_dh parameters.
  static const long single_dh_use = implementation_defined;

  /// Disable SSL v2.
  static const long no_sslv2 = implementation_defined;

  /// Disable SSL v3.
  static const long no_sslv3 = implementation_defined;

  /// Disable TLS v1.
  static const long no_tlsv1 = implementation_defined;

  /// Disable TLS v1.1.
  static const long no_tlsv1_1 = implementation_defined;

  /// Disable TLS v1.2.
  static const long no_tlsv1_2 = implementation_defined;

  /// Disable TLS v1.3.
  static const long no_tlsv1_3 = implementation_defined;

  /// Disable compression. Compression is disabled by default.
  static const long no_compression = implementation_defined;
#else
  BOOST_ASIO_STATIC_CONSTANT(long, default_workarounds = SSL_OP_ALL);
  BOOST_ASIO_STATIC_CONSTANT(long, single_dh_use = SSL_OP_SINGLE_DH_USE);
  BOOST_ASIO_STATIC_CONSTANT(long, no_sslv2 = SSL_OP_NO_SSLv2);
  BOOST_ASIO_STATIC_CONSTANT(long, no_sslv3 = SSL_OP_NO_SSLv3);
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1 = SSL_OP_NO_TLSv1);
# if defined(SSL_OP_NO_TLSv1_1)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_1 = SSL_OP_NO_TLSv1_1);
# else // defined(SSL_OP_NO_TLSv1_1)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_1 = 0x10000000L);
# endif // defined(SSL_OP_NO_TLSv1_1)
# if defined(SSL_OP_NO_TLSv1_2)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_2 = SSL_OP_NO_TLSv1_2);
# else // defined(SSL_OP_NO_TLSv1_2)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_2 = 0x08000000L);
# endif // defined(SSL_OP_NO_TLSv1_2)
# if defined(SSL_OP_NO_TLSv1_3)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_3 = SSL_OP_NO_TLSv1_3);
# else // defined(SSL_OP_NO_TLSv1_3)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_3 = 0x20000000L);
# endif // defined(SSL_OP_NO_TLSv1_3)
# if defined(SSL_OP_NO_COMPRESSION)
  BOOST_ASIO_STATIC_CONSTANT(long, no_compression = SSL_OP_NO_COMPRESSION);
# else // defined(SSL_OP_NO_COMPRESSION)
  BOOST_ASIO_STATIC_CONSTANT(long, no_compression = 0x20000L);
# endif // defined(SSL_OP_NO_COMPRESSION)
#endif

  /// File format types.
  enum file_format
  {
    /// ASN.1 file.
    asn1,

    /// PEM file.
    pem
  };

#if !defined(GENERATING_DOCUMENTATION)
  // The following types and constants are preserved for backward compatibility.
  // New programs should use the equivalents of the same names that are defined
  // in the boost::asio::ssl namespace.
  typedef int verify_mode;
  BOOST_ASIO_STATIC_CONSTANT(int, verify_none = SSL_VERIFY_NONE);
  BOOST_ASIO_STATIC_CONSTANT(int, verify_peer = SSL_VERIFY_PEER);
  BOOST_ASIO_STATIC_CONSTANT(int,
      verify_fail_if_no_peer_cert = SSL_VERIFY_FAIL_IF_NO_PEER_CERT);
  BOOST_ASIO_STATIC_CONSTANT(int, verify_client_once = SSL_VERIFY_CLIENT_ONCE);
#endif

  /// Purpose of PEM password.
  enum password_purpose
  {
    /// The password is needed for reading/decryption.
    for_reading,

    /// The password is needed for writing/encryption.
    for_writing
  };

protected:
  /// Protected destructor to prevent deletion through this type.
  ~context_base()
  {
  }
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_CONTEXT_BASE_HPP

/* context_base.hpp
8L1P/8rfQH/j2Bwkirp/+DtIwP8e/G+hkPv3fwv9Gtz/I4q47/pb6N2lWGU79AzW51sSTYOXB+GvfVBKgT+FVO0K6CuUYSdoPT9C1+9ET32y+wXC7nN+RRYdPg61Gv8eTu9VH34ZfsoVYOQVzV+A+i9A9XfANh8U/rP4wnL+9+Eh9J+h7b+A9NAcn1AolUuju68Z3f+XgLQf+O6e5B9ofLn761+AFPSS3f7Gbv0/ArUXmtij0ibhMzIIuYeL8SM+A4o+BvZ3IN9gkTwJ/xfCgPvwaD+UM6Dwo1h/B/QNJvEKyaZOgHd4tB3KGb1wu1h/w0+h0aZOhHd4jN3vn89gkv4LYW+0HfxvyAD+pucPSAH+pjtaAeaMWoifvL/g5U386l3C645EohXUTZ133jLRdjBn9ELt5NcZv32Mw3kWTtrxjDI5z0L/CW0omJFfYjI+vjNVtgPbULAnv0S3B3kApkd0DcPijE0Fu8DvlI3vBh7DcwzwJTq4I33ZXncwtdXmZ2toueiZetjQE6xIPcZ6+KKw07iUfpbFP/9s4wFfkvI4dQrzbRkoa3NC2ttTERpugIbVQcHgK6d7n9J4zcaEZ7YuxIiG1WW2T6SJ13Cz0ThC2Gfjy0tu1VuF7wDfZ4g9EtUXfe8OP/BXgu17vsFE6seIsd11N7fH5BxktAvfM/4qLIsFXcScKmhUET49C5tbpOpelU+pOzAkHBmLNJKYQShNdQIk/Yt6eAM2w7LRLl7POFdYlhO6yA6oBiX49JxnaaN7eFYNSIs6aFQZPj0Pm1uGyTnRaJeuZ1wr7P9ExneOeQCp379QwLJj0m3tGfcIyzoHtQgkUoFPL8DmVniW2p9iipjTBI2qwqcXYXOrMDnnG+3K9owngzqE0dWjA59e/LNDuj8VKWmfO8itw+Rcb7Rr3TM+D3oIhog5bdCoOnx62e8ZygIVoZ8rkCE7hLHvYQ2/0wZ8LkaGrBAuysTosalCtg0PtNehC1g0IjbYBze+FwX0eVFdtgia7a9qF74UaKZy8HvUfJepHt8oUBZibPbt4ZXM832/a063SnD9j73k6Qb8/XQ0yfON5hdT138rNoM9kR9+VeCbPtedKc90WqAgu7OTcX9TRFgF9vNMPiwsbwYJIYwNI1ya9jRJx8Gyv+8G9gkt+t4kCdBrcN3ztATmZ9bbnZkMFnGuyT9qfHOtEiOlYn6rzBP35uwBBJxRvcqUTA5QY934vGhu32X99vnlERrfm68jZoTyuFP0Zo5MIRJkcF5uaFz48nrs98UVPJOoAkZ5BM6t640id2BvOAib7GMVMCGGxlwQiU+8x5ZC2irwBcNSw1lE+eIaUIlPbC0BXZCvWEk2rdOIhSb/oJm4cnNK1XG+oSQYWBU/NhCaXxhyTnZcEqAiUL3l5ss5eHJvj64oROdykZEjhiIRbl9BjuecEc7dmiP/8FX1IJ1dIkpZ/iCnaIZwRKpu+eYz1SflMiQerp8fxBRfolDuvLnJ8Sia4fH2LlqAS09TXQxPS1Nd6pGPVGlgafduV12qUpXfp8y+H1UQBUsobusegOFW7c9Sjg3l4ZIPf4g0se/gxeNO2ZDsrYLldz75QlzA5ltwCQLOM1A6D6zAe/UNQT3/5ncYzjIkzrI+n1P7fguRTou2nLH218WX8giR21wCeFt9hJHvlOWPJC5X3xhAqZS5HeP7LObYoUvXLXscU53kXAYrl7kteMfD8pQhFWif7MrNWfiAgHPaUyJJmZR9c1eZc9pVwo5EfpEUBEUDWJR2EardjMooXZJi8KQYTP8N5uxVV785PCkWU4RuN6Mjikwd4T/SXf1i8P/jmCqSzSiUCGxxRiPszyGGL0mD/h2jyeSJfr3ivCXx9VzywQBJ6YI3W5MhLEMCZRvL0FeJRmAvJp4zcc55m3UyeXJ4Kor4BYZjYY6CKB4N25eRZ/bnJ114BErBwSw1yaPDZuL4P9MNN+lNI5m3TKKfZIPPeFQ7s94hggpWiojhDf7p8y84k2x8nivcAdWgDdRUd5rBbq7ObhUlioww5lPV+NCZlT8wBdmyvBim60VUaApiyUUqSu4p3VEFUvdrU0Xv4+2CvH5g80N/AmIJGjD4t+sCfLjukY4AGwSsDKTvikzZemeMejiZGXsxu7B14I2tmSKqekBM+Aa05BmTz8APsLQp5/vHSbrep+hy7CeRZqN7pL2wU4FcWsS8QQiUYOTgX777QMIgnHavdbXOOIPW6/lFU2HiC1aQD/XPb4F87B7YEngNsrcb3AHOZRc925LShoz1pX4CQG9L2YhVZl2M29rR7NUIzVxnzSybha0Z+tWmvrCU3d1+oBVbZw4gFewlc4Kb/71sYwZUJfaqkv8IwA5MMqBzuvkAohCyEf91lEtww87RjGcNM1zL95nv1lZfJCHtpK7AyQCcA++s7PxjACpg5S8b8QWrh7S4pgE7YNaQ11/bVTp1ytt6kWzsmq6YcctSVSwWBiZMHAeLXB2XBuJi3a93ySIR5DEP4uggCWI/eGGQOyQRSH0j69O1NhwxtqW2/qzTKVPvHzQWTGsKjIaXlsLU6kmNgwT0kg9Tr8rNuIyy2a0MQwhzbcTHx5R2Y8rPeuKkBuLIVD7kwgwYCVT6DPBYrzSLfxhZhAuuHOt/7iTnHfyj7yA/+U4VX+LwGjdg1RXU0UXAFbikNdL9EoKfW5Ue2XsfYU9weMBHWHueTjP/BwDz3cvyZGvKKfHDEjEkwGtrSl2WeUT3Mnz7kdeE4JdMd9gpV8cL9lPf3qB5tMX0Dwplm+qQpdQyclS6zTzOI7DSYHnisO5LLYdeUPouW9hEAq3A7erqDcRmIK9uuO30Z4q/eF8RWABej8f+8D/36oZjhH2N0+kNgCn88dYzkw6yEfY1hiA44M0rXRaw1kM2fw7AMuUNAAKQA0C/mtF+XfPWRidVJ15t7p2NKTAukeiUY56W3fd9m8nG7Hw4uy+GPVRnRVXSjGs/SSD3N8rvshSrsp1ta+39GXqzTVLq2ZVMi/DVQ8/zBwYgBct/oQtDVDVSOrlQXUqhOBC3yRYoOFC3qYO7InOsKvk5rfTdNyNFwQqXgSMnVEX7piUvLwbafj0HNLIymWOMWYCpniNQGzHeZYDv3PtTqYzt1otnPI8HwsebRYJaSd9iNvzfDUHWn4WO6lV/Id1RtjOE1IFW1v4FJF/Wj9/KPKKX1i9V13u5Rc+NQHgsNZvTL4tiCYhhRWWFn+SGD+2tO+2tn++t+zqfWjg7EOh9i2Q4FsTCGu9RmIAOMWKi1/STZdYeD2Pw/cDg+5GhPC8cpI7X3Miid5i39g6hdGPhsy9uwtwbvSy2XUDmFGGpAuQBNOoRNPcKivUXs0ZbcMm5ohdUm0fxdN+a3wfylB3wEyUfT/eVMuB1ZwRDZQbbumccQiJ/ep8BxeZJQONBQNPvfwDwLwLoAJ5XAhnVEgyOb57PiP/PAVUBGwWfQyKaH5lH6pRkYz9VajFsq/pKWobuRfDo+q4DX6vv3VXyEfM5M9Qp7eLXCERnk2BRKEwKem1k4RRWdRy7Txl9fj/uT1uCCwNpWt7pSS2ISOgGXg/W+dWPLQja6abemagbOnmC7xH5z3ylGsjj8ifNnZGHkuLp+QI2EckHPae7aPuCN7GKvUFihmKh33P/tFRg0Sfm0qYFAb7fboEv+fKt23vBWTOb4DQowjHPiqU8rYqr5U+CoypNuFSf5PRbdntdY0qDDWrCM5A4bPVTXcoDCca4C5Y6S5uODnG3BnALpoWLiUitZI83S4UUDUqXLkrfaReen5aCHckP7SfRYdRmePDSEqZEJ5G1iBi31NUkm7lV0uIRLguaY11Ea/SjbcU4SrJvEThKcMnYAhsSUqnl4mXzYoyoUrKpYkmoZImlaxBC+SA8XjaXJ8dbEEtVlr+TM2c+gMVa3FUKjCHOzaImHAyKpM8Wwa0fJhIp8ML1xU1te2uZQ8kRMi9WmzWgyOysqyRCZrcLycWUT5zGUStE4DLYzRavzwTjiDs3gRAfkdr4lqK0NHyRnZU6ozFGceF6fWhRu/GgJ0khRVS7TpPx07Q/xQOuxEbVhm7+GtvJbqZ63/gRrjo8Pk+VocudFEK+GNmCAs6C/ZHmSXwo7t7YRV/snPhtXCCF3Lf+u8lMmV7Nm1Y/64ncLNzdly14pxOZn/DeDCu4ckFQmJXgndLgx27ZyicOvd3J0jWHE+JSI+dybcJTqxuCmaJpyK93krKW2xl1TU7UV7ZKKrLZc0nyoIca3NycM9Wmo6iYN9W3qpqjmRxfYZgox0ffGx9lEF6MdnWNca39oGfy5StJW1V/nnyMjI18GgH9JINWbw2lWm8NqPxDg99g+NnZbnN7nJksNfUYQ3KinjIiY9laNUSNDhtdxvFleTLTQPOazWrTZP7YR5u1ibMgqfmtqqBX80wnKe0qkU5eYS4tdq7WCMnKzLbrKdQQW1V1PnC3iSZJvRRluJw0yPxBs3mIFZ2FG6rsg8V0r09xsPlHjypdvD710Fqfwuq0QmLC13qg6PRJyOnmRGdL9ajEuuNPso3PWtjwyNNYxnB1dJS1+vDUczccUXxXP6b0XM6FJG0p/Az+emlfa65mvBnCeLB5Grqa5bt6idOdq3VL6HJUAzNxi4MrykBJSUUZZZk0jdGAX913qOr9ffq3lBUedU8XUMcJrOjxvZYH0K8Wxn0Ox4PAcigVdEmHonlGPPOC+It49YDz0XOxw4cQyT6lsqPp79T1BWgV1KpWV+46CByq2GAxayhnv75DrI2ckl9HwA+KNH4N2ysX5JbO7LFO8T2vdC/LFbX1Nf1ITl0Rd+W8hwdZMsUMT8GncgLqeDH89c2475I20mSjhDKaHpHd+2dnjwKJ0FHdprYmTs6OpoY2sKCUnZElLDMjESPRc4KXFygCynC2sLMVNXQ2JaIS5WZmZORiYmbmZGJhZWdmpWdko2RkpKT+Rc3OkYiKSAhUhSmR4hs7ZzunN3b2RCIqrERyhsYWts88NVDOzuT3qpgYGTkZ2Zg4WTiYGOkZWX+pStHRzsTF2BRU1z9XZQZ6wO9V8fP/o71Mv7dXxcLTlIiZGahsZ+dM9CxXBkrZmtkR/ewTKC2qwyvEKiLGwSLEzsYkJM4qxszBKcLIwiHGJcbOwi4kJCzGwU/Ey8jFJibKzMLIysUoJC7OIiwqxMIuziQuIs7OyCwqJCbKrwdU9bA3BWoqm5oBNXSYiJiJmPSAsqa25s5viDg5QU37dUQBoAsMgATCL5/AALzPLIjaAcDA0ABg4PUAsJeg9MtrABi0AgAM7hYAhugJAEPVBIChLwPAMG0AYNj6ALBXNAAwHCsAGK4kAKwUA3T3AP4yZ07Oho7O7o6mZrCsrMzMXLDk5GIK4uSKouL0TAwcsOTrG2OTsH8YJkVDc1MnIpafY/KzJyKGzobWdua/DyrLH2zAzsUWNJhAGQsTJx225zK/dv9nLb8XYfu9iJCjs7Cdu87zoDNzErFx6YEqsXU2tXV2ImL/+VA5UxMLw39SUTR0BGn82iplUyc7F0djUCs5fm/l8wN/fx7778/7dejZOFiA4hbWzqaOQHFrkJmJmhrbmZj+Ph3uCzYqPNW4TPA8n5c/Y4V0PRUoxJ2pcfmnsspvL3XASNoUm7SyzAiiwgiu7lx6SPFBC5w8eLWBfWURKZomvJgySgjp81JUP/9SVWARqPMa41ic7r0LFn8pryynp/r2gmab/SJXvJRbR56xfIqOysLrEVn9xaoBk4NP+qmHNmocQ5xUdXL4Ft9jelDxeaDOi50J4LFER20MKZd8+sjHikZ7Sq2HeHWt1A9huJxGX1weL05pyQ7Rf7V3QUP++pUqaybcIaZgWwviI952/DRXxCfWgTc3++61Ls1GyaauoR92SkVdW9TVv9V5y63dVtJ1yVy4y+sds9JVG5qOq9OF37G7Q6XHbb3iKl8D1iAGadQbxpS/WQmPaSFYQixw9wE7gIy7xGLz0YytVZXFN/u4EtwkPnjx+A5805o3PsABxoyhv/vgbXF1sK0LZ+2gLKrQ+IZnwuAAGtdL/GCWnCAHe8dyfTFNmSCvQpVNB76XlnocWRBN9Yg83jwYoV4+tFa8U1dmuUp7jQSm+e+/mE+n8WtJmsraudjPcV27yevPjoVnxaY58qlfBBiciEHURrp9Isx5o7/CUcGq9JHJ2/W1p2v+trgYA6WsMKl3Q+jHWmIACvLt7DzM/TvqWi4y8cFzeVSTL3trYdntobLjWSPCr4GIkDxOOyVM6h9g5skgXIeSmPJNmmaHoZcdEwzfYTq1XpRlx+jxtwWav/jBJuypgshE06pimuXe0vfkjSvgp9tRXrGycnF9dXfb+N1H1w/QpX3A8Jc1x/G7/Ym5O0uoOIMsDpSWUGECYZC/cnZ0AdkeP/+zSzNWMXXWAYLWI1DV1N0ZKGUDsmThX4jIL0RKD6ipYGRpauwMKi1lw0jE+Wz3z+V/ex7n78/7xfv8og5UcTFyfuZ/VgMUtnB2UjR1FLGzsbezfV5PnKC1Z23nqGJvaGwKFDV1tTA2VZYQ/m2diIqo/rJKfltDRETMXOxADQsTUJqZEyhpamH+xhm0Pn9fRU9zT6sAZGlxKXGQH3v2byD0tAgQAUBDQkJBQkBDQUHBwEDDwqMjwMPBwb9CRUNCx8chJMDHwcMjImOgJCKhI8XDo+KgpmNkYmVlJaTk4uNk5mVgYWV+rgQMBgYGHg4eGwEBm5kYj5j5v309dQJQoAE8ADxwMBLACxQwcBSwp24Axs+m/umCBonRkf9ZCniWgv1LKcpfpQsAeHAw0FPAUQACgMzOP2T5Pc3/xWC4/l1cZXq+OEABkYWV42/FVTYiDQtQvW5O/xxVny9OJnY2ZrbfA/R/P6oyMf5TVGVi+ktU5fpHUBVhF2UUY2blYmIFRU0OFlYhUWZWdg5xMWYmUSEOMRZWUFAVEmUTEmEXYxRjZ2PkZOViExFnYhbjZBJmZRRnYxFlEf63QZWV9W8EVcAKKKgagO4xABhENAAMku/fBUomNi6O/0Fxko2LiOWvcVLCEeQknx3CT28ClPmFqABVHQ1tneyfA6axxy8P+akJcjZ/iqy/Vvq/H1lZOZn+Q2Sti/8c9o0RPiiz82TVWGe3lGwx1oV+KZAA60XbIX1efOxe9d1j8KA83uKRLiUL49qQ6FOFQf3Kt1SZ/c/8hk9aFcdrixj3sxpeL7H6lUJ7usTUyIXPNHLCQlG739oGMoNJEFDpdzLAF1VKEvvL0sFRKJ6V4FIrU8DOW0aixybkrraMmhdGCRVvGlr4AAos9dMfrPp19tAEREhaMCjlcn7PndZyUivJqHWplKu9XAj0pGhg1lsC/niIu1PJ7kN9cEIgZFEZ1Ibbxuac+V6zFYMNqd3NIiKJDWUp6yRYzo5BjDoc4Z+tBkRwkQ5tYq2SQ3caVB5xw4cjg80hxGerlz/GpWdjerPJvr3h8xJXfzhO3nxEqcxjYts3dW/efHbP4z5zB5t3CZZARZT1FJW3N4087+0Cvjaa5vuavffrw+IHlOmlbjRpxKqpBZGoocf8zZfvy86VOd/gp5b1fzq/m38cpIkb7ezNs5+woHb2vJp38SToUuac82QZO4rgq53roJO/
*/