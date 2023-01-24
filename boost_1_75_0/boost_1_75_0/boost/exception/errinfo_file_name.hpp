//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_FEE5120A6C1211DE94E8BC9155D89593
#define BOOST_EXCEPTION_FEE5120A6C1211DE94E8BC9155D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //FILE * f=fopen(name,mode);
    //if( !f )
    //    BOOST_THROW_EXCEPTION(
    //        file_open_error() <<
    //        errinfo_file_name(name) <<
    //        errinfo_file_open_mode(mode) );
    typedef error_info<struct errinfo_file_name_,std::string> errinfo_file_name;
    }

#endif

/* errinfo_file_name.hpp
OjcL7BLY8omTbmDHwE/rh51emCO5cgf1V+scOEp75Reng2Yq/JMC/1wK/3SDfxLhn47in2qzLf7bGm60wD+dX5Czf9qo+rqrxdpJGI58+C2lwpZgfdWA1F6PcchaLht6cn3yPDh641DsDqqi9Om+si3BhtNfFqXwifBcMHpMU35uGYiXrgXizVaOEFKZseJInu0E+MPqBPjECKhAD1jRUmCC2oYq5EVadqfZzj2LEe24TLf9xmgtOONQFCdg3iZr4rpmRInOAoNQfAhyEXnttOtIOv+eYH7dxlA58e68zEOkCBPwfM1V3FP5ZEyq7WTMf3VHcU+f2B2henjkv4FQBHuxvllpWC8gs/1+Du2lVHPVWMFs7wq6Yy5lfXPTHHj170t0J8P5l1l6eJrN1ZIKenjXSD0ECohMhfiI2SKSFM5Uwcd7kh6eipmxovnNWkt/Nm1HBw6ehsjbdPFS4HOrMn0Swr5hvOnXk/Em59x4Ux52TryZpvDmpjDCm+OAN9t89UI2G8WbZ5LPhjepjDeptii+PyFNwRDorEW2ysaiYj0hTAlJzevRFt6kJAMhykKpVbTf7fNvFYgivhPYeYaKoSOW9PAF10Ew1c0QTHUIceSbJ2GhD1zGODIzFEdWPylx5NkbBI5MFPJfd8aRl/HVvd314xF/9bBo6RU2W00qUFNHuEVNBSfqCPHf4itmIEwhSU4POh6RakUJpvrs
*/