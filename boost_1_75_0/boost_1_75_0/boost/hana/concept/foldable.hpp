/*!
@file
Defines `boost::hana::Foldable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_FOLDABLE_HPP
#define BOOST_HANA_CONCEPT_FOLDABLE_HPP

#include <boost/hana/fwd/concept/foldable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Foldable
        : hana::integral_constant<bool,
            !is_default<fold_left_impl<typename tag_of<T>::type>>::value ||
            !is_default<unpack_impl<typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_FOLDABLE_HPP

/* foldable.hpp
f2+uFS10tvo3sMmr4YFdxgQD34eD6opmgEfdH+OV2o/ihMzUBPTkcfQoF8NgGakdga1KPfDJ7fHM46sFa77k6D3IMXUIUKGhp4e9cjdu6+9Bowq0vUxtweOpZ8unJ/vGak20lCsJpCS0Q75gOrzwBBDMpg3cZa5cNZcF2/E1cjB2E389c1FWaef6lwClgIZ6rSJHv+CcP8ZPjy0YQT1+j4Q9rjX/JnjHpn92nua/9D2bz7RSb/tiSPPfuzum+a+uG9J87No4aLeUFGnmo+upPTnYzBhkvANQqIktvIkZmbywUPe5TbxhODXxZz5sYkb9t9jEi0dEYsEv/BSNkW5PfS6d0Fa6n01EvvMOWwiw0AZLWzDbY7Zgchssvjr8XVswxxR7BnI1G2xxjP+Li90AEM/aUhxjg3WxJF57bUvxjG5B31I8ZEvJXj0mfIdS0RnZEKyHDYLJmVoU2TFyy7+inOjVoMaJhj2JM0QFN+u5SOb9a/Asm15xjE0PKsrtW8dw7ysw7h2faevsejFnOqPFFOjF/PbnOLGnLsTmlCJW+TlKbX4zLaJgFDJ03Whxe65fyOsRx+ZqmbGUQx+Fwwo2FT1m0Cz1RCfZVvX4R59rZqk2Nu/nuteMi536fIgxBzq14jB74HPdNloMfXslzie6hZZ7zZjI1FKhmVrotJHooWE3X0LWWskZTjpM4cOg0sBn7+haSGsHugm35cnz
*/