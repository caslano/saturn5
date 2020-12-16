/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07202005_0900)
#define FUSION_VALUE_OF_IMPL_07202005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<
                        typename result_of::prior<
                            typename Iterator::first_type
                        >::type
                    >::type
                type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
jNgatB4/l/ALs2U1Q3Nm1T7U7kvzp2GQTd3c2dT7C2nEOfXqFtAwu0HdfGhqueiM6nEeDQtrmMukbkE0tVwcZvU4v4bZLBrzh6bWH1g15k/DQhrmzK4xf2hqudhzaMyfhulyasyfhoXRujCb4e69kmrPpW5htJHMlqUoPYfG2qYep8utbl4N0+VR78+PphZnz6tufg2z59OIQ1PLxZlfPS6oYc5vNOI0zPmtRpyGOQtoxBVQr88dr7EmNMxdUCOuoMZaStBYE4U01pKG6QprxKGp5WJP1FgTGmYvohGnYXa7RhzaQGah7Wv/S3NbVN3CGuYtJvdLP6PR/V00KG6mZ4nXoqVep3QQFkIzxEn79dxByhMqmaFRrLSE2DI/U31V0YBMXk+j+dBykyU710AzMuPnNmGNOFs1PD8jS3Y+jxbPjJ8z+NACEVuH1qxPra00ZtXN8IZZrydDrgkL1DDDoZTSWp8aVYXyrGeG1DHSsvcLZBfmaWiG/oq0/fr272huG+GYMWvzXF7HQRMz/MzaXHZoVg6Ka2YGawppZQsUW0X9tTbDepAWvjppDY1LGzPsYJal3xPZZlszpE0rLcXz/vmFhb43w3YWd7px9W40Lj3MUDFWWrXmdVLS3PbB+lgcXxOOvmaowuL6WG+3ozwHmKGeIu1ZuonThcEgM2zgc/T6h9SUJ9q7iK1Hu2duVkSYbYg8bm5Ifj6hYTBU3dwaFkLrwoxv765hZhjCrP3L4jQuMByvH5jVWV9SEeZDU2vTNkLdfGhq/TlGqvcXGqlRwygzTFOkHRt9rZUw5xgzzGVxRZt/7CpM58F9Voy0ElWVX4XZx5nhGotrV7DkPMpzvBmGM7tSOX8M5alhnglmGMqsdr+DXWjMJqpbAE3sIzeird6qb0/jOSnaGuzZkUT9TTZDQ0XauVL9f6D6pmIcs3ltZ5WgMZuO4xLLrOmvvwjze82wG6St+XwsHeXyoxkeMguldI+nGmbj9s7sfsHRT6jNOWa4wKzox2eRffme2MBcM30uuknZE9s9dl0/YeF5Zkhk9maeZ5cw+3wzlGaW7sHtl8I8aGJb2YwmtxVsU8NcC3ANMqM1iBbSMNdC2eaWZG0GNcyxCNtkxtsMaJhjsZm+K7sV7cWQTjeFeZeaoRBI27x8yW3KBS0vs4fWEx5hsMwMRZi9+KZaauoP7RtmzpKTRwtzo22PkWb/Plyf+vOZIU2stAmFJy4S5ltthhEgbdzSixmpvzVYA6uv6LUDmWhcfsbtlpmt2thpwnTrzbAPpJWtlqgIgw1myJhCWo2UFz4Js201wxzW5t/jahvItplBYdaxztF1VPt2M+RgtU+ZXOoWxe00Q3dmD5/1aC3MvscMLmbrh77+jezXyP4sYrnn3LgiLIxWh9VwY2iLrMKch81wlsWN7dVgDNlvuB0x49uRF60oM3rnA1oQrTOzhTs77aM2j+C8M3u5/O/XVMNRM9gVaWlS+m3C/MfMUJ/FFSvxfgXN33EzrGY2ssa2MsJCaC7WZmJ9wy/CfCfN9DmlH40+n0YLo+VTpN2fn7MAbbenzdCMxcUOr32FakfLyuK6bf03H9V31gyxMdLyTosvLSxwzgxukPb+SCM9jdl5XBPMhrX9/JbqQ5vMrF7VKf1ojoJmiIvYNjT5rB/WrmF+DQtoWFDDQhoWRotnRs8Iotkv4H1hZvSMIJoLTS3OpxEXvKCRp0abtovqbTrR1OK8FzXmQaPNIFpFZvTsHZrtkrq5NSygYbrLZigujT1HhvVpmFfDghqmu2KGTBHbjkbvNkezo7Vi5hgxdCaNWTJbktikIbV5Ndq+JP4aI8yTzIZdukX7z3AyG/lgze+0zq4=
*/