/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BOOST_TUPLE_09242011_1744)
#define BOOST_FUSION_BOOST_TUPLE_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/detail/is_view_impl.hpp>
#include <boost/fusion/adapted/std_tuple/detail/is_sequence_impl.hpp>
#include <boost/fusion/adapted/std_tuple/detail/category_of_impl.hpp>
#include <boost/fusion/adapted/std_tuple/detail/begin_impl.hpp>
#include <boost/fusion/adapted/std_tuple/detail/end_impl.hpp>
#include <boost/fusion/adapted/std_tuple/detail/size_impl.hpp>
#include <boost/fusion/adapted/std_tuple/detail/at_impl.hpp>
#include <boost/fusion/adapted/std_tuple/detail/value_at_impl.hpp>
#include <boost/fusion/adapted/std_tuple/detail/convert_impl.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>
#include <boost/fusion/adapted/std_tuple/tag_of.hpp>
#include <boost/fusion/adapted/std_tuple/mpl/clear.hpp>

#endif

/* std_tuple.hpp
uIDnCAmIG5IjB0qgNtpjMP7ESmzHOdzCM6gPYqOvkRNV0AFDMRtbcBkqIe1ANlREe4zAQmzHf3iNRIkYUxRDPfTGVGzEJbxB0g9jo8yohHYYjkXYj4t4jvgf0RekQDYURU10wEBMwFysxm6cxE28RqLE5B0yIhcqoA5aozv6YxxWYR9O4DbeIVES8gPZUB6N0R3jsAjbcQxX8Rj+Y65HDlRFO4zGMmzFIVzFCyRMGhslQwaUwW/ojhGYgTXYg//wGok+IZbIjTKoiw7oj7FYhgO4gpf48FPGDCmQDeXQAJ3QG6MxB1txCW/x6WdcizJoisFYiv04hWt4DvM5cUNy5EAZ1EZ7DMJ0LMMuXMB9vIT7gjYhDQqiGjpgOKZiKTbjCC7iNp7D80CP75EJpdAA3TEC87EGh3ED7xDvf8Qc2VEWDdAZwzEbG3EEdxD/K/qBvKiIJvgd47AMx3ANTxHna3ID2VEGVVEPzdARfTAB87EBB3ERD/AOCb6h/0iOHCiGamiDPpiIRdiMY7gB8S1jjRTIjqKoghbojUlYhq04gat4BJ0sNvoCsciLyqiH7hiJ2ViHY7iB94jzHXmNlMiKkqiOpuiJkZiHDTiIC3gI9T19wxdIgZwohZpoiwEYi3lYg704i4ewP3AfYpEb5dEQXTEMc7AFx3EdT+F/ZEyQEtlQDL+iKXpgBKbjb+zGeTyA/ok8wldIhRwojEpogu4YgkmYjVXYjYt4hPjJyW+kR1HURgt0xWgsxDZcwmuEFKwrSIlsKIkm6Ir+GItZ+Bs7cRrX8RIJUlIfkAFFUR2t8DtGYQ5WYwcO4Rzu4D2SpOI7kQkFUR410QLdMQLTsRK7cQr/4gGiWGoHvkI65EYJ1EAL9MBIzMEK7MZpXMMLhNTsQ5AcmZAfZVANrTAAk7EYG3AAZ3AX75EkDbmOHCiFOmiHgZiBNdiPC7iDN0iUlnxHTpRHPXRAX4zCImzAEdzEW4R0xBKZUAL10BHDMAlLsBWHcAGPIH+mbuM7ZEIJ1EZr9MJozMFybMZBXMZj6PSMC1IhG0qgOpqjO0ZjPjbjCK7iBeJmoOYgPYqhPjpiEMZjIdbhEC7iPqKMtBPJkBEFUQlN0ROjMBcrsQ2H8S/u4A0+yMTYIB1yoyiqoil6YwyWYTNO4DreInFm7kNmFEAtdMEoLMBOXMYrJMkSG6VFLhRHbbREH0zHcmzAfpzFLbxFgqzUC6RGAVRBY/TAKMzFWuzBedzHG9hszBN8gwwojtpoii4YiDGYjRXYhVO4g/eIzwuOPsb3yIgi+AUN0Q69MRqzsRK7cR638R4JcrCfRyxyoRRqoik6oR9GYg7WYi/O4goeQOdk74m0yItKaIgu+ANTsQSrsA0ncQPvkCgXcUEGRLyJXkYq0pGJbOQiz8kkJooTxY3iRfGjBNEHUcIoUfRh9BEvoEsSfRwljT7hsfqfRZ9HX0Rf8tDhr6Kvo2+ib6NknGa+j36IfuTFPcmjFFHKKFVEVKI0UdooHQ/aTh9liDJGmXj1VpYoa5Qtys6DfXNGuTj/5OEV1/mi/FGBqCAv8y4cFYmKRsV4TVuJqGRUKiodlYnKRuWi8pySfokqRpWiylGVqGr0a1Qtqh7V4NHttaLaUZ2oLieo+lGDqGHUKPotahw1iZpGzaLmUYuoJeeq1lGbqG3ULmofdYg6Rp2izlGXqGvULeoe9Yh6Rr2i3lGf6Peob9Qv6s8JbGA0KBoc/RENiYZGw6Lh0YhoZDQqGh2N4WQ2LhofTYgmRpOiydGUaGo0Lfozmh7NiGZGs6LZ0ZxobjQvmh8t4Py2KFocLYmWRn9Fy6Ll0d/RimhltCr6J1odrYnWRuui9dE=
*/