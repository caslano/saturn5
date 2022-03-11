//  boost timer.hpp header file  ---------------------------------------------//

//  Copyright Beman Dawes 1994-99.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/timer for documentation.

//  Revision History
//  01 Apr 01  Modified to use new <boost/limits.hpp> header. (JMaddock)
//  12 Jan 01  Change to inline implementation to allow use without library
//             builds. See docs for more rationale. (Beman Dawes) 
//  25 Sep 99  elapsed_max() and elapsed_min() added (John Maddock)
//  16 Jul 99  Second beta
//   6 Jul 99  Initial boost version

#ifndef BOOST_TIMER_HPP
#define BOOST_TIMER_HPP

#include <boost/config/header_deprecated.hpp>
BOOST_HEADER_DEPRECATED( "the facilities in <boost/timer/timer.hpp>" )

#include <boost/config.hpp>
#include <ctime>
#include <boost/limits.hpp>

# ifdef BOOST_NO_STDC_NAMESPACE
    namespace std { using ::clock_t; using ::clock; }
# endif


namespace boost {

//  timer  -------------------------------------------------------------------//

//  A timer object measures elapsed time.

//  It is recommended that implementations measure wall clock rather than CPU
//  time since the intended use is performance measurement on systems where
//  total elapsed time is more important than just process or CPU time.

//  Warnings: The maximum measurable elapsed time may well be only 596.5+ hours
//  due to implementation limitations.  The accuracy of timings depends on the
//  accuracy of timing information provided by the underlying platform, and
//  this varies a great deal from platform to platform.

class timer
{
 public:
         timer() { _start_time = std::clock(); } // postcondition: elapsed()==0
//         timer( const timer& src );      // post: elapsed()==src.elapsed()
//        ~timer(){}
//  timer& operator=( const timer& src );  // post: elapsed()==src.elapsed()
  void   restart() { _start_time = std::clock(); } // post: elapsed()==0
  double elapsed() const                  // return elapsed time in seconds
    { return  double(std::clock() - _start_time) / CLOCKS_PER_SEC; }

  double elapsed_max() const   // return estimated maximum value for elapsed()
  // Portability warning: elapsed_max() may return too high a value on systems
  // where std::clock_t overflows or resets at surprising values.
  {
    return (double((std::numeric_limits<std::clock_t>::max)())
       - double(_start_time)) / double(CLOCKS_PER_SEC); 
  }

  double elapsed_min() const            // return minimum value for elapsed()
   { return double(1)/double(CLOCKS_PER_SEC); }

 private:
  std::clock_t _start_time;
}; // timer

} // namespace boost

#endif  // BOOST_TIMER_HPP

