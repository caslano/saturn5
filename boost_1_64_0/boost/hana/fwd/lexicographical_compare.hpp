/*!
@file
Forward declares `boost::hana::lexicographical_compare`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LEXICOGRAPHICAL_COMPARE_HPP
#define BOOST_HANA_FWD_LEXICOGRAPHICAL_COMPARE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Short-circuiting lexicographical comparison of two `Iterable`s with
    //! an optional custom predicate, by default `hana::less`.
    //! @ingroup group-Iterable
    //!
    //! Given two `Iterable`s `xs` and `ys` and a binary predicate `pred`,
    //! `lexicographical_compare` returns whether `xs` is to be considered
    //! less than `ys` in a lexicographical ordering. Specifically, let's
    //! denote the linearizations of `xs` and `ys` by `[x1, x2, ...]` and
    //! `[y1, y2, ...]`, respectively. If the first couple satisfying the
    //! predicate is of the form `xi, yi`, `lexicographical_compare` returns
    //! true. Otherwise, if the first couple to satisfy the predicate is of
    //! the form `yi, xi`, `lexicographical_compare` returns false. If no
    //! such couple can be found, `lexicographical_compare` returns whether
    //! `xs` has fewer elements than `ys`.
    //!
    //! @note
    //! This algorithm will short-circuit as soon as it can determine that one
    //! sequence is lexicographically less than the other. Hence, it can be
    //! used to compare infinite sequences. However, for the procedure to
    //! terminate on infinite sequences, the predicate has to be satisfied
    //! at a finite index.
    //!
    //!
    //! Signature
    //! ---------
    //! Given two `Iterable`s `It1(T)` and `It2(T)` and a predicate
    //! \f$ pred : T \times T \to Bool \f$ (where `Bool` is some `Logical`),
    //! `lexicographical_compare` has the following signatures. For the
    //! variant with a provided predicate,
    //! \f[
    //!     \mathtt{lexicographical\_compare}
    //!         : It1(T) \times It2(T) \times (T \times T \to Bool) \to Bool
    //! \f]
    //!
    //! for the variant without a custom predicate, `T` is required to be
    //! `Orderable`. The signature is then
    //! \f[
    //!     \mathtt{lexicographical\_compare} : It1(T) \times It2(T) \to Bool
    //! \f]
    //!
    //! @param xs, ys
    //! Two `Iterable`s to compare lexicographically.
    //!
    //! @param pred
    //! A binary function called as `pred(x, y)` and `pred(y, x)`, where `x`
    //! and `y` are elements of `xs` and `ys`, respectively. `pred` must
    //! return a `Logical` representing whether its first argument is to be
    //! considered as less than its second argument. Also note that `pred`
    //! must define a total ordering as defined by the `Orderable` concept.
    //! When `pred` is not provided, it defaults to `less`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/lexicographical_compare.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto lexicographical_compare = [](auto const& xs, auto const& ys, auto const& pred = hana::less) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct lexicographical_compare_impl : lexicographical_compare_impl<T, when<true>> { };

    struct lexicographical_compare_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs const& xs, Ys const& ys) const;

        template <typename Xs, typename Ys, typename Pred>
        constexpr auto operator()(Xs const& xs, Ys const& ys, Pred const& pred) const;
    };

    constexpr lexicographical_compare_t lexicographical_compare{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LEXICOGRAPHICAL_COMPARE_HPP

/* lexicographical_compare.hpp
uztQNr38cDiAzxpiRMUkDxjiqzTwZublj+JCl6j2CJvu4K8SDaoq9ebUJznVm0uf5KI3PcBXOdL9jWv1cbHtWfrlGqz0cbHwjizQ35w3gKwRrUq/0DNXr/Yc/QFDQsvszgeu/QKmGyC5TZnJHCITorXMw4EGQCM0UasdGUukxfni2PCCYXHte0V7hDdbjPbvqj0mBquFTvvCt31NYLVOaIp1ZM2tPCLPtWJnZ9+lz/ibcZxdzxJQBEwE9+LUJzrFBJc+0SUme8RET2z7PuqDthyMTGxVln6B56P5KePK4UPO2KBi0yMwVG1le4n8A0Uysb3p2vPFVuIOwBeeMU20QL7jiDU5wIPjbOhB4pbvKHHL8ApQzo1KQpv0b6134hWEZFay4WHKiuzyAzV0VfWnWKRD346e1G1rPuaP9ME055TfEW/8kjSo33AcrGsvSuAUwjKcxKudQCPTbF/wLutJQMmHx2FFr11P+hkKL5yMCKDm74rSn+OM4M96/QnYMLdVndA0F4M4p3JW0qg6mmDgk/iF+xpX0QRYWrTPnADrzQmAaL6mo56RB8831hRTXXGf6h9g6P8oVSjH38ZzqqoSxHkaSj9g+u2wSj/8Pe8Z+onN0zAxEBeRxRaCnZkMdqaysQnszEQtdg2zMxMPid2Uvvi8jnR6UQOxGLGmEaZEC/MMEi1/pbOhUyf9FL47c0DvD0iv7rPmgfA3OBs+S1orm7UPVBdWsyhrmCXK+upv9sLWhBxemFdUH97/iKofREq2hhOq0xaJvLJmAem/WkwSyVhKXOgho4G8aofdjPcNjvd7FY/GEDXYnXBGc3FbtiWuf/sR0iyjkbmpYdUDMvClzzEcaIk1jti25VgZT+CMQ5mMI8IPA/4vh8Qlmng+8SGOuTacHoY8RkzHfhYyBRx3ycYOVnfg1jUdOPQqVyyp9rMody5hsDmi5FA72gpGphWMXLN1R5VIfMKZeHh8srvE48Q+L7MrHC13bVAqjOr7+wDfe0wBj7B+Nben3zOgX798Bf/cg+06kV7+9dVvejBdFvWjkYcUISy9UAJZk2ZW1dwDJ80Zv6ZJMw0zgSeNaJmFeXMUCs0wEwgWcZPu7cq7uQmKFvLJCFQlDzaicJy4gFkSL8IcyJiv5XRWGWSRPCU9NnyODa6RVjxcaPOEYb6Q3oCcEPPjlP/hrX3KJ1IVlo4fm15MPAyATxAVaW7yKPhynvl8poSt5HzpMBua4Qbuu43WROeO/7Yrmje+wcUNCAe5AUGzAYhwHsKiw8Jyz13GsUM6SmtsgEgv163yDMrZGIQIdL3Pr+O82RYNSPTjIEdWF1B/hOVPl3PDM2ORS4REjcXOu/4BY3FA+Xl9y1fD8/m7+o6FB2Nx+4sfPRai1OAn/D1RD7a1Y9ZZmVYlDWd0OB7yLZKJgj6BQJ7YpBTmQ5uMgyZFby34oj/lnp7C0fghITiy6VFSFrostuillBuQK35k6oMrL6ScQqCzd5pVdVOavVvMNKc2bll0K1hqpfJPqmVdTUjrspr5QFq/SHDXIoav6YjszH6/A85fP/ACLcmm5ZnzS6XEyBJCC/sTtS70xg5Vq1TODHz88LfmId+8sGnWmSd3c2M91mnw52GGuPyojzfxeHoz6+uKLQesL/rjGfXj36pmJz9yfT70wuHxw0W//QfMyQPKH9u3fFbbm0hhxR1HhRQYv1qLiV+o7j/9zT+g7gfg8+7ojHiFFoANXECe/rS1vWP+JV6Ri4DcgBxsBkRfj1eMAmwUrs1ZbcI2gcT1FxUlenmJqCjVy0uZPhyxfPCx53CxX8SRNC5mBl4470q8oCm7yyvtEHy+R2thOYsyP/2g0Z9H0T7krWQ=
*/