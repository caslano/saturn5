/*!
@file
Forward declares `boost::hana::Metafunction`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_METAFUNCTION_HPP
#define BOOST_HANA_FWD_CONCEPT_METAFUNCTION_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana {
    //! @ingroup group-concepts
    //! @defgroup group-Metafunction Metafunction
    //! A `Metafunction` is a function that takes `hana::type`s as inputs and
    //! returns a `hana::type` as output.
    //!
    //! A `Metafunction` is an object satisfying the [FunctionObject][1]
    //! concept, but with additional requirements. First, it must be possible
    //! to apply a `Metafunction` to arguments whose tag is `type_tag`, and
    //! the result of such an application must be an object whose tag is also
    //! `type_tag`. Note that `hana::type` and `hana::basic_type` are the
    //! only such types.
    //!
    //! Secondly, a `Metafunction` must provide a nested `::%apply` template
    //! which allows performing the same type-level computation as is done by
    //! the call operator. In Boost.MPL parlance, a `Metafunction` `F` is
    //! hence a [MetafunctionClass][2] in addition to being a `FunctionObject`.
    //! Rigorously, the following must be satisfied by any object `f` of type
    //! `F` which is a `Metafunction`, and for arbitrary types `T...`:
    //! @code
    //!     f(hana::type_c<T>...) == hana::type_c<F::apply<T...>::type>
    //! @endcode
    //!
    //! Thirdly, to ease the inter-operation of values and types,
    //! `Metafunction`s must also allow being called with arguments that
    //! are not `hana::type`s. In that case, the result is equivalent to
    //! calling the metafunction on the types of the arguments. Rigorously,
    //! this means that for arbitrary objects `x...`,
    //! @code
    //!     f(x...) == f(hana::type_c<decltype(x)>...)
    //! @endcode
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! The `Metafunction` concept does not have a minimal complete definition
    //! in terms of tag-dispatched methods. Instead, the syntactic requirements
    //! documented above should be satisfied, and the `Metafunction` struct
    //! should be specialized explicitly in Hana's namespace.
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::metafunction`, `hana::metafunction_class`, `hana::template_`
    //!
    //!
    //! Rationale: Why aren't `Metafunction`s `Comparable`?
    //! ---------------------------------------------------
    //! When seeing `hana::template_`, a question that naturally arises is
    //! whether `Metafunction`s should be made `Comparable`. Indeed, it
    //! would seem to make sense to compare two templates `F` and `G` with
    //! `template_<F> == template_<G>`. However, in the case where `F` and/or
    //! `G` are alias templates, it makes sense to talk about two types of
    //! comparisons. The first one is _shallow_ comparison, and it determines
    //! that two alias templates are equal if they are the same alias
    //! template. The second one is _deep_ comparison, and it determines
    //! that two template aliases are equal if they alias the same type for
    //! any template argument. For example, given `F` and `G` defined as
    //! @code
    //!     template <typename T>
    //!     using F = void;
    //!
    //!     template <typename T>
    //!     using G = void;
    //! @endcode
    //!
    //! shallow comparison would determine that `F` and `G` are different
    //! because they are two different template aliases, while deep comparison
    //! would determine that `F` and `G` are equal because they always
    //! expand to the same type, `void`. Unfortunately, deep comparison is
    //! impossible to implement because one would have to check `F` and `G`
    //! on all possible types. On the other hand, shallow comparison is not
    //! satisfactory because `Metafunction`s are nothing but functions on
    //! `type`s, and the equality of two functions is normally defined with
    //! deep comparison. Hence, we adopt a conservative stance and avoid
    //! providing comparison for `Metafunction`s.
    //!
    //! [1]: http://en.cppreference.com/w/cpp/named_req/FunctionObject
    //! [2]: http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/metafunction-class.html
    template <typename F>
    struct Metafunction;
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_METAFUNCTION_HPP

/* metafunction.hpp
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
*/