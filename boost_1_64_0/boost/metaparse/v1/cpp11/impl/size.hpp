#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_SIZE_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_SIZE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/int.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct size;

        template <char... Cs>
        struct size<string<Cs...>> : boost::mpl::int_<sizeof...(Cs)> {};
      }
    }
  }
}

#endif


/* size.hpp
s+pevsk+HlYMFw+5aGn/H35DzrPLvkrxe5PYK6e4gGezMuPE690ruZWufNT84fgV9EQRGuL0M/JztTj9QZwO0eP7nN8mOb4EjdSX3w/D4ezGew/dzu4x9vqiiViQQ6tx/zaY9Zi4GM+uzxXACQ/o9zjH3Un6GTnF0SJ9vGQ9LTrwQHn7hcxpOZ08cBYOpxsa0LY9X4VL98tz/mwlpnofYGO2uSw3DY1TGsPYVebw3lA2uhw28OcnVeHlDHa4jt2v0a+G90MeVYf9DBed6wY99wavGH8HebpEvFgPyzSHXn1HvnVSH36iL6OmKnfEufHFiiXG3FcsVxMnleDgrY7VD+idDV5Wk1t7xO91MG4Z7O9qDiPlubnO7KxeGq3PsEkcPf1LbfPCVXLDXM7k+yXHhifo18DyoX3p2/NyuxMMFKM/4dbYaHlOcwyK72UoTHelGM8IOYQvavcTG7+F64n4NZcYSRUTVWGhNb1+l4jPxuZyl1ibbZ8i+8zVex3l++vgddo2tdGHapXdYo9mS6S9v9wJJ9vRTfoqLaMwbzvu7yGWad94b76VnnhiLn3aMfoyFaL29rAnHuwyhL1WxO+FsH9Nby19oFzx3fLsFt9vveIaMQ/DFjaxnmNuWT/Be5P1DTbjiPOuk0X8iOuJk8TJbcbo9yvZImTn6xLsUEEc81OzQTRUf/2PpjRkfzrkj/TNQf6tSU/H7+XDR18VUldcLeYmGYf+7bDxOKyQ/NPPaDDD+My5szXTql1oL3+7zDjvog1H36UfgHNaV2LHeD8Jj7Wjhz8qKDbFRG/4dpeca9+KrpK7tRbAALVO8x7mX16t0woOL3fuM/Awji9yraO877KUdj0ONx5Qv/SmU/q6N0Gv7dkBrsEe+WmroeWM5W0a7X4/e8kTeVtJbL1Gf8f3SO1KhMvsMnc0nB/E5jTkodliRO+u76t0bVaaZI48p1cfwSFVRopLfZcBaqTp34gFGqBZFpqCHfqoCQvRQHsrOk4t16YgTLWHI++i+B5+++Nmqx2/DvZ4uK647vtRBJbp9+2nj+0HTRFD3xeBFfgvPZs5FnD/2UuBPdwPIq9L7Ha8uCitlhobUScVEmvFcOAmfl3Gv3yUsF/9+JMYSqcVl1uHsjeivDXWynPho/vhusb7ie+b8zLa9Zg6FMZWpDmLzuc/eFX7JFvREkn6pn9QVyyVqwcet/Z9v7H8ALeKi0d1wtx2sPEVWJFdr42Nz8uJS1bSvJPpKrj1ahdrxHL29I9w9Uoae5P4akBnjLLWCRPevZv2NI7v7Vmsmdu/n4hmrIVfIncSP+Tv4fIT1qZV4A/HVyvE/qvwThRWwMH5Q9W7tO45vLczgs9S1c5H6XwabUpr/ueHNH6cIQaPqh/X4tmGVfR2RxuXfLpfDDWi1QfCjWs+pKty2Fv7knkaQ55pOJMNiteiz/jh1NZf9hIkG9uTx+UD/ZOlglwQY60H0x498YPrjHiUf2j0jWqE/kPFTefgnlfnbwzDRtLmR+E8Td0qt9qOX95vjGPUL+8ME6vmfP45a4tH5WJj47o/fq+/vVgHrBmqFT4Tc62uhSk16W95k3m76wyhhW6FpfaBNJZfvZqoPz5wbbFU+0Fj6hLvu1lDf5nWsm7w8ELf2abWa2WtUq5U6y3uzouTG9U5asGR/HkN3TCQffbdgIva0Pifyi3XrloadjWn6VupI5+MiEs9hTWwD463fQZ/4LPMqY6xzp16k1jL2KtPgy5gQ1xe8wkYWJOtxHPTM+xGQ40Xs0vL6CnAgsGt5fpnNMMH1tvh9scb1ST67u/NoFFO4sm1MP459oTvfxDvg9kxj/MX7Y9rp9PC8mNAIz2z2+VRCVo=
*/