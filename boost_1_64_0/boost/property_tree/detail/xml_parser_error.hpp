// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace xml_parser
{

    //! Xml parser error
    class xml_parser_error: public file_parser_error
    {
    public:
        xml_parser_error(const std::string &msg,
                         const std::string &file,
                         unsigned long l):
            file_parser_error(msg, file, l)
        {
        }
    };

} } }

#endif

/* xml_parser_error.hpp
eBy/Olwf7ntNUXmFgWj7sJx3PDnsR0Ugiv8UxZd1Shf7nW92x3MsbPdPA1H/KsPxu054fH0h3O6QKL7j+NVE7ft2uN2rwuPppmH+L4pixYAontkI1+E3aq94i/uF4zDiufiOY+G6+SftEq9zzXCdfFcgWn/D+NPqa4rqDY+7z/5TPvH1TZ6LHwnb0VCsXPHwPcNx+ma4328erv8TYbtf4XWxtMNz8XZXhvszHI/2ZVHsv68onhsK99dnw3XrruHx95bwfPBwMbD9SwJRudFwncgJz4uPt5340C+KgXb/PRAdFxXhfLhlRPTa220nXudbHosffOQ1RPGtgWh/m4e78RFhP74nivebvbponMP2ffMXgWhehe3+zsPD9efD0sVP3TkQ9euf4fx7aLgOzHguvvucKN7iCtuLb/p8OE474XlmOrl/IqJ5fmfbi299oSi+48vhcTV3NVG+cD4+/VGei8/9fHi+K1GOeJc7qUf8yO0CUXn5nge2aw+PvyeH59lrhvs/nP/f+ZTn4pcL5Bdf88aIqPwz4XrlPr6ov9LF64Tlv2lceuDxNcLXHyqKD35meL6aCa9jwu1fHxHFu7/DdmLFE8Lro/xwfX9mRNTeewSiftRIF9/35EBU/ovD/TUQiMbvGeF5qTCc34fD66Qhr4uvzAlE9V68mijfpnrEhvZwPXxdRNTe94fH2z9F8X7jEVG+38ov/vRzyhPP3EAUD4+E11OrEdHr3wpE4+o8tPs8PJ/f+iHyi22vDMfvAeF1WTRcb2KBaD7/XhS//9uIKP/u+us1n9WIrm8iovYvhu0Lz1M/6r6maPtwXv7l3YFovr0nCI+ncL6E8/i5YT2lX7qaqF8/Dvv1qPA8dUQU//LTiGge9ITjlB32583h/H5SIHr986L44LuI4nXeJopfu0V4nu8LtzPuu+16R0QUn3tNUfqf5BN/cVsxsP0dw3n/oEDkaeFx+cxwvs9IFx/xN1G89YNtJ37zC2E/t8N50OB10e1I0f7/c1jPcwLRfr5JOI5fsi9L7tfc1d3X3tXZG9wyuMGNAv+O++zh6kFzU/x4c0PTlRXNDzl+ZXDXMM3fgpF27FhzebS55FC8vLayuqapMXq6raP7WGFpaVSWYw8K865k5i2rjDaWV1VW11fGorH23u6OlnPHDvedbu89dri3/8yZlp5zye1bk3VtZm5/n/qGyvKa+nhZtL3z8V09Z/Zyn24M81b7fDqVN1YRra1uqi+tLK2L1nR29/cdO5zYpEU8dr9jh1vbHt/S3+FJvKLBK4XlNV2dbccORwP/7hSWl1eYUfe96hsaqmpLq+rVvVfv4cow38KjMvtYH401lcYaKmorU/W2d7QdqLW3rzVZTNCZ7OtWZUY5962IN1U0NdVXRbv6+9KdrQ3zDuzrq6rqquI1sYq6aFN/3//X2Wiqn0WZ/bx3XUVtdWNZPJ6od6/OZD+H+jL72RiN1VTU1jWVViXq/C8dTZWT7OfqXTL7WVba1FQVr2yIPrHt3OX9zJ/JyFteFq2oqo5VGZdovKf9yS19qrPZf+6t4Q1S9WbfNXMuxaoaY6Xx+qZod0tvb3JntCX7Om180/XWRBsrm2prmsqrD9Sb2PYpXT2tx65IPDp2v+7TPS29hjYa1unn1DPrrCuvqI/XVVREe9t62ls6wjrLkuOizvT41kWra8ur68ti9Yk6O/Un3OhwZ/+Zx7X1HDv85JaO/ra9MnrvFZaxnVlGYzReW1pZWV5dFe3tf9wT2k71NZ9u6T0dzrvHJevNasqstzbqGCutjzWVJevd29aDxMb7qk3XW5hZRoNDwFxsrKiNtvf29rf1ZFRrm2S9JfvqrYnWVZdWNzY=
*/