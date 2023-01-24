// Copyright (c) 2001 Ronald Garcia, Indiana University (garcia@osl.iu.edu)
// Andrew Lumsdaine, Indiana University (lums@osl.iu.edu).
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ARCHIVE_DETAIL_UTF8_CODECVT_FACET_HPP
#define BOOST_ARCHIVE_DETAIL_UTF8_CODECVT_FACET_HPP

#include <boost/config.hpp>

#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#endif

// use boost's utf8 codecvt facet
#include <boost/archive/detail/decl.hpp>
#define BOOST_UTF8_BEGIN_NAMESPACE \
     namespace boost { namespace archive { namespace detail {
#define BOOST_UTF8_DECL BOOST_ARCHIVE_DECL
#define BOOST_UTF8_END_NAMESPACE }}}

#include <boost/detail/utf8_codecvt_facet.hpp>

#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL
#undef BOOST_UTF8_BEGIN_NAMESPACE

#endif // BOOST_ARCHIVE_DETAIL_UTF8_CODECVT_FACET_HPP

/* utf8_codecvt_facet.hpp
ysmMQemQ4x2ZtCYZucsyAf7+NrSDlavIaVfsV1pgkt/r2mPzOY+H4IFJsJ+uBJhFzt1kX8MUtxnQ4jEBtlGFg68x1IOtCsNECF1l1YMXwRmRjpafAH9jQFhmUAlbFQxP7GvhNjzbV+eJ1jIZLIWUOGpnK62gCLYK0WLijMYELJTYw8/uxDMMydMzFcA3zJYOXGi6f7yvfh5HSOPRwUjUyT9erp/sn+ynUxg2+8l0zvDXCbzGKsKTTQumBXR9saEOWskCq/BZ20BuxA6/XgItrMIGQ9+O15Ur/eOLwbs2Ysv5DvD0969+EM1QEMWnAmKMwKFW9An4g7eBadKEamjCO2AyaK2WaJGMpwNYqpB8q4/iUJVuRpTjiIJE+lcsNI59HSVTUTya0udxRCMGE7g/LKHIv74G8sqjKRwQdLM4I1EddIgf0aV8UKykRtbLkmtvfZwRafG625JIbFHerDvQFgd0i6uAgZSJB234CtVH6Txsn2KCMwaTBnRjEgF8Y+fAzsYm6XCiTSrms6GDiO1J8mWT/LTgccTLef9O9FdgyCAdDgJK40YIlvjGx6EDQO87wf8VO/A9k1CvtyEVeKm3wO4hC/Crayk88tWZA4O0TYO8ej5EALkQ0FqawOb1g8kJ7B0v8BDJszv/am/ag3+uN63ib79Byj3IhaG/qQI/s67bY4/Mtar4GrQ9MD2gzrVyKoifazRPhNs8U71Z
*/