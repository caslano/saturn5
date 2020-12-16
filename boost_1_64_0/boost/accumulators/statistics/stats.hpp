///////////////////////////////////////////////////////////////////////////////
/// \file stats.hpp
/// Contains the stats<> template.
///
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_28_10_2005

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
/// An MPL sequence of statistics.
template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Stat)>
struct stats
  : mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Stat)>
{
};

}} // namespace boost::accumulators

#endif

/* stats.hpp
5FEOD9sZGictNURGc8C70J41b5SjuC8PODry+D3oSASyqh9AaNJT2blk/fY8rbL9Yqejfh5zEkCFEFAbvzDZjB0bYdK9tyHvtAIegC/ngLX495J9TlWFv6RpnvZRmb+99Aj1wacIWqZFNJiVq+ANoeZv1gg159U5uyqY1n+RmjPIYI53ZYaXbmQGRXhr007N7YsPpv8qJaCSwifyNli+IkzZGeySnmSGdB2+1AvLRDkMnDHsnDpLAeeVNUcsSOZ+L1+NhfAYLPO0lPduEXjHNgUqnnnZcdipU4T6I7LAINded/JMR060iF5+pD0huAajv8pHEX3+FSD4HPHuF0H0fyzp+e8Gpodb0m8Okr7/sD/97lWB6ass6djzB75/s6R3fT8wfa4l/fuDQd6/WdIv+i4wvbclfV+Q8hdb0lsWB+m/Jb1mkPT9P/nTn/s0SP8t6Ws2Bem/JX0eVoeK9ylzdbrXlcV2jNNMvxBO30ZE1KFNkpOX58IVmvEPF8a/pTiaeP4LuN1foTK+NK9Pzn7+kfa8mzAHDvfT6oWnsVwGOd8OcQ0VSt99SE/CQVkuWIvnWwzaFkbKvHKJZ0fIOVj/KfeUL6dF4s507ydJTTz1g5tJYe0UeIlN3IytXyJkZIfwSnRKOXvo1PHhjAjWT1mX5q1b4BuSJfgA+6fITTDhEyf2yYLbj0opynFkjCnCGu6Leb5H4xByjQ4NIHfKL7MWUQWAmTV3zG5w9aXfrj3/Dw1pBftjWbz/+9FkG3nonH3Y8jS2moGHRH9ljY7v3LEhR+x30xan6wlScyW9jpitiAXK2/vtwKwQMli7KjqkcJXW8lBpOzUdZPFjj1qzwPi3/Y05fFi6VgdFUwPDAEn92toPIz/58LHiuYTzwpD/s5ko25N1F7CZpyqrcg1wzvvNR38QCcjFe0wxwwiiG3ciHWB5FlymycPJsgSaB3ddxF77Afk4iB6ROwGIutTND97Z7m+7w3IP4wsxH4K+RSPrrvI9pwHfkYPmjMQYETg9/OAwLB0NWHaImaGEELlVfq6vH54/YJ5J0wW2qt0hm/e/VW//at2+Tdq/0NJ+k2q3j/NRVqD+/v7vBRpmGCv6aIZxPzjZ+drTcuplNPd7S39PUH+vZbUZJlV9K+WmnifuFDaRaPhH1QZAksTXGfjDQt+wLOGZZBEk9ytUDLvOKV/N2uJ/z1OVpdXa/1KBDn4HeuvOr8Y0Dao/Oszgl0ukUDrpw/IR6XAaOWZ5znBe6Iahz50qbClfvD54H0dDqCAW3W/A3rG3dz31bDj3DF7rlC8LyMkgfomNhgN2GZPqeRrMOcnIjkwHa13pIt560D2mb5y98HCLlI3i/huv7H0xryUx43Ogdl+Rmo/9Xsr2WY+U1hUOm9cXu5pOFk1GIOi3cBus178D/vWvfkGQ9d+SPgF7zorr4zid7nUlnXN9XKoZYz9hjKXLeX3cAb74mOrwedXWx6Ml/vVxby894rveDTLiBFIw+5J/kRpU713B+FvSufjb4zaTv93Qyz+f+x0U/tbidNl58rcGJSZGz8Vfapfnb5tT/fAUfv8r+EuS8Jfy8OSqKsMDlRErv0u1wNOu2vDo/Z+y8LefXHrAX8aOPHj+rd+Z/MDIXLBEMgfSR3xR4PsPKZ+ftQNVPGxUMdNkKQH0L/mhWg9XTpdi4lvG40oUZ0eCQu+JH7KurwdB1bRUy3SqruFirn/fCv3O3WHSb39tyQOHlnhPW6JO8sPyQTRhXwNALZ8UsN53kmD9gNDrLSdMel1RvfeioJf4wPdYQ74NxIdJD85y+LjoA8bHWCoWeaDa+ND8f7+FPvZcYax/pyqjj3ckPzL/1ci88M+WzAE=
*/