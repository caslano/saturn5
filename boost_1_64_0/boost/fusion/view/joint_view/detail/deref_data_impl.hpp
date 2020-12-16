/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
Q8eW59il/4iFrtIzhUl5/jytPPrv463qybnxuLe+NWmjk1ie6fiNfoW3e69fcL9Jm3CAqmf2oMpWBy/3DD1YXjW7KrjH+NEqvVZaIE/Obvcs5rW13Qm6Iwi/qI9qumYVDJ209wBc91Z7/dcH3Z52LbbpJ+cw/TWYbv6r09cp/tgMphv8on37/neTbylq/455OABVFv4c9815NB2bzqAcazvePd8qb6dKp+W16ZfPN8qL6bS8di63cn5q3tDmSJtuM+o1+Fj7ldb1HcK6v1aO/oa2JSDjPucP1R5mzfr2B+v9axFdrOdODwEZVLuMccN5lZ4n4RSpIuG9l4dBnV8x6yglzuUn8RS+3cIMqx2MujLG57LGfm9WYy8fDH7Cs599+RT8gsgOjz05yeM3cwflsdFv5vH+ecyjDW7ngf67G0ecPJx6Pt3GbTiKcl0ASgNbBuKgzTFuiytvr2fusGLMFk1zxqj1MV7Q6VPHKJ7ZsPlaD2H+5qarf7N37XFWD1F8fr97972r7SlECUnE6mWF2vSQVJaWQmz7uFtXd/dee+/WhliEEPJKCCHJOySvEOWd5F2eeSUUIe9HzsycOXfm7m7ljxn/2E/t3Tvf+c2ZOb8zM2fOnDmTRumn6+nj0jE9YeaPZVA6yf+0opT+QulN95fzi8z+oqWb/YXSjfob+c36U7pZf0pvXP9uqr16fxH9xJzq9LyZDzTOS29MBNRM7nkVyzm8dJI5L9L42kB4ypwIXYzmYSNPU/OItidEeRvNHTRex4w8xnxRq+r9Z0zkiYcm4HwLLQQyZapOc1E3gUGgNIH2SZic0YacCOm2D1/kxeUhmIKAZ+C9M1ksJPQ5OVPmo/ZRxlDNpDAENOWLE73cHRrlj8JqJpzA1XWNytdG5lMuNCpXFVqKiXc7y3yherAvJczCSCfrBHnU+inBcdBDyJ9Hx0pBtYKRUWZpLA9l25CHssbywFLloax5eUikykPZdshDWRPy0I5ijvE8yBOY+2l/UKSbzSXfv+M4NlIZuUtC5TDeKj20BNcSQreM8pmoNCatxDL4DV9IlB5VetTQohN1P8P9kMfI14SSnZmG/tm0RMShT/VT7ZH0SSaFMBbJ53X5hEqBF8qUoqJRA4bCsmbLSMXXUeL5/nuWliqNinuBRiupGUXFgwcU9+GLId4U+nIMpYp2qfIWNi4PxP7fl8dt8Hw+mSDGs3Bc4wW/t1j04i6QJ68/zDUij7yrERe1ZQlN5vfHfEWN89EL17KzHkh7zNbL1ask9KGCfkrjKy09ki9Y+HKO9yewV7Tg9JlkCgQVCFfXVZOcxCeEqxJM2Q+3dwzPa1m3nWM413V69SMb0ki1RB3Vp5fA+iSxQUePovVr88/hHiLwSI2+/NIwoX/tC+2EjLCUhTyoj5Hw4nr30P5U5qjBYvMVCzbKpWJFufvwZ7DgIdr5nrDfrOAeOgnueu3UFXBIj3Tr1qm0FMyZfXrt05UD+/Sjcop8VQ4J7L8qp5vSa6icpocCoafReVmet9l+2rev2aNJT1srnhNRlmNi/0WM/Ek9rWsax8NxKAc8hLl4RqZgxB6xhi4tL4vrcSH3TOf5jbGN2nOmwLa6xiYbZGEGz7vtdWgP9e5E/u1a6xKN9pn8mW2uLSn/NJF/m2tLyr9J5N/mej0Zay6b8je/lla83HbepA6kzofSM41tEXSGM4fn2eZ8QXJXkMvzb7+9pa9aH+Rt/3N7ytUA8WnsDvRsc/YXstN+QHmbtK3QGqK+Bc+HzSR55i+FpxvDOj2zAjGRKOTK1GUEzXiirrwUxDBVs9HyNzSX36wx2ZRnbl9+TQIY2WDGNfNsY6lnCfVMbJvP0Lox0cc=
*/