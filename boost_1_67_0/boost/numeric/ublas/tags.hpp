/**
 * -*- c++ -*-
 *
 * \file tags.hpp
 *
 * \brief Tags.
 *
 * Copyright (c) 2009, Marco Guazzone
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */

#ifndef BOOST_NUMERIC_UBLAS_TAG_HPP
#define BOOST_NUMERIC_UBLAS_TAG_HPP


namespace boost { namespace numeric { namespace ublas { namespace tag {

/// \brief Tag for the major dimension.
struct major {};


/// \brief Tag for the minor dimension.
struct minor {};


/// \brief Tag for the leading dimension.
struct leading {};

}}}} // Namespace boost::numeric::ublas::tag


#endif // BOOST_NUMERIC_UBLAS_TAG_HPP

/* tags.hpp
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
*/