#ifndef BOOST_METAPARSE_V1_GET_RESULT_HPP
#define BOOST_METAPARSE_V1_GET_RESULT_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_result.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_result_impl;

      template <class T>
      struct get_result :
        get_result_impl<typename T::type::tag>::template apply<typename T::type>
      {};
    }
  }
}

#endif


/* get_result.hpp
a6XbsyUnEuSGt9wRiuXyvqLA7idLVO+YnYHC4eNk6q5mRIxcYXzRKtLXIOsQ2iQHvcJI3OX0aatJzcScoD6bl2BBtjMZZr08XNUZO/yPr/6Ir5NwghV0zsaIwDQ6tKDdbiKicSsqsKq4QWCSGrc3+qhY5e15zGRi7okzESzLpMairEkAM9DfUsPCM8MbxHwJSHpZKcPAOC5mkWGL3Gx/TRLUHzsEC7JaQrN/3e4b/5ckTeMadH4pT63YPBUxq71Ya7+Ajm9IRPcF1lTyDI+IqolvhV15Igz/TtX2uJHHFlxgq3a/O2/wU3eZ1vXulOdkdOg4Fc+rl3ei9l92x2pkvDIJFvqVearxNeNxR3jye1R4YCZ14IaP3PEcoe/b9jz7+3km3MvNFRJ8xYN5NSCdb4Rai2sfRxDi1oyg+l/iWlDY2iSKpMlAqQLCDG4vtjPPLjcMzOxypXOIyOm0OJY6LR9mMBqB75G3Exy1Dfaf1M0HvtKq/UyV3a95MNe+/PaI1SnsSYJ+wHVqAcFCrxYIbAIDqHJ/PktEhXYIJEW4e94lT+yOxBZwR6PUWdmSBK1cYRALP08svlcxZmrRl/AuwfgtLBK0IRZWJW6/ZprNkxeOVLTU721J0645Qf/Ous2SYMG6uvpd6VAR6RhpR7Y1Qf2+R7DQz5hkxIvEfIUM534rN7T0iN1hDyHeNA4KdX2FO92IleVHvyQZDTh0rQGOS5ywWA/lboicja78OIkDPQIESgcdMIe2hRStesNA3moiRldUi7P4joKfkUmcAkzBz04cbvlt98SeXRg7iAr4RJ+fgx+Qb7AGXIYBsIH1mF3DmJnzpC/uzi0diQkcv6TTCKDzoNz9eCemY9AnzY53SfNJZY19ggXZebATLJejfWuEz5PdKedn4WXF6qgl5N7yCC6bSloUAvTc+BdCLL7d89UHtgarH6ePZL7FJAjC4fBIyeGmYVajLElQf/ckWOib3yjbqwT4+J11Ja+SBK26gUEs/OgQ/TzCpN+428gjskycn1ccgNwDuAM7E9wsbZytCAs/RDqTmLIZw/LBuIOMpMPUUreOCRb6jk53htLEDoEc2d/AIgoK145y0p4eRs/skpIJDhelwZZgQXbq6yXL2QTlG1Ju1+0tmQuld18RLDQW2Zy8T8kzIpTzEGKh338FaVUmjiOEg5WHzHD3TRK08odBLMiOf24hdBea/Olp8Tu/FHSDM0tXCrAFxbdw8QNpU16L1uMyZWnPiI9f3KgQ9V2SUZZGtakxLn7ETNwpyiXyy2/WRXt/Q0r0zs/CC1rXueROtdvCvkxvJBnf26RMb2GGjzqRcpV/STIeQcqFj3KJp6FyL1gql1DEx8NXuWS+JBlvI8o1gnKJqqWyhGMubN8TlJO67X6G+qLVH8/H0+H1tNo9rLfvTfvwk/Mf/fzsGpjXh3/ah7ftuX1eZIPt1f3zMXtcLIvfi8fs+cfOtX7ZNO/HItlIbMLckS+IUqWhSBa97Uf89AJHz1oByWgmoCcyxyVWGvsN0l/DKAE5+wEB+Amc893/IGVuPQQLDfAIMDJggBxPMAJw83gMGH4QIEigZ4DMl7UQGEApCwNGnr8yIF4bOm5HnUF5ZSOwSZf8gmS35JW5kRyXaBrQ6nfK49ThRy+urHUsIOlloax1zHFhax2HVUFsuXVzRCGA4ylAWNeTpOpQRsQX1hv3BzptOsBpXT0tFtISCB0GOTr882xUjURSyrBWggVZZKWTBHS2OcCMLTo68ti55hFGkRuC+KiciI9yr8gGIyo75Seb1qMEM2U17Czda34Gkl4SRhV4MS6jcrfErvkqbs7RPY8cSf556EDygC5ygqjDpYhDJDY=
*/