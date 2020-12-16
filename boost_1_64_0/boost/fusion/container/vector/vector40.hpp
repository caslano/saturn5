/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR40_11052014_2316
#define FUSION_VECTOR40_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector40.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector40.hpp
BXnmjc/6PM2X/eb+PMejjihe6uHvlXr/noTFyn56S/9OCTm/3CeXpe7zRH8snJE0IqUeuhdhHWlYPdJIL3ZVz/qw7iDP/r2Gfu9Z9mJD+tGNa7dvWK+Uv0f62RyLzkx/6uL0+0B//m2Q9NpLWq3lPR1VWnpUufuwnfptiJJ68zFfI30cgZuU65d+nbJ/fKmjVvrB//3tmn7wIVJn/ZarTLXTUteXWj++Kef92+bnfbXkc76c+9lyna06K/mk+iytMD/LudB1wa3zGiT9zvVlbbgOTfA416xSn7+KEEZYRignbuw7WvpyHai7/PXbrr8OREvffuN1IFbme7sOXJG8XSR0IfyUsIW8XfXMG9eB+uUtyDNvfNblSa4D8fLZeB2wN619vd6qXAfeq8mb8Trgz7mitlFR4nkeL9ck3QHyrLsf4TGWjaxJ90u/Nsgx5W4Xkj/H8F1SLI8/w+U7vLN8h5fq8iRV9z5vvy/f39p7fm6t3X6gQjmHatKv1/XKeBwHI/ubebIu428ZyUe5tI1ZT3iCfFzU50M7Fur+PSHlbjYGhv74kHEltHk0jFGvOR3Oadcc1+c07bPn9Tdc6vH7yvb1lmtQ5Tkt31mL0us+lur6rbdb0mlHaCZltF0pHy0dZ3pBPdp4DOla97HiPlbDmqsr2CbbWk54kPgWrd1rocOWn57hy/6p4/ee1k7huNK/sptSr77rhSdeefeN+dcWtzreulfTP4/3f0wJ8/YIX95YE/6Oex0YO+KrHQ/b25gVQ9V2HC2Wvzwj1P7r257Z8P7Z9H8sr98YEZEWue+T+0GH8Z3w0v5iD4Yb6uvlPo5ljfHUsSGaYXPshi1Q7Ysu915yT+Yw9EXPlvTyMBQd2BnzcSQ6cTwW4mQswjIsxq24EPfgYjyGS/EdaY/xES7Hq7gC/4Fl2FzGGAjFVdgPV+NwXIOTcC3acB0W4XqtHOQ+DluZlAPrLG2MHbAlhkk5xBMiJd4widcEYyTe71j/7fh7bItXMQL/gJH4RxyKn0o+Egnlsr5kWV9THCfrO8VyrfFlDMNv4j34LeyHp6V8X8EJ+G204ataOx25D8J7Zf36djrtpP1Ie8lvKHbDDtgTw/TtbWQ9kSbl9aS016jEXviUvt2MxAsyifextA+5JPn4RN9uRuK1N4l3vywfJeXTT+JFNJD7CbnPcBC6qvvPNUXLcfog9sGB2B9jcAYOwhSMxRwciktxGG7E4fgCxuEZHIFvYzx+gGPwDzgW/4Lj8BbSHo+9cAJGohWH4iQcjpMxAadgGibgEnwI1+JUfBan4fOYhK/ibPwIbXgJU7AZ25yK96AdH8B0jMVMHIFZ2vEn9zU43+T4e07Kqwo74Qt4Hx7GQXgEx+JRnILHMBtf1Nr5yH0LrpL169v5fC7H9d8wEr/AKPwHxuA/cQyygtJE+BomY0PMxUZYgrfgMmwq52kF4aqke1HSDcYNku53WW8X/D6OxjfRij/ARHwbM/AsOvFdLMH3cB2ewwr8EVbi+/gcnsdT+FN8DS/gj/Bn+FO8qL/+vOf9+nOHnBetsSW20eIRJN4Ak3hPsFwH/Ab2w+26eKUSL9wkXhu57odgZ2yL7nYwVRKvg8TTt4O5LO14foVt8NcYir/R7f+LEr/cZP93lutOD+yBd2JfvAsH4904EXuiDXtjDt6DC7EPrsJ7cT1Gatsrv5Wxr8n27pfj+gD2xoO6eBclXjuTeMFSTi2xLbbSvhfk9ypsM/le2CTpPYKDcAsOxW1YgI9hOX4dqxuq76eIW1b3Oxzd4yXsvu6YCV/deAlRtcdMuKljJRjHSPA+PoJvYyO0HmbyfgzzsRFu+rgI/+3jIdyssRDsnFc=
*/