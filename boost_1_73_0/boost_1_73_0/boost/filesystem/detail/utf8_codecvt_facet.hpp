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
pFSw9es9gB0G8v+yBxS7JDiMX/buGuFwmg4e843VGc3uBXfbgF51sJXG4CH+vG1XsOImUYcAV8kQVFU7jTZ6PShQbX4vjkEYa1cG3aUwpUI4yMo2T9D8JOYmP4g1vjS25Pr+0JZn1daKaC2slai10MMcPZTb+Ibw4d9nKvYEtaM0kuh76ePnqKBFXrgaZzo971N74E+98jSctI5jgIz340Jw8RGHmtxPf3TrbOwJ2YuZhJqfZND7s30G1V3hdzvIUlAHQWsXo2oivxxeTVaMhjO/MF/MVrPz2WTJ/CFNJuPTb43+NfxlPkE+lbKX53z/5Uc/6f3Amvfn42q114fOYnq5qMx945tK7/WcqxkosduzMT9+/HhwY5FKui7uyLRLiz34D4PnFxpaaC4y+EDhqSvwIi4eOF4ORYTBG6RaRxupvCKAwVG4hVT/MPjatWvbXL3gaPBtA6qbVOVoUIdZ03IMUxGF58ErT9Hs0VivyqLe+y+LUunjN/x1OJ4MfxpPxqvrEF1bFgV2OeBNMh3/JTqJ4OhNNXen9f3rgOTd++itF7gYra4WU/h1OLkasUWV2OTGaD372VN0lqMRDCfLGV5bf1rsXZzPlqtwa+1g30S4m53FqLXB/gdQSwMECgAAAAgALWdKUkvHcOrQ
*/