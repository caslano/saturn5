
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_USE_UCONTEXT)
#include <boost/context/fiber_ucontext.hpp>
#elif defined(BOOST_USE_WINFIB)
#include <boost/context/fiber_winfib.hpp>
#else
#include <boost/context/fiber_fcontext.hpp>
#endif

/* fiber.hpp
iU66ysRNUL7iudFL+NUdVo+lJGnOZOR46N9+lg/+zAu84cwN3vwWcDYBb3CVJt/UnPzANpl+jiRrXbi9GiIQGu3YfNka8/hWNMDFhhkSswIFb31sFlI3DYm/uZVWdl1IyfbeR9bdN+x7XYAzez4mINXFOYf9cx5vw3XqcznxOHHx/zjmq7l+/Ly+9ber+wDGx7HvgcGRmlBaf1gfAO89SZLcasDulNc4Dqy9XncIoJ6J9o3HXvigsvZ9nV6XKTsM18/ivafaF5SymNTgrWCVRaOwU0uKosqh1KEktsRTxf2Wa83UOyalR5GQ5Rl39As20w65SjmdO2wxYdVYtOQkqoPzFZ3M0JETTP0JnPZcsutcy3roRKM89BWYLCNX0FFh+7oIwaEB5bhoda0IFmbTfSVaBaEh8IKP6psYf23tA1EmMftP0FK7CsEtCNZfWldtFXqoyChLrWxm/IG1QtHVPPrxPu/ffBsnHygo97dJOoqdCxU3LwjlGO553zYf+IUXOCprnB9do/teR/+L92N9F+0N4+ePsPnvPcWy/yKjT93J9YvScpnbSKD201tWtcbHEvomeO/j8MwYCvQaXVcEahXCLA1yqBF3DeXjtZREX7+2c7PCoFnTjhaSaHovzFv2eRKwwVHNxKwZx8As+jL7sq3HdUMdwlwACYVARlm8r3A2P0D+tduBl2U5B//j42vAHt/let0oABFRMaWR
*/