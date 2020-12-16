//  Boost string_algo library std_containers_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_CONTAINERS_TRAITS_HPP
#define BOOST_STRING_STD_CONTAINERS_TRAITS_HPP

/*!\file 
    This file includes sequence traits for stl containers.
*/

#include <boost/config.hpp>
#include <boost/algorithm/string/std/string_traits.hpp>
#include <boost/algorithm/string/std/list_traits.hpp>

#ifdef BOOST_HAS_SLIST
#   include <boost/algorithm/string/std/slist_traits.hpp>
#endif

#endif  // BOOST_STRING_STD_CONTAINERS_TRAITS_HPP

/* std_containers_traits.hpp
PqVy94afJpPi2wM+ZEJlu1T9J5bgfPzse3jlvwKHW/x4XuxU+4n91Af4hboAv2SAwycD1e4FCOvk/xWAVgZiQDE/hMHVYFw4rov404Sl/Yrp/cz0lcTaFcT0lRG/U2F0Mr0/ExvHh6HRTguMX3yK8zg9khlM1CdqI87jwu9k0TXlZ0GytKywivdamireV1ao3l9SoXTMIIOJhsD4Wvec3P6Rgv6nNOuRQ7lwqmSno2SdLpL0aJ9S8J7cpCcGsX/dlc+fz6/2qSeZXl9OrHr0cstY0rOfMpb4MSvzX479WiFj0sRA7Bq01EjI/03uOWM0HIiCLPCEYqS9Xgq7bgL4OAyUJfIZDUVzIhHRoWhFo8yGivhrUhNPzkVGX1yNysbWeV/k4g1oUJ6goU9H/Bvxyq22iV/QMu+Ivu1/TwHe5/DoxQsiF78b8dOOJvFIA3IbQ2Xvg74aTMgW6cRuVZeAUTBpqDY/bubZZTVSNS5eAKSKavznp+MNB54pstNxp2akYoMv4n+X+SSUseGUfD2SOyig2IQ2bIVBS5MfR+zOQFWu9kVcaiaaZU1EHXja89B0zDk1TEXtCdWIjMgYKEeXottUtJPlZjjvHrmfHXuA1y7/tzuu0/15Rz40txkH6Zy4kiMQ36LZfrgCs7dAAELuWeNVDHNNDDQjDN8vXRhAfjks5vQgoGmYEfq1K3qua0TU92vXOTGnA0jgHGCdkonqjOlfONpwB6r/oCKmYzp3UBE1tO9BRXSCKw4qYgZ46KAiZmImqiKuRsQHKOIDBxIRalA9TC14NOBC7y1QTftj/xn6g/tmTzo38BdOEw0cwKQEvdtxcAlwU0sStx5sEtTokkTwYJOg5pckMg82CWIESaI27SCTIJaQJG482CSIOSiJSv1golvNOfvkvTIz9GAkhaygmQWpbP390aP80dHO/zjnWv+CH/aXb9yTk1b7WfJ3gvvKwjeAFIp920X+nxscabIl048N4dXGtgpjsa2PxwJOrAtV429hRSyIqJOr08LVLjwX4uDH3hr8LfpYd8/UN9D/wfahtEd8ysJg7BLX30hTNy7sCMQu8QTHV0NzGqzHyh3aIl1bhJyG1IMtFp4XyzV8bn+T4YgOM6M9fcawD4PjawT3HEwyGnVtIbwrYDV3TjPwYAFx3hkd9qE/6rwTuO3B8XHB1ZEu8BABiEjaRm1XqNsVKrKPXUAJ+4A4jFG2jwAKij9kJaLViIzyQZ/7+mcPXewRlmuAuxbK1q/vjAvEpvQJsevseqf3Rmz7xWn+wdOO0dkpeSCW6w2V1eJegl39MnHmQfzb+dAnzY2P0pbcwSlIK4BERtQCnbdaRIYPRgQKKESsyPDT6fXQyPAz6Nk7MnwIPYsiw8+k52GR4UPpeXhk+Fn0PCIy/GzzemQynwjRG4aPS1N+v357P3I28o047xaKuMXybsTF8E469kiYtc+H6h0Z6WRghgJmMjALQBcBXQzMtu3OI3pERuYAmEvAXAbmdQLzpUwj3box2mMsire4ImM8kZE96ZWVqZG9ImMO6TzYSqr61y9hLPvGXxrUiQycySmnG5pPPzYzjUvQoDlK/D9qGOaM/vH1toZhrr1vzr+3YVjutItO8TQM87RvXFb7WXYGdf9nQ+p5nzcetvasQDRY93ELIccLKuSCeJ+osBw+GnrBObHc6iGNU7XEcHSGhuj5Bcb543DI8EgHvmn/A1nPBtMmrmmh2LQ+gXCifOrh50LUw4lK+VQPTjaalx6TmeaYMY7d277EHFu2hg9M15rnACR8yE7ClpgngUhmI/FLUbYbq+rRzGB0uAt/HvwV4a8Yf/3xNxB/aMf1gXhrJu1ULOp0bPHBQyg=
*/