//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_HPP_INCLUDED
#define BOOST_LOCALE_HPP_INCLUDED

#include <boost/locale/boundary.hpp>
#include <boost/locale/collator.hpp>
#include <boost/locale/conversion.hpp>
#include <boost/locale/date_time.hpp>
#include <boost/locale/date_time_facet.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/locale/format.hpp>
#include <boost/locale/formatting.hpp>
#include <boost/locale/generator.hpp>
#include <boost/locale/gnu_gettext.hpp>
#include <boost/locale/info.hpp>
#include <boost/locale/localization_backend.hpp>
#include <boost/locale/message.hpp>
#include <boost/locale/util.hpp>

#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* locale.hpp
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
*/