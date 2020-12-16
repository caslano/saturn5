
#ifndef BOOST_MPL_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_O1_SIZE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/O1_size_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

// returns sequence size if it's an O(1) operation; otherwise returns -1
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct O1_size
    : O1_size_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, O1_size, (Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, O1_size)

}}

#endif // BOOST_MPL_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
EXm04ALAIPJJK9yZYoVv2Gi3wl9X2aKSjY4XQGpaqK71c/zLf3Tn19lFGIgB7riNdhfhYEUgJp7FcJztp3GJFLF+ejYI6G6ObrB3c8cG3c2QDnoCCONtA/FHTzGAANkgLzTowQ12G7RUEUiI6aJzGdxm8MB0FchawLyHNtgHyMsVgV4ZV+n8kSg08aeqoL23YzbYvbdhikBUnD46ECKjDfGnq5AIDYL8GOvtGtgOGBoRikvHsOAKdRJ/ugq9oYEwbuvX24eHhYpAXEYVejsJ4ryJ+NNViIby0OffWW/3XcYrAglxeeh0CdtaHPXQVYiFBqLPj1pvl78hikCviC2dq4EIbib+dBXiIR/6vPt+u3FsAwyNCJtKNyLCS91A/OkqkBlDn6+93z5yz1MEYjLg09kxWJodxJ+uAo2x6PNr7re7lRcrAnH2RvEwFYbBRuJPV4FGQ/T5EffbTUOuIpAQi0KHz+CjbSH+dBWoEdHnXffZx60dgKERMdzR8SBMINYRf7oK8VAu+vzH99nVue4+Z3VuTVVnH/r86vvs6nwRYKY6796ZY2rzJtHmNZFXbuD2ykGXH3afXZuzATO1eXdbjqnMHaLMyE/KnIsef3WdXZmfX2dR5t0v5pi6vEV0GflJlwegw+9ZZ9fl2essusz8iyq3iyojPzXWQPT31evsqnzROosqM/+iyRuIOc0/zZjQ3Yets2ty9jqLJhP/qYqM/NrPe3WtXZGfB8xUZOZf9LiVmNP8U/uhs+9Za9fj2YCZesz8ixq3iRojP6lxHvr66rV2Nb4IMFONmX/R4kbRYuTXLs5ha+1anA2YqcXMvyhxiygx8lNbedHXr95rV+LnATOVmPkXHd4sOoz8pMO56Ot77rXr8GzATB1m/kWFm4g5zX80NAB9ffW9dhW+CDBThZl/0eAGYk7zT5Mt9PVh99o1OBswU4OZ/6QCa/7JCqKvX11jV+DnATMVmPkX/d0h+ov8eji+Z41df2evcdTfrlT9zUJfX73Grr8XqfxxNQ7ERYBEgTsbD5mXnBEcusauwIMUgYQaBxKQoA2iwSBAGuxDb3eutmtw62rVgmoc6IUIrRMVBoFiEkF094rVdhWepQhE1TgQpX9hgxKqCtof/vpquw6frwjE1DgQo38xlPXqKvSGBqPDD15tV+IsRSCuxoE4/au1GAT0aNzxY7sWtwCGRjTHgQT9q0djENDe4FIgp6pxDWBJb5CGMsgRb3nXVSC/EH1+OZBT9fg8RSCq3Loo/QtFSOgqkEuDPh8G5FRFdikCMeXWxSSMQvzpKlAjos/b77FrctM9qhGVWxenf+GZRnUVoqEs9PnCe+yqPE0RSCi3LoGxoJP401WgsQR9Pv4euy6fpQj0KreuF4PBFlFmENDO9ZB77Mr83irViMqti9K/WptBgLR5APq8bZVdmxsVgZhy62IYDppEnUFAq/O8VXZ1vm2Vszo3pqqzD31+8Sq7Op+hCCS0PYUciTZf/N6lG1mbB6HLB6+ya/O7K3Ubwp6aYrRZlBn5qbny0OMvrLQr85Mqf1TZU0jRDtFl5CddzkKHz11p1+VbVf5Y0p4mYI16Nf/kz6C/L15pV+UzVP540p72YjyLav5pPEF3D15p1+R3V+j20/5QVCsy8pMie9HbL6ywK/KTKn9v0h+KyXis+SeHEJ09d4Vdj29V+aNJfyiOqU1C80/+IPr64hV2NT5D5Y8l/aEEVKBX808CiL4evMKuxe/erdtP+0O9mJtFNf8kf+jrF+62K/GTKn8i6Q9F4Y/GFP86EjT3brsO36ry9yp/CGNBKzGn+afBBH198d12FT5D5Y8qfwhDwTrRYOQnDc6R+O/ddg1+d7k=
*/