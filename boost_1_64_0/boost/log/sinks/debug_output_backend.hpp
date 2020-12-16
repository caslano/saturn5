/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   debug_output_backend.hpp
 * \author Andrey Semashev
 * \date   07.11.2008
 *
 * The header contains a logging sink backend that outputs log records to the debugger.
 */

#ifndef BOOST_LOG_SINKS_DEBUG_OUTPUT_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_DEBUG_OUTPUT_BACKEND_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_WITHOUT_DEBUG_OUTPUT

#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief An implementation of a logging sink backend that outputs to the debugger
 *
 * The sink uses Windows API in order to write log records as debug messages, if the
 * application process is run under debugger. The sink backend also provides a specific
 * filter that allows to check whether the debugger is available and thus elide unnecessary
 * formatting.
 */
template< typename CharT >
class basic_debug_output_backend :
    public basic_formatted_sink_backend< CharT, concurrent_feeding >
{
    //! Base type
    typedef basic_formatted_sink_backend< CharT, concurrent_feeding > base_type;

public:
    //! Character type
    typedef typename base_type::char_type char_type;
    //! String type to be used as a message text holder
    typedef typename base_type::string_type string_type;

public:
    /*!
     * Constructor. Initializes the sink backend.
     */
    BOOST_LOG_API basic_debug_output_backend();
    /*!
     * Destructor
     */
    BOOST_LOG_API ~basic_debug_output_backend();

    /*!
     * The method passes the formatted message to debugger
     */
    BOOST_LOG_API void consume(record_view const& rec, string_type const& formatted_message);
};

#ifdef BOOST_LOG_USE_CHAR
typedef basic_debug_output_backend< char > debug_output_backend;      //!< Convenience typedef for narrow-character logging
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_debug_output_backend< wchar_t > wdebug_output_backend;  //!< Convenience typedef for wide-character logging
#endif

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_WITHOUT_DEBUG_OUTPUT

#endif // BOOST_LOG_SINKS_DEBUG_OUTPUT_BACKEND_HPP_INCLUDED_

/* debug_output_backend.hpp
jNy8nFTYD7kGezlI73KNTpZj4GUKq4nr0UdxfavSTpE2A56nsDgRiLT1IIprHOmV17jqOkZc5XUsn5sPUPh45bWLtOprl+8Bqyg8F8dUD7jUFPwjx+0FCo8UhnEqx/iTFNauXNxaGLeehnG7mMfhiUh9rF3Lb/ba/H48fq12aCa7jLEp1zXGHM/cq7yWYhjEC3IH5B/6M9exBvM6xxbSud7/VeMI8VzteWSmZ6ufrRzX/ThIoPCByjGEtOpxwH3ZhsL7GG0HyzHSg8I6sQ2Xsn7dCIkJvvY+nfbetfZplos9C2oThV3SP9cO6eTXNPhP3/rtyZjEjuk9k8dMLl5zZr65duF/ae1Cf8e3En+PJfP9oKuAY927xrp3H9a5V2Odew3WudcBG4BxbKuCbGXwNwx9H3G+VkhjlzUD1Tg/XzAE9DP8lmUxp2+p+C3L6pw+BAzltQNhvJYgAgzn33asyWsMaoEJFI/zd7y7gx0V+Tfh/JuCwWA8ly8GrAvGcn3jWKfdHOzA8ZA/EvN7JL+bJ9vzFAX87TuEded3cHmHgfX5tz5jeK1IJ/6Nzz5gMq+FSAXhJ9JYNz6GfzN0LNu4yAA3gePYzutd4F7+zckDYBZ4mH9z8jj7nwInsf3XyWz/dQpYCt4N/gDOACvrdcL/1dn+awy4GOzLawfGgfeBC8C/gGvBVeA+8K9gEfgI+DHbgf2Sw3/mtQz6h+5DIL6vqXxx4DNgO7YP28lij3cLuI7twK4Hh3L8Ozl+BsdnmyP8ToA6KWyOJCKeBWzH47A92/joyP3Ridc0dAbbgV25n7uB/cCebOOjF/dPH3AcrznI5zUHk8EBxnHHa4WGKcbdNi7PTtCXbYDUBnfxuNjLtkUO8vleB+8AD4G7/sPWNOxbVMlc1+CyruE42qQUEri4koiHDIbkQlYuNtc4/JO984CPqkgD+Lzd0EKAJECIASkREKQYOihSFBU9mohYQEMaECmJJCCgHCAWVFBEEFRUpIioIAonqKhgRUGPO71TsaFib5xd9PT+++23k7fLLCan5zWW3/DPm/6mfG/ezDfzDv4O/g7+Dv4O/g7+Dv4O/g7+Dv4O/vj929b/c8bn/0rr/y/51v8b6xp0fb2XDEytTswXbYvMPeeOLy0oKZX0jfGvP8q1c718W+y8cm5haYljrdLpt7So2D0Hbf2mlsVbVFpaNM4Y59qF9Z/I3LHH9cuOtXDjXAfWuWG9R11b0vlguZfoOWLNcxp2ydZO8xaznvSDnkPfgHLvDn8kY63bG7PblveogvEFE3JKC7LzS3I4kH58XoGJKveiiZH1z64//vRTnadD4d73IuuJP0k8Dey8/PxnRC/D7m19RK9d9bY7Uhd23YBKH1UgafUirdaS1k6bVn25buioV1dcxRMKJ4XznUVcWRJ2h41rkVwn2nwny/UwZzvY7WsHH9WW9Y2CkpIcchqOvyPxN5bwr3qRtdrKct3E1U5sfGm6f9LGl63rIY61LQ3j/G5Fd9LvKOlts+kf/nTZeezpvrjSY+LSfapF+UXGlsUYCXu4F1OHkt/vpDWPnzgue0x27hR6qm9d5TQJd50Xb/2th7iv80LxnF1P3OnkReM0IvvNiLJ85ReNLzBWl+BMzUeGfpugNfedauPKLxyF3Ij0zc0/hd0aJxh+0XlNg2dLXuZJXm5ogYW0F7qB+gzF0UDz8lxTww+ZqXH3Id0e9PGaJrwOfYN+r+5p/g6E8hJjPMwduGfBJfAe1UN6wSv/tyqoA/d6tPbPVP+akvajVP9aodxfmcwIteO6vnacoWuGlLvaa3vUuNNj1qLwL3VF2WPnr0fxL3UjcWkdhtLdbP1rXWk8oXKmDrA=
*/