//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CSTDLIB_HPP_INCLUDED
#define BOOST_NOWIDE_CSTDLIB_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#if !defined(BOOST_WINDOWS)
#include <cstdlib>
#endif

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::getenv;
    using std::system;
#else
    ///
    /// \brief UTF-8 aware getenv. Returns 0 if the variable is not set.
    ///
    /// This function is not thread safe or reenterable as defined by the standard library
    ///
    BOOST_NOWIDE_DECL char* getenv(const char* key);

    ///
    /// Same as std::system but cmd is UTF-8.
    ///
    BOOST_NOWIDE_DECL int system(const char* cmd);

#endif
    ///
    /// \brief Set environment variable \a key to \a value
    ///
    /// if overwrite is not 0, that the old value is always overwritten, otherwise,
    /// if the variable exists it remains unchanged
    ///
    /// \a key and \a value are UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int setenv(const char* key, const char* value, int overwrite);

    ///
    /// \brief Remove environment variable \a key
    ///
    /// \a key is UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int unsetenv(const char* key);

    ///
    /// \brief Adds or changes an environment variable, \a string must be in format KEY=VALUE
    ///
    /// \a string MAY become part of the environment, hence changes to the value MAY change
    /// the environment. For portability it is hence recommended NOT to change it.
    /// \a string is UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int putenv(char* string);

} // namespace nowide
} // namespace boost

#endif

/* cstdlib.hpp
sn2EucLp3hOzQn9OEmhrsmowfezxZJlh+jVQEpU85xy1NUHsHooPpo8vhCwTTB+fxyP7tixt6F52/EDEjjzJlDxFZ2oXmP4ZLBdZNZg+Pg9ZZ2a9Vk77hPIUm1wwvj3SdaF2genXm4nukn4948gywfSxJ3SRMQSrz+yR+cP0fZtMVpZZ7h4+z9HWXSl2mD72GLLMMP16M/FkPM9d/WeuRlt3o/hgyj5GlgmmzAXdZHxllGcEw8j8Yfr4IsjKMttauuB6tBlZNZg+Pld3ig+mrPFJxvPMWGDzA/QfWTaY0n9kmWBK/5F11Ox72jDQv4iMvQflCdPn6SGzwpR1qciqwfTxJZB1ZuapGfEV5fXU2+xj9TshHVlmmH5tpiSy9OopetExgNn8vsFv0S5kmWBKu/SS8bmVZycTyfxhyrgmK8ss0rpLHjt6U7vAlHFNlhmmX+8pnozn+beocgTx9aHYYcq4JssEU8Z1HxlfaeWZ2TAyf5gyrsnKMlswZS3qmUBWDaaM674UH0y/hpSbjOdZdWYJ+b4TWTaYMq7JMsGU/iNbo1mptP3Pr5T8Dn8/uv5jduT5bfk8EVluk7Qqy6tWRpsN0K6BNLv02ZEH7TKQzq+ZDVzXZzT6j8xjlnZrdtbDsMEO8QtLd9ZdIh6xD6HzZGY96kyZjtjJ8jDLsrhqEmIgy8ts2dorhTFehtJvL8ye9a61DHmSHWXWa2zICdgwh5jOzHGmjlyjdbhDTGXWPcsieW4T6RCFmdWzxE5Dv5Px+H6J9W2IPMl4fBdDd+RFu5Dx+DqMavcA7ankmb/Wz/LYr+TZbG7BVNRzhD7Pa6v/qox6kk0xSVs79zu0ddAouv5jtrjHUjlPRDnEcSFtuiugK2w0XcPC9NewSQaWTLaRWUTWqCrIc4xDtGGWrUf9AIzdsQ7xK7OKbfsuQwzj6PqdWeUfjyUi9mi6TwvT36eNIXPC9Pdp48n4/jC2etgjxEBWhdmc2T/IZ7PHO0QWZpPO1Rwn17VNv7xosuHMdj6PXYP4JjjEbGafu8+4irYmQ57Kdb+Y6BANmF33WrQedSHLaJb2oPOEOYhvEl1P83QHU3yQbjJdI8CUawQyP5jy265BugQDSzIwMYXuJWhjt2Rae+Y6Jff3qXLeLaGe65NlN0kbH2w7hbae7hD1WLqALv03Iz6yHMxG7Dz4J8oj25zhmxWnDQUrOx+invPp91tmL0sfqI+2jtXurWm28fWEZNRlqUNs8JL29PaxL4jhZ4dYwNL92ShUrnkbR7/HMdvzR95HyHMl3ddnduFLsb7YH8gsMOWdejKbNl6K0YY297qYsI+toetpL2nPiybK6+n1DrGcmX/NtZ3kmrAOcVBIa199WgYcj7Y6xGhm18vUnIFj8TaKAaaPIZrMAlPWDCA7wKzEksu1kS7eIf7SrGjasXFOu2JI96tD7GW2d3zWfki3nerC7PWj/tUQO1m8Wdq8HtkL4vjwm3ZPXLN8c/1uYe4hq8PscpvxtRD7blaeGjuZBabETpZXq0sR2rB64Jci8vtjDhHE7Fpkj6WIYb9D1PaS9teXzPI3lEMOESuk/RHTQd5DIhvGbP+c8RPRt39QDDB9DElkFpjy3CHZapO0f6OGyjWuj9I+zeyEpa8Hc9Yx7bxAsw697qfAjjvEG57uwppuqMtJh+jJ7HJ/v6rYH047xA7fb1bYRPvjzPoZsW9eofMzLV0h+ut7puAqtPU1ef+zIG1YPrJAKeRJ5s/s3/cv5fUDmRWmv4+SyE35DTqJm3IdkMxNuUcmrjNT3y3jplw7BZGFMnPmsQ3D+CTLDNPft4njpvwmnMBNubZI4qbcKxE3mCn33YK4KfcSQrg=
*/