///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_DETAIL_REBIND_HPP
#define BOOST_MP_DETAIL_REBIND_HPP

namespace boost { namespace multiprecision { namespace backends { namespace detail {
template <class value_type, class my_allocator>
struct rebind
{
#ifndef BOOST_NO_CXX11_ALLOCATOR
   typedef typename std::allocator_traits<my_allocator>::template rebind_alloc<value_type> type;
#else
   typedef typename my_allocator::template rebind<value_type>::other type;
#endif
};
}}}} // namespace boost::multiprecision::backends::detail

#endif // BOOST_MP_DETAIL_REBIND_HPP

/* rebind.hpp
HXLnOGpUYG4j19JVpIs7e48iu12dbeGp0pVqf+Yn8kmK+XLNrLfUob5tMYAvsN3lFcV2P9ZlwXhkPeHVZUkjq05OW998pVrfP5jFkP/+wLlYpmQQbHP/QmXQW8jPEeegrLXJa/Kw72N4g+5l67C0LDHjaaM8juW7ahqDFI/lKFIwgSHfgP/QvwRyktDRBo0ZlblccOWbBzJ8pzF0D8kT9cW5pYVdfWKb2RHf6OUz4TKaImwin6+phC6PThZ76EqLg90hG+L5hxQKM2t7WtHQVk962JEB5mtguD+F1rKwXDDwLOg+2Huc9vp7kQuqbZCkQn74+GA94A/BXprh+NN1/EppBILbv4fr+C02xKjPwkrlNX6zXOKtVmMcA4wN4z/YUESQGHQei388A/wG1515qXmOuT58f6k2z1FtIAHG3nDHhvvVC1VykRxBT4Me7tjYcKcimIw5SWIBqPYtQH1paqdncrzfWGakkU5isFmCCPDLfUOv/x7hY8ohGrL/8TpvrMC8bnJsg5O0K9Sq7kiVp1upr0BuTI7tV0oSPHLhyf7VxVndStr38MXBw+bIPMFRsAXEeJ5prj3tbQHPptspCzkx+WAHHDJlIQXsO7y90B9tOr6G8VIuyhrm4BjV8duFcTq0f2BW8VDY4Dtc0djJVQUeYy38CGPykllyvflbpTja8v6MD/s9V5E7n0aOYEzUcfw1xosyeOssnJTWFDv/6D9xPBczp9JFGwaO2zcRxTXHfw7tSiUVnPX2XkAS9r1nisF2i+XIUuwp3hZy/eYO/l0C97+mViTK05hXUfM4zycucGwQxROXogw0by9CVN6rd9inx1N47vVb370B37Snpew85CocrFiripw438ecTTY5W404b1XEeSzbATPXQSQNyuk42rVKiK80cE48Fi+1GUhvbSCN6vDToQ4leudcTLPcn2veAuJID7oqBVds1KO/P8zZTvdPg64IiZfIGHAfrdaqLpvOnUg3EpGDsCnKjXMXe/8TyIkpMT63znPu9Yz31dolF3JiyuFdILGYIkXzeLLVG3Xfj3Q5sdznHIoceXcG6AzuWZBuaImNvI05zebzSLvr7ys5y1cSPfNm5N0ZpXOwr5QolrfSKVtqm78VO/jcKv8OvJ0P7RsFK94E1L+DHTIHWy2kK4kMzlualhkedvfvX5w9ahfCa9hO9xcDbqLKGEdRvyLr5I7fb3vd9ygRIrd24cQw5/fnAUdGkwRFeWDBRnnE+QdqR0cVszHkZk02x/nXgKOKUDmreS7ijg+caxXOfRFqH1hJalb3i2Og1MW7vqEwlrMy22AT5oTmJJ/WwJtqfCPxwbM6wC4PPnvMl4EaLyvmOB6FGvd9qpUSHvND85DDOaPXTYRpFUvgscbTOKlX9af9uQn2mfsKj38TgvQ2R8wRzT8Otl5qyIsTTSk0k9NVjJLpIAT5jQesELjOPBTMDc01aM8fDe0pY1aZu0Ae13P03CeSQpy1oT0Z88xaMeRFxvMO3qYHTKZoZsIbcllz0c4xyaT3lwGT5/ao1C0p2Dgc3hz+qdC7Is3SceWXDC9OcVs+Qw9jM7cVRRvMa/N8e2mvuyNLpIIx1Vbr/ck2Ywts9gccm2yILNFZbugN68d2r3tHSBeLSr7iRMpXj3aA8/4BR/pCvaQR88FzDeL497qpPUdmakufFmidIwLsegc85YI1PgTMC88zyM2hcd6Q2uxeLyO9ffGqqpwPNq9f13jcL47GyijMDc8xyLWBdBUxLW27L5ZM4RA+VK8xlwa+O7zsz+yXfzpgcyZDLlxjnmjOEYiLoPF3vat1pkYC0UcPz+oLyPEsD8OfUPvYwCKnUi3ULhc3NUsNuPM=
*/