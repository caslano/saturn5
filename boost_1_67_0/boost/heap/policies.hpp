// boost heap
//
// Copyright (C) 2010-2011 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_POLICIES_HPP
#define BOOST_HEAP_POLICIES_HPP

#include <boost/concept_check.hpp>
#include <boost/parameter/name.hpp>
#include <boost/parameter/template_keyword.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/binding.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_void.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace heap {

#ifndef BOOST_DOXYGEN_INVOKED
BOOST_PARAMETER_TEMPLATE_KEYWORD(allocator)
BOOST_PARAMETER_TEMPLATE_KEYWORD(compare)

namespace tag { struct stable; }

template <bool T>
struct stable:
    boost::parameter::template_keyword<tag::stable, boost::integral_constant<bool, T> >
{};

namespace tag { struct mutable_; }

template <bool T>
struct mutable_:
    boost::parameter::template_keyword<tag::mutable_, boost::integral_constant<bool, T> >
{};


namespace tag { struct constant_time_size; }

template <bool T>
struct constant_time_size:
    boost::parameter::template_keyword<tag::constant_time_size, boost::integral_constant<bool, T> >
{};

namespace tag { struct store_parent_pointer; }

template <bool T>
struct store_parent_pointer:
    boost::parameter::template_keyword<tag::store_parent_pointer, boost::integral_constant<bool, T> >
{};

namespace tag { struct arity; }

template <unsigned int T>
struct arity:
    boost::parameter::template_keyword<tag::arity, boost::integral_constant<int, T> >
{};

namespace tag { struct objects_per_page; }

template <unsigned int T>
struct objects_per_page:
    boost::parameter::template_keyword<tag::objects_per_page, boost::integral_constant<int, T> >
{};

BOOST_PARAMETER_TEMPLATE_KEYWORD(stability_counter_type)

namespace detail {

template <typename bound_args, typename tag_type>
struct has_arg
{
    typedef typename boost::parameter::binding<bound_args, tag_type, void>::type type;
    static const bool value = !boost::is_void<type>::value;
};

template <typename bound_args>
struct extract_stable
{
    static const bool has_stable = has_arg<bound_args, tag::stable>::value;

    typedef typename boost::conditional<has_stable,
                               typename has_arg<bound_args, tag::stable>::type,
                               boost::false_type
                              >::type stable_t;

    static const bool value = stable_t::value;
};

template <typename bound_args>
struct extract_mutable
{
    static const bool has_mutable = has_arg<bound_args, tag::mutable_>::value;

    typedef typename boost::conditional<has_mutable,
                               typename has_arg<bound_args, tag::mutable_>::type,
                               boost::false_type
                              >::type mutable_t;

    static const bool value = mutable_t::value;
};

}

#else

/** \brief Specifies the predicate for the heap order
 */
template <typename T>
struct compare{};

/** \brief Configure heap as mutable
 *
 *  Certain heaps need to be configured specifically do be mutable.
 *
 * */
template <bool T>
struct mutable_{};

/** \brief Specifies allocator for the internal memory management
 */
template <typename T>
struct allocator{};

/** \brief Configure a heap as \b stable
 *
 * A priority queue is stable, if elements with the same priority are popped from the heap, in the same order as
 * they are inserted.
 * */
template <bool T>
struct stable{};

/** \brief Specifies the type for stability counter
 *
 * */
template <typename IntType>
struct stability_counter_type{};

/** \brief Configures complexity of <tt> size() </tt>
 *
 * Specifies, whether size() should have linear or constant complexity.
 * */
template <bool T>
struct constant_time_size{};

/** \brief Store parent pointer in heap node.
 *
 * Maintaining a parent pointer adds some maintenance and size overhead, but iterating a heap is more efficient.
 * */
template <bool T>
struct store_parent_pointer{};

/** \brief Specify arity.
 *
 * Specifies the arity of a D-ary heap
 * */
template <unsigned int T>
struct arity{};
#endif

} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_POLICIES_HPP */

