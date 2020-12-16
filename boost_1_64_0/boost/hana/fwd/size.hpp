/*!
@file
Forward declares `boost::hana::size`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SIZE_HPP
#define BOOST_HANA_FWD_SIZE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/length.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Equivalent to `length`; provided for consistency with the
    //! standard library.
    //! @ingroup group-Foldable
    //!
    //! This method is an alias to `length` provided for convenience and
    //! consistency with the standard library. As an alias, `size` is not
    //! tag-dispatched on its own and `length` should be customized instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/size.cpp
    constexpr auto size = hana::length;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SIZE_HPP

/* size.hpp
PrRLsGV4enuCX34PBU3P88/9UxiXTT3lp+a7Ewvtony8TNLj9yvcHNmzvDNIsnO1mHJRfZzXng9rPaumgMMdHO4Q8WT4CB11Hk7g5QRe8Z1kAnuVxArtZDor1HTAE1nmNtT0E79FXnIqMlWS1YVDaVx5DxfqvL/Rn7jTnbjbLdJAwGgBvYRT4AejgjOyxG6o7hNZ4jBUm08lXubyHXwmQyAo/n4ioVXGjJMKuJ6QudN/sfYKrudbu4c05iPudO0td1S78BU9RH0aS1aaOsUbO8eHT443dY6fclJ8RNiqB0WEsWYsfK5mA1VM1g5+B2ko+vKXJP4kGkB9ZMC3jTKAZdg91yEgRl8h59Dq9HBCSrm/1o9RTtkExI2zmbCojdUNJyMibAhbqCwu775UCXrP/aGmbzM8BpoaJ2K8S3ouxSjfTT/+HJQvbA8FdiS/XE4QFoBYGRBrhuuamFv8fppOPPJfUIzhCYLmDsKTHc9riKjqNlUPL8UkNyZFr1VGaJdJ7/mfxpSQIt7J5Z4PSuZdp8GA+JOVUts59b5k6js59bO5+hDGqWU/OLftqs+s9VJ9/z5Z2vdkBYJKoiImL3D28q12BWXJ6tfYwCTg6I6msoDYjfECuDeou2maDhskK1ohRg/mYZi4imFmnqTdJKyipH5xOJWH4M+NZvjHYYnprFvZMT+4xVftKGw31XsfLlJEtXkiKBP/Ak9ZRjeDiwM0XeOFMelcHUcaPxVC5oVi88CkOU5knoNMZTwoOBH6GiCJlDjsZLwmLFy6xc9ftNt47kaqEyGrC2g2gCY4fUAs0oDxAJjVs1CQxouE7N0STrEnOalrkSzytrHmKuRoOinHK5IJV9uRsLVP5G2Ts+64dtc+2vpqMQqDLJVh6/opWSGJg7bk55uM+HyAXxwp4MrgAm5n3aMIY4aI6bFCPN+f5w4C6+uIqhDTBlCFysQWKkP84FL4RIX49yhZYt9uwFZzaZlU2mx8Xia+PYzLIumA+IuFGQZwW5M461+OknE2kYc64gQYKtWLKDRe7Yd4KKOMBiAksdgi7Ha9Ew0g77fkzNJczB2Sh7OcUJ9u8PzDmqz9Fu2qfupqfrFvtA6XN1Rk1roK87iQK8u2FieKuJ0JqtXEmZiURkqRGUrrVsoyvZRltxHt6Zw+uvdhyQyCIpYirHoK9MM+0TxYG7wmlDGbLYol0vXvwHeH3sBTrB7ZieoiKeShzDOp64Y+au68TPjsCGJX5vVhWs5Futmy251D7/7v/0l58yQwzGW8gMimcUbZxwtgEhDrK2HlTXEfmo5sQMVLg3h8mUgt6qy7XxKLJ9KWwOzcluKs/RxCKphpHOCjPkCUeLj6jpWfNdAXNZ9I1LjF9y5HDDb+Uc/ziCUgb3rLElNncfsSsYH6rteo8Go5/GFs+/O1PGig2+2rmRialxy5Q+FFGLndCkOGjF1zy8SgXGroyhLkLWaXU3OzUVFVJYt2wuhy60cwFJ7kmnlw6NZklp/iLONjJNP8S/HsENknqx9Wp4NRvjYo2sFQE9LyhQUFK5t4jfV7IjnnzM3KmySMb6nG1PzMhftp67+JvH5m+1wH1tA8RDUDh9RH0HZlMfRFMayvNmBVj6YrIsHhD5Fc5UTqQtWTQg3Jui8MV6Pu66+VE+HhCnEtGj8U1+MDIvcqxme2pmOiZRUZgPcwLAdFvUnv84+Kn+Xo42/XNLcm03xRJSlogSWS66qpU/PB/dmJGhACTyJbJ4SxYyRpOSDQdNUddtbOAqLLxEaHpA8LzXBFCFLXo57KQBqRq/vS/3tKtA/pIxePrq+ARRpmg6KZcGEyGEHVb9FAyX9QCS3Fh9y22iFKhcTNWcqE+6o=
*/