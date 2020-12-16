/*!
@file
Forward declares `boost::hana::extend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EXTEND_HPP
#define BOOST_HANA_FWD_EXTEND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Comonadic application of a function to a comonadic value.
    //! @ingroup group-Comonad
    //!
    //! Given a comonadic value and a function accepting a comonadic input,
    //! `extend` returns the result of applying the function to that input
    //! inside the comonadic context.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Comonad `W` and a function of type \f$ W(T) \to U \f$, the
    //! signature is
    //! \f$
    //!     \mathtt{extend} : W(T) \times (W(T) \to U) \to W(U)
    //! \f$
    //!
    //! @param w
    //! A comonadic value to call the function with.
    //!
    //! @param f
    //! A function of signature \f$ W(T) \to U \f$ to be applied to its
    //! comonadic argument inside the comonadic context.
    //!
    //!
    //! Example
    //! -------
    //! @include example/extend.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto extend = [](auto&& w, auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename W, typename = void>
    struct extend_impl : extend_impl<W, when<true>> { };

    struct extend_t {
        template <typename W_, typename F>
        constexpr decltype(auto) operator()(W_&& w, F&& f) const;
    };

    constexpr extend_t extend{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EXTEND_HPP

/* extend.hpp
p91i/0BblEjjwrxx4Noz9zSWQSQQwYji4Xx6sOJhrGDpsS/AA0eNxwNHTSAfCOT0tXFenosOvt8SvqwcgLBkzK4wnlyHVfnyjDDSQvK4UDWA6HQrd/+kM0ZmXITQykkVOgUIVMYpglFO0BMsBMP6sokFFRMySFxlmVpJ0EGY2dBwWEYHBKaSwTJRiVG0stwgSi83isIXmRrLzXikKGxfOCqtsTqd5HdC0EVFwCDPFj4AKmDvYuHJdASNwNsQ+K9zJiDkXa8+2RkTlpadPmkGZLqS9Zd0arBtiIP22YWPzRBW1+XIVNorz8E/84c0RpikjpKiNvv0SOtrmLrWksw9vb6Nz/pdeajzjNptmpVAV0yzILR0YxPCoALx5I0YY7EHDVseFZ6EH7WE2kyh2Bm1L7liarLb48kQP0NNNxvpoBQLqlL755pPWcyo3g9knSYcBHxEvOWj4jPcsUH33DDUEek5f85H5R8pzyC1SOyjybpvSIF3ffwL2poH0DFEM53UUPbTgd/RS7y1x3hcCnDthAXfpfbnSxyqGshSoc3dffr7DXocjvY3N2v2f+5NPTHR7Z/vpDNxkq5q9w7c+o2svmj80X1DW0YCRUho0KU+q/1+XD8xBfvbgdzIDkibpsUioQ8GB3MpaDYFGf/B3pXAR1Fe8b2SLGHDLppIlABRF40kYiQpBRMggWQTlGNDzK4WSKzFOGwRUXYDFNhglyjLEEutbT1oa1vbamtvW4NSm7BCAFERW0Xx6j0xHohtErm2//e+mdmDxKDSu5vfZOa77/e97733vfeePVjmQAvKHeiqcLngsqDJg/Hb81B/5udMe1pjjo705QvPcmkzCdvmKrZfaSzcot3cMwP+EOVkfpzagLTWm0zmnd1DqebjW296P9RuJekQVWR2qAeXDs1nCetl6AsEmcKFg9zj5f6BXFOggOwXWAKLkBmNJzqkMWxspAXWGC5nnpRsgKSk6JVQ34jAZZTAESiKJeDO6yzn4U9OjH7mpPbh5dbBOzWp/WrzUxrlMhMNm78HOcTPDxadbLU4Oy1Onhs+gz473jQPODv0/CODuBtDk0ysJ82f0paTxPZry6XyvwDRSN5wJ4HT1pm/018YUkz+/JCS5b9ACoOazvOBDaxKt4kp8f6jPCWIkUyafZUzN8HdZwy8jX4tNqJHaXe3D8fwYI+20Uc27fW4lQKegjHqZ/qvjY3y8pP1MMCL3AdRlkulX2gl+kxacRtRnFf55Vehaw7ClLWgcJKWMHknF85Xz1THqQ/NyT99PJpx0ZXZfLiN4fEWwZgDvqLr1hrm21seoAotrIOsBFVYAbAmXtgVqAJflnuldZlxY6Ux/1WypQuThAuK3iJtA5UIJ1sR9D0Z32SEMp/8aFyPGgND1k0aJ0yoSMO01kOJ/Rs/pIayOIm9xUihF4hQtsE7q/Qye8uztNXtMMnHW+cacd8jrQqFvp//ftfXqJ6XoZ6lqCc+5EOxKjtK3sbA5uoDewsN7AbR07lbj+tKtYU21FGoOBommlTJBenFdE+eDAJ+YCRH4QitVxg3mmdw6ItdRsFdyOZEpP9BT1jUQ932O4gEoW6iZqoJhKfgJ52v142MMnY1IB/Bz0d9qkncEcz0MkyWiaGoMZCKkRnnz5eytUTeOuUnD+k9FxgR32tdZ+p5xVSDfsxZc/p+bXmYgEp0ewxfXu+kHaNW3uIsxNsjP+wsw9srb+O3cu8GXnf+c9j6vbyJYwNNO4IpfMsTlFukTjLi1Qqkmwx3fdeBPeNO5yzhlQNo+yuCDb0vbSXYgIU7cn/o9+mNoRLTPF+uW0sKbZ1Pwf4/reMC+lcazXqIJxPGwy29YIgt2FvFNHo=
*/