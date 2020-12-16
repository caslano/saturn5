#ifndef BOOST_METAPARSE_V1_GET_LINE_HPP
#define BOOST_METAPARSE_V1_GET_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_line.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_line_impl;

      template <class T>
      struct get_line : get_line_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_line.hpp
pn/lwOdheAC+VAvkS+P7mXih99xhhOErF072/2gMpf1voYuwfmPkLwq+OcMHwbn8HQ6+CdO+nwPn7id4FZyL/9zlYlG/CzSQfyT4ZZHvQOLR/t1Z4McR/rw3U90/dDb4sYQvtryo340u4Z9/RwXfH3wZhh8Dzj3/ieBrSoz6508CX11iNP7mZPBVJUb31y8CX0xidH/9QYX+hxT6H1bof0Gh/ztwbv32PXiS4fNdwbf/BRV8YQVfTOKzNOBLKvgyrPz/v/7/+v/r/6//v/7/+v+r0def3/z5TQt+fg2bGFbwej1DlXw5GBquZvOT/wyKa/cNF4q5tdta21r9/rWnBSm/ravODuvuXDsYyFTzubWr+WI+E+SjTxQLfdnq9EptaIfNW6v5oGmyc/n+RHa9nkp16KBqpuT1F4r5wFsNaVfvObRQzg0dGniDhVrQ0+b3FMrZ4nAuj3+2+q1tHe3rtrf6PcOl8c+Va60DVmImM9pzaJBChpzJKlQspKX9zokHzFZrPdmhah4/ew+tFUp5U4FTsgeWyeWqkJVrVLNhnUYSoj/3FAcywYCbDJQKZXwcBaSbh3y1apoDuUxdFmVnnLKcbPORJPys5avlTHHy7+gTlpkZLoVF2pcJjB9sxkZn3LMatt+glisMmUqcWupBrZopFg4qm0qbkr/a9Eo+Zv3lisVSplBuzdqrtSqNRuU7IbA3O1TuLxzUqtmtgkx/PqhlsoOmGRLtEENfLVspVEwlyY9WyhSLQ1kXktBgCuWDXEiKiruUL2Ur03sDU5lkwiiUMbQNKccRWnF95m1oagbGB45akDMV9g8dHoWu3RYnuxpSrbS777VWM7vlM9XsgLeht1K+UPHwR++AiV+CyV86vDXxq9aHvZVS7eGva09ws2eW2jweM1dwUXbB9ABtNWM88Io8OZwMatmBjJNp91BXgupNDMMdeoCihZWCnuFKsVAeNB23RakibTYfBLWBaj6TCzKVgmY7RdPzRdMzaLhTU+MPqYk/dDdHXL2ntKX+LQX4S8fkXzrDv+gNH5mg3NaqOeRUBrNBl26iw9L+urpp8tMqqiT58kGYC4KefG8lk8Psh0arp2M8X73T+qe3auZtuKCbYlzTtHbT/jxlqJoY9HX1TxSV0nQTBZpFf9UtTQwwxqu4qTNsvAXP1Nz2jq93sk4X4KQ4hvoO1u3SHVYDmJQ6HCGsBjBGXDTg2A1g2grEkNZppTJlV8L4QfKTMi3jMLnvJnnjB0S6voosC8lDeX0NhHeDSrXRTgoff+mk6jpM8x+qMK3NKLnUYJzmhwqU7VvTJmSgQpSzaTNL2bVSkZy0BNOerxTo4ZHt2oaBCmFT+c66DyqRVms3zUDatBh9u2qNkktN0a5alQI9FIJdtRqocDVMGfe+KLmUZxf1zggUTcuunLVU1Eu+07SczQ0C4xndbXIPz2DXJ52sCbscJa/np8uuGTEC6yXWbdpo7Ixc37FN68dtscYmrL4GD2Xsws6UW7lVobdbpfZdTFJILgrQxZTECPTwxC4mIC0VHirJzlJN2bWZKLmzoVop0N4iMlDhoZztGqRl80vFMmJdCrRfBBmokBZBzozzyRFSZymt8YySMeNi1LMbcaPUorztpjlOXvS4Oq7myZ2p0O3ZM619wjkXKwnZ9w+dtIWy0uVJVfYO14qtmi7MvuH+/nzVdqPCum0w4qK2bFfdruWpty7+bQX2dplkI8XrI7oKfLv5WDt/HkrNrkicPHDz8kMEOvHIGqiwn2p8rzn2ZjOtS99JVU4kd2KuKgXaG7AGKuwdCpbGYJRcyrOLep8iMJah11wVHkrehU/O9QymNWFpmS7YzG/Tt5FqxaC/NWs=
*/