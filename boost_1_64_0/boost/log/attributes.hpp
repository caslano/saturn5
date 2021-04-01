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
W8KGmPxQf8wMutCU6smNt0bevHFTd0K/ZOY3qtd4kR/JI1AZUncZ5uZa3qvFkdFEEpRnpfEhvdGF7eZHB6T2lXkDjvJI9rvkUZ8LidTNCMvk3NwuFeOgQ01jhrB+Enu1Be1OphRqgJNojNAxoMoEDwBcojz0zg+Rh22AZG/+N9CAaFkKGc5eAu3jKRXu4zmgr032dZcxaieSNJ3MtRlsPzB3SwQtDiBpxDXGD80lOjq9pQkaiH6vV6HkTH9YexQOtil9VhZuREwcQBKiLSiwCrqpqaMwkT/f3/s10pLzSJ8T/Cw9Mraomv5h8y7esNZ7NgRoQqq1v/7gXh4Yps6exsXdzh3ZDYl6XZzDqpmik59wrX/pDfTtKgFbtIEM4IEApD00HqJQ7xXysO+4C4BqJyyZCL0jQKAj4T6IM4GuhoX4Hy+vMk2+4cKvvc6NISsybJkwS99w7+R7E+iM7UBeaeV5zzmX3l5OtqcLXZnX5tyGJZd9IecbGOvsuop9053+O2B2dbSKt5YcEO6aG0eHeGMWZukaCOpnQLfqDna2CEALwC3q5A7xylNKww==
*/