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
Fd6rHueIMRwCBmB0yKuPARbMrCa/VpyHjQPlABwP4GkyZ8EzbBtjZrW5VSVD5w7kpLN00vz9JDURQUMyYixnBN0WIvUKwV8zgl8cbdnnuAAzWCKJy6BVEkV5a31m9T+y1cUD0GEkgmmk1WLaDpOLXqoAI3BYR6+xnP6b+2FPr+gy2p7Auv84lPY/saFoASz/dvvBSfzB9S+do/Ysu6KvV/GuJCMPUGreyJ/URcn9pFkpGBg/zrgOLcU2iaQn4MPFjwdaBln59CxasC1ch8ku7mOcndRqhRl0V0pECglebKi5xBnVxRIZyKhf5DBnuB5+FbDNRj5vWucd2U35Jws6RlYp/2hb23he64iicpt2kcmu7So3OIn25++i77Y23UcwPlYw2p1/mrEXWUSZQ1vCknczySi64fqQZrh7gLUHfIwjDB/CjWyO/LS/FXkjRyI6BzFNvfEFGtaLGbv302zQf0945iGN2dAuJGnEo0rj/vBwITK1KwvqdSpvJAzKoq7LlYrnDrWQ/VwdddGVqs4RcR5btnI2n4vOPDd2kRwk19gGyYJA6s7Hw6WEfGN7MXFDqPaeFOw2d0Gzgl4/3E9vjc8j4Tfd5xgrx9yoAnkh603P+vU42UF7MYdOXFPSs+qXfMZ81pe7lJbx0JsWn9yXKExXEcBu+xfyK941EhTBPlqccXFE9O8mL5vuYE8PqB0vTHr8c//6cGF9KnYrxpvrepBGtTGZWq4mzZiFZyxTnOBmtj0iinbt4ovTlm6yjwUQKPbnYsSnu5IIZCLOMSkfKo6W2f4Trpj8U/+UPaKffq77cliqLycXpvqyJ/pypdZ7sCRsEXGSh7v0OyVqyWEEQGQdozXSs4OiN/Ko8E/z9fAQKuTzvYxJYwf6SjsowxziDa/oix6nIQzLQe/YNr2DWNYsp9FV9PaoHGt5/VJMEFxs7BIT8xV+S3Oht7gL5J4VxOY5xTdfJZUgtXe0XBwu05XsXPxm9UypTdFAjr3avWQ1fYg10P69bmjL788hcLB/v3Bsy/jHWuX/tGeLb16jXPa1KL2M90kKwdZ4qr2EN9ad92LOL5S448JDpTmfRURj19HbnbLpPuurmejbszaz66erD8TCE6vqYqsWdRocOMNLJaxb+trMpg1bX4vufwwUSr6aC+EuLhN9GS1CRQq2rHoZJa3aVb1soHG5BsWXUDW0aAoaWWVNfNVJ3uirH/1lYk/WwjEQ8/XfVVGZXlNkP4mtgv673IDObDButXBcpKE6+lqGbxtWvYx63N82zduHWCW3AM1CQ197zLy1+4/nKzbzi2h3RvLOxNKitPgwGE9ET3aBTvxfVQcuPdSOShBmeRDD92WV/bNq2gv70+Ju4frLrqSa0MZ7unayv+6TFdzbx9oFGS+k+lFHv93n73O2p+tDy8syIEB14gtQeKd6RWEFFK9W5eZ8tountg8ncpfSyo41LPnJLkVBfNhlaeRXEyeSrTiBaKw7NLA+0yO7m4GsqgrnsYeB253xEcSIp8V9RkDH8R1mviYdk1BwyWYnw9C8L7Uh78fAJXcz8nVGth3UPOf29HjW39i7EvgmiyyetKGkWEnAggGCVK2KFhAtKljAtkCpihCITVWOoiLGwCpCQlGh0E1BwkcRFF13PRFFXW9FwAsLVYqKgseyKLrAek2tSr0qyJH9vzfffPnSi4Lu9dv9IP3mm+PNm+vNmzdv3mCaDVhqznoEk7I/N5ZpzfmBNvLa8mgHN26DJQEtCFbWh8Hj5/SzYBVKRUZ+0+PyG80Z+vMlHLVsf0w2wWUutbNaxA3rsgSPFqcLzIOqZVsb6SKmdCeodEjm/ynWtCo8wXXETfubPFS/KXKTJDM=
*/