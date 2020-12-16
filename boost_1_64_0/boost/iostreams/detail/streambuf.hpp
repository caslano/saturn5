// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# include <streambuf>
#else 
# include <streambuf.h>
#endif 

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# define BOOST_IOSTREAMS_BASIC_STREAMBUF(ch, tr) std::basic_streambuf< ch, tr >
# define BOOST_IOSTREAMS_PUBSYNC pubsync
# define BOOST_IOSTREAMS_PUBSEEKOFF pubseekoff
# define BOOST_IOSTREAMS_PUBSEEKPOS pubseekpos
#else
# define BOOST_IOSTREAMS_BASIC_STREAMBUF(ch, tr) std::streambuf
# define BOOST_IOSTREAMS_PUBSYNC sync
# define BOOST_IOSTREAMS_PUBSEEKOFF seekoff
# define BOOST_IOSTREAMS_PUBSEEKPOS seekpos
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED

/* streambuf.hpp
H2ESRgasVDqZxnUC+PfYtVHR0d9136HONzPYpPBcO0H8yrUD/l9QOulGOxVu/+2dxDj+K2eUBfy3hLcrnVHEQKWPo0Sn62517mT97Wz8c3V/3mXy66fq/BirtcsWxhrDWIgvzBoIJ8KtpDyygr5FLXksuj5tp4f4i24aJE9wkzzx2JsaL9+xc07YyAwnjK7ky6Gg+oHnPlzMXz/26vLxpzELdlb6F7FnL85UPwjPUz9c8cmSfGqldKZayfx/GmKqJ+5wylTciZaUVeAb7mcpnd7oJ7jLS5flRep8Vx0Xy52PUt9PVDr5aMU3WGZpYcpsr6ccpMzClsMy+WDBh1IO+6Qc1oWWw+zKyYNCyiFLyuE+pf+6NZPQF4Upi3UNlEWOlMUdSme3KotFyLWOPklM1v5vpC9pGmzPr4GyyZK20vIzdPCZZrWgjHN0mDnKvYIQW7jLTJfpQyrsq+nD5lgdHTd+bVZuW6wepLKAcpqFzMH3BqQ+jGlWlvQBW5X+bXStfRmn6sbVcdfhPEdu9cLG00nsD80z1Q1tg+pBpb/VmkpuzkWyrHEqj+/P9teRB+D92ceurtTK98UW2YQB50OnT9/6WXBdoZ6oTt3Tp+v2tkPpd7FXU1t8doJuy1d+7rjfSp52MtUfrtNwX58N31M6rbgW5RvwQ4xfYRfzYLuDDk/ONdj3n/ov53yKqe/H7+H7/l7KfwtT34//sH2/tgE2X/LDxw7mUquHuNuST5tx7WZdwxfBm+swyovVejWp89OU3t/RuEPcAn6ncWc/V7WBL7766qvLlNt260dWjoqP30wuxdi3T9HU8vr7aB+ll6n7s3vU7ySVvk8IJ6j9SFnPVTq342eVlSPpSlRune1yyv8dSuLfVmupG4H4PenUAXykh02zu51lSH6foHTepAf+ub/t8StNub1B/RlqjaVHkXYv4W1R1/HcP3WfFq90RmCZ4Sza5q3EH3cd5ieEmMCZa61tVhMV7iHyoEid+wDXHBXubBXu1BLLVS73KZ0++PJ5yuUOymWRy1/pLFUfJL/XKp0yqxXpP4t4Zyh3W6cFv7pPeFD6BIc10if4IugTjvY9H3dVNzqqMHSdCvrO0TKJ2DUSoeXIv5xvzaj2UzVxRtmEylmqW6EuSh9vW0z3mNeJij/bda/Cb+8B+h77rDo/nX40znivd/uvdNmyVvkNN6nzV3E3STL2DeLf1JZ0HXhd6UyiTiaFlHdzaScHlA7lLG2gzRf85i6S43qeeyj78Lb+AmVbpsqGfNNrWuUeoPNHvmETxl59ZWromt54bKMWEC+XnXHeKVhYHLSmd2KZFaas8Kvz2u7m6PJOYl7Ti27wmt4/kPZ3I7DtFryml7i40s81ceOanrQWNA9NayK6VSFpnVxmSVprM534Tw6b1qoo0lplSOt7UaSVuJCuyRGl9ZwWoWltgu464uC3GRp9ua5zpdU6TFrXGdK6N4q0msrVCpPWQWmhaW2K7mad1ujLdXMUad1sSOu+KNIq5RourcfE5qB53jucLcLo53uPlo3Ck7Y77ieOjDs/fVTSjW27j3+4ovuZdx09G4Xm+fZjb6PwWNsijHY+/2itI9jv3PsD4yAyVlSHNEcWIqqOyzx/FkyDrWFbmA07wDbwVNgVDoHHwdPh8XAc7AhL4AlwOuwEK2BnOBd2gQvEvz8+8q4PZxri0wM9G/aCzeBJMBWeDB29PJgO+8BusC/sAfvD00XvDDgQ5sNBcCIcDKfA78IZorcfbg2838o7ep30XU9KfDZKfO6R+Nwr8XkNtoCbYHt4P+wLH4YD4SPwNPgYHA2fgAXwT7AQPgWvkHCWiL8b5PeN8Bm4Dj4L74XPwUfhX+A=
*/