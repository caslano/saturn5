
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FUTURE_STATUS_HPP
#define BOOST_FIBERS_FUTURE_STATUS_HPP

#include <future>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

namespace boost {
namespace fibers {

enum class future_status {
    ready = 1,
    timeout,
    deferred
};

}}

#endif // BOOST_FIBERS_FUTURE_STATUS_HPP

/* future_status.hpp
EBey39rj8fa7A3Bfj8F3X0y+3YB7NIIPca/E5HsbcB/E4Dv1iXh8nYA774kT82E8GATMaBAXwtcAzM4IPtTvXYDZG4PvV4B5Kwbf54BZ+GQ030rArAniQuLVNYApx+C7FTC3R/B1w2/vk/H08Qrg3o6xPvo/ORX+Mx3fXMAtfipafpcCxgziQviqgLkhgg/t5QeA+UkMvqOAeTUG3yeAmfN0NF8PYFYGcSHyMwEzFoNvJ2BujcH3IGD2xeB7FTA=
*/