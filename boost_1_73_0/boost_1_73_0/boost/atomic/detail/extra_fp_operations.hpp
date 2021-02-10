/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_operations.hpp
 *
 * This header defines extra floating point atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/extra_fp_ops_generic.hpp>
#include <boost/atomic/detail/extra_fp_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND_HEADER(boost/atomic/detail/extra_fp_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_HPP_INCLUDED_

/* extra_fp_operations.hpp
ajgczWbc2f4DUEsDBAoAAAAIAC1nSlLX/Tu+QwQAANUIAAAlAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9NYWtlZmlsZS5hbVVUBQABtkgkYK1VbU/bSBD+fP4VI0C6pBcSyn25cu0pru1Si7wpNgdISNbGnuAtG6+1uw5E4sff7CYmpaLHlxqRtcczzzP7zMz68N2vu7xDePPK3H9GF602YKbkN8zN685Z9gTbPwq6pfUNigHsI56yLrwZ8QQdF5HtOD7a+yx7g+bWJmZ/BjbwNrO3ZPEOKS6Q9Ubxu9JAJ+jC+w8f/oJjOD05PelByCqOAhKD1QLVXQ8+Fs4yLNnjY1/jPz1AA0z0HVBacg1aLs0DUwh0L3iOlcYCmIYCda74gh54BaZEWHKBEExnN/HkvAcPJc9LwtjIBnQpG1FAydYICnPk6y1EzZQBuaRowi64NoTXGC6rPlEjGFQrTRCWnAktga0ZF2xBNMxAaUytzwaDvFGCMh8UMteDvN16vzSr3S5uKIMV24CsDRgJjcYeWL8erGTBl3YlKchYNwvBddnbp0JEVTGQCjQKQVAUxlFvU0ZIdsr0rBfUlC03dtGy0pbpoZSrF44kIYEsG1URDUlAPoUkgXvQVAUq5+s23TLs1HTS/qQk
*/