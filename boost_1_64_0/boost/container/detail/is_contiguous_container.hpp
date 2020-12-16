//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP
#define BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//data
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME data
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace is_contiguous_container_detail {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 0
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 0
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

namespace boost {
namespace container {
namespace dtl {

template <class Container>
struct is_contiguous_container
{
   static const bool value =
      boost::container::is_contiguous_container_detail::
         has_member_function_callable_with_data<Container>::value && 
      boost::container::is_contiguous_container_detail::
         has_member_function_callable_with_data<const Container>::value;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP

/* is_contiguous_container.hpp
aQNMTebFrNyylVtgWsFqmYcPgcWT+TLbMH7kR8xBT4Y5/E1zf9QK/y22ARIzmUxS+Nvef6TfP24ksEwW980Cn40eXWh9JQ4yzP2JdIBkyeIjF2HK8f/ZU+lQScrVZxmFlixJJMOaz6RjJaNyln/EfiYW91w6SjL3y7J7iLORSeSFx4tD2kfyokG0vNBUEvmC/95HvpeOliT3+FAOplvoKjEUK7R8MheDz2Ac87q0/2b7gc7NZ4+8ImHxgnUbevQLLFGwBVti3GBJgv1v1ZcbML1gjvuxkbAUwUI7znwDMwi2etsuByyVDP38ZjNbhPbEtcfK7KO0nyS2dMRH2BsyvNP5ZsrzQ0ZgzXwW94nWbK2aO7DQhkpUi/+zLzSHxY+6xcP0ZHbXwl5/lVaXaJsdLQMzLCs6dr+bqljMDpiRzIPZqjPrmsJWkuF3qt+sZO6UdJiZzJ3FhT19GgTLJPNklrG3ezAsm6wEW9PhWacjzEYmY3Hpa3/6ArslxN2YeHgbLFewIMvmVTCHULtP50NbYJLlNFsWF1L3gz9MRsbrOzi0kgamEOxJo02PYeXIirM1yx3y+gOmJOO5nCi7dwBMTcZruD40sAdMI+RZ7kS4H0xL5s3WbP5WNxQWT+bL7MzV86NgeiGX0bVbboMZyPjctxl/uQxLJeMzqtLmUnGYicyfWdsS4e4wi1BD6xWtLsEyyXxYXK/L7RNg2UKee/YYX8NyhDlUryVZC8sT4n5+9udjWD6ZH7PSv253wOQrnM+H+k0r/QKLIvNktrDq5x4wFRnvtaL/GwdMS1aJ2eD9m2W47hqYSYo1o9+gvDsC20OG74i+WdzRzl6wTDIvFtd+2dBLsGwyH2a1Ms7nwHLIZMyul5xWApZL5sr2G+PWdifMIcTVzy2ZDJOsdM4ltM8xX5iczJOZdpDlD1gUGc9zRKu0tjAVmS+ziWP0LjCtYH9J/TfDEsl4nv1mno+CDSXj9fXNci+ApZB5sLit+8efh6UKlrr23huYiSyE2ZhXU0/A9pAVZ/vlna+bAMsk47NtkhaTDrOSubM1iw38ZR3MRubPLKLHoARYHuuntFiC5OQZTw0sn8yLmW3W5Aow2Sp6dmKWe++aHqYUbMLrn5rCtGRhzFYok8fAkshCmc3J39wdliqs+U/W/MEwM1kIM0fdcTZYtmBxr4Y+guWRKZjdGdiqKky2mnrGbFfPz6VhUWRyZp3udrsDUwv2KXJzMZiOjOciXTLjHkxPxutrqI6bAzOSBTC78uPpmjAz9oMVb3URZhVquP1nm4GwHGHNOWdCCmAOMj9myzvvvweTraF3XcyuHtmVA4siC2fmue+3H2EaMr7fjDsdvWHxZApmibEGDSyFjPesR9Ptv8NMZDzPanN3T4FZyHg/27R81wxmE/Y7ExyaBHMIdkn3SQqTp9MzJbO3R7e+g6nJeH3tD2ztDNOR8RoWnlhWC6YnkzOrqY4OhaWShTJTrZCdhZnJgpm5bey6H5ZNxudQo0vTKrA8sghm90xz3sDka51t/vmfdTA1Ga9v2vUxGpiOrCyzVX9evQczkCmYTWxxeDssnYzPqPeqFddgVjJvZv36lk+H2ch4XwbW2Xcd5hDMXnVKNEy+zrm+Z5oWn2BqMt7P2ctnqmDxZGHMalcYlw1LIQvh/eyx2AYzkfH6FDWWd4FlkgUy056uvAVmI/NgdrZPyBWYncyX2eb6hw2wfDJ/Zk1DW/SHydc7x9XbP2oqTEnmzmxovTUamJpMwexU8p/usHjB/vyj4U1YChmvvVj97KowE1kAs41nA0rDLGR+fEa7zkbBssnCmVWOS/oJlkdWitm8gyMaw+QbnI/PaOuJrzANWSg=
*/