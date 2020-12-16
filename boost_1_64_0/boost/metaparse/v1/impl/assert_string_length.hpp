#ifndef BOOST_METAPARSE_V1_IMPL_ASSERT_STRING_LENGTH_HPP
#define BOOST_METAPARSE_V1_IMPL_ASSERT_STRING_LENGTH_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/static_assert.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int Len, class S>
        struct assert_string_length : S
        {
          BOOST_STATIC_ASSERT((Len <= BOOST_METAPARSE_LIMIT_STRING_SIZE));
        };
      }
    }
  }
}

#endif



/* assert_string_length.hpp
Fe3iFyjj9je1w7y6h9/6vTFey5Z+FNSNjuwuOV1kLT+9uPmO/OUZxNb6LH+E+KmzBA82o8dD2WF9WdN83HWeGNUL1o0lrMn4ebmzmDuK0M0J4j58q0sd2eUe7II1Uqu7yMAj2lJR/E05E7KZt/aSc7apLx/nMnl5lC6esnZIJSdRYtYxx/nQ1+tzc3LZYupOnn9obY+Wz858zxaVIEsvaJv038XwCZ/jI/JFmnzJxx0oVnnJHHs/OaGLJ/iGtXJph/XM1C7G9Gs20RxaTrlD0BapeG0COxWvr9nHZH05/TIbtDIU9+ohTtTyWvtcbmbfr2VnPUvsyJ/68WY+hLX7RL5BiZN05JT6VLf2Yp+LkenhE/jZZ8QJ+I4dlofOABxQjxnPk4lksUH6WJsv3bG1vuQvteAvPqouZ8WyCpLlt8wbQ5LoeHE2riFZetb6rU/ofNt8LIRbBR6Q9+vCbMQ+toTPl/c9OkCIm1fmFzxLJh8kY+xj781iWmTlFTq27gD/1L371vZ8aKm+kH/SGH39Lb/cervcYPOL8u+mN/ED7Iv194d0Z/l8cj3YvoQe7FNN/S5WsoO/fs0GfqNx3pJszlTO162NXaw5nz/8TnCvvbwFyfs5epuJjhUswya+at6N4wtkUh65mp9HLG2eNdIYfjv5XP2ceLn3VWq73vxxoQkf/GhUYOsePk03z33H+Zut3ZDo/tbEM8RdksjtcG3Z2ZZfvkt9tL27tc1dYhdvTjCPKmt0QeuOk+TiavP/O+xKHbLyHTsUIx5CvzObv5u+6dldIzG69fzYIdYE59l7a4y36O8H2pqjOJuGwvjgAXHqCnxL8/vWBHPmu+Jrq/mPm907TXvv52/wS18aZ41Pr1sFn7+yYSP60J8YNjWn+I744ot5zIVk6fHLbMhYY3mALOiHOVms3VOtfae6LpW9okdd+JtVzolz3Ux3jOu4BmRejKpo+NxhOfTBQPTHMRzBgv3ipxPJ0h7jWsze1tuNXyF9ZQ2barySzL8dUq2xGgd/u8GceoNntPcFrK+NzWrvl9u7spj+sCcXt4l9sH2ns5EP80tHfuvTZHbgY57Nv2GebMP28uWWp/Jh6pMH81oz65Vsx/kiYpivWteuWGEd1NF7a/q7g/MhG1Q5wJ/yXGtiVnbxaZ+b16PZ+OAZhDn30jn+3S73/HCjtVxTfdOTv/amZy0T2Y1eZPYX9tG4R4s3NT5j3FexG563DB9KdvlQI74KeCbC5yW79Yz51EPWecFY20Fzvvs0bKtd/JTCvw/Gq+hpDXMLe7BFXGlkcTFlY9uCTD3XXHzRHJDTtV99bA5zvu9yJrrkueKGX9j2z8UEbhMjcf2kIdY+FdnontbQCeKpm9i/FD7JfH6uufMpZY1U91RlTzfnB9ecT7ThM6pzRG99q0236aMZI8mRNiw232zKZy3XT1tGmYuiIgPUOLBrtDEsoW3y5jM39HybTbqLnrxN3nfTO3PSG8Z64xvqt0BfXMevsA6qYS07eoe9d3yO1+P0v35oFSWWQDe3DtMe8/jufvycvOxjf/4luWyUO7h+4n+IbTT+nbWb+y59xjpFP6UdN4+yx73EkzrVED8hE5cv0mVrsA/X03n1WMOe9nTfXl3F1MyzT3v2NVj//VRWuwMRgQnWYPHGtllZPjs/eaH79zHPr3uV7TK/DySLrazDF7FXB9j1s/uMV4x5YR79v9GagY+RaG54qaRn7mXET17jJ3kOXm2DsVjLH2KTv1CHGwrqq8z6hp8YUYGuaMfR8HnaHfgYH+FT7MUB7A+fuT2O7MrPhpzIHz5zWxBFEIsyKI1yyIHcyIW8KIyrURTFURYVUB5tkYTO6IFu6I0=
*/