/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attributes.hpp
 * \author Andrey Semashev
 * \date   13.07.2009
 *
 * This header includes other Boost.Log headers with all attributes.
 */

#ifndef BOOST_LOG_ATTRIBUTES_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/counter.hpp>
#include <boost/log/attributes/function.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/current_process_name.hpp>
#include <boost/log/attributes/current_process_id.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/attributes/current_thread_id.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_ATTRIBUTES_HPP_INCLUDED_

/* attributes.hpp
PLT+zUoKEPgKKFjO44rSBQihIEQuMNuj4F+RljmABDYUZLgoDvjMzmExQR4dQ+yVFQ+dbRyL5NSduzwuQJqAszt7DUIdOPoEiF3PKelhCM68rk3XWuDMCsqSFUqKXIg1w3bTO3s57N3cXN9YRfVjMMfL4GdBJTQtFTVRy83yakv5pyyyPVC122rKcKYQeo4kyCXOBGJ5I/ciEFvIouLKW6rvVlutwDcr7J6F+SxSxpMBiuqH89+qrFRaT8jq3kYTPVnZwIj2By8vrxqd9jKKeuZz0XOrVoOQL+bwRGuDsUXUCuvLs9IuYJXtbbC8tAzX9DqWl8VnRYxI8bqlEy24wW/Cv+xxMd6NrbNSP21IqjGtgax1OvUHY9i7ciB14EG1TISfOz6u8XnNDzb2qR7ylc9lijQtVnVxJIWcTJnEaEdhHUNIIFSnKdh5yMhUP7PIgEM/YAklc0h2KqBg6jEKo7uSrBxJPydPbMcsuejREL1Ih70hW8HVsZa2hmzb+EcaV3JWdgWncmFxuyySLuN8WcIEo3A9jqsdPVSyTOSEhJHSxID1gEzNWXIfPpTi6ETEtxBIKZ+nQrA4V5qDrs6RPHqglOcFapXqp0VJCfqhmqISkLkZM2XwEc5IcE0OUCOlngFi8gTihQWhJ+RH
*/