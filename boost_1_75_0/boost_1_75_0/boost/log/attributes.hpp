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
M+ueWM1jAFi70SkfWRp5WwrUM+wX9ND2GghFEMOSqPySMFjphMcjfYJ3n3CvtvdMfOqYr07RVQpdmD3rpZolu2cQhLO+kp1eFgWXtXyD8d+0HkicMN7n3WtCSV6z39DZvQTt+dHHEnadSem/O13N2GcL4JxKbcA4ckoQoEhd6QQqRhEqp2ap9vldeEDKqAW1/QPmIlPasNEVQR8FtRNUQ9BFxoUeSynFsiVzCOMssYCbRQxpdn1nZHrDXYw0C8MXkamzp2fFrtuBqRj9vUXBpCokgsBIzdvcuPqYDxKLXyhAOy/4tmfSx8dAGZBgv+mEBO0vWjQcenJ7fGgskbGvRUXRiKlOV4BYV0XrFJ9YZkz4/h+1NmIkNb4uyY6gOA6S7lcIesp6FlAk1aMyJaz5i9b/yihXy+AuuVBXc7pSv7NDm6UYUiv2hzxmds2ZkCh93fKVBTwMfBS+l6f/w3j2Tj1m9Xu7AWKCkab9uGwem0Ep3LZ7nT+mN8BGff94lrFXBHEXSkedMvKnKWD6ojoqkvtam1P3QP31VRmJDdXPMqOpVc4foUUF+KKHEWiuNGDSVbjB6nXEI/9mDxsoCbQKTkicx2t46C1FNaeXH3bmcM6IuSM0TDgMnlH9liE3SD4krQZOBfIHjHNxbvSUJNjSDqDZV+1fe06wFUqfJIUd1RE5pdQbX2rQ0Ibq68l5uCJuRXD2yawojIGxgHm1
*/