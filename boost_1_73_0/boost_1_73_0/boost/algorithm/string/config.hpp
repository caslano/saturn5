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
8PJyYEQAPctR3papFTCzw4njCBbGAPeXn7SR9o5duiNlfQ2ss76GaSlcI5QRU8D1yHIw/Jo0crCuk0ONWjnKoLdCSDmFGFknB9TaeF+foAyozSbblI1iTIfmlQXogPxJnphVX8hR8Pf2okEjYKPxlWl6ctLGDNXBDeEqh65DndkVhzq3dbBJh8Sh6dCTp2TRs6cBN6hxTviiL1M1j9kb54Q7Tqs/punAuUwzooVH0dbgM+jTJ4LMqc+FVj6DVoVX0asu0SJPlXmhwJo5XdOqcjmtbS/qxOcdLUYNYE1ZU4wVIWOjlLFRzNgcI67AEBwjQtJgZhmLxcOG4xks1D6ZLiZ295adD407283o5oNhJxlaqgZ7snDm89mkNR1KgpY8PMG/buGuFsH6AF+tgefLlJ85c6regWjBD6EtNxo4XoekcTOB4+4T0HkQRg8s8CB/vMoHRNjTCfwfXnqPq/m3wejy2qt8KPnAsZKviYCB8cbtqBKBh/ql6wrP08KP4zcSJTmFrZaCjVmABsFvdx9e8xb9He98rD3kvxUkpDn/pSEdiXCyo3if3Se1TSXLfQ/kMZuEdAmS73wBGYFAqav2kPzqUuEfqoDkGMd6l/Nvo0MuS2d9qYtX2z/+kJuadRUYhSrpc0kcFhT/Ge4v
*/