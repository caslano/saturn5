// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H
#define BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H

#include <deque>

namespace boost { namespace msm { namespace back
{
    struct queue_container_deque
    {
        typedef int queue_container_policy;

        template <class Element>
        struct In 
        {
            typedef typename std::deque<Element> type;
        };
    };

} } }//boost::msm::back


#endif //BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H

/* queue_container_deque.hpp
lKRRt4G4Tevy5x5DzdmqFXchv6jjJUeFrru3NukMVVo34szH8v7zNN+iPsK6KEnDfJik1d4kFmUa+I0xH7MMKc/Xxl/SaaE9OiclWbq3vTBPVqmK6MZdNhZvkgdswkZZuLztPmg/VaypjDzG9MZI298u5Wt0rkmaBreFnT0qHGmTm7DxC+Zzxj/O8jr5ZSduHAvyjKmNOv1emPcMiseiA046UhtJZycxxhmXUUWdceVbulwi+wFpE5qTZcTj2y5cTDqfZdEcVw5zy5rjblHY+eBWPpdv5+gn9W9sN8nzgsE1MoY+7m2nBraT57ON19SMv/slx4RimLeTeh63e0EOE3vuX4IcT8gRbzHM+X5ZOcSZxiVsdhBikvw8j4K8zvPktUKczvNykNN53glynGfs00oOS9TiTO+FpL5abaYRQS9LHceDuEyjC0tdLi+zn1F0GfJCxBshF5Oa8UBYK1xcaPY8IeZ4l5CaXEbmvrZ4ScFYz6PdoihE/ZU0Q67maRuWaNeS04cq2cY8Lm2naQuFDyjrJLzPfg7rUSo8OgViSxh+6a09hvfkeB7nh+OFMVBp0vuO204YlO+J8acLa1g3cnRqWPL876WkpkctvvfmcZyOJmzaCau12pmgtFA6kM7zfN1Uqbhje2mp68Eae4Y0V5Ec9brs579MhsHznEyfdOOg+E1hsR5dRumUULF+LnV39OJ6V4y2tei6PpNva1HBZ7WtDW/tM9rWim44eg/Y122zxHqTn2ZOK4/Hfhhus62B26s4brbE3SqzmX35XKW6RsvbdSpd8kgaTYqE89K9vPgd7y3zfZWDVpfj0lqjvmE/roo+MuPsbiMtIfE9jzOuRl9fGbsAzrfG3N/LuWIH873buIycK45cTc0Vd27r6rWVDV4nuZ2ryXlkz9Uwj8zKPbq9q5viuSs9Uf2A+irdY3HK3Hha8Iu6+neBaho7cfjN5B3+x9/EEdviOfc39OWIrPBXscbmhWs/fNeEj3lHT0/oEjFRFDMtv/NcLrqT4lrNtJPktU2P2ayeqttMgClOegzPMbjOfGaL67PvaXLdaVR1Neq0svJge/XKbKyb9+uZodILMtRFMjP5oBBDNSCYYTAcShVpmY0Nplwm+R9tLD7k/e5/sLH48P/4m5jTF9XVb/BuS72m4sLvimv/x+9iMfeY1r/rtNgg4du6XCKNTfoF/RmPI2OS37WM/27H0WzAb9QmaIXN2ecb+AzpEwRG0of+h2XS1ZqtxkanYdtHEkkf7INXHnPTs7SkuXSCD6GIM1aTmnHWX2OtO+89T05ceqzP3Xl2bsb01mL9Mvr3ea5mxuU1+0yHbIMHRBj2dhLmrxcRGvXUNeoNaKilLbtOdYVCgc/lcrT1wnnsX8zXTEBcnv2Lh3Q8YcNjw/UlZ3d65fmpG7NuS/ok+sb7S43qbXxERKRxxddpQV3WU83Tqfqd35/09YWpuWnx+wcofRw+1s/u6+n24W9nL/9+YcYeIuF+N4cj41wHc2PFUJGTT9ZMUPclzVDd4FIet0+3bOHb2TIGN1gJc7as2eZqeRyVuQzvZJizZc/hPSCXo3jF+xRufvlL+pzlGuZDy4ptrBMt764Ncxi/vqJqmJP1VfbTxv7uOtbkfMa2EU5+VOO7SZptU/Ixd3HDUr7zjtIbjl/c1Tr16ZwStEuVjo0qJWPt5rhbr3TaJh072eQRc3gZXwrz5EQ7OPuFfjrTaWAM/daubj+1HcNmjvt6TBGlkyTj70Tynud/YTO7yPjhf+PJOOWa+fCeu/OJWP/t14Oswbg9rAUZmdQ2xvJ8lqLlvdDlg4qj71pEm/CNVf3RGQGaReDpW67DO2P88OuQCqbaoTk=
*/