/* policies.hpp
vmkk5BOF5yCdMaAxIvcNujUr/cMjfQW4axKIGXbdrlEoA3OemDtV6ubIgLlU9i1QNgFsj+uUoX2trQPu4sdsCa2FGmGv4S9LPcr4I1EgIMiQpFL3CfGROPXe0X0ModVKXYcleeXBDkjmJVYdEH5Nkg2hHwIaRTy50SyVgIykwUrg4c9x4O0Ct0ri281u8bmrs88/LlijgdLEgWsm8Ucwh3f7Copxckzof6RrV1TxIdU/falA4sneYllvym3OmEPIo8hjy1f0YSb4u9pn431X4TvAbbcm2ab+vXGjuyabnC5vZSPOfnOpSGGRNLA64n4YqOlr5B90ypzWooM7Hz8+GmVChBLbFpP+UOQu2YRkrPkpcad6GSo07GtLPRWbkIA3C6dLUpjpZbpVjfYTIiGZLIkdgFm/Yis2qxs8yjmbPQIrTprx4+mqYK1K65jM8qZsvwQTStnNd01h6sQi2yCtXXbWKAiiRTCZhXdFvn1Wx3QtB666qKHKo4pS4PbayNvyIZ73yeDw9qW1FKm9DD6jpehKGLMaP/QltsOAwfMytByPP0YauvOljo1mIiGPQRbfsnErRwV058tLquiUzDCFtlBi1W2OoHyR4VQ3EcwmphdzlqfLgSqFdEKBpf0Zax7OPoiQAN8vhW9qYp3ExgnDQzO0590kmI500GL5fMOS/5MDKEk/AE2m0HWlA56cJojGKE9Nk7bVpSXidnNJ522Ui7j9l90bzQZar5UnUukpOK0MiieqQeYDEbn7UJuYVdwuN1HYCfnIaRTi00hrunFLk5dPSBTqW16HWWvNbMmPyBuduA/XbHj/9CfQSTSBf1lymQj6uIyE+3wZWR978wUOUBmK3ZjyVaTw3R8BHb2fJt4Ue822S2tbUIajSBfxevIKNFZ92XOYKyPNt8LKeMXEtFPfze38Zdk9pNETVrmfCzPKoyNNjwrLhzfmupw9UAoLgcwQcjj3Ya/Ow5TtFfHyAXigNMTSS39od0ZBeAb4iWdw3kDO5ArI/sxEg8mEj7uj2ylFDN8ak2IYNO/4nZEhZHuOKhOINoayQnzqpMMKHZmAInHoBec9/xJc36nsZ5MPqp0l4lOIwoaqN21hKQD9HpcA5KaZAv562ScKuvU1fQk5yTkBUYhTxlT3SrnPZXE8q316us8VeeISwvXImDQW52qVcv97g9SgFf3SoLRYoOjN6lzYN+yl/VSQ+gpjOQN8OzNhQjW/F2L2lJCAtbrp34nwz5VpvTrdsBBLDG3QZoVK+FpoEu/7hLVDMnTHNicPP3psk4Q9r6oCOsMFl1wAwISNT4IIyODjfllz8EpJxYkRO9OUMXrYWM+Pthg3UYdmCcEdMYBRKIH7XwEPHS1lP1GTF9MNOrRScVIR140CtGhelcWsDyVIyZ2WyspU3KtOjBa1OZzs5PBaB6kh2He/7c8mYxAXkrzz45563R9o5gjgtVH08URMC6OUe7T9Xge40vPz9huYsnRDaoOY411T2GVtRazEMeJRtAvqUbCbh0477NVq3acWEiRFaVl+Il+ZI6tGHUlqKe887EFsR2oThLDKDAARpdpQxiFME2ishwpbA96rLzjZrt1qmqpzwRchw59O8vgZijtXIz0WpMll5pGdCrQ1eG+z92SCYMQR95hTNYEWGhp0Z9dACHoBv0i8xGgqJ9BCGOvWXEkUI+NGMe3ob+arsxDqdEUv+b7u4Ahme4jLDkr3F/eND6jIVqxZ9ULHJrGc7GsW/8yhATJDDEjE6e6bTZqTDX1+ueWTRDa5LFtB3XNHcP45olmN+IcJ2TjmJqt9kH88PhqXstbh0k3lz3t4QpESeEtExmFNzeVg8IK0ysiBB+RHgmPAAKpV1GFe/hpnTSlMDbeoPZYqZtt6DeoSKZIoCyfnABGmBRQZwA8kYw0p5lUPOBBddWnrd6gFfmYlndC9+BdLOqEooopEtPbdFCu1am77f0q36z/lTi76A73QKLfxEKxffxYPIA3w2uk9pUlOn7COxHQDfY7I2CloAkOwzDJlAl1R5NmQIueTBc3M3dJEFiFUNCQD8TRaWHfTXW2Llr7HE3HfE15WBL4E5jOda0kwBmp15XIeII++XZkdRq0+rPCbcJzy66DUvsRCRG0f0jPC5KkHQWf1cSS2ih20iQjlTjcbSHiWpxoI0xYMXBy+/xasfEUQJD7p6Fj2Idt4wWBEVcRrHu8cXQyYZQx/235yXDuA/LsWMp8T/6thLV1cjlWdfelu15qWp3StZrh8P3P6cyZ1WxxHdI82TYbqdRg2QrFb01EoivmGMnev1qxYaqqPx5JVWZbbzVK15bU4+5f9xkqnWDLo02P0WSfm2O+SiCSnKaPPUvMMMbYbEbn5JAt58W3SAmv6wYfdwU9Q+M8itNrUmqPTie9TtOwd2f2GrxMLeFmxw9e7jsbjetD2kUo2vlQ0OjYvcKOVSGL34eR7wqGgTX44FiTHiyX7Y/rsyx/V8Beh9CS1GPuolo/vs2BpERZ+vuL+vIX47rbYnQ++Hbboh5CPWONMVQ01bAyy5wrX6Z0hUAOymOJwirKACERoO2gEvt2brOWuxPvgjY1lqQoRNczvA2m9NC6+yU9H7hHHMfsjUZdWNCSA2N60JHJ5vxQpR0Fj+zx1O8I2DwHLWciQ4ZYbC3VWOz1Aj6B9bUUkrDP25NU1H2kHQfvOWt9EIT6buONsDbq/wqBK6/Hp3PbG5plZtBD7DvR3OjRYwb78z+x/Xc30d5QfAtdAhF+ue8wi4JCM8Fw/WF3hw+Xzfu5dGbtH5btp3Zm0wlmFjsojIKAHnwZO3cGxFezwgmWMrrSDjGkG0PJZ+HBo4aevstxCOv4HWoClf7fIwpJ/QeU5h0R681Jl8FaLOydtHlaBSbg0oNQbpcSZMJAQoTyJ/ctZ5N2jDXliuKz2vO75LZa0pwG13NE9SqnTN/PcDUm+pbMEdVcaaqOCozPbDfIO5BmuGJZEaYrKbkOtLDPhkBRumdxsiTuKGzBr9ONhDTH01adw5CtB9/DbbMT/7Yq2LIrWbHUYdWUfjgxzrpBMfSvM0OBIqbbkvXet+BvVErg5lDZr+NkC0BK7JPD7u1TC2wqGDLxHr0SU4RIiPt/woQsxirohFH38xLFBAehero8GjeMX76MSXKmGBJhBatBy/a1JUBh7JX+a0NDZf9G0AVmuy9SI2I1fmxcT34GWzgklx4qjIhmDmXIBCYma1PxFBNV7VN/d2UuH7dXAWo6ZFK3o+B+g/Kq0GF8ZgqORRqs+aKWuTrInuf9g/TD2newQWMRHQMp9Kww0qySaDROwKqGD5hwr6OyZ8OnsCv0B4AAsClhx0hHgCU17YmKQsedv/sKCiT/qF3XQjURzWK7IXJC18fVCZWcDGoT5S7ezsGBLxZzflL/6mOYGBAMYmoGxiJ9sKcLf/aWv0uCKxwS/fGrnPTVpv6qfolt+H9RblpFSammsZBOfv8vVRiufvaZ8xiohlXhKpcigBWvpevq3MfS+mi7a2kino05lZqBwabQt6Ukw9JsuJJ2ZiGXWUgUqe5uGADRsTUME5AsCad5QnWJqQWR91hakqX1ecDa8fO4dwzTla1lhyoSd0ileUnMNKSiwzEs7o76JKKq8mwJw1mseEo31fIkBVIUxO72TVQeDpk58IMs+KdCMgID5VvcB2mY8SkB9In6Bj74aalkdqclijYnm2ECyXlA3DsRdO93lDiZ17CBzLYzczYreiTMajxWYtHY9GOCfKA2aTF7Iz75dVU+tPKjRcyH5DB2C1cdLceIN62brmDXsNLZYz4ZCV7AcvHLD1s8l4u6ACWDUI8NK7LTZFwoWJzAVqq/3KpImCx/3Y0YsknOdim1Gr6HrGzVp17+axDJfba2sHIJ44ESyHzOd6klxc2z3T9Xpfe2SoYNsitfTcw7LC+m+HIrXdRS/D1R5jH5peisFf1QkWxzLLeLwLpSGS9ZmhD1WZWeYSBSj5AhqchPoNDE7YF1/Qkc3JWu4XValr/dtsYKIB4V8ajTPhdoeyNg3kh/WiXFMXFvxcNmNRltqHBrGZyydALvFjzVE7zUs6a3e80wyjB4Sn9UFoSEvXQNJHbXsqMscaVLDkV9/ds6bk+tXP9fT/G70Z0F1FVuw5LyprmMaC0pF3FpPAquJ2rS//SLnUV0wph/gQKsCYLAVbSkn8qhcPiyyO5FXYZBdKSaNdGEJAnUJGw0J11Rq/sw83ZBslJmOAN+cFsyJIx10bG/C+72VPvj3xBiTbbvInDkY/ZTyZYoyw49kZ6KmzrtVZozrK0Q5HoUOICTTjmo2BUX6Mnu8rizHtZ/nkZbBQ5Y+INpUY17tb+2/58ym3pHto4v+opjQ0M5aT+tIaUiyEYFNbe/Uw11rIBnzoaeZpcgtoJ7GjiNkFEyjhr/C965TM5Bs/ing23XDHdqAfbktBH2GL/MWucV+jLAektVZ20IeFXtXZL/d4VTXpXW68nqlmeIEsrd6ZL7uADTDnCQPx2gIPqWm07KnbKYLlCUKQjU/Nv9C2MiaCcDcxADNWUvAtHCI3UICcDIhIXe9JpnvDr26ATD8fiDVBQ+nrpjd/nTb3XxNZecA6L1rGGAPQGzGECX6yWRAZgFthMq2i30Edq7rVB+wwzHlyjv96uVaN0rBO68QubidEVOe/CzGZuHtL7F7+tfkQg5/2hqE+dLh0cVyXUjlPFd3HFXWapg1G36Ly3ZwC45A0kX1GlIZ94+HBd2rMje5sYDWcFssq+DhhsMKgzKj73+nDTu/WHDqzL/nceJ9c9zuyqT1OFWK6eJhUNGV19CiIxFLDfUS3Lmo6AGHUzFKcLo1jPbaCxd1Tg0KN6njEMb+3TzFFpGKEw3fROPvrKGsTbQQ7xbUVFck0yjId5oq2nAdVozokcjc5IOf8C0gAYDeH0NVLwBYAX7PNIuQ97015KyvlfEk+BeQc1ot2Bi+KBpF+rGxXZKpVjz8bZbnEzkfSzyQ627j2joEZk/QAcZBxTBgJOkcdBSdmrlgvIqYI66WtZuk1im4BB60k0av9bVTInauzGFOg9tXwUkWiKFoIecjFnE+bS1+DPwgHl6TOgQzN4/DzdeUKm/QHURdY3ROF5G0j1DMPGKy316Vx0brNPAnDdLkiIgjnxFydzJGQgAe6t6uKV7bZc0WQvjWoLOaY1s/1JmyHiw0s33C98B20WMqKdxDTT6yfnh2/SSFwxKIUqey2QbBoidlfi2ISGHNxDXgHed+sSh5bqWrMqkb3v4yhIh4JnJgE1aBHjuhn/S0vgSTmFmD7tipjgzb+Z7SYQ+ksDqaiqOU0FEL2NIAJ8KNcTBCeDvobSP70FgQfurueD4fb8seCaFJ0svHMgCw9EYzj/lQCSQt0TjKsGWV2UKr8s6DN+bXqxmvWP+edqZ4MCcoELH01j2ld6/Tg3NqGbjvChUGd9XsTCEbDv9GkSfMqLlh0cYUPETT8CM/Wz9IbA83XSJtDFXUz0vgmI+vbV2QU7vthuZaWC9VRRtxokJ4Jgzhh/HGWnAPLImoWJGdBXUseNFFLltWjhRLJxPgS7qi9EcFYexCCbxtYdy1tsv04RzM903ajZq5sNb3dXnmm7CZVCa/qoCWmxjnN7sc5fdWBiqPEk3T+Gd4e/ZhvX0+vsHqzaUvlLIYstyRjF9a43bQZfoGhWPsIiH2+21fpoxgx6/xIIBmUpKfvkb3gCFoaGqXJ8ZIbKJwBHIY8dNzqq46I9KSYsrZaemRTY/uwFUnBpba67Tfv7REDAxoYfhWdAr2/nVg179PTfIGdkgOI7HKAHBNGROuieCLkMTZBAkt1AXe+R8UHgMF24FIfBKax32F4ap9mzL4SGxOuInxLIIHadjFrOIzdoY5Uavy+ORbU6tLWfVU62Zha4ACVbONijMAaNYPoTBXDXSsfVajpaa+COSUcckW8OV+dyA8mkLCPY7b5hR+Xkl/w24HcByiQ+LbdXUSo8vdKT4qApzJwgnWG/Q4yqTrQ+NSCU2hS1t2U3BQxh3AgrmF5h1EZ0Yg4CUp0RclQ398NJ4EnQsB+Wo7Pqv93uv3tRYWY0VOvdMUGz0IYG9GAe9ehexeeNir2N+zIqbXaXNGYLAhgxRMyRX8eNJqt9YzfW0BdBSrdtwgECgBv8NQhoWTbmBiB5PD7ehXP4T6JKMr6rxOo7i14p2vm0xk6B9WPipBiROtmoxx2DPmCiDJ/pEglktqn1vfZ1Kkt76R+98seswIJJVBvdVFuBQ5RV4c5RpIdIiRd0lh4QOgdWfwSeEvmXYnK7pR3ZFB81wNrxl4Cjx2uKQGAJDMyeteqEbr+VCzCdyTzQNzZwDErVPBCenMH06nOdUV8qArIuc1Yvt2HFXfrdnI46dX+YTtKxCLqa3TSfjZZDsVzhSKIkWZd62BRn65/31bHjQGwzlAZMyJcHHiU9l50EzGLB3LaWqqfhHBLo+kotwUlo48HX5r04xuVxoS5C54LfJyJWrSLIFChmwZRv44z7B8Bc/H4KfDDunbmbNiw2kdaMJ2aD1Z/tqPsFFSfRyOFUU61nyHyD8MqcUIbRioOb1jGurX/o1dW9PRKH9eT8eyqmzrWxp/eIcHM5kxMPtXk5FB4Awa8QDMDJGZlvLiqfkhPKf9i9WnbkPhg4WZgPCCweXeKY2LfTwVaSTFMCEVK3+IW1vCIdbbHeDiJNO8ocdC/E7EBIvP/5Bb71Edw0BhBbhe3Hk6InKZ7CWZc90wuOAJRdpPeFNQZT65WInCXaP2W5LZ4HN5MAXS5SxWkp0x/XT9YccZYH56B3iLznxSjHGjGIMnG0kwmPnpHVu1lXjDFCzFYqJ/13mr+gIgP75Utd0iZCYRXAF2LEZ5wrfB9++m/9agTxaUtwaYX7QAACz/02zjA7CZDh+NXzxlBaM4Krv2bJLYshCo7K0djUwYNXlpKDVrDtMPClj4eent6OAvbMjhd14qzjFf+VLKyTUUmwY7xzwblCL36Te0SEXekgXjPWToO+gMrmM/Z6Ps6mdBmc/3bIR4ARK7nNZoARukzrWyRqKE8dfougvReZKy8p7rOGk5maBcsxBr9RUFfM0GbaVgGe0lU2rxRfsy++QD27ph+HnXVdKWC4F1qYc9m+qoL+sWyCvNV5lt0SJ57DjpL/e5e+d4MfeagIc3Ml462YOiKeNbAt5E+Pznwq5ZSIw69xJHxLiAnR1m69HszyQTvEMJ5l9+7Q9Bsv5Ao8jC4x1OWH1+OMnxCzhntSjjJFwG2RuHExnblX/HxCoKYLMjN98gN1POXo/X8omrD1iiu6XdbuUCV63pTC9oU+no+Mgnre27gJoSBq+VmsjV+OgaAZPgFkZ4QxjzsOfqwe8yHZDtm6o2YLSlJdm8JosH3g8sDsFTeHsmNpW38CUJQeJsraQyPFlDnGMxRo7zgV97MuSE8E4H7OcVMEeTGUHAdLHIqrnloydXNT9swJVXvWEbxe6Xh02lkj/2GIg6XptwXB8KWvalS4i15H6RSHYF9JwT58LymX/cymOGReuqbUoi3P9jCGQUeWuP4ecBFnK1akiLCDNIHCdxCHBvTlbsZPYCCsJx/mjCRILxa1cusL2rcAv0pfXESb7ChIP4A/glGFOosMyxz+ndLv+eVckv1kNzvuMRttPmBL/xHsA/rjHfSQn4TVRdVhl7xX4rrjiL/AHc2ounbRixmweOswMAA+GrkMAPOaEy4T/kLzEKVpcgptm3Ev9kKm0+dPyRa3RqkaFBT33PQxacsTAgejhWfkLCeC1ANpBsx6FwjLYLzaPnTAVwCyi3QoUI9uz6A7cqASMHZBHBLuP09rAanHOpcnBuOtI2Eab25HUtKEa8kJWM1pfISaFTbQZqheu7q7qaGyh4e7vk4FVIEkcdJdc990dD1hNFO55NDONHFtm/hI19WzPTVXGhs091OKFkm3TSSGslJZ3c3+cp9evrNCBGcTvN2b8qdHvcS3+sOggorUXbP4B0xc/gYrIPDL47V6/qg+J88dEhFP7hqSleOEeRWz9B6lgKpJq8sdnhOH9ebHaiWH15qz50oAGhiOby7TGQOHMoUsPi55FZQ+34mJ0f9B41Ddxn5cMvVRSy3s9n24jTPbfW7k/PkeC+PiNwtL9cCaedbyJpvO7zq4J7wH1RN1+OOntvPiKKDLWbP20WcJ5EDPdc1lWIpcwbHte/iiVLcEV9rFeAIimf/dF+RYI3xg2T20c+FJaURUm16L0MSKlMZ5a18OPmXwx9JAw0ouj2mtD7+mUVCTekatDbufNtn17/SJQ7yKtlUSJfhsYsEb4eVC3wmdylL0w4yYi4bg9ZkA0wEETpg6Sr6BLBmiZrCVAKg6x1AlMQTIvjfeNRmmqokIxEQHnkQsoxp/1xc2rltmtbiRs9C2JWpCnMlOWLdASrxNA0Q/6BfO3WihHTJjUAoxRGlDkIaYM619kSd7GFGHYy1z6AvPpy2Z8PNKcgRh7uFhqnCsjSFJZNm7qeOcfKDnB+fVSbHnQLOhtPXUz+/gJbGRA97h7bK4ihvkKpzKUdqb9XowbLQ71q7nBsexO8PDtHd/OK0lrCD03G+4QL23hxwgdVTdFoUbipRNAYfssOTduJy3LW7c7eChP6LxbW6kcA4U9a1Gtml+rnH6JTMthKwUAsbfAHvMRJlRAlQ6WwQoQ7E9pAKi25BDYiDe9q33ZDW+0kYDNBLVZKa4yNW/pnW6Ew2UQX0epwRjZAWO8w02JrLA+lMyzBmxki7/gw3t9CxDD3x/ONT+6NIdiccjJoS0KvgfhpKWP4TdB3gbMPim+oSfBVZ/hPPfUa5mo0B8MoZLx525ud7kpddskm+O2I6KIzdn6GUHE/PcZ/E6lq3WFTyhCz7rq4AN5/0gPyMItGUGCRSJmvxAPmSVO/YMcORS85bqITcIjByhwtXu3kAN0t7zGYnFNbj46hVWVatlOBnhxgmKPkZLWVIg0uHG4wja2JPENMs63A6ic+0hdpPo2Z/ZJG6HwFObpvd5gvG2+wtyvccMTA+ndN3mYPOmSPvPf//OOT8t5nmlNhE6eaTweK+pBjhXqNQwRpVLhAIcGihZrPICu2J5mfmJf1pQoEXLPBjbxL8PEcPvS4I5yKG66vi7hj/o6XW/ImeyXgo2Op8nuvs71E20sIHHCjDBGSWXZ8OSUiZdpnKVFDVkk=
*/