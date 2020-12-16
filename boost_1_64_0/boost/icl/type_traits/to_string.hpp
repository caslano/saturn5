/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
Function-templates for discrete Datatypes like int, unsigned or
    any class that provides a ++ operator c.f. iterators
-----------------------------------------------------------------------------*/

#ifndef BOOST_ICL_TO_STRING_HPP_JOFA_000712
#define BOOST_ICL_TO_STRING_HPP_JOFA_000712

#include <stdio.h>
#include <string>
#include <sstream>

namespace boost{ namespace icl
{    

/// Static class template for the string representation of values
template <class Type>
struct to_string
{
    /** Converts all values of types to std::string that implement an operator << */
    static std::string apply(const Type& value)
    {
        std::stringstream repr;
        repr << value;
        return repr.str();
    }
};

}} // namespace boost icl

#endif



/* to_string.hpp
emqHF4U/ATZPbL4xtjXdRsarQSlyMoEMvniV/NPYvCp83u5iXAx/jnS/m2peR77pJG+MmUCHwl5kyIWxdWp3MXvY+UKWes6uq6z5X7rdHr73skZKJnnGzuLrKxLJw056xxp/UQ0bCj37TyF/uPuedf8aQP86dtYZl+can78xybp8cixfnkS6Ll+/HKTGsOVgH74vlG/O5w/SL2ZZSWrSUPuTHhl93YP4oDydT+k+J5nu1vmveA4y5kXty3X8a/3m/fhiGL3pfld4Rsh1j40zbxR96HwDv+Volw7TZ15WrPUL7H/z4pPZL7f74SxsMreMz04S3xjjDrXSnyaX6Rzb1jpj3Ascj7NOW9e3dbNvrPujmJwqHg90VQPJneDaUmMeM3ZEpn1D3gtsGsCehY5XtIbYbxanOud7yHivmk5V9O/ATn2xcmpmPZ+oD6Ndn6KvMR2vr1OvxTkzfK/Jxlv4eXmoVXRLLPMs3FceiMHioCPf7Thdro9W68M9ztzO/Hj+VHYY9+E0/om3dpI9VcFv4bOFOPXJdL9IN3a6eq3vcHd2tKanvdtA9vhke6HGc3GGnCHvAbpXNsgFOmTTuVcpW4rswRBLfhtlrcIo9Zc+3Yy/tVj9qZHLtXJFHvwSnjHkYwwbJ1vnamu8aUxqkVxLkAfhGTFRDlWKqePfctgl9n+y/SLjH2NXci4f8/fZGBjpnojD4/mLPV1K3POcD+KH2QVqXviOqIP45qtLbDxXLs8wP7KCP6PFq1w8g57T1LZKdtD97Tz6khFe0ejBXwvGWaujYzZ+J//314iZMa/W27uoFr9rQp215suOrxKv27LkrHoWba2RmD9GDrIh3/gv5c9oPDyQj7Rf6a+uE582bIu3Bl06Yh3Kw/d63fikE985TiuSG2Ssmchv4XO5fC+w7iVt6dPTPH3P5/AxnzWlU3GWGmNunvxJKBazkBsT7N2+xhh/uTi8JI9nW3dtnJwN9S98X9GHLxzPtF4tv/fPMB8l4bvXZHkfan+JnEjhA+P/Y+zP2kJtAuL07+KzKjn5rPxcysf7tLeFZ0vHG0vlHFnnDbSW9uJq+tPtom7iFZ79xe7G0XzleLscnlenzoxU4xynsm2La131vcimM3uRr65MT3bPosOpY9hszKc1/KY9XV+GHK/h677y8nh2RmJ9vrrm2tF4c1Jcz1UDJurnr4Xyoszxe2KwhIyH+eAeaz3DZ9eWyHmxvUy7H8ut3dicIrZOae8ekUBeG751HO96JL1ytbXyLV3frTgW7nXauDHsSbXPXBuDbRhgn+TE2PvaCcYU6NuPBMf90dSc8vC5j4xv5XFUS3bpf47vrtR/RHuR8ZPDM4v++2vtCUyUz73p9Va9PO2r/vLFfdo7cUF/1xPpXcCPfNsrhp3aj8PnbX016BJ+60PBQLkS7u/6OmhHa+Mwu4u+8dAud/6pa83L7CcyJsXznVxqU2IvlRrfXU4OsG5fMWbPLm2h81JsFpNr9FXl2ws5/K/d5PwqdCfzrFbyTs5s16ZieQo/s7WntebYS826ynt5tipbvpWSo701x3oN/IkmWeq6OYMz+DzYghZk/yy3Bmr/wO98mhjuE8bt5pecSnbgsf58ksAG7UJ76t7T+WWkOKjd4R8QOIzeyEkwjk3t89wn0ujaSX5ns2s6+9qpx3Scqc1GpeP7I+3bJLFpZby+o8bVqCMxUXJjEjn0+VMO9pCXfUbbm6PIpNfcXmJi7Rlye1Se/JKjJ8nZQrEt0Tc7V24a90X4rW2gfDa/hk3JbOzFRzcZl9yFXL7IlUsNLY0bSk99nabKD/UyIvy+5nrRRPanG2fvfF0e/l9D9/ZK+4leFw+wH5Idh98=
*/