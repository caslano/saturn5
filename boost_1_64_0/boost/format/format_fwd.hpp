// ----------------------------------------------------------------------------
//  format_fwd.hpp :  forward declarations
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_FWD_HPP
#define BOOST_FORMAT_FWD_HPP

#include <string>
#include <iosfwd>

#include <boost/format/detail/compat_workarounds.hpp> 

namespace boost {

    template <class Ch, 
        class Tr = BOOST_IO_STD char_traits<Ch>, class Alloc = std::allocator<Ch> >
    class basic_format;

    typedef basic_format<char >     format;

#if !defined(BOOST_NO_STD_WSTRING)  && !defined(BOOST_NO_STD_WSTREAMBUF)
    typedef basic_format<wchar_t >  wformat;
#endif

    namespace io {
        enum format_error_bits { bad_format_string_bit = 1, 
                                 too_few_args_bit = 2, too_many_args_bit = 4,
                                 out_of_range_bit = 8,
                                 all_error_bits = 255, no_error_bits=0 };
                  
    } // namespace io

} // namespace boost

#endif // BOOST_FORMAT_FWD_HPP

/* format_fwd.hpp
IFXJP6ZLIz1XpMibFS81C8teAA1ALpcPWpBcWsZQuSCxQd75hgVpQB0hYYVaB3aXC9KIZHGr6PxjYvhgjk5j/OUWKRB5Vmkz/2WI8aDHXDH0yFu1Yf8mTYRgeKj/rnHPJmINVWejRUBe98Yvs6AtxfF10siCy9Wb1MpJ056wmiSLfg3DW5F5obLOKvjBD4MNpN0h5Ju7pv4b5JtZVX6fbq5e25ctNnFMc7KPCiqEE7r/3l3EXGMRil1PnHoq9pxfpuErPDpFfoVvzZBfIZ+nc1kj6u2CYNsCbi1rQEgz25BL6ew5tabDiJlXm9+SC+koYOMZinMaP8N2cy7oMzTcD0xW+Mf78c9V01lx53Z2NFw60BPvPxFrCp7VSOm5S3ZE0L7+7AyDDfnM7kaeGueOMtwKYpskbXHVpxWANwC/yWyka40iQeKhsesKr9fYvTayR8u2qlZlWGkcnPTJc7YUd8mrjN9liB87YQKmqWom3ocyefGTTMFP0GvxXa39/rpgVaa2mI6LRgRcJyPjytI4vXYzfO7M0KPPy9cCzLBxjQ9NlzX+eZFURLqWFClofcXhvBEOZ/8JI/OV5B8306TY2VPat9YTHzvGu3aygVX0Qh1lgrJliQPXsia+xsb0eIPlVms4jLQq9Gnm5anzNsgyrfW8wmT4PxCm8vDDTHnix4r0/UrtGSMTQB7ZvDGAa99I7BLAw5XJPCk3KoC4dmISLrUvNTQBW1+X1hJudZe8x2eFN6dGmfwufsZ0kVsOGzGqxxuOhHJFI+qNru6SD7j0XVCat56NC6CkzPdImnxhdsvFMMBwXvqiCv0tyyQp409VnnwMfZ0t+22GNNMff9drMh+YQiMJLqYPEun1ClIZxjgTkm1yBS7MYn74QeUVTx/KAhBfJ4rCPD3sBSlZ0uL5TJVT27GB+tUuHYPQErMw3aOsuXeSVbpLT1jIcXPCFHbcrGAM7WW8BWWu2CRFK7x/5rcx2G9fIMzZLMRlpmsVzYBSsgmMTzc/Pm2ooLvUFMF+yycLZLCmN3oGIALW2Hnx+B1k4hzTgG17Yaeki/cLSQ+TzO7Q+ED2Ej7gPqOEgAY3Lhn4V1xtgJ0+vogfoZ9Q98xc0AzLpHLerHrEpbLNsgplioq7/Vkt5DDLE4dZIOoZLD27nbwZyb6viWliNYPUr6COqlPjOv01cArfECQ7/Uttoj6y0/9OpHxLwBJWxukqqeAhKzcV1Jd1asdP6jqelJZTioFMVboa9/cP8LwVv7xZFYoffPRanCi1PnazVo2I/yBRMl+QWSjuzvSwww72Eva52dizDsojWZAzfU7VkcEptQPfccPeZ1KkKDdKebDeyi/suAb7kY5lgGIWM1Tu/ZVdrJNKByBmq2iqSx/ym2DicHwtKJRRgcxGVrFOVINiFhZyPlMWcmpjmrJmg2mvmbjz8BNVXVw4k7u4kJTS5AmsUGsHhwTsWb6WvfIO0aGc+HYOFmICRVEyN7flSOQAXUhnsMUs6Yto+S/GDonEhvuiKkZAFmIzbfg/ZzOFQb8vyWUj7UghYQfm0J0lJv3WJ0g7N6hAQFauO2AejxCKY57719DmEC3ZKz67PHeFLTyrCj8Pnf/HEH6Mhv+Widr4fJBJmDe4Xdr5TpU8EiUYzhYcj+1AZri8SSo+1xhfMFnF5xhoZWgs5oO7WfuJLKZeymr7Sv/ig/AI7wh/QMS+AcVl2II02X5Q0cxCEBCFBPJGvznxnvBhenCaMrEe7W+cKosVB2teX3lWr77mdXi/qufH2Juqnh+z6xjnh1odmFcTv/x5SRyy5CGZqAF+bha/HSLEaoMuD+k9fntWSrNeZd7B9LbstHt+PfE0clEsP+0=
*/