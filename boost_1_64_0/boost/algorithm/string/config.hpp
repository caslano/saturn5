//  Boost string_algo library config.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CONFIG_HPP
#define BOOST_STRING_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_STRING_DEDUCED_TYPENAME
#   error "macro already defined!"
#endif

#define BOOST_STRING_TYPENAME BOOST_DEDUCED_TYPENAME

// Metrowerks workaround
#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003) // 8.x
#pragma parse_func_templ off
#endif

#endif  // BOOST_STRING_CONFIG_HPP

/* config.hpp
xD+R9kDJRmL7+urA/T+QC9cF2TYYAWZvwAHUWmJxAG3WazoU5NP7fZW6khdZy7ygHNst/NaxTUchENiQ8m/up5V4Oge33AfXvsYt58veqxD0lM1fbssfsLh8vs+Wv/Qv5fMH2/KvXlE+v5Mt/9IK6o+35e+9p3z+T6+G8utWUP8+W/6H95fPX2vLv2BBBf235U8vtuen6VfMqQKRYezBwZbKKiP6IVJMgvhaBiIuhprH8ZucsG5ykz7su1m4aDOpr6sfUFrhxL9rq5z41/Ed7WZc0Oi5TDV6guiK2L3ycWd5l8RKHOmVuLIeYhYf4mSVRJpQb+AZUTxF5NRmJ3d8k8in2oIcqeE8XdsU5i9QW+8x4DHUc4+Tzc9UUVU+WlyLnzrycLJqo93is22AWzE/LWPsWmu+L3qIe4hikq8wmvTQuOz+0Isg+uNFW0X7lQPcmi83Bx8T6nzLRuabSm0Pxto5T7H6mAztWL9p1FHwYdD+uEXL8A3hxUq3kAz/Ncjwj6u7NMLGgvBRgUx1MMJeTlbPwlsvz7e8Z1KPVJLwNj436TdvkaYusTf1JpUMzKaa1RyAuAuW0iA439betjeI61hzajGvDAwvAqsXhkqmc8n7qeRO4kLKu3Nm7zaYxbPD7+84vfm1+U/r8FdtX31MXuNwo8btsd0a60HswvCH3sJpMhs3bKbZeF5F4c4TaI2B136v4ZbHizCuzNDW4eHnkU9FNUDWHCWTUJJwXsQDP00Gfqp67REg+kzfkUYBnJ0CSTz0v9WKitniLmgnoTTVpmnWomOV6vZID1CEtyxjl2nCmKyVwFaA+aOtjTo6YgKB7RlgU6lbiS2iwpeytKxX1cAFxGuOyjHVxMiIoUGKqvYXq3w3KT+Wyh8tNstfLuVzAp+flFBntKCIt3NybMud+TUsl9A4dWLg+oGa1eoOdIFWg7k0zqJzuDP44/Whn7KavsQrAs+yrR4Le87+c5FMXEOeuAnm5j75kHlXTDPftpyFMYTpIARb6Gvhn/T7Xr47ITcYL7ZuzXlFTWNeVWXda0Hwg3cngmiiH2HNIKdJRbTiXlX3PCRbMaegXL3yMHoG72EV8hfaA4FrjaZ/B8jNAyhTbRZ4Gnvw/6QSD4vn2Cut2p4LSD1YL2+SwWrNg3WrOVh7HjQbPd2M50O4WJtSZKzpIdeUlPSMzZf4Y9qXuN5qtLtCvuUT1YGlEuF2ziOeUUBIcfPQCK7Ava4DC6AxEzJI089WpB/beHkr9G/Dp+F2yDzYa3OGESAyNNL4iT6ytSdmBDkkK/aVT4RCIPbTSqxkbKI8OObNH55RSt2EUcQxAcoyFLCLmgEWl/Z7GnGZdxBSYTzdEDZin66YWhrE71vYqA2JjZFIFGkSbcKZyOSxBcQEf4ZD/EQe3YByIyhLFN5GwhgcARJ/chtbVh35Nb3N92RYVNvtnxaM+YmT2nwPxyGXiuGmuOeOfwU4PCtxDWLdflVXV5SmXi7gLaVW49Pyz52MVeVaQOq8ntzbwca4FvQUyQIuizoMbhooimtBG05GNPML8IWHqVEMdX1OnOtV6KUz8TyGEfhhdQY9ThwHqwNb+DntwBSx9NeKz+Y2KKTWKveRXxH5lyJhORchXltxRtctt3+JQijThspsCMkToN4717EKhdxHglaZfsF0lPicqF6U+AZiV2xL5bY6hmxEQcUVs2WYdC9pmTA+9jCM920Cj10g4JcCnM2JcIGk9G+wm1h4SplNohm9dvbmmiNFnEhlNj6965E5w28MxZ8r06I3lwj8Bw6pYpLGc1eupG9w2LG/NFtSVyM1WOxGjLQ1XpwLQ5EN6XkpD98WWo5H8RXZLm+xd9QGNb1GNWo=
*/