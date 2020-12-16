//  boost thread_clock.cpp  -----------------------------------------------------------//

//  Copyright 2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_THREAD_CLOCK_HPP
#define BOOST_CHRONO_DETAIL_INLINED_THREAD_CLOCK_HPP

#include <boost/chrono/config.hpp>
#include <boost/version.hpp>
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
#include <boost/chrono/thread_clock.hpp>
#include <boost/throw_exception.hpp>
#if defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING
#include <boost/system/system_error.hpp>
#endif
#include <boost/throw_exception.hpp>
#include <boost/chrono/detail/system.hpp>

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#if defined(BOOST_CHRONO_WINDOWS_API)
#include <boost/chrono/detail/inlined/win/thread_clock.hpp>

//----------------------------------------------------------------------------//
//                                 Mac                                        //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_MAC_API)
#include <boost/chrono/detail/inlined/mac/thread_clock.hpp>

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_POSIX_API)
#include <boost/chrono/detail/inlined/posix/thread_clock.hpp>

#endif  // POSIX

#endif
#endif

/* thread_clock.hpp
uKS/CppYI/B3juf+UuKEWp1TtMinr6/QuDUHqaHMzz8n3b5Zty+7jqV6s41upv/SFF8NcxHruiIzk+wer+ZpoyXNu8N4FU87DvJ08+5Mp1b+Rt4rU6lL3/elzoftvDvxkhfGxREyVB07fTrjJEqbuRz+H8U/FrqzSHUlnJduXberJCm7S1BmhuoIZ67xtAXltjAauihzzEfLyG5hYVGhVSPbiY7drO8ajBNbztXOwpxRjhjsDQmPLMsWF5DHJP6Wn5Q8ZakuyE9/OLs290+JV7tU7au0+nazrTRnW6nD/vRi+u9N9K2zhqzxw3AxXmOQ1h/QdWY1j48eo/GpxNuqVuH/jZ4+jukr+uvgdfnslP3vo3cIhd7wbtatO12S5fopo/X+wyjXBZZ66mQwWcr0GvqhwBa/R6M+pNTPE9a/uf4a9QyLtVNC5ZzQcvLejaX/Cvrrfenbj7egvy33d/zS+vcoN45jxllfV1Pznu6pL6s5h3h/MR5St1K1/HXuum4GSJxL0FdGqrZwrBumTQrUu7MtDJL9PVQa/u8Exz6f6Sqe9ZiA0qydMu2Ab3u/h/57E4Pa7/OhXdj7gBm+5T/N1sU4Hm939dqcowOHb57x99M0WGm/cXh1lNpvU0dITSi/Qcm3sABNaCdqc7uAdcFu1BTCiaawJzgZ7AU+CfalJq8f+A614oeoDT8KDgB/oyY8zHBpwiPAq8AK4NVgfXAo2AjM1Npsfk8BCyzmOBpOjWEO2ITaz07gGLAvtaFZDKdGHN807DXiE6n1zqNG/BpPPvAd4vxpxMMdfE/ndwYzHx281iddRW3nOnAINZfXUoN5EzWbt4FF4H3UWs4H36dWcwv4PLWWheA2cC21lhvBj6id/ATcQa3lx9Rafsbr2Qt+wXrax3o6AuLaRavdBfwO7A2eAEeA34MTDZdmugCMAKeDkeCtYBR4N1gOfAaMBZeAceBKaqffBBPADdRQbwXLg7uopf4OrAommGUIXgDWAJuDNcE2YC3warA2eD9YB3wYrAs+BjYEXwYbgyvAZPBtsJJ5XrCJeV6wGbgNbAHuAFuBn4CtzfyAbcHPwHZgMdge/AHsCP4LTAerOF2a6AZgZ7APeCl4KdhPa5/53gXmWmifb+BYjBvZnm7iWjQzOXZgBjXAN4PNwVu4tsut4MXg7Vwz5Q6uwXMntdJ38/64l1r+mXptHL4LgdMs1sYZYJY/tcvJ4CCwCjXMbc144EVgDjXjQ6kVz6JWfDiYy3gTJB7HDJiO5VDRYk6wAt5nk3mfTQX5/ij5uE6PdeBzuJRZ4FiH0YZLsz0OjKM/kf6WYC6YCU4Ac+jPo38KOB6cSv/3Uv589gMP83zRkl/XNosa8TnsT+f6jemYx/t6PrjIa62iJ8EtHMuxg/5P6f+C/v306zEezEe2xXU/w3w8B6ZyrEdHjvXoSk15T3CJmT+GX8Hwq7iW1dX0nyqFfm7D29DWvv3X10j/1TR0Z6uNDnknQqXCXQQ3EC4P7i64hXCr4LbBHYFTG/4+WujgFtz+btufZf8fIdb/c9P/6/X/fe3/I/I4///H5ZVez30un683KpLruafvc9s5kTBg1Xllt+480zlP+23SbeuZLvE9/gLtD40bs0/bV2zXpW/L6xhCHUMjjl2v5b6O/V7X4bMqveWa9Ixfw3YN+hGyv6we3/6Je3x7Kb6TeK8tP2S/3/ciXsddtNeP5Hfhq+A+r2w+1Pja60f41IF4mUd33EraZjpf/B1KZat3pU3RtvoF4u9Roq3+RYnTQmz18s2OtvqkUsyTFe9TNiNHlMZG35hlVWwzZ6A64G2jH3FG9vm7bOzzsQdKb59H3BLt8/EHnOdkn3c=
*/