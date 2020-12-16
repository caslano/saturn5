//  Boost version.hpp configuration header file  ------------------------------//

//  (C) Copyright John maddock 1999. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/config for documentation

#ifndef BOOST_VERSION_HPP
#define BOOST_VERSION_HPP

//
//  Caution: this is the only Boost header that is guaranteed
//  to change with every Boost release. Including this header
//  will cause a recompile every time a new Boost version is
//  used.
//
//  BOOST_VERSION % 100 is the patch level
//  BOOST_VERSION / 100 % 1000 is the minor version
//  BOOST_VERSION / 100000 is the major version

#define BOOST_VERSION 107300

//
//  BOOST_LIB_VERSION must be defined to be the same as BOOST_VERSION
//  but as a *string* in the form "x_y[_z]" where x is the major version
//  number, y is the minor version number, and z is the patch level if not 0.
//  This is used by <config/auto_link.hpp> to select which library version to link to.

#define BOOST_LIB_VERSION "1_73"

#endif

/* version.hpp
AZVmMmbbTa+ZbAjY/xpUikHpG/KpMzB1DzP/H6F7P/NrYjb2luJeg5WC+4dHsv8iJPwlNL4FcX55aYZSWsD8P6dCnOD/C8D/Y6IX/H+E+f/fMP8/l/l/LJWkx+pn+WRHoqUO7k24crhFcM/DPQZ3P1zezkTLxXAK3DlwZ8D9DO44OBfczbug24AbCafCXbALaeDS4FLgzsUk+Uu4NLg+cEfBOeD2NCVatjf9xP//L/7a2POsukSYWmmX2WF759V6shWDnYzw3OWwwTvFiR8Weq8bxrBrw5vsXnedUFMr7grna9DnbSTmw72W88Uh0ylu/JA8ZC+x4GekdyD9KRFLhAIweyKBotWsrVfcq2ZuzsNPCyNvMCFk7wZDNaQNDrXrz4MVE1O+PH3+BwQAGGlUOQdfXm0oace1o9fqqJoKctfaAG2ZrLNM1lmGOqnKMgApYYwBsUy0SNqcc7PCaBa1qipcbycYCQ8aAu3ucmizgwnB4fb9slQ6sB/6y3g1cZS5uYLdhOi8HrlifzW1GDziWh9dZvweGVDMuiOOtEA3FSihSc2QZEzwa9eSytZn9WFrYfHBZ1d4B8HGE8Qvyp0GvhS515DeeFNC7kswbSh2OUs38A2m06Af/8qGORRWFGeuHM/2Ezlazf6bUHhYiQy9UvsmFJiE84M5XiyLHv3xMWxA4ZEGFF5q4EEwosgKfAUN+RCy79wLvTgdhwgNdQRWxlpP7BXWEw9ZyXpiJWmsk+McXWQ9QSgAaoEqYMnAxQOjW+LiR+LBV5pnkaO11CdLgC9OZFGgDUAKmw87RYTK/Aqy4isBoYn1BayN9YHwipvBQ02w+0PFtL8ZkQDwJyAkFR+J6LF8wXEJ0htmFcyYPzhVpU9hobGJvMKCRyevYcJTTyY8dUx+0w3yk0Y8xYY9BiHk7Bytiu0xIORGKZBxd2yS4dm3SYZXPymdTDI8Wp5Xcb/ph2kDTDKoWVqYGuTVtpaC9fuqpQkLIxM7aWGd0b5pBhPeRazJnAorpGK23qFzHWyQgVawtQVawa2jlgFa3ub9YHNqZXOkbGAtoSWYVxzM85Jxa96pZJ3hgYEQ6AYNehtk7nOvgHEGDIYCEWGa8fe9TYaZ0IA4x8E1zYAdSjFwRtTiLU0V3JpSmggPE90wkN8KJrovQHTXxflKb7Eh1I5QJrptKfiKR2gCzdkFLUQNVzH/9NbeREsYbiHcc3CPw90PVwJ3J9yzVoflMbh5cPfAzYK7A+5muHFWx0/8Txf8Wt3v7dUusdMlGFo3nnvg3664w8yDeN1VzH3USjNKdzkv02tB2kjrdVcz9xGW3EeVXNqN9A6kl5xALXMfVci0VqcMzHzUKeBjao73hvpatAqf+z0/7rWYj9NTCGO53ZhutAHLtnu1OK+7xu+GmrQapFiNwmGu3z2w6UJc7n5kYPOFijbvHgsJdtzzfmux0TGkMhWQIYHi7vVb8XUkvjjezvGyALr1iUMxhYpi4zi0XoSCC8qkvwn0F3UkEkDDk73u98ACOXzuGgFRBWCTufFisYArjuHqdY9RDsebUDC0shmyPgl7Z6FtB65eDJYLuGKICDaAg2okOLJ1Uag6X1tnoW8Hqr4CWyn7ha1DD9fQNAJreKrXXaGEq6AtAtfpd1dJWLLMcpm2AJEJh1l+FIayNjC0gZV7Npa+iDIZqkQJVQJja4DAVnoLbAFNaH5bmid4OoOJtuMCcDEEnab5MxmsDK8A63CB6jyBrUGHG7YEWJ4uxRaBhNB9QzVU9TLJ+xXMtuZ8KuCSAIm6Di5cHWNrJGMrt0ux1TFUV4hOHBOlLSw9AE1CY9bVweoTra/N3MYQ7Pcsfw2DlS+xdZjMpsM=
*/