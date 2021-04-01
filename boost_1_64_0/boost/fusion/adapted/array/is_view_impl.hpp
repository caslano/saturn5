/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::false_
        {};
    };
}}}

#endif

/* is_view_impl.hpp
TdScq0qx1HTzDIGg8QLLUxCVfNJ9cIEZ2Om7MK/e/yG6E3gVm7JxEHrBpH2L1Az/0VScpfn5i7RXN9p3OzBBzs1liL2+0464tkrS2fBVmpx+upMpPgpwq/I+PlKiz7af6Q2Ljm2KTz61RDHrPuOp2s2ufhqCpOUalIGZC2W97y2gcgOFqysiC4vwDN57W/o22UQikZd2DKG/f+3tayn3fQZ8qh5UYd2RDtf0vrWKodbD9BH8hTKze94F+WD+I2Qs7E+4Obx7KlPLqHeuRgjUcnY/8Uoe7KD6VNyUiH1/zbcaskWyy8RW8DtuK7sq3wo9K+xY7I4Moc7fsqLbBfTerngvfDnIsRXndiWBxDBklyFBeqGxObMWd6Wu6QKJZ/Rz8xB8f+5m4IWYxnJ4XdX3ykEmYxY/fJSnu/14EZh9O5T27lkDemmnCE2miQGfy01YK4Mm6w3w3r8f6rtIFhtHjtgZ3Z2z0/jLqmByVYbJeIMK9QTfBeuR6/RCPA1G76X5njcASftiH5Rlq1ob2GYkpv1/QbJMSB9nJJRCcmdZP/vaMf/8NUwA/8+aOg==
*/