# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LOGICAL_AND_HPP
# define BOOST_PREPROCESSOR_LOGICAL_AND_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
#
# /* BOOST_PP_AND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_AND(p, q) BOOST_PP_BITAND(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_AND(p, q) BOOST_PP_AND_I(p, q)
#    define BOOST_PP_AND_I(p, q) BOOST_PP_BITAND(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* and.hpp
OjUYS6UvIrSo44IC2sbXT5vmdGeY8BV0RkiKDBTTlK08Y5l8tZsrUpJlukiftSoXG5TeMhWXRnRDvpAYNBM+uhNxFqMBApWI10u/mHDnz3cnxSa5N90UPObKH9dNcmI67qDswjpgjJPQzHW0PKtKZm5ynxzPaHnNDCYKSVRTkKkJ9/daxjT/tK307FXbPGCQkSkWwuMPTNQ0oqe2fSOnkInHJN/aPvmFd536wY0Lkol0Vud1qXw2HdugCUSbxGA0h5i0SVJhuYf7iBqXVluKYXNLp9vRsljlfJmUzBsInGA13Mn64LuAJ7H0utiGvDgxReyrG3EGR3mtCiqucwVUMl7NaEdC1sWLjPNiQxusCH4NDNDU2buMBjPqqc5FaRALSXsnzHb0gpgVkpuYME/IxXSEE09QLUlwMw+xcwdbvXT6jvVkYr3GR8fT6dRgqmBkXTOVz+ULMuIzHZ64fyH7VGgzXfHjM9eNaXOmdsVJHR7pmgHNflyaoUnx1KpJkm6odcCeJSI0szPcvnSmjzIT03ZB4sAqiM5HuKCDZbsu4llAv9hfKFLrpdVXeRkkatpcXNpxJteYkuL6yxdmphSfYvzsL2QTg0E+0kLR/rAUw6Bv9pWkdz/1SHJUFlukSLkUwDVMMG37uVgnAHYgYesnIfDawGtInRopzJKitgDXRsbY6rAZzkjjraWQgqDdru0X/T5esgM7QVwx8eqWmmmzJrO/YLxQ75qsM30jee+bBTXYK7YYXGgulR+agR/efEqe5G7nuRoG7TholDAjIn5vRLfbl6EY9Zi755sb17G+VJ/+RF6iJe6ZWQDteXiigL6ZOsraWkJiyhisSGTcpoZQvSCKUgx1rueYfkALe4piRmKTECQ6vWG+MIn2xOutdU5EcIIujQygEF3T3TrHnexFjxLWtGiRtAnaQyeCtYVFA35GGj0tAzRtRpD6wijBruF5trRakL/FRE0uPkReaB9uR11aWHwRKlVn85I85ZVIx3FR8pveQEpso/bW1e511y1e3Nzc1rZ4cVfX9Tqmi6tkmb50TWqrYUC67cmykpdLxanJNXHaPImb3LXf1EInySU6pKraZZqjjQhqDaPjDMYFL9Xn2vZ3MF5XzWVWtZtP0nLl5DbDyWp3rfknmTbJPE/Cso2343gTCKcjR9RJO55Vjyoc1tMiYRvtyVQfPPFGrlN0Xi3tvuapkQxN3enbijldyBC3X45b+G8qusYtG/IlNeCmtFOg1cltyDJBs3MybjYe8sj6R3pARvE6LuZOpmsi6RouzqpzBCLTn8LxuOrjtrqh/ZO2AXhDMMy0zJbTyZov1yYTOW3wEFX3Qp2YSPDIoD8i58nY8BK+TLZgwhej5dBaRJ2iLEhNHapfa5p9CghdDn2v17dRRdVPv7Etmzcy75RhjyPy1H8iucaVgGsvxTw8QYlfm2heYswlWjXMi/FSXBRt/EvISEvVnhvxuBq3LG5Y1E4cE2ktYsaG9gGyInaVBsdWMJmDUhbzqURvkpm6Y9QyENKAanDEkST1kBJBi4170hQxPJYlQ6qt6YS0/OOBVoVmLkiw5qS+D5Ew4pGUiXgxoXJJypPaaUNxIWFk6eRJfwrbUPxCkjq+IWfzUj5osbXHNms01bZcaGS8hpO8zfdqNrdiS5rNQowWj4SRcuna6SUCWNJHLQ/ZNTGCU26HBHZJIWuHRVAqqZZedKWBTMuQRdthFvgya1B16t2W+MmrSE5/GCNlV7sxGZ/H4wj1yNNkClaN2qcnZgLlEjPpRvsosud1KLwI22LVdtwUtGautpnY87sPta72tW1p8laZtEyoqamOy2ZNf+nama7vjaYwRdGMg6gx+NvF2mo=
*/