// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2012 Bruno Lalande, Paris, France.
// Copyright (c) 2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP


#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace boost { namespace geometry
{

namespace util
{

template <typename T>
struct bare_type
{
    typedef typename boost::remove_const
        <
            typename boost::remove_pointer
                <
                    typename boost::remove_reference
                        <
                            T
                        >::type
                >::type
        >::type type;
};


} // namespace util

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP

/* bare_type.hpp
yees5PM3yeec5POl5PN3rb7lt0Ctvi98fr3IJN/p/UzSK5f0XpT09kl6v5D0XtYf50n6/Xfh8/V5fk+DBE96FzZf31RCuqQ3wyS9HnJ8hct+6onDsDfGYV9MwH66/VEh6c0xSW+CpHetpBcr6U3EqTgZZ2I8au0P/yfzCZJe48wnmEaokHTXSrr6+fWelHSfknSflnR/LOk+g1b8Cd6Cz+JqfE6br1B+J8KZnvQbPl9hpaTT3pNO3eYrdBDOSryvZCxIG7RJvHnUbyguwFGYjuloxR9iJj6INvwJLsIDmIOncTF+jvn4NyyQ/VVJkN9gaEuUfN31eEDyfVTG2DyJfaVeR+FuTJb6zZb6vVnqd6PU78P4PP4Mf4r7cS8ewRfxE/w5NiHffdgZX8ah+EucgvtxNh7ADPw1FuKreBsexO34Oj6Lh7R5A+W3GBwo9amfN7BYtmup7Ndl2A+Xo9oe7pD4Tomvbw9vkvgrsRuuwj54C06TduF6/CFa8VbMxdswH1fr8omc6zufOySfUslnreRzl+SzTvK5W/JZL/ncI/mUST7lhArJp6Ps5zDPflSWt+T7QCVG4Du4AA+jA3+Py/FdXIVH8S48hnfjcdyM7+NW/ACfwxP4Iv4RK/AjfBNP4zt4Bk/jx/gZfoqtZX62dnhWO6/kdw9sYTL/ZYK8q34GNsdE/fVB4q2QePr2LV7OqwQcg1NwDk7FxTgNXThdu07KbxW41WR/bZT9tUnOlwdwKD6Io/EhnI1bMQcfxjtwOz6AO5B8UH6rwBzZXx086StLG/me0x7jMASnYpiUvzNuwa64G7vhXuyB72E4fo49sTnp98IQ7I3h2AeH40CciYPQgkPRhpFIOTlf5DcL3CP10RbzpJxLpH6LMBxdeA0uw2G4Aq/FGzEBV2IersIf4s34AN6Bj2ApPo1rte+R8hsG9jM5LuY3lXYTe+IPtO/J8jsEJkg8/XUqWso9EvvhKByA43AUjsdxGIdxOFErj/ymgGEm5RnZTDlOR2FHHIPadUPixZvEG9+M8uAEjMVrUcZIqs/9+T2g+hjJWXI8zsH+mIKROBcn4PUYj2mYg/OwCG/AG/EHeBcuxK2Yjk+gFfeiDX+NdjyMi/AcZmNTmW8yDBfjQMzF4ZiHo7EQp6MD5+MSTEenNkZSfkvAtSbzgF4p9dIVr8FuuBSvwnXYE8uxF76FvfF7HID93Mc1TsTBuAIj8SYchrdgNK7GGNTm+R0h7YnJPL9JTWmncRaOwWRMxNk4H1MxF6/DQrweXZiGynVLfi/A/ibXrSDZ3g4YjldgH+yEynEtz/vxQ5Pj+gs5Hr7Dcfg9pmIwx28BNscnsAWexFba9zp5ro97TdKdKefLLIzBZJyLsyXdOZLudfgsztXSlWf4uMMk3XV8riduxEG4CcfhQ5L+w5iH23E97kKpR3m2zjnm+R5W93mDj9RhLGyftcxjRzi+ycd8mCXmY2O/3RQcGB/rh/GxIfcHm46R7XN/8CUxTjYwP2bjjpMdx341Gyt76HXf42WT7w+u95jZs6/XbdysjbRLCDsIFYTjhG8JXR4IDhpFsBHKCHsIlYQvCSE8zI0kpBGWEzYTKggnCa14wNuHMJXgImwllBOOE4K2MO8mYRwhnbCasJtQSfiU0Owh4hKSCQ5CGWEPofKhwLjewBJYAktgCSyBJbAElros/hv/z3BoCzbC+/+7Mv7/6pAgfjx3d+nIt7uyC21F7rQdyth/W0iQ1n+0u8wN2Er3vqcu7vE6PJDjnyZOm2XJcketa19ydYzCKUl3p/QH3E7oGsb2eNOlV6p0/XdnwLCpggKGaAfVpV9o8w7zokhH3lcpfTEN796WMSg=
*/