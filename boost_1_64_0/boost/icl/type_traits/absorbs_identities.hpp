/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ABSORBS_IDENTITIES_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_ABSORBS_IDENTITIES_HPP_JOFA_081004

namespace boost{ namespace icl
{
    template <class Type> struct absorbs_identities
    {
        typedef absorbs_identities<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* absorbs_identities.hpp
23lJHWTsyZX419n7Dd5KbHvT9nzSfYNmBSnmmBW1fOevJlCmduK8frWomnQxDQZ3islxW5uoO3SAvampU1ruMQu39ZT39E6GIiPSieUVMKvm5DY4SzP7k4NC9UEUi5fYGo+QJgNFN3EnwOwPIrE6pbYbOz6Wr66jrqNOP9KpaMcfGcZdLUelPwNC0JOCSRs/OvCspOXat12CDv/CCDimCMWXPMClAK4pu9NYGTt98IGJKYg9LSJhPh/lOH7AmUo0MTRMXGi6O4sPt4eeMlqqy4QO2V5aipYYr5eyY/0wTPSKtsFVNIVPy+2Oe3D7YO7IWvU0g8Wr6kdcPoWvBDXKhmgowXLr9j9CREVbn1FUXEcnSxTNkQXjDPm9c/EacEWqCf1nuCUjzMKr7yR1+USDcSfS5BjYf4lQNm20y0vRXe1ZE79TYPxPbo+OQHM3mM6sbxmeCL34odRSa7/IVD7JEbY7lI0rwJGfrMMdkBCLKlh85lver7DjdLlP72krHcPPBy4o7A9Z1IlgcUu4mfNjhQFAJxqvxAZ81SmOwuKWo9P7RtDgF6/V/poPvw==
*/