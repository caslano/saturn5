/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_END_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_END_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end_impl.hpp>
#include <boost/fusion/iterator/segmented_iterator.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_end( seq )
    //{
    //    return make_segmented_iterator( segmented_end_impl( seq ) );
    //}

    template <typename Sequence, typename Nil_ = fusion::nil_>
    struct segmented_end
    {
        typedef
            segmented_iterator<
                typename segmented_end_impl<Sequence, Nil_>::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence & seq)
        {
            return type(
                segmented_end_impl<Sequence, Nil_>::call(seq, Nil_()));
        }
    };

}}}

#endif

/* segmented_end.hpp
ZUYPciCFOo0pWXveb7ZRyFw3Fsku/UbWBh5UarH2aaWOz6Le79FEVsB46PpByStLFg4b89yjz2+vM+WE8N3iovCyQL4f7HuXRJOL0/nSanO4FaKaAsz2Hv8ArY/rFZnjRSmpT230WtfgBDxcrB3aF8RZSNsPxB+g+b6SzPeiJGHTUkcpamHEjDuB/pEmX8GyJArzLBShoGDwW2yab/ED1PbYdf0wcGJWQi2Ba355a0H0d8V5Qo2PMybfYd9PXC/0YlVNVKIeQXsAWo4XFnBaT0q2tiVuC05Ci8DV5UIfy8GYVB+g5/zUC4rM81xsEFAUwxXpuvgshu52+e7KV9LkPxDxKggjEZX0/rJ+mO/vPTR3nxd4UexxkaZoHbaAkKBtQdVtVb3T5dY7uWESuxWTSn/V6FinKfSTnR3SfAf9zMuSpPSZ6eu/hna6tF5+FGYwBEPWiqqNlcP2pnxFFQahG6eMy1FVYRBcmpPvCmlvh4VBzj3Xz9g0uaQyeR20x/kAKbMqE5gC01xeU8GefmXd5GMYx/qD1C49yL2sChLmyJObwcQwj5rJUzGfJ1WWOiGr5A0njW9Hc5BfNNvm/klcJlXhQZcXF6hGWSHG4zXLmvLTwC0zN2MwS9mxc/fTd8nTyk1yV4R/lvomYafQ6nvM5HkANHjuuZUHLI0qCzkAekS9Azd57s8rp+BeGQJPoybDNr6jocvbieecxifoxNKaPl8OCzrV32iYEQtsROJwT4Egvf8fBcw16PC3Cc7S4SNubEzivKoMZx/i5McCcr+L+vcat9lHPZ+uG2Juv0Ni5BFzZW4dA9VhPOf3UD2qmzhlAB/xv70HNvWoO0ZmiCVmvfUTiz/Ro9o4pWYhOrkuXN+Wx0Y6cSgP/ZoVDuwmUR1n0JdHNd1QxSH9qkkHQtum+5FjBh1DY8GaaJTx+RamrevLdxA6UbuhHSbBEHUb3k08byfB2Go2Mzbe9TSWqtgMvSHFoHqN2GyOWxhiZ3qJ0C21D8q5z/VNHKp8sC7nCZ2ocRAzfgONoSorjdk2MX3yvbDOQzckmIF1vkhwdp3jXYTeWeefEwypM56ZNm8EmP+gB8K98XtacXozWOw9N6KxYMWeDcICLtgriTmnjql64VSj49y86hXmOl/48J+T+Gz/dstW/OpFuldPojQO/OyaY3ao+QZz39G1v4x8Pw+qgNGow/S8c9jkeUCUF57vhiJ6uxoYMmaywvsmfrJKeVKkQcZAMDYVieWTm/jrosqL3SRtQqhPytXKUdivm/Hn71+GTlmWgceOlVlZPbSk/j2cfMuAeakXusLOPoZYfiTUvLUfWMc98Huo3yX3ggDmFUMVRDKfhJhXRyx18P2b9Qsm1yAKjtK1FXMAjrbnYYTp/rRnROJgwjLoKOeypMt8MnlUmaVpOQujEgfzjAbo+0s+BnR9f6ntfN9CcyZWAQ84Lxm5sWz52Z57Cz13eGGc88Bhxk2mtcd83Vvonr6ovLLMU4d1qUIa7lG0823x8jIti9SpWMf1qOJVZ4krhDdjXgj+nWkYsYHXpsRGGw4jVBcVFGnspDxlg8waW7m+9xD+kJVBHPMkrVhj4wceC8a+So4JzKNKeGMWll5SeQFsrjvNpCw/uke3+KPc9700CZCfmE/Z/GcIf8JiLw5Dz3E1PzWravscv47weyxP3TQq3ZJZJoT0HHOJ8DmsAJ4o5xVrmRZaPs4tPtet/CwPXc23jmbkRA/bbqeizIMyz1i3maHVt8ffSr+xHxeB4wUp6zI/bLgZ3lcRXp+5ke8Au89ss0QrhxAjvA4rC4fnTizKbbbNMmG4ZES+44TPY5xnaRVGHL5rw4dRganf6nqrrmVaOZw=
*/