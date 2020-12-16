/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   basic_sink_backend.hpp
 * \author Andrey Semashev
 * \date   04.11.2007
 *
 * The header contains implementation of base classes for sink backends.
 */

#ifndef BOOST_LOG_SINKS_BASIC_SINK_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_BASIC_SINK_BACKEND_HPP_INCLUDED_

#include <string>
#include <boost/type_traits/is_same.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief Base class for a logging sink backend
 *
 * The \c basic_sink_backend class template defines a number of types that
 * all sink backends are required to define. All sink backends have to derive from the class.
 */
template< typename FrontendRequirementsT >
struct basic_sink_backend
{
    //! Frontend requirements tag
    typedef FrontendRequirementsT frontend_requirements;

    BOOST_DEFAULTED_FUNCTION(basic_sink_backend(), {})

    BOOST_DELETED_FUNCTION(basic_sink_backend(basic_sink_backend const&))
    BOOST_DELETED_FUNCTION(basic_sink_backend& operator= (basic_sink_backend const&))
};

/*!
 * \brief A base class for a logging sink backend with message formatting support
 *
 * The \c basic_formatted_sink_backend class template indicates to the frontend that
 * the backend requires logging record formatting.
 *
 * The class allows to request encoding conversion in case if the sink backend
 * requires the formatted string in some particular encoding (e.g. if underlying API
 * supports only narrow or wide characters). In order to perform conversion one
 * should specify the desired final character type in the \c TargetCharT template
 * parameter.
 */
template<
    typename CharT,
    typename FrontendRequirementsT = synchronized_feeding
>
struct basic_formatted_sink_backend :
    public basic_sink_backend<
        typename combine_requirements< FrontendRequirementsT, formatted_records >::type
    >
{
private:
    typedef basic_sink_backend<
        typename combine_requirements< FrontendRequirementsT, formatted_records >::type
    > base_type;

public:
    //! Character type
    typedef CharT char_type;
    //! Formatted string type
    typedef std::basic_string< char_type > string_type;
    //! Frontend requirements
    typedef typename base_type::frontend_requirements frontend_requirements;
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_BASIC_SINK_BACKEND_HPP_INCLUDED_

/* basic_sink_backend.hpp
7quKexsFKK/Nz15WgUnAsj0xntXJLgGv05XHsca1zewXZ/xt9mnkh3HPfoEGv1j2CzH4ITGdM1z6petxaHxNp2Meh/CLAjG24Iex5bJXpIcX23rivUYvQZojbu5XTvcbmGROz0spSE8amjue+1pep6p7C6fXjHHHC8N1sYPCk7BLyaq8n8j00p5U9qiMgny5l2MChW8Tq/HvFojivoI83F+bQeAaCp+D63iY6t4i0xuuHZl2lx6GdIPRmmVjO0NIWycUPhRrVT34HqiJoBLdr6qoj7HtrceOkGOb/m4KfojM4wxjUFQwBpGnHIP+cgw6jyXvMr/xchxK+xrUrnIcyrHjYhNsLE/9rea1wA9DWujPpRLVODE+mZyeTernUInyOaR+zpQonzPK/neNy88Guf6/gMLnKPpenTbO8ExaROHj1c+ZEuXzTP2cKbnG50yJcizL5+sYCl+hfsaUKJ8x6udJiZvnCY/7DAq/T0RiDHsJHr9lY5ik8TWOX3+M38ty/OZgBP/++6inyz0z0OAXp7iPit99H7XvS1nOD4tNfB/dCDmdiLn/r+n64BdG+d6WgWDjGKZjh33yVpTmcbSXJpao93Ai3/JjLEN9zXBc9/fBeyh8GK51m+o64vTu31HuovAcuperriVO73qfpH7Io7DRoh9S+peF59tvIELa3V9E8brh7aSmaCG85PvCXvK3iYYYjz6CnuP0zrDVH89yesYb/wavaVw6jcEM432Uxw08eRwqxomvYpyUgqeEez3ZZ6QP2xNVv0nOcNu+s01PvzL40MRB7vVhOyj+zMkpz35dI+eHg4d7hg/J/qr59eu31Hqyf03vNVbj91H+fgkBG0JGwAOO9ntUAtuBkbxOXg/vCMbzOvYOvI69F9gVHMjr2FPAW8AxYE/et9AbLAT7ggvA/uDj4CBwF3gbeAwcDn4B3glaNPt+jnAwTT8vOAa8BRwHpoI54D1gHrgCnAKuAaeCz4PTwYPgDPB9sFDPH5wH/gjOB38BF4IC7bAE9LfY8wm32PNpCD4AxoCrwDbgX/X6g8vBPuAKcDDHG8bx0jme3t5POd5R+P2Nni38jBa8v0DT44Gh4Bbej/MC2A7cBnYBt/P+kB3gKD0v3h/yCng3h88D94IrwFfBteARcAN4CNwMHgZfZP/t4NPgS/oxl3ey4/nCZQzh+0sml/ck4nmAZ3j/y/tgDfAD3t/wIe97+QhsBRaDfcBzYBJ4gfWll3i/zmXwYfBL2V58LwI3KdormNsrlPcxhXG7NQLDwBrcfrV5f00dcCQYyeMzCkxlvW4ex5vO8RZzvBVgXS5fI95f04DHbUNwI/sXgLq+d4Guc/1NXW95Pe8cZ92u1OuuQl5pLnrdTfA7DrkKiZhj6ndNZzrTmc50pjOd6UxnOtOZznT/Pe5P0f9PyslLuwFr/3X9/05p+4/WuZPbzPPIz0FGYX6x8KJDz5KSlkYnN+pVUqTNu79QvPsxt2ERPdESC9W22jg//o1TOtckEclzsnMp7GnhjX9vpl8gChcFwkOsUttqc80LLlPaLPuGwqryPK4mztNxL+EjAjFfUttpTpjnkzlOV5EoPKSu5jXyqyHCMM9rw/GdyPyoL+lz6e+na1dst81Zt5CCY6MtpUlOdsL6WAW51zmf1yBndLtonzv6IS1joqIfgri8syjeo8IT/zUXXqo+QF7l+yCM5+RzKWwrpQwVNtEd5N9r4XSjZV7ST9qrknob+TuJeRT+PNrdIsIgPRR6S/pdOorXBvWwyvO9Tn7JhvjjpK7iIQqbizy9RVPRTOo6D5O/p1yH8AQdzzaMkTRpD+19CgunMvjLtLdg1ES6jCn+bVwKb+B6Lrk=
*/