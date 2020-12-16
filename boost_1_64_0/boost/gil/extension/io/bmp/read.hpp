//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_READ_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_READ_HPP

#define BOOST_GIL_EXTENSION_IO_BMP_READ_ENABLED // TODO: Document, explain, review

#include <boost/gil/extension/io/bmp/tags.hpp>
#include <boost/gil/extension/io/bmp/detail/read.hpp>
#include <boost/gil/extension/io/bmp/detail/scanline_read.hpp>
#include <boost/gil/extension/io/bmp/detail/supported_types.hpp>

#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/make_backend.hpp>
#include <boost/gil/io/make_dynamic_image_reader.hpp>
#include <boost/gil/io/make_reader.hpp>
#include <boost/gil/io/make_scanline_reader.hpp>
#include <boost/gil/io/read_and_convert_image.hpp>
#include <boost/gil/io/read_and_convert_view.hpp>
#include <boost/gil/io/read_image.hpp>
#include <boost/gil/io/read_image_info.hpp>
#include <boost/gil/io/read_view.hpp>
#include <boost/gil/io/scanline_read_iterator.hpp>

#endif

/* read.hpp
YyctHzee/5cnIB+P84qP20HD4if+ZqrwJ+DY3IEcgZvBwbT/1+Nm/3Mnx564g2AzONz1RJ3CquC01H//MNPBI0r/2YNHlc1kn4AjPwcP8FRygOfxOpIz49MylSwQDp5m+R8+zTKTgykHD5o88QdNHt+jIBWc6zh42KKSZEUOW5ylrzysV0X/zjtUqUePVmr8cPu+JjyV5hu19v+PHatUPWhvwu8fgu5yPO9rUPzXBF4Pgc+2Y4vndeaswu+/HFP4nTtqKm3VkUpdP0+pdyC/e/D/XtDMb1HqkuOR7yFKvWu2UnMA+3qjUl87GnI0KfUI0jwHtF8A77EjzHVr/HcF5b1ljv3/U4cp9XB1MM+/opzl/s4Evg18a8HrM3huRHkvK0I3/iT7/zMgp/y7MmT/vxx5n9BcgO+sCdI9APxc6PFmyLoO+n3jk5U6FbBa5C3/boQu7pur1F3N9vq2q1Hu96BMOpsHUQcvOBI6Os7Sfh2/v1UVTP/qFvv/U4+FrMDPRcL7m1DH4Lt5bnEdHAYdfAc871WV//3g0MLvgZbiNOtCyHce6h3lPR9y3irsNXu0/f8+0us7he7On23//x7V63ueVFqONU+2//+e7GJQ1H+I0t0Fvb8IOrj+OMoL5f0V0p0J/BzUwSsgW/fRkBX6aYOM9x+v+G8MtPOAfxbSLib7/gTKddoJ9vcfIav7a0He4yjvU1D3jxXRyQbk5f4Wwc5/fAh4o4yXHUr6wvt7IcNFyOfN1HaXA78edTkB/VyL+uwG7EOg+/oRFv9+8HlGY3Hd/JTa8edR1pcJmtmQeRfJNwd5dRwfTHcU6J/r2e9l0K/864c+X1qkX5kXLlNXzcH3s1HGY5qK0/4COr4aMmyC3t+hDv4d/Dv4d/Dv4N/Bv4N/B/8O/v1P/A1EBgYjnf2Rzq7+wUh/1/nqkT8+XNVUrWrV4GqHG+hf1x9Z1tvTpSzuEInrGhhYibCRwZWdq7oGlcEfKvCd3R09K7os/DABX76yZ+VAd9cyl99cxl0Q6VzdMxjp7lq9utemO1ziIKdLc4SAr+q6MNK1vrPb4Y700kTW9S+/kOQPC5yUr07Ae7rWD0b6+nsHSYZ6gfNlb3C4gQus2EaRFtfIuP4p5WpSy/yE67r6Vy6/UKdf2zUwSDyOEvx1XUgeRwuc1E2zgPu6eZLA+fV+jMD59X6sKIvMa56A+3kdJ3B+PRwvcL6+nyxwso5aBNyvhxOE7MXscr5XbvzsGFw7oDTuRIGT+Z0k4DK/pWpO01OwLs7pBV5Yqd6BgdURpFs20N2xqstw7lILzu244PRimPZ2zaNfVdcjD70U6+pYZjGRbvzs6jcyhSR8ae8yp7cqCe/rHTCK60SBgV8AuapJru4wc2Zp6J1leCPLsGZgRWT56t4LImt7UM5BFNPKwPCu/v7efqSxMjAc1tPTtaJ3cKXOw+CqBQ7ZrexZYeE1BfgF/SsHGT7LwYWKl6Acs6kc54WFdKIsDBPleTrKc7hpr/ovtzkCv76GO1iNhuU1UNPOaqpCHqvFgrdW6S2HzdGkzmIt/QZrTavUVs9VY7b6szlDS79Be6iqCveA51xob3HRdDjiEElvim9xafmd0/dR+iVF05t4DhBH1iNTwyEAIR79xGOcdNIbdjIro4/zw7q86UxiczQXR+5OTwOAh9XwKJyqSr+3oCKaVTae2RzP6Og9R3ciuLUIeCQZHx/JjRqZZ0Gvg0KvrUrvCwcKLQHt7aiPS9kWL+jtXxW0t5CBsX2gynv72BY9XGdvD4xrbZfDV1v8mt7+rkgHtaEaAVtK7WYW2du6sJVA2hq9s531kE7zpnQ68M6ENaTyuawiOPKYyCRycUY=
*/