// Copyright (c) 2001 Ronald Garcia, Indiana University (garcia@osl.iu.edu)
// Andrew Lumsdaine, Indiana University (lums@osl.iu.edu).

// Distributed under the Boost Software License, Version 1.0.
// (See http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FILESYSTEM_UTF8_CODECVT_FACET_HPP
#define BOOST_FILESYSTEM_UTF8_CODECVT_FACET_HPP

#include <boost/filesystem/config.hpp>

#define BOOST_UTF8_BEGIN_NAMESPACE \
     namespace boost { namespace filesystem { namespace detail {

#define BOOST_UTF8_END_NAMESPACE }}}
#define BOOST_UTF8_DECL BOOST_FILESYSTEM_DECL

#include <boost/detail/utf8_codecvt_facet.hpp>

#undef BOOST_UTF8_BEGIN_NAMESPACE
#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL

#endif

/* utf8_codecvt_facet.hpp
/LZpfbScJZKGGtlC144QwzLm/KhoQhhEXM+QMYGHxoDDfy1Q3dghGS5aKkw9CmUI9IfXvwIk3FaudQbn91gPVdmKJjUFmoXZie5XToHaEx15GBm8oo/b10jTI00JAf8xCJ4cGmhKojtd/1prjA22g2x0U9N3UnPWBokeqiU+PXTYbACUXFq1LV0Pv/84YSRQjLapRViGdBsG98UKimKuepUFjd1/QET0sdlVWx6h1J48O33ERkVO0462smGQqZ9JAcUI6BYycBQ1rqhErazhmEt3JGde5fyAtmO5o5LAmMLloTfCA/+Dicqg6pah1NXW5CiBzuP8FDbLSNswxHuSUv/kY5+ZdUkD+X2ux+zspe8ek9XO6ibhVMy8ugQNhUn4Px2gEjFv6o+Cars01WLVrNYS9Pq0I7APZKuENZkPGnlWbiFox5UBRam5OVAFOCV01q8p0uOggsY/FzZrIFnUEPzwVMSqbWKhE2cTQYDdOvDrwrZkiJDnc6MnjcqoKk1QSyjRMVWNS5kT6yZwiVoXdwlIxqIihWk2vzwWluotQcayamVBt7ai/Et74Q==
*/