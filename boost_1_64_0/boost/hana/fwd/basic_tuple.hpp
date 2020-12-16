/*!
@file
Forward declares `boost::hana::basic_tuple`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_BASIC_TUPLE_HPP
#define BOOST_HANA_FWD_BASIC_TUPLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-datatypes
    //! Stripped down version of `hana::tuple`.
    //!
    //! Whereas `hana::tuple` aims to provide an interface somewhat close to a
    //! `std::tuple`, `basic_tuple` provides the strict minimum required to
    //! implement a closure with maximum compile-time efficiency.
    //!
    //! @note
    //! When you use a container, remember not to make assumptions about its
    //! representation, unless the documentation gives you those guarantees.
    //! More details [in the tutorial](@ref tutorial-containers-types).
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! `Sequence`, and all the concepts it refines
    template <typename ...Xs>
    struct basic_tuple;

    //! Tag representing `hana::basic_tuple`.
    //! @relates hana::basic_tuple
    struct basic_tuple_tag { };

#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! Function object for creating a `basic_tuple`.
    //! @relates hana::basic_tuple
    //!
    //! Given zero or more objects `xs...`, `make<basic_tuple_tag>` returns a
    //! new `basic_tuple` containing those objects. The elements are held by
    //! value inside the resulting tuple, and they are hence copied or moved
    //! in. This is analogous to `std::make_tuple` for creating `basic_tuple`s.
    //!
    //!
    //! Example
    //! -------
    //! @include example/basic_tuple/make.cpp
    template <>
    constexpr auto make<basic_tuple_tag> = [](auto&& ...xs) {
        return basic_tuple<std::decay_t<decltype(xs)>...>{forwarded(xs)...};
    };
#endif

    //! Alias to `make<basic_tuple_tag>`; provided for convenience.
    //! @relates hana::basic_tuple
    //!
    //!
    //! Example
    //! -------
    //! @include example/basic_tuple/make.cpp
    constexpr auto make_basic_tuple = make<basic_tuple_tag>;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_BASIC_TUPLE_HPP

/* basic_tuple.hpp
RgmBuKIaEWCfUvZ1n4fmghdjnqBJmJrYoqOyK3QOdTf0k5gV7QiFWXyVWfEs+OyGCYLrujMOY1s7ke/jCP7uEaK2LQOgOMXd5QlH10vspsc+pk0ipj39SVCQ54I7+X8lZirGfFNgelA1+icFVck/XlsraTdIfB+sTnwNlAaG6heggPOBGvg8KWe+RG/cwOeB4I0SHCb0fZvZghp4L330ILYoHpo4Jn74bDvPjbHL6eb4ZyOyE3flT1VXPYsKHXjEV+juscTjb6pQNXZxvJVO/SC+L+Uf5TOImEE6FJ9EKwgrXh0xcMXRpVgdWiaBQU7wijTpFbwpAdZCsDaC1fVLihdEu/yDvWuBb7K64nm1DSUlAQoWLVA1aFmrVgNaaIG2QMEHGKhNcDzKNsBv0QmDBGHWUkwrTT8izLmHb6fO93MqFtHRUqGAKA91ovhA5ubXRSa+SkFt9j/nft+XpBQpPvb4bYE033ef59577rnnnnPuuSEj3unFEkg9+MZJW3BXIsmjJh5JkYiC85aZvBeU001vbk8wmhzIVl5J1WZ5Et/m4fYlM4GZ9zLju3rcp1nxvkfvxKzvdns5xbjEFNRI2pVgGDSwMwjsS7d06Ir3fCIhqB3gvnNS2/K/MbgLLFzEcflPEbsKGIXlO7ApLyKw6LyWxa28ua9DQ5r48c/m8U9O9DcshKqFrv1Qq6Yr7b2FhZYwH2AzyTgfw3PsOsfgn3+kj+EyxbhVoydulROYKDiBRJfD97J9wU+ZOburR7zL4fv1mGLpTcGF7GHSlQ6ZGlwOLwS2Cs8jMZfD03uoLocf0jKTsc85H3VoLodd8ljH2jmIjC6yFEUXWaOLbATeTQcPTZWeYig8yr7dHV04HT4hzumwyqLst36vTof1j+5/+IkBXS3GOr8yOKkzvzJN2H4rS0RGMvDiO3RVbiTXKjgFza//bLeyMk3jO/5ME41C87gQtaSJL7EsEvFrZIsTFp/pjK1qgXtSRIFL+4A0qWEtapigect2wAxzC0XZb2okJcf9Kd+aW9Ht3y3ijDIQWc6T3VZonIMdqfaVQwBh/bhzonVAclcjycM078s9Ne/LJuF9ObWT92V2KgvcDU+bY5+0G4FqnDmcOzFc+xFFkqtlOhPQtS/mjK49MKd37YHZEeywVf6gviQVrlxPhSvXwfVTe1Yfzqs8ofrwiGV9yKlrIbJsCK9n166FSyDYcv6Q5cW60+RwkD1oe1XW2sly32GPPPcB3CW/SvOBrO92MTfv7OQu2RbnLjlbibzYEXOX/A1M+o/rcwQ/d46jC3/IY0yJ/pBPOLY/5GX9u/aHXLOn40h/yCd8S3/Idxhj/pBP0Pwhy4PhDpkuKCJbt+AXPe0rn2YrNuEPOUn3h9yg+kN+XPWHfH/M4XGNUTg8rjSq/pA/ta9aYNSj56rRdFZT+P4t1Z3/UtLxCIfv32EYffvKfPFyCb2sysELiOkwwHHVWXCIvHqyEZuQc8LFwPam0Pj0yInh4mhovCPSJzTJFkkLTbJGrKFJlog5NMkAj8jJ9pVkMhfpiTJSVL8JcU6OP413cmxFm2rJ17Pu2HjPkY6N7atoqQmXJastkw2iZaQFjjk5XoKZ4T/SyTG1r3KG2rZlZYApEyDCyfEb7OTYTh6PUzUnx5lB4ePYWnkjOx98DFgDVqhcuaBZW7Z6E6YlNIOovvBzfPkko2MpvsvxvQ5fGd/Vk/5z7CMEX7mMGD/1KHV9r5otS+BkcadGrjOC+5YB9UO9m+ubnHsLGwPjgodN9pUthFezjFDMN4LW1E7FphOZgvsGQz3ftC85uHdMzx3CiY792oEmUVIDaRP1sg4U7g3MCB4221deTWWVGkU=
*/