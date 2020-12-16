
//  chrono_io
//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2010-2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o under lvm/libc++  to Boost

#ifndef BOOST_CHRONO_CHRONO_IO_HPP
#define BOOST_CHRONO_CHRONO_IO_HPP

#include <boost/chrono/config.hpp>

//#if BOOST_CHRONO_VERSION == 2
//#include <boost/chrono/io/time_point_io.hpp>
//#include <boost/chrono/io/duration_io.hpp>
//#elif BOOST_CHRONO_VERSION == 1
//#include <boost/chrono/io_v1/chrono_io.hpp>
//#endif

#if defined BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0
#include <boost/chrono/io/time_point_io.hpp>
#include <boost/chrono/io/duration_io.hpp>
#else
#include <boost/chrono/io_v1/chrono_io.hpp>
#endif

#include <boost/chrono/io/utility/to_string.hpp>

#endif  // BOOST_CHRONO_CHRONO_IO_HPP

/* chrono_io.hpp
beQsGrJ5zrF5Nr/PMT5bHQOGZvN9syyb92ebs/k5x9XZfAwoyub3ul/O1tsZtNnO97ofyDbudf8WstnOXsjm5xx/yFbb2V+z+TnHe3J4ztrm8DGgYQ4fAzrl8DFgcY6Rsy+ynceA4TlGO1sK2cxZ4xzen4XnqDkbkMPb2dM5fN/clsPHgLU5fAzYRfo09d7QHOO6k1+O8xjwnImzTyGb150ecMLZuRz1utMTOXwMGJDLc+ady99v1svl7zfb5/J73RfkGu3MNdf5XvdBuUbOAnMt7CyXv3danKu2sz65fAx4PNfJHuRcPgbk5vIxYHMuv9f9dK5xr/vMXOd73Z8xcfYZZPNe9/xcPgb8PVe91/1ALt83W+fxe92rkn6BOm7m8Xvda+fxe91n5Rnt7L1c53vdu+QZ97rPg2y2s3Z5/P2mf57azjrm8Xvd9+bxdrY+j++bGXl839yYx/uzk3nGuaDJec7nth/LM9rZ3yCb54Ky8nh/9mGeei6oJI/vm23u5zlzh57jzAV6LgY0gZ7zZ+Oh1687XaPyzkSJ1Zx1Qh79nOMsyOa97jVwjrvfnAa9aq97X+i4fY47nXB2P/ScP0uCnvNnq6Dn5mmPQ6/vm5NIjtemMpyVIY3ezk5BNvfN5TjH+bP3oVf1zSLoOH/WKp/nrHo+b2c/4frqvgnM5zkbRfpBkrOj9zvvmx3yTXuQIZvXnX6538ke5Hz1ulPzfL5vFubze90L8p08i5jPrzutyef3ur+Wb1oPENfj3ldZbOLsTchmO3s0n48Bx6FX2lk+Pz5rVsCPzzTSj1dydiWfv0evSvkzlJwNLTDGgCPCLrn7zdYFRs5GQDbHgB/y+b45pkAdAxqLMinfWVzAzzlmFPDvvokq4J/hzy3g19FfLjCuBwSRPA8lVs85FlKa5hX3h5DN7z1IFJyoOHuD9Hdbcra94Pa+H/KvvBPP8a26mGiN/lzFBV1wHPLCu8we1L8TLzQcny5TfWtLpHXFVYfTN/Qsv7llSlfPkC5ApvM1pWtiSBcm000ypfM2pusOkc53ALprI+pPRHr8W+SxGb/pJdJ216XtXpHWKf/u4tuB5u+31LP4fovuG4LynLc8FybPdag4191xrrvp2y/6dvwgSaO/cDRgHaC/+G7aFX078t9ME2mbyW+a1Npgl1+3ye+hPUxzdJbtOwbpq1P6CS6ivcX1mhi5FukbA6tQ+umUPlikt/x2mtT5ym8gDaG8LfENpDRbuW26pd8Yj3wulG6ui5VfmAB9M9L31ekD/aOiEjUP0cdv0e/6uRRrDWyDXdzku/522PPh3AwtSPbln+lckPE7SYKLYRusvqkm3olHuprSV42EzH1TbS7pm8j+EkNyTys/RdefCr3+3Z0JJLcx+KnxG/hvH6WIPFZ+atIGq+9DifvqDRbf1xLcXoZO/6zQZpLvVb478GlRb3mvQ/IUpX8uF/V28PQ3knsZ3hu4C+cs5wNFmT4kfQfL9wbuZ+pd5SHar2NZ7zHQ6eOGDbJVe7uLa/1Kv9MDM+zusu7dKE87Zd3rQq+vey/xG/q6V6dzbsq69yN9W8u61ybdnZa2PlXUz8rWS6DTr9PNgez4ptpYXb9uqCXaDtsmqr9nRPk8K74lRLJ6XmCR0MtnnkgehN+FrPvdjtpC2w7bQgNPIZS2tpKnDaTvr/JNlvzFivJYfVPt3EMWvkLUsyf54EayX14S7er4FtpZklORd556bypdw1P+3k1r7iTXP0Gvf/+7F+XvLL7jJn8T1jbd4FO+e4j3Kd50nTuFTzWU3dLPXPvN5m4rHjexiMfeFvG4g8X31LorvqfWNkvswXXD3BZwNfBJXE/b6Iix0ZFRiu8=
*/