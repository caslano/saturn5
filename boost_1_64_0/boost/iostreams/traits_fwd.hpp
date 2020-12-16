// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Forward declarations of templates defined in traits.hpp.

#ifndef BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED
#define BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <iosfwd> // stream types, char_traits.

namespace boost { namespace iostreams {      

template<typename T>
struct is_istream;

template<typename T>
struct is_ostream;

template<typename T>
struct is_iostream;

template<typename T>
struct is_streambuf;

template<typename T>
struct is_istringstream;

template<typename T>
struct is_ostringstream;

template<typename T>
struct is_stringstream;

template<typename T>
struct is_stringbuf;

template<typename T>
struct is_ifstream;

template<typename T>
struct is_ofstream;

template<typename T>
struct is_fstream;

template<typename T>
struct is_filebuf;

template<typename T>
struct is_std_io;

template<typename T>
struct is_std_file_device;

template<typename T>
struct is_std_string_device;

template<typename T>
struct char_type_of;

template<typename T>
struct category_of;

template<typename T>
struct int_type_of;

template<typename T>
struct mode_of;

template<typename T>
struct is_device;

template<typename T>
struct is_filter;

template<typename T>
struct is_direct;

namespace detail {

template<typename T>
struct is_boost_stream;

template<typename T>
struct is_boost_stream_buffer;

template<typename T>
struct is_filtering_stream;

template<typename T>
struct is_filtering_streambuf;

template<typename T>
struct is_linked;

template<typename T>
struct is_boost;

} // End namespace detail.

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED

/* traits_fwd.hpp
jyxCNiDbm1SvV6g+qo/qo/qoPqqPX2v+f9rMn7//357/f0Rb/5/mcedb1RHrzLvudsbouG7m5Jlq8X/At02Vg3m+lbD6eN22KtjXU+N1Erc+r35C5odriz28WNiIF9FcQzoZsgtOp7v2fpHy/4PvPV+YfMNf4iDmC62bfFo+cDfarjPPze42jCNr41ufqfNZYpMtcAyuLlyqzn/re8vn1/YMTHfHjHeo87f4Ss/NcL8Ntludu0k7N8sdd/uzOrdEOzfTHdN7TZ27RjuX5Y63HVTnLvM9Qx22s9S4crCocemxMhY9RvhoINU43LcIfxvH6NrBVOSoxKX7w52wod3aa38XGeSAnJPxv3LHuxu/4oz/mXRR5lN0e2aVtElR1bGex9RY26Npx4d12pqZPWXHvquKz795fOixMPPYWaixrV9uDNE8VhhyjE/GqqRtkPZmUNA7OG6LVP3AWFgLqu90eeT+kvufcLQL5B0HZ2wrBtaDA+FpcARMgRfCRnASbAxnwiYwDzaFl8Fm8BHYBr4A28L9MBV+CTvAKA/XhI1gN9gL9oRjYC84F54Nl8N+cAXsD6+D58A74SD4KBwK98IR8BAcA/8Bx8Fksb/VFU6Co+BUmA6nw9/AWXAtzIab4Bz4CpwP98N8+B1cCBN8/MP/7eASeDZcBifAFXABvBYuh4XwZtgCboJr4DZ4E3wa3gxfhGvh6/AWuA/eCj+Gt8HP4Dr4JawPa1BfDWAstN353lS54xAyBvFvsSXC2MC/1J5I/KNVtymS2jTMGtq0+n27+qg+qo/qo/qoPv7Tjl/p/X/i3Oz2P3v9v23fr8Up9OFu8lte277fiJLVrkN4bZ44L99qzPn9ybw/Gc7PzZw9IS/PcuKgs+j4UStlnChUHA3rco3A83oUys/bdBBPOH4mjBg1asKIvuf3HTbK8dUMP81Jy6C1jp/hfQeMCPIkNgmf0GwSpnplrEDqx3Zs0Yz+9k4ZK9AzlTEv1zKsRTOOaxBeH9cYW4lv7Ve0X2CDpDVcAoUhJ4g315TW6XnG6+n7E5Iosx+SmE9U5Torhx38BAu85lCfuXwWyTX1CqN4KlU2i/4FZbPDZy6b9YZ0ksdKl80OQ9m49iz9ZcumDWVTJNcMUsIpczJL1q+1UnYrJprXFAeVzZRaFZeNswaJeCmbiQFp3Oc3l0uxOY1ksfJls2Rt6LIZFCZjhBKwJnIG6dtvvm525gLLzfPUSuRZv9bhsLL10J5rWbvkWtJgaNWg6qFd6Hog7E+vh3aGesgIN9dDijGNlGYV6mFfOTpaHF62HjqQvlTTdVU1/PR6OCb7JeqJh1OQCQ1oC0uuldFh+oSANsrZn3Nxg9D1QFh3rPRwnZI1vMZx1SC/6AJ/sbw51Ddggur3ykrk1alf0qvq1xnns9OVKOnCTa6Fm1xfb6cSosxllKuVkdZWVVg+uVUon9wqlE/ur1w+jg51q1G2fDqjr4Va+QS2HSU61LGce7mwCmVUWIUyKvwZZdSx2U8vo/HRZcuom/3c0ctIv6/lPutS3nOnCmVUVIUyKvoZZdTlZ5RRHxnETyoBfujzEV9xSRlN75BhbIuYBwpdRsVavr9TZZQzL89YRvgNyveiKuSbNATkm2vxm2sFtSUpNc15PKLlUWtLKszfkSrk78i/MH9OHfpjy+avJ/mL3+3kr0xbUGH/Kn535fMYv/un57FVs8rl8ZAhj70Im+rmMfherrjvklqFPKb+jDy2qyCPbWUPxcJ4CSyR9EVOPwUdesHdQ2FPkml7nXjfxYrcdDY9J8m+mWPK71lWFFdvYcUb8018br7Prqv2VWCqrHTfQ6LqeyYZy0EP+40qM3pS5jZN9ys=
*/