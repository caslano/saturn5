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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_METAFUNCTION_HPP

/* metafunction.hpp
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
*/