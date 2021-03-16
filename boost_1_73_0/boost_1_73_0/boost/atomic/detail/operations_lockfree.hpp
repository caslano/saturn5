/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/operations_lockfree.hpp
 *
 * This header defines lockfree atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/platform.hpp>

#if !defined(BOOST_ATOMIC_EMULATED)
#include BOOST_ATOMIC_DETAIL_BACKEND_HEADER(boost/atomic/detail/ops_)
#else
#include <boost/atomic/detail/operations_fwd.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_

/* operations_lockfree.hpp
TqrEM1bR+zb7cunev6Gh4/tnBr3lGLtW59869pm2/Uu/2vCfV24Y/nshprM8uqP1qt3/GvXCG9eXnTDmw8lPCnEzyy9+bPGGnLcG3X3elZ9c1PLdrDuEeILlg/o1el89f1frqaesW3X5ont3C9HLgPyy3HVPPz1vaM2O31760M7RF5bIH5fPMR44x/fN/rNK3rjx0w+2NRgNr8gf+coxzq1sGPrhrG/GHBM9YeevJn5H/R5g+Z49fW7edPqa5VM=
*/