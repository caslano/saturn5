// ----------------------------------------------------------------------------
// format.hpp :  primary header
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page


// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_HPP
#define BOOST_FORMAT_HPP

#include <vector>
#include <string>
#include <boost/detail/workaround.hpp>
#include <boost/config.hpp>

#ifndef BOOST_NO_STD_LOCALE
#include <locale>
#endif

// ***   Compatibility framework
#include <boost/format/detail/compat_workarounds.hpp>

#ifdef BOOST_NO_LOCALE_ISIDIGIT
#include <cctype>  // we'll use the non-locale  <cctype>'s std::isdigit(int)
#endif

// ****  Forward declarations ----------------------------------
#include <boost/format/format_fwd.hpp>     // basic_format<Ch,Tr>, and other frontends
#include <boost/format/internals_fwd.hpp>  // misc forward declarations for internal use

// ****  Auxiliary structs (stream_format_state<Ch,Tr> , and format_item<Ch,Tr> )
#include <boost/format/internals.hpp>    

// ****  Format  class  interface --------------------------------
#include <boost/format/format_class.hpp>

// **** Exceptions -----------------------------------------------
#include <boost/format/exceptions.hpp>

// **** Implementation -------------------------------------------
#include <boost/format/format_implementation.hpp>   // member functions
#include <boost/format/group.hpp>                   // class for grouping arguments
#include <boost/format/feed_args.hpp>               // argument-feeding functions
#include <boost/format/parsing.hpp>                 // format-string parsing (member-)functions

// **** Implementation of the free functions ----------------------
#include <boost/format/free_funcs.hpp>


// *** Undefine 'local' macros :
#include <boost/format/detail/unset_macros.hpp>

#endif // BOOST_FORMAT_HPP

/* format.hpp
lgt5oa/idnm9OXQtXX0ERDE4kgBrYZ8rOtSFx4PbMvWaZw4ZBu2Aj+1vku48os45Z2e6K3+FcEHU/4I5BTylwqcnfGy+FCEcygdkcm1FuAhEfyXFoS9FdNSenEpbfKLkM81eA61AjzCid56oDDmBHpEqAZwWjNHoqJ3O94uLREype/4K4W5yH49XB/3P3L+eu02M/U4HdyGMPQaOmKPoIpIEfmHaSe4tWbgBuVd/ynITuEBmLI2ZIRsdFlpmgMAh8ePVV5oMJLevzkclIoSCe/Tdjlp7yLezlpUJHUmltOzEpdzyVCkVdLhQhHbFYrsF2Vlr20smO2qzQv2M6eOkRsIGrDDP/EVqJNDW7JLKBI2EB6ZwuUnOAM7AVC0+RS1E7AF609z7n6J/9Dj9s/Sy3dA/t4p41LkN0LMUzRGgr6balIQdsVY1TLYTBoXB1vFabtK3py7Vft94q3xeC615NQ89+FfjqeEIVZ44focw00Pzkr9IvXsN3WwU38Qu3qMNfqwBrcKj7euS4lnfxO/cpG/UN0We6Rc24aOyUylrQq3vP7OrTepXNPqK1sFcyE4Hb+uFMyDw7MZkfYXMw4s3pZVGx6dGJyWLrtvz/Eg0vWLxWntGLWkqT8ELhHYRdPWk+XTQTVx3O/mLR+XDQRPVN72cK+IEDePL+c2gpN6nrJV6IGRpx2Wuo/3FR4bP13Zk2UPeYmnNJQyV9NuoGkqVh6CyKoG8UP8X6MgDabGrHucUq1vxamlaKO8Rcez4UHLSXYgM0l2n4tJqgujd4BBJJpS0xPpDNvtIvZLNlusBcZuI+iO4vyGKYp7tcgWxVnk/L6s/zcSoDOvl0/9CoB48prNzeaRX9STZJ+8POWXiMUx8HVX8XkTr1C1jZhI+1mobFRnetIp9K1vSiMWixAFiTxuGG7I9qFlzDm97VufJ/kBlRdFrcDeWKbJZDF0pGnLp73Wn7JydD0kjX9sQLDtoEwEqN7orXpZ0IIBjKyXwF5cJ4DtoAqRpoWTekG25trw18ybQmnnz+6vFJRisNU2UGkvrh3Uqz4dkng/DeW7T5fZ4R9KIB3vAHPnjwd4VLYOAQ5PEXUOW7I3uCcnI0cpkt/QE4jgAFeqIwm5GYUauaOrsI5q+kwLD0+YhcOeDqv0IK8f9Ayh2AUelts3zLsERfoNl1JtUrLwNfp2r+GLPrEvi9KYyaCX5vsfPiuvHkDBAyxn8BLjmvmqfQzSjXH9VLb61bQRhOjFWR9KUbJ8/BXU5GdiG0FHU9tPzgFq04vVcg+y3CZeKPu/JSh+eWOk2stLkiMiLiO2RqlKl6nGpWKVSWciTS8lCtqzwzHtqmcN2xAqHbcVyh+0azIZ2+G0UYf+5NOnB/BOKHUleJE6oUEvhVHDut5h8eigHYNFSSphfcGJLU3pvgK6ox5JtZ4SQedLGDA3bJ90H53hQJaAnLoX09ZNu9emvmlLdcmqS0edTaiI/6dZrIEb/RAOF6aewPJwb0LMgynIv2eFq7qrpUzJwZ5wFtmg7fDZX6GRIIjeDVmg+AXC4Ix/54fvwVkZ5gtWTXGDj6D3CbQDzImGcMHMX+SEz3Bn49eaKPGlV+P64PT/BDmZ9T5IkmKEjknPtarkEPXGbTBNSwUJgtMIZ+aGT+5Z8CfJWb/JXV0Bx3bEAl7WwMt+zWq3M8BhLUVMHTR9YwBcSDNmoRXNeJZeXPFaoul0mfqjfIqzjq3I+5ir3Bv4Tp1Tjl8PiLgHWIlRV9l1w00VOS5bl2V6xiyl+p7Sk6T63xSiGjmdTRGZC8BsnokdC6qN7GB9XBPTD+NGBh/wLwBZXkT0zhOvH5c1BZP57XfbBJFHarPO9eraPC8M=
*/