/* timer.hpp
T6zo4sBdwZSC3w/529qtppJi0tFgR70rhgosTZd/ZwoUBLG6a8Cchg+lUfj1eXJ/3/z1bwZafT9bF2dIOGEzKhSRF6ku/vwyh0InvT8EHslfJvhRDZtzCQEoc/izV979oXWt3YhSiBRVxHoodSric8arF1wGegQCH4HvoUA7ceIj5zcI1dQ0aaKsD95ngM/4FfvCosu3CO39QXGk8ajLFxVtTGpmXUP+ZDlbFuXXvaD7kn1ZxFGQHyL9J38Xpm4P6KVt2gO2ThL2ij5FmAwBRaHdmO072YFuYiqFzs/cHIOHsQ4g6lsk7v7nqqvi8EENzBjOo1DXCNPv8nZhCwvYECQ7LdajNBe1z/zzSJFaa1lA2JK5sE1oF+h4DEaHr1M95g0qnwCThmOj05KFiF1Pvm/OQBhOKTqLUjkvg8bglAKRJkXND9bZjjRpuBMz6NHIll3mjCvgzHEolejGc9YhdClnFDm896Sx4X5y53rbrLE1JJEryfuzz615qRFtPn32V04cpA8DyYaLauGl3rx8AfMcT0+QlVOHvfVPsqUq5avjcUp1y20xptkATiYnwp4P/ru7GDyx/lA6MtME9CmIalJT+45Hv8muPsh83IzJmzbVG17QO9/Pc/32kvJlkjgEcbuXEbE6MeIZ+JcPhNiLiBphsJh8Crku85vPM/OWUJanJUub7/Zy1Wgn7iJQ7zBMypg2i+xntLPuTQ7Iw94rLaADoWpjd5wCFxrbAAKutM5UwKtZgQCBa3nMdMwULfOqt434+z2oXmOkhv+NzLayIE9Rj+rS+Yd8QTSQc5uo6vYhgUtKpIARL9brzYEEM/bLmWeY/6ozT4HCyfrdKz95LUO0cF5VdB9hfzu3CK4LPi2q6oWLzAkfSVkufgBG1qg3qy5CVlCplpv3TtNRF9UxtcjxG1tECEBA1i+NxtWwjza1AAYdy50z4iBp2r4EpRmgJAYeyx4Zk4QECROT4vQdHaEoGShgkIjjPRTUJogyzyLdA12iwGLeaA/M11NhQfGi6vRcF3Lb1EfIErD40jRujrcNFdk35b2YSb2FWGpfcpPoj3BzuivDpVi7y53IXpEUnQ4twJD1zDLLpmeHV8hVmwcswRH43dfr1Z37N/PE81z1vf7wJvij3+QP6DL4pXZ6lTrhMXJpT+kJhf9B6Oa2j9iwZCabuQnOcdTz7/2DMMS3574jQgQv0YRpRuGOhJQRC4JSnmdnvY053FKubbuJAHxlcyB9tuLHYwxlPB/DLnBRzERT17PjmOmHkBqL+wwq65WWbVdIqFrBtAwi3a3b3xRg/5YiYMI+hS3v84q4QOKBy+YQkOqMAkpTfVrKUnDSjYhwda1d/aTxNyFe+TbuNvcMuZo3xCkevGcKZCXNuEQNAjF5M0QHIm5ulY6JVUDu9S6jBfW4JkvYbyoTbTVKdG4fV73B3xnXe7e5rEhtFQ65WWIm4utu2tvKwvfjOUKwYdML4RtrxJR62xFuk9s8zRFLyyerVj2aKo9542IhU9ER3DZALsKjDIrbDm/2E3fei3HhfgALT6LmEng3KujVFxDMdJLLnxXe6l7t8qVLQBvKneVISyMCFYxdtYhxDllawBcEK+A2sSAAwn69k7Fdvem0x+55P1I5CCllCdNBG5szhBOc1Ee7h3CHviMd4KqteM+3DixFSj3ZsGp/vx8EOu1KQBynvgHlgEQRV3MoFffMYPVXkkia7yVb/uSnIYDqB5hW2WtO0MlRTv2O9/G83+LH0SQSbU2ndZAlHEnvWF/MFpUJEAoCsqQVS2X6n35dpH2ze5lvBZn/JHqRtruXCGI9nfLURgbKSyRrkjsqnf6xpGLGN0JxSy3fy6pSGiviUr1r1D2VZRofgHPBEF5+vNprVrLPPFcQSMqXbuyyUUebbjmwxXMlO6NQZ+0Hi8vFkZp2CLLIH5oD8NtZIIzuDAucFJ9aYscVZo1vEHQ8gGc2FxinbdaltCqHbZ7eLt3msdScXtETiqOdvZqgZTdwaylPWWzM5gFU5AXGULKITqGOxurTK2qsXQoRnHfC8hms5U64siryEDgqURX08xNB72iiIrSk8KvOZ1BvpoXooAFHaXrxa/9LLOO9Jnj78ROMcYDtALPh8gx6FWQC5GhVslDyviH2vLLkCbRQkKzYTyPnvYAeJPBauu9p/vfVmjhGFcjx6cLp7iM+gRG3nRSf6DWtC0FvmfZ9jxXVNFy0itujTRNBue9lGD7+bjUOmKjDMg+sWwvYBPDZO4KhMQ1Ac+HVdOmIQjAwY1f96ZW3AZQ6WSj5YqmEEIh/2r6juAYlDYaCbngSrn4u+eHf1/1l0XUbXNAzx8UDY74MrIQ6tLMm1ltfDbWjTcoob1SSK9Uak88P8RLnaIQ+1ceFHD2An26m+6r9b6YRoBv5FkvIjyYcJWmDTstlcNIoYJnFPwITyKelhAp28nrYH09v43vKXSpGSKnhapLocjItx9IzueV9mUJ/Yy12jz//PAV3uHzw2aihDK6QvWX9f/KhaHC1IRwWnWgNaGXo89RtJAUV+n0MHGjg196Fu7FzYrWj5Xsn4t4vV71QzLXcouN0Vx8t3ZArSWCLpcofLxnpIhaQ2KlssDFtPG5TUEfslHarrC6iMHMPiWuGcYesH4XcWozoumTLlbQ+pxseIJSu0iDymrsh9y1scAviEmPPnBL6TSyoeaYKTY0F5dbCvh7ucq9OV719HnU3w+nFJhal5L0sBCPkBt0QBb/mzVJEaUASjej7aJbX7dr5FCxerGZv3SGlU/xReUSIHDskhwG1AwPWdN1onGhQB7KOJnAoUcpNeRH5fTo8WXAZPazXI6wlL+TQgWKu/vKQP77xexw747S7QG5CdEoFV2MWnHbNFJxVNU+HEluQPqElKqRxpuqpcb04RYf3rRdgvWHwXaZ726PjT8Lc1qIb4hDLpQn78z71m5VisT/uB7keH4NKWoeEukj4qI0ebAZhoZd03U8v2IoPnotpObBu+fc8UFgWhMabwgbE6F6aCreMp48Ehf3WEwWceiAMThJsRuv6xYASre7GRtiCYp0PbPNW7AEr7d8CPZuiFmP98Pe78fNvk/6k2IAdrITVULm1b38WkcPTCkx1lgY4BiS//q5vHhD+867uRWBEh/zr6s49jZNI0GVwRMWBAEs0lgm9boQ6n+W1RY1gffq0VTvAcCKiBrzJnbIC6KipZwgrab1NhkT4KAF8jSXgZ9LBuWDZF8DIMH2exe+NZQizmGQ62zfRlTqbOIprcg0rxFqGsYqUYxq3hSd8CRuhaPe56QbOJA7ws9zUBOECJ8+F56mteEZGYs+X54X1NK4LJzSYFax10FDnGFm5hCc64VFJLgetov0VjEKYNNd0QtET4W+gDjE47mLyoLjLlPHrpFmcp3ONH+nnef12lZc75U/WxGc8Cyg6E4HtO0mwLmJ5KLmOugXF4em3s6RC/CRC5/CQ3FYBe+B+QStQ+jSLdgSQ1DMvn5Vy6N2Y/LW2yhb2aLPvzkWesyf/2C6eFWDE7hoTbozAmxcHE8aurgNrGNYX612Cq86vkL6I1U6pJCuIY6MXlsCwb3g5OPU91+vYwLXnu4TarPZpWks0pmF0mnxDqjMDTPqfq3NJuSZJZ4DBJcMErZqoZqRfLepJx8i7kWb0xXm/lA91MuBegn9jHrgRaaBo2hjrEXJIGdZrBL780CDrM+a3loahvotvd37lPF51/Z4xhVwwt8t0fG6jQLtTZ9X36gOwcfgOhFJViq2ifJJHu5uBztlQbufY0c0VCp+eoLAmoFMNr4xm2sCo3LU2J07OAiues3cOBfbBT1omeSJbv1kQM62mUWK8BrGNkyISfecbJdrV+CSExO1ZRQ3Q/hEwlK6ofZq7fF3XoDzF8Cn4Swlpw1roeCPsR9+3JII688KKTmw9O4x+8gHFYyJf0XCYjg830nQWTxyBGsNbHMODIFozCy0AgNogifavgeGId50dwMwQbkfd2hiI4F9i7Xzp/mF+DzOveCRVS0qtADONOrZziQzo5hKQRlA+lnGsdHwpfiLMCYLo/RMzELs1qFOS3AGxbt6GewLGqO99dJNYzTRHkGF18Z8G/2Sb7R5ArNo/GBgs43hoqcwFtIayGKWP/wResC0osXRTGsYACVhGyhiDHLsMmU1rxzN2tyOhMiI3f6WcBV1fMaUojYY1claba9+9IxrRBpErxqGOjscM/Y0UdyZIX3nId4RRDnuQYSaL4/QT1Gwzs+AFHJbVng2M7YbDqFiqxyq/xbTNt5X5tBXIviLWXTRK+pthpgzu1LU3P2iavmVHPZ+zj6wJmNohvoEPZmvP3aHkxjAAz680fINCgHEbRrwLU7qpbb/Fr3YETGTvc+COoaYhc+7WN1TAE27kSisIWAnYRE2L2Ykn+NSwEh0r1YunQrx/ndwWqkU9yoldbauGhwSOiLTSgSGzQacJOVIG9vwFUe0XVZCvimG6GLE0iTyEp8058a+eC0bVImr7JWQ5mcy0wwzNhxFAcTuCQnOF6CK4IFmzaEWcNnWk4XzPKeg4Kq7ssgkGfRoOHOdfzJxorvPHxX0W2W/KQnRhtFSCiR7zvoOvmIg0RqzYCISuKiVhH+7t/eMsbmPvuSTR/CtzNSCERXQdChHqgQOx2J95NkKM4OoErnF/CdZfNldbl1iHqYyZ/9HUtSDh8kFi5VNhDWI1yYfOo+jnEyF+17ylhQavXZ3ftwP1OcujaLpPfdsMqwiMtP8m2uZSRoF7MG4DQBjvsj6xyU27rprsIoVygmqEV9KPRKW7R+pG0Qw4y1WNoH1Ih0rOeSYPBqJWkOKqAVPa8mv4OArvC/XaM/Ns8L2NXisMdHcf0wxvmSGq5l6Dlu+xig0o3t81BGPaYK21KDSlbusIv13HX6Vtg0OfF4tLU4c96wjdIlj/wqcyOYXOXDmSLvkd/KMvnETCuu6+rbOlVBWu4Qp864JM8AeCiWjPhwCDj+6IFyPcGHKdz7ze5Mjycz7lvcIl+dKqcSjV5PdZq5Y86IO6/pymnzKwk/2M+aWejk1dAI+4TWoxgY48VdT1honIB/h6sRmVW9D/AswlRyFYOJaUGkZxBzrCJBDueQ8v4RGLJ3l9mi6TZqQ5ijeoiNMl+W5DgLzetzUxJRPmv5jsr+HvJux0bOd1f4Bi/htd1mpgTMf75w70075irbw0S6mCJez9agShPUjOxI8AuJluychvp6Nhd4bymfIVRXOlx5NO0XPBy0/GxjHGrZ+6f/LKgQtlzxmNHpMcYm1FRgD2lmdze5VZOQbXVgy7CekLum9P0j5p1J3F4o3+E5wWGUZrfquc4UW959lM5bZeTNCop4ejW5+gRpH/sJnEskBTqI+c02TgI8Vxd4m11l+FlC63Zbj6K++TJlOy/EMu64YoADyJkQZu3D8axgF/hCdMyfQSCEnSQ5MbeBoqzbGyIlFmLKtvJ5CIRibG5rNqc2LYXCBcUHpoKfzHG61s4LOeYp/Q0u+8zXOJ2r8AsDELGyGPhgnLVC+L0GiBa0n8SCJcbQN7EJbZOSvzLcAOKoP50oHQXbzHzrVvGbF7+9y2oDkRrYcTtAkiRKILH4h7DzN5BrrpyxTcWxzPT9UuDCYBmKS4H/Q1vkpjukLG/KRjWiq/5p4P9c1gePNKWrvmbgc75tascXjpdVDa58MvnuTlq+HACuWzEamnXGnSHrzldwprqJPKb8einq5HT/QoIKAZuaPmA7qZTY9ZVU/Sl4GtUYZQjRjchRP9HLx7sHVLjymbAAc86TSvEV3FeF4w2pB/y78dYOvpjs9rP3f+zRFeMBqNCoyO5wKmkakEs13YPdrsDucw5nA5OaxZgo7vekidETGbq3X4Yn8PSdyOOqGA6EJPwdITWMX4kmtOczpbSPOkkga/id0zKo3lt1xuHoA2uSNZU8aLKA9y2sQ0NVWqeO+kkuH7tlucxVuN/F2F0ro4pPIXkJV08KWEp+MXUQxTdQgLmbJQGNKn4Wkb4K3a9nSN6uAKSU0Mu1XJwdyddECVoCG3RAcZDk4B7cn3+vVFPYRFhh2SfQbDIf41I1xpuslRDWXC3rcwlPNnvM+QMcDt1xpDjm1gbrz+q+F3w6OkxB+eTTqal5tfUloaXn3i5TAkSQqG+ww4mPnm7+swoZhxOby3EJ2Ch+qWUOFxrE/lUkZGobdOGQv+lnwG53j6CObZXic8yvrlHlWrQJRsnjDb4/6Um+zt/g1D39UBKbM3weZ9N0+JehVHHEkOydlpClLi7sYgOhHFDnAT3elDzUmpStbk0Lp2eUZLc22pyTUCI/bkP06h/gkYIfcAlY6olrwwpLaWnjlyuhFKGlBAV1wttw9Ba7c1mdrSkfkUjJ3C04pXR2TDTbDyflbo3ZcZye2fIWeworej8fV0xbdNZQ7qcZMIP1M7eWX8Bd7tC+M9KpaRhKG36vzOkn4euy3TzyAt7lANgr0e4/sGokl6+HDygCqEj+BmHmjl6de17ABlQNGsEvuxzgFiM67lRGLQ/hQFI7+enlPNJjTFRJrznt72Ts4PVNnUcKhein2jDPRlBWj1nOmwDfsvIkkRGlCIpmJhY2FTZToo4SB45owyTfEIPdliuI4p26RE8rLUErGED9SepuTz4tbrPZhQuPvrmk8wg1YznPbdhrdj+TfaGHVJSduHqa4/IgRC6qcZWCl7PCAE4ekV4uUMr7QXlthUNZqc/hq/ClCKAgAbgniCAJ/7nAoyHFSxyBk728LIRwywp53NsqZKFHHrqMrPXPmNiJ1uwVfs36TG6yT3i9/JIVsbj8FOC9d5nH4ealA0n6cYnTTkXfoYkDhUNzk2euRme8BQeSINb+Gf+XSpIXaDX39jDxgwsyHZZIumcMARIBN4+ufcD9QNJl/grAkqaZ1BtMjUa7jMapqqGF1lsNq7XGOZczlafR3bOs/WbbqFM87o91NKh1EgvtwLkRLUhLJpBVhRkeeZZQ4Z8SkkmWCYpKQSuLkYxa3IrMhW2kVWu7YcH4TQhgdik6D2rS+NHnH1EAY6sk8cRDtk2RlbtFDtgRhyQQLUyLx5wbitNyI5t+9yHrkxY1OqCHpXKoiC+SQnOaWas5zMWtIsEE4htgahvBYk0g+A6T98mm4pJeXE5RTvrN8QaygFgrrGckXOuesEh8wwq4lFkIotOyyGU2B8+EFnPKduLTxUSMmxeA7UIuHZqo2M2T/eJUfJhd7YYkmtU30OHbj1Nx+Ht89UgSyr63qLK1nCqiGJZsMm769ThNsr3GvCHRbTwKodFJvYD83WeK63BHbZkmaNJGluzZVtBifIWD4GqQsKXklN3OfrMlF6meQRCTw8hTz1fIN41ePfWDiIaeSMPtJtUoNNZjwverlrAGcHEV0TIPPVJPzS38P2nlGuu5fULp7xgRyMR0NEIF3jMJBVq6wNM6jHL1v/21P+pv6HyD9xPW5coY+KxlXapB/T1TaQVlQM8ERNSDwaPn8B71YwKNy+5OFT5aUeT7cI/xFMA+h/zqNchgjEy4myzqb09beIPfHaG510A0K6hQCmEEqXjZK5OHXJYo9qfoLbtn2kkyJrRn/WG+EzvCpbM2wZUqnNHcS0RhWpI8o1ZfIxSlqdiYjKqXaxqXGzeqEDWr7rErT3AknIaqCXCIri4NUFOlYpJEEM1RkBIE5F5HbvimEplSRHyHfUGILN+btVLO57AknUOJ/k1X6LhrAJt16bK6LnrEY74d0koR3EyPMG50R6ipy0gvAnA4qPzw6nHzG7VceTJViBCW3bzXPK7a8DkQNad9hvy97Gx0rPZodBtj62meBXFF8RIds9wOD7OUBN5WnmVwMOGDYyHiYOueayXD7lRAvclxYjeCqQz8TpkV/wGceYMLN3qGdca8p8LaqbVophFVmDkCwM60q7SNR2JCSmKhSzvi4ziLVlVFWG5+nt8zQdhHkHSFZQ8zoo2gM5UgbXkygzCUgLtblhcC45qqySDYERsQOUKGmJ++JraEOmg1gx9qAUhGoI247DaQ39YNNjwRic31HLb0vmw3Agr042erBrQP7n2XUpLZOjzIv/1p61JjTHxqJRcvKo0kwk9ycquxG6qvpPGTq/yrUGGsTushEpHTcP33CoAziukdt6fx+RxHOzro3Ilcjxr8RBixOktBhcNnPoDtr86bpEtTNo0NhATCV0wo2+AkkVPHlpYMRpUT81ZSjZc0T6QbVrGaKXAxEYcuowPSijmEbzfUzuv2Tf4L9ctk7src7oiY1yC0RqO1/V+rQDTiVrJlzUoEom4N4r5SxFN+n1Yq5dTvGI2JLLHWd6blXp14FL+UTO2RTyJBMGFu15BXz2cDGImtlbGf4QmBWhlIY8xAGvgW3GEhhlY3mtcYSsf2v9FTswwW1iyju5JLrHeViA1aLH0FNSB/mJkM4SdpPi6l0G3jr7x+Y9GhTTpLY1t4gWRKKQCu81FScxiFBFQG8eTvgoj5rasFk8l7A79EAtKuqyuImM4HlyqiLZiQO+CG7wQWFRXVnk137b7KyQIgWImWv3ZUgwpRJK5ZupBk2dAlappIehEmk3q7w63TkE6GjxXfkwm3oPKSQr4wQ1fKssTR/vxz2wIPjiOd+9QWNdYr/cLl1tVUouHtKzKwUITrLhd37UFvsKlXXu2mldHRT4A6koVOyGbUiWh1dY6xVRuYynGG8RmoU/q2xVLBw5BkeqUPKJXfEqT6BWCv9Zt5U/14FcdJCJhEWy+UKBcMY3jNgi04qfKvJEi0r+qliHSHMuyLaW2llWdrGX14TtUDmpYwqBf17oqIQLBDYuY5pCpiRimjblNcEaGlwoXE9RWjEnZ6l614tW3LVVC2q3d83fs9vendCLPNIZVaggIFslDwqY7UMv6zRs4nB1iSjqfREP4FC+NylMfKTb5chd0MZ5LnUGgwhHOlYjkoJ3do1tDF55IBykCSYASEt+flDam2UotGofcefU14/n1deswJjavu/nx3JujPdxL5Rwm6dOLRKR/1PO5wrxA68EgfAg3qhWPjsLQAoyQjbuXe+whqsXb8IEC6RtIeOB2jbpRDra5srQz6SDxR0tgT9YaI9ZOTrkRPcX0x/slYJDH5BUw/zxwtya4VBf8XoIsql0e/aQsYXJ8C5R1GwouSmrjUjvz46td+zucICphMTT1Ob4d50=
*/