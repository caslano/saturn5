#ifndef BOOST_METAPARSE_V1_ERROR_INDEX_OUT_OF_RANGE_HPP
#define BOOST_METAPARSE_V1_ERROR_INDEX_OUT_OF_RANGE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>
#include <sstream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <int From, int To, int N>
        struct index_out_of_range
        {
          typedef index_out_of_range type;

          static std::string get_value()
          {
            std::ostringstream s;
            s
              << "index (" << N << ") out of range ["
              << From << "-" << To << "]";
            return s.str();
          }
        };
      }
    }
  }
}

#endif


/* index_out_of_range.hpp
+ulJ1NEy0pICIrWghef4U4APrrEfMLiHe+xTq24o+u8cOhrCuyt9mVLMmADJiS5T5CwLOYP5qFCfy4iEf1CVNfKrojTHrPZJVB74MLYpj4HlM/NAB0oeKg0uTzWlwccZTWlGBlc1pcEHwk1pzEO/PpFKQw+ENaExF/Gb0riAJutQ5bOKldigHwb7Z+YBI9C03eajqyU+VWPdHNcp69L5dKSbjC0crzfTDS48NB1/a0dnrocCrjPS4NHOpvpdN9Skj1aNNpW1f+3MPFwSyZn1v2JAzBVno/bBA2w3zsF9BNAuinu+5uyLYlver9riA9udDIg3kj3bFLB1mw5z+JpvDw2a4ySt7WwvXdZL7vOn93Q4RLYDthLti9DQE+KSzJfh0HaX4wVIU4994Evuow4DHhlxwcbL0zTQt7aPn/Ly70iCju26/Xgm8O3QAcA7JnhqI/SN+rSeLzQr35Vb2M557rgvgznr7HG6vZkCAmp1LdW0LfRcGPfbq47k/Hfg5JpE53ciXxDgniTO1dorlJMPNBbuyZhW6w9+t9ir05gjCL8dR6s09BQfrcGvBs3561pSV4O+nfzlDMHOELAxgh0tYHVZNq6vYk9u1tfHMtVaNnLWcoU6PzajHlfOvamfqaEncqyvrSG8n+1T8Fig5ALFEuyPyyf2DJwfjRertYBP/Ob2AB7eNtf/lnD90yVfAv9ed4iGjgpjv10r9JYtqX7w1Zrforcby0PyeisbKY1aqN5r1Xrf0a7nPuJ5psomCXme7R/JkYSpEC9XN8tfyOnfil6vjDldtsH+mP6lX2deGeM3xq4P7lSsd4a5PjqBjfTRN9U63xPoIz/p7Exjh4hi5kliuZRxc1t8PSxP2tfu1C5a57fVOt8f0AMVnlkPPpG9l4Py1eNbUh8HbU/cO8K+rPisekqbV3exrGLOfDQgK6fQCc+ZT4btDb1Ve3jjNoWZ8ZotcwoZvJt/nDMRddU2kjdI77h6uMsljj6Wte/HAX7ACS2pXcxaRuvJlQSbK2BXEazNwJLpFr9c26O6vUcdB9e59ZJkHRlaGXr3/qYInt8aThPN7Q1oJMQ9w8r6u8P5VtRR9k0RX/ffjfAL5ji4K4KP+lzfl30g3k31316WeHoz1b+PGsBRhvVKMKb344gM7GP4eQvbI/nD4e7yOivnGtFNl0xMCceb4dzoX1Zo6DUrv757Z+6HlB+zk+2jca3rBTWI98t/oegl4ZqKX5SlObJG/J7HZ8y3nwXPir7O/SESf3kYbbjoxJbUTeD9yrjf53I9RKDmdVF9gg+5HGJusSmMZ/H6mbU0ZZE/6ZF2P5/YMPjjCjnjzmTbh60QlmPB+7fADSzXWIvcQMHyWFYYd3oQZ1wk/qZW4OT64H/TKvByHd1X+JahbOGIs/F4H8PIwlsYkxX4i36MEDzrYEO1mTfua8EYOeGrXXxvUMF1tRM6kJtewUNt2KSUtwqdXh2940R5vUAT5RViBHnCNDjbQhDXJ/DwO7dxDhBZR1gXpFnShbybFODvf8/8LUV+dBAnDhQ6uVmnpUg9092u0nEM3av7Rp0ORoj7Y2EzOfFMgfbt170yZwrRImEixryjPFyhYzkr0/RAXFNaZOWwkQYQBvr810wb0hPT3B+lidjxRxQayvvk0zys1WU+lUtuFyfh5Wi5XeZqZzm8DtlyNg+I/1adWMsq4n2wJ9gOmBMcpPvxQhCYCzpfemYcPGZeJyezWCb3jfpuVJznCq+NdhrZ145msS4hXKTZ9X3manY9xzLz9o3W0vkKDbuZTBiKmRApHSoVOUfBM4F1t998TLRuJDO0dnAV+Rwyvzj5VaRIilnJHAYBPHlePIefbVgXO1E=
*/