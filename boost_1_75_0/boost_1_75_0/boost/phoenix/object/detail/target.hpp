/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_CAST_TARGET_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_CAST_TARGET_HPP

namespace boost { namespace phoenix
{
    namespace detail
    {
        template <typename T>
        struct target
        {
            typedef T type;
        };

        namespace result_of
        {
            template <typename T>
            struct target
            {
                typedef
                    typename proto::detail::uncvref<
                        typename proto::result_of::value<T>::type
                    >::type
                    target_type;
                typedef typename target_type::type type;
            };

            template <typename T>
            struct target<T const&>
                : target<T>
            {};

            template <typename T>
            struct target<T&>
                : target<T>
            {};
        }
    }
}}

#endif

/* target.hpp
p1lwDLdZrL2Zpt1x3ARrPSPMGrpxSwtPU5PgF47ZCfEFGenelmb5iaGANVBdEZd1t8Ea9j4yhCXsLhjATVh3R1jDhjjcjLpQtCkxWT3rHOvmRD+oBHH5sllj6+Zg7Y2s242oszGyNWeinsa2blvY+A4mmyNU95OepPmwTFufYd0Si+QfwC1wf4ZYw2QMb4gNQjYYeQHWWfFxBdCuzQHrqrx4jLsmP0FQkEioMAkpGai2CCuFUHEqlnjfk+x4pteVZoBBd31ZVj3qhhCCl/qFm9I3VObi3cgbya3IiRanWH8Tre3CCzbJniaBG/evX4v3rxFrrACoRJawgRPE4TGVt1P+XJS/AegeqN6CXHqUG9kWd6b6YsSgm+7M6fNRGRMbWBOWuJb3ktshStwQry3Wj+2fGwG4AXY2+PIWXmaIdVwcqodbMFgXJHJircMqSaMJ2G96m6wz6YixaJTzKcp4dXZ3sk4ObEkOIhUIlcRSADB50skHiMI3fWgWR0/XieI5w7rJPI1kTeKmZrME2TCmJgaaMaYjsqorLNaS7FpyngZYm2s8ttczRqxtiYoKyTo/HYyvLfOTIGtg0cAbN5RmkA2OTEJE9pWF1SRKvWBEbizPJojT3DgK2TlN1KUiqmkb5jA2PSN3KMXlMpB+Ix9OsaaF7A76cMyXJQZrFM0Jk/cX+fZ4WvhmZGueokZJlBszcNNYhzvQZp6TQ7Bg
*/