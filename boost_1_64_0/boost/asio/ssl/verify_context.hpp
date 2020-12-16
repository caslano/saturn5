//
// ssl/verify_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_VERIFY_CONTEXT_HPP
#define BOOST_ASIO_SSL_VERIFY_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/ssl/detail/openssl_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// A simple wrapper around the X509_STORE_CTX type, used during verification of
/// a peer certificate.
/**
 * @note The verify_context does not own the underlying X509_STORE_CTX object.
 */
class verify_context
  : private noncopyable
{
public:
  /// The native handle type of the verification context.
  typedef X509_STORE_CTX* native_handle_type;

  /// Constructor.
  explicit verify_context(native_handle_type handle)
    : handle_(handle)
  {
  }

  /// Get the underlying implementation in the native type.
  /**
   * This function may be used to obtain the underlying implementation of the
   * context. This is intended to allow access to context functionality that is
   * not otherwise provided.
   */
  native_handle_type native_handle()
  {
    return handle_;
  }

private:
  // The underlying native implementation.
  native_handle_type handle_;
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_VERIFY_CONTEXT_HPP

/* verify_context.hpp
v1LbjnPfjTm+E9wPpV5q8w1P0rak8XQP1gdvaLqJfxz+JImjKCm6zmbWmk27aCE0E5J03wGX7lMg24vBNhJ+blJUHzb6qWfqGoS2mwxDo3YsnLYutF209DxH1254TmXMc/ZJHA4Zaf/RzshE+44Y2wffrNK5Z91fcKP472BMWOm31mj2e6apnOy55pQzKMuzdM/NVZ2oo757bgL30DStju6huQiedoT1gv43uN/iXsLtwT2D+x0uG/d73Mu4vbhXcK/iXtP1lB04ez1ln445qmNc7H58L07d9Lpu4tk3M8erw19oF/vsQah070GQ8bhc5CZ71cV/m/rfK3CPz5PPDidmToi0ghPBY062i1jbhrGH3PBZjjDPiaZenRj2h3z3kmm9yRea/obG9LNlpaYOFwjNSSG/MeYRCWuue3HYRyX+PaSCexqn6Xcdfe56oWtm2vQm8bdVHfWReHYxcueygnuu9Le5heRgCGNluL+92tPfKs06aHaF+9u16cmZvv0tdNQA7W9rP472tzmN62+thdI21c8/8ac610ngl7MYuPjX573r8e75zD1Dw8QLcZ1wxTjeR9Bp5ao3lVULZrNOF93fUc8ZJ+XtafrIf4l/aESfPBfRVEf7raRFdvgZvmtu/12o678mbMFc55m/QxI+SveOaNyO+tFO4k6Xcp9GOc0hvy/K2uwAK7bcIzRroNlt0zQ/M1rmcdok9XkflXbbVdIh525c34rWyDDzK3R8XRVt+VcucspfzhgE7ln+vtA+nHS5sbMa4e8TuG9y2OVSv9TPTnyhzzPffJaulWZpvz99sfT7pD3Z9x3x3svk/Uv9rKKKn/ToHlZSdIq9azBL+4J75Hmbkq4ixui58gXlpY6y6yDPzFZ73uE4nOurt0kcDyat4dezBqvjzkah+UHS1VaK6hUxbc/Uz79KWi8MZYk/ZD0vPDegM7VL4BrsU8LTwrLHs71DqYfDde00dfnA9JRcduFD61o7Df7uvFPiSld/RHZNw3VS488doeuoLZYXetZRlaZyhI6pF0aG1PjH1L2LomPqVHiyCRutZ4jGtZF1WbF1Pgh3Bu5J7g/pGXYjcP9WXSU7obsP9zquGf5RYFPwjTj7qvre/wpGhYnv1++5dbiP+vOzRNtK1EYHe/xrGCjkvLSvPXjyDJ97/b+j+K/jTEET5THtxrS17kKz2JpmtXDYu1kwu0YOGYgtI1M/OwntGusSfvUMhcgvLzMsr23EfyX/RyOfqzJt+Ta8R03ODi9x79fId9mRd9rGCLIt0XibGf42J4JsSwTZrvj8bU4cLdsPB+S5zz588uznc95417rynZsq3v7OpZ+/7Qp/Gx5BtiWCbFEE2a5ovM0Sf1spR8+mRWNtrgTYUJG9RZPh4ZJ9zDv5/4oV3ku3GWybJOfKZc9qCe4Cx/9vmP+yN1roPwyRhjzRGwsv8nf8/6/5L2ez5P+TuG3mv7xbGppd5r+8e8izJuF2m/+yX4x3d9EbLft06vT84fOO/7/S//2h+7Xj/xbH/4cc/x+I/pe+/1SwN267/j8Hd7/+n4R7Sv/fh9uh/x/B/VP0Bas+LdUFYYe10vOw9tUn2artCvYDRbc4OBbsD04BB4DngSeD5eBAcBV4Gng7OBjcBp4C/h4sBN8Ah4AfgEPBj8BhoJ2eYqMPSvRSSXqagZNxltoTaA1OAruAU8AC1Qt/jtotKAeng3PBGeAi8HzwCvFH9ZbX6XNS9DlGb7nqcZcxBbTvH6N803C7le8K5UsDxygfeSN9UXsmb4Fngn9SOxR/BovVXslc8I8x9kvmWKqrB7xb428OTtf4X1A9z7vAXLVDUqD2R4aBL4GT1a7L+WpvpRw=
